#ifndef SRC_S21_GREP_H_
#define SRC_S21_GREP_H_

#define BUFFER 4096

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
} flags;

void parser(int argc, char **argv, struct flags *flag, char *pattern);
void processing(struct flags *flag, FILE *fp, regex_t reg, char *file,
                int countFiles);
void grepFile(struct flags *flag, char *pattern, char *filename,
              int countFiles);
void grep(struct flags *flags, int argc, char **argv, char *pattern);

#endif