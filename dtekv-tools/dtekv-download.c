/****************************************************************
 Author: Artur Podobas
 Description: This is the source code for uploading data and code
              to the DTEK-V Board.
 WARNING: Feel free to study this code if you want to know how to
          upload and boot the DTEK-V Processor.
          However, DO NOT modify the content of this file, as it
          will most likely result in failure.
 ****************************************************************/

#include "atlantic.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

JTAGATLANTIC *atlantic;

/* Defines the size of the JTAG FIFO buffer */
#define JTAG_WRITE_BUF_LEN 8192


/* Drains the JTAG-Uart of existing data */
void drain_uart ( void )
{
  int left = jtagatlantic_bytes_available(atlantic);
  char buf[left];
  int ret = jtagatlantic_read(atlantic, buf, left);
  return;
}

/* This is called to download data from the DTEK-V board at address adr and len bytes. 
   Stores downloaded data at val */
void MM_download(unsigned adr, char *val, unsigned int len) {
  char data[9];
  data[0] = 0x0;
  data[1] = (adr & 0xff);
  data[2] = (adr >> 8) & 0xff;
  data[3] = (adr >> 16) & 0xff;
  data[4] = ((adr >> 24) & 0xff);
  data[5] = (len & 0xff);
  data[6] = (len >> 8) & 0xff;
  data[7] = (len >> 16) & 0xff;
  data[8] = ((len >> 24) & 0xff);
  int ret = jtagatlantic_write(atlantic, data, sizeof(data));
  assert(ret == sizeof(data));
  jtagatlantic_flush(atlantic);

  while (len != 0) {
    int left = jtagatlantic_bytes_available(atlantic);
    if (left != 0) {
      ret = jtagatlantic_read(atlantic, val, left);
      val+=ret;
      len-=ret;
      jtagatlantic_flush(atlantic);
    }
  }

}

/* A simple min function */
unsigned min(unsigned x, unsigned y)
{
  if (x < y) return x;
  return y;
}

/* Description: Downloads data from memory to a file. */
void download_binary(const char *name, unsigned int base_adr,
                     unsigned int len) {
  FILE *fp = fopen(name, "wb");
  if (fp == NULL) {
    fprintf(stderr, "Could not create file: %s\n", name);
    jtagatlantic_close(atlantic);
    exit(0);
  }

  char *raw_data = (char *)malloc(sizeof(char) * (len + 1));
  char *back_data = raw_data;
  unsigned back_len = len;
  
  fprintf(stderr,
          "Downloading data to DTEK-V device from Address 0x%x (len=%d): \n",
          base_adr, len);

  while (len != 0)
    {
      unsigned xfer_len = min(JTAG_WRITE_BUF_LEN,len);
      MM_download(base_adr, raw_data, xfer_len);
      len-=xfer_len;
      base_adr+=xfer_len;
      raw_data+=xfer_len;
    }
  
  raw_data = back_data;
  len = back_len;
  fwrite(raw_data, len, 1, fp);
  fclose(fp);
  free(raw_data);
}


/* Description: Our favorite entry point. */
int main(int argc, char *argv[]) {
  bool attempt_reboot = false;
_main:;

  /* Open the JTAG for communication */
  atlantic = jtagatlantic_open(NULL, -1, -1, "main");
  if (!atlantic) {
    const char *err = show_err();

    if (attempt_reboot == false && err != NULL &&
        !strcmp(err, "Cable not available")) {
      fprintf(stderr, "Attempting to reboot jtagd...\n");
      system("killall jtagd > /dev/null");
      system("jtagd --user-start > /dev/null");
      attempt_reboot = true;
      goto _main;
    } else
      return 1;
  }
  show_info(atlantic);
  jtagatlantic_flush(atlantic);
  fprintf(stderr, "Unplug the cable or press ^C to stop.\n");

  /* Load the program binary */
  if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
    fprintf(stderr, "Invalid syntax! Usage: dtekv-download <filename to save to> "
                    "<address> <len to read in bytes>\n");
    jtagatlantic_close(atlantic);
    return 0;
  }

  unsigned int adr = strtol(argv[2], NULL, 16);
  unsigned int len = 0;

  if (argv[3][0] == '0' && argv[3][1] == 'x')
    len = strtol(argv[3], NULL, 16);
  else
    len = strtol(argv[3], NULL, 10);

  drain_uart();
  download_binary(argv[1], adr, len);

  jtagatlantic_close(atlantic);
  return 0;
}
