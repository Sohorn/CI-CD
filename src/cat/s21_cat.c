#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Flags flag = {0};
  int err = parser(argc, argv, &flag);
  while (!err && optind < argc) {
    FILE *f = NULL;
    read_file(argv, &f);
    optind++;
    process_flags(f, &flag);
  }
  return 0;
}

int parser(int argc, char *argv[], Flags *flag) {
  int currentFlag;
  int err = 0;
  const char *flag_options = "+bevEnstT";
  struct option longOptions[] = {
      {"number-nonblank", 0, 0, 'b'},
      {"number", 0, 0, 'n'},
      {"squeeze-blank", 0, 0, 's'},
      {0, 0, 0, 0},
  };

  while ((currentFlag =
              getopt_long(argc, argv, flag_options, longOptions, NULL)) != -1) {
    switch (currentFlag) {
      case 'b':
        flag->b = 1;
        break;
      case 'e':
        flag->e = 1;
        flag->v = 1;
        break;
      case 'E':
        flag->e = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 't':
        flag->t = 1;
        flag->v = 1;
        break;
      case 'T':
        flag->t = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      default:
        printf("illegal option\n");
        err = 1;
        break;
    }
  }
  if ((*flag).b) (*flag).n = 0;
  return err;
}

void read_file(char *argv[], FILE **f) { /*чтение файла*/
  *f = fopen(argv[optind], "r");
  if (*f == NULL) {
    printf("Error: Unable to open file\n");
  }
}

void process_flags(FILE *f, Flags *flag) { /*обработка флагов*/
  if (f != NULL) {
    int c = 0;
    int row_count = 1;
    int empty_row_count = 0;
    int place = '\n';
    while ((c = fgetc(f)) != EOF) {
      if (flag->s && c == '\n' && place == '\n') {
        empty_row_count++;
        if (empty_row_count > 1) {
          continue;
        }
      } else {
        empty_row_count = 0;
      }
      if (place == '\n' && ((flag->b && c != '\n') || flag->n))
        printf("%6d\t", row_count++);

      if (flag->t && c == '\t') {
        printf("^");
        c = 'I';
      }
      if (flag->e && c == '\n') printf("$");

      if (flag->v) {
        if ((c >= 0 && c < 9) || (c > 10 && c < 32) || (c > 126 && c <= 160)) {
          printf("^");
          if (c > 126) {
            c -= 64;
          } else {
            c += 64;
          }
        }
      }
      printf("%c", c);
      place = c;
    }
    fclose(f);
  }
}
