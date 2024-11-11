#include "s21_grep.h"

int main(int argc, char *argv[]) {
  struct flags flags = {0};
  char pattern[BUFFER] = {0};
  parser(argc, argv, &flags, pattern);
  if (argc >= 3) grep(&flags, argc, argv, pattern);
  return 0;
}

void parser(int argc, char **argv, struct flags *flags, char *pattern) {
  int currentFlag = 0;
  const char *s_options = "e:ivclnhs";
  while ((currentFlag = getopt_long(argc, argv, s_options, NULL, NULL)) != -1) {
    switch (currentFlag) {
      case 'e':
        flags->e = 1;
        snprintf(pattern, BUFFER, "%s|", optarg);
        break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'h':
        flags->h = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      default:
        fprintf(stderr, "Usage grep \"-eivclnhs\" flags\n");
        break;
    }
  }
  if (flags->e)
    pattern[strlen(pattern) - 1] = '\0'; /* флаг е */
  else if (argc > optind)
    snprintf(pattern, BUFFER, "%s", argv[optind++]);
}

void processing(struct flags *flags, FILE *fp, regex_t reg, char *file,
                int countFiles) {
  char text[BUFFER] = {0};
  regmatch_t pmatch[1];
  int line_matches = 0, nline = 1;
  while (fgets(text, BUFFER - 1, fp) != NULL) {
    int match = 0;
    int success = regexec(&reg, text, 1, pmatch, 0);  //

    if (strchr(text, '\n') == NULL) strcat(text, "\n");
    if (success == 0 && !flags->v) match = 1; /* флаг v */
    if (success == REG_NOMATCH && flags->v) match = 1;
    if (match && !flags->l && !flags->c) { /* флаг l */
      if (countFiles > 1 && !flags->h) printf("%s:", file);
      if (flags->n) { /* флаг n */
        printf("%d:", nline);
      }
      printf("%s", text);
    }
    line_matches += match;
    nline++;
  }
  if (flags->l && line_matches > 0) printf("%s\n", file);
  if (flags->c && !flags->l) { /*флаг c */
    if (countFiles > 1 && !flags->h) printf("%s:", file);
    printf("%d\n", line_matches);
  }
}

void grepFile(struct flags *flags, char *pattern, char *filename,
              int countFiles) {
  int cflags = REG_EXTENDED;
  regex_t reg;
  FILE *file;
  file = fopen(filename, "r");
  if (flags->i) cflags |= REG_ICASE; /* флаг i */
  if (file != NULL) {
    regcomp(&reg, pattern, cflags);
    processing(flags, file, reg, filename, countFiles);
    regfree(&reg);
    fclose(file);
  } else {
    if (!flags->s) { /* обработка флага s */
      fprintf(stderr, "grep: %s: No such file or directory\n", filename);
    }
  }
}

void grep(struct flags *flags, int argc, char **argv, char *pattern) {
  int countFiles = 0;
  if (flags->e) {
    for (int i = 0; optind + i < argc; i++, countFiles++)
      ;
  } else {
    char **patternTemp = &argv[optind];
    for (int i = 1; optind + i < argc + 1; i++, patternTemp++) {
      if (patternTemp[0][0] != '-') countFiles++;
    }
  }
  for (int i = optind; i < argc; i++) {
    grepFile(flags, pattern, argv[i], countFiles);
  }
}