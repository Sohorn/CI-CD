#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Flags;

int parser(int argc, char *argv[], Flags *flag);
void read_file(char *argv[], FILE **f);
void process_flags(FILE *f, Flags *flag);

#endif