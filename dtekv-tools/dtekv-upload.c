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


/* Description: upload data from host memory to DTEK-V board memory at adress adr and len-bytes. */
void MM_upload(unsigned adr, char *val, unsigned int len) {
  char *data = (char *)malloc(len + 9);
  data[0] = 0x1; // Write command
  data[1] = (adr & 0xff);
  data[2] = (adr >> 8) & 0xff;
  data[3] = (adr >> 16) & 0xff;
  data[4] = ((adr >> 24) & 0xff);
  data[5] = (len & 0xff);
  data[6] = (len >> 8) & 0xff;
  data[7] = (len >> 16) & 0xff;
  data[8] = ((len >> 24) & 0xff);
  for (int i = 0; i < len; i++)
    data[9 + i] = val[i];

  int to_transfer = 9 + len;
  char *data_back = data;

again:; 
  int ret = jtagatlantic_write(atlantic, data, to_transfer);
  jtagatlantic_flush(atlantic);
  if (ret != to_transfer) {
    to_transfer -= ret;
    data += ret;
    goto again;
  }

  free(data_back);
}

/* Description: Uploads a RISC-V binary to the DTEK-V board. */
void upload_binary(const char *name, unsigned int base_adr) {
  FILE *fp = fopen(name, "rb");
  if (fp == NULL) {
    fprintf(stderr, "No such file: %s\n", name);
    jtagatlantic_close(atlantic);
    exit(0);
  }

  fseek(fp, 0, SEEK_END);
  long code_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *raw_data = (char *)malloc(sizeof(char) * (code_size + 1));
  assert(raw_data != NULL);
  fread(raw_data, code_size, 1, fp);
  fclose(fp);

  fprintf(stderr, "Uploading %ld-bytes data to DTEK-V device at address %x...", code_size, base_adr);
  MM_upload(base_adr, raw_data, code_size);

  fprintf(stderr, "Complete!\n");
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
  if (argv[1] == NULL || argv[2] == NULL) {
    fprintf(stderr, "Invalid syntax. Usage: ./dtekv-upload <file> <address>\n");
    jtagatlantic_close(atlantic);
    return 0;
  }

  unsigned int adr = strtol(argv[2], NULL, 16);
  upload_binary(argv[1], adr);

closedown:
  jtagatlantic_close(atlantic);
  return 0;
}
