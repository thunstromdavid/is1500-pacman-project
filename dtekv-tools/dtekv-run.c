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
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

JTAGATLANTIC *atlantic;



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
void load_riscv_program(const char *name, char cmd) {
  FILE *fp = fopen(name, "rb");
  if (fp == NULL) {
    fprintf(stderr, "No such file: %s\n", name);
    jtagatlantic_close(atlantic);
    exit(0);
  }

  fseek(fp, 0, SEEK_END);
  long code_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  char *raw_code = (char *)malloc(sizeof(char) * (code_size + 1));
  assert(raw_code != NULL);
  fread(raw_code, code_size, 1, fp);
  fclose(fp);

  fprintf(stderr, "Loaded binary '%s' with size %ld bytes.\n", name, code_size);

  fprintf(stderr, "Loading binary to FPGA-device: \n");
  MM_upload(0x00000000, raw_code, code_size);
  fprintf(stderr, "Complete!\n");
  MM_upload(0x04000000, &cmd, 1);

  free(raw_code);
}

void usage() {
  fprintf(stderr, "Usage: ./dtekv-run test.bin [OPTION]...\n\n"
                  "Mandatory arguments:\n"
                  "  ./dtekv-run test.bin            "
                  "Specify binary file to upload (e.g. test.bin)\n\n"
                  "Optional arguments:\n"
                  "  --config 0xf0                   "
                  "Specify configuration code (e.g., 0xf0)\n"
                  "  --cable \"USB-Blaster [3-2]\"   "
                  "Specify cable type (e.g., \"USB-Blaster [3-2]\")\n");
}

/* Description: Our favorite entry point. */
int main(int argc, char *argv[]) {
  bool attempt_reboot = false;
  char *binary_file_name = NULL;
  char *cable = NULL;
  char cmd = 0xf0;

  // parse arguments
  for (int counter = 1; counter < argc; counter++) {
    if (strncmp(argv[counter], "--", 2) == 0) {
      if (argc == counter + 1) {
        fprintf(stderr, "Please provide additional arguments.\n");
        usage();
        return 1;
      } else {
        if (strcmp(argv[counter], "--config") == 0) {
          counter++;
          cmd = strtol(argv[counter], NULL, 16);
        } else if (strcmp(argv[counter], "--cable") == 0) {
          counter++;
          cable = argv[counter];
        }
        // Add more arguments here
      }
    } else {
      binary_file_name = argv[counter];
    }
  }
  if (binary_file_name == NULL) {
    fprintf(stderr, "Please provide a binary file to upload.\n");
    usage();
    return 1;
  }

_main:;
  /* Open the JTAG for communication */
  atlantic = jtagatlantic_open(cable, -1, -1, "main");
  if (!atlantic) {
    const char *err = show_err();

    if (attempt_reboot == false && err != NULL &&
        strcmp(err, "Cable not available") == 0) {
      fprintf(stderr, "Attempting to reboot jtagd...\n");
      system("killall jtagd > /dev/null");
      system("jtagd --user-start > /dev/null");
      attempt_reboot = true;
      goto _main;
    } else {
      return 1;
    }
  }
  show_info(atlantic);
  jtagatlantic_flush(atlantic);
  fprintf(stderr, "Unplug the cable or press ^C to stop.\n");

  /* Load the program binary */
  load_riscv_program(binary_file_name, cmd);
  fprintf(stderr, "--> Starting console.\n");
  while (1) {
    int left = jtagatlantic_bytes_available(atlantic);
    if (left != 0) {
      char c;
      int ret = jtagatlantic_read(atlantic, &c, 1);
      fprintf(stderr, "%c", c);
    }
  }
  jtagatlantic_close(atlantic);
  return 0;
}
