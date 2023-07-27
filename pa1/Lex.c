#include "List.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  if (argc != 3) {
    fprintf(stderr, "Program Error: No infile/outfile specified.\n");
    exit(EXIT_FAILURE);
  }

  FILE *infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Could not open file: %s", argv[1]);
    return 0;
  }

  FILE *outfile = fopen(argv[2], "w");
  if (outfile == NULL) {
    printf("Could not open file: %s", argv[2]);
    return 0;
  }

  int count = 0;
  char c;
  for (c = getc(infile); c != EOF; c = getc(infile)) {
    if (c == '\n') {
      count++;
    }
  }
  rewind(infile);
  char *strArray[count];
  char *strArrayTemp[count];
  char buffer[100];

  for (int i = 0; i < count; i++) {
    fscanf(infile, "%s", buffer);
    strArray[i] = (char *)malloc(strlen(buffer) * sizeof(char));
    strArrayTemp[i] = (char *)malloc(strlen(buffer) * sizeof(char));
    // strArray[i] = (char *)malloc(sizeof(char));
    // strArrayTemp[i] = (char *)malloc(sizeof(char));

    strcpy(strArray[i], buffer);
    strcpy(strArrayTemp[i], buffer);
  }

  List L = newList();

  int space = 0;
  int countOriginal = count;
  while (count != 0) {
    for (int i = 0; i < count; i++) {
      if (strcmp(strArrayTemp[i], strArrayTemp[space]) < 0) {
        space = i;
      }
    }
    strcpy(buffer, strArrayTemp[space]);
    for (int i = space; i < (count - 1); i++) {
      strcpy(strArrayTemp[i], strArrayTemp[i + 1]);
    }
    strcpy(strArrayTemp[count - 1], buffer);

    for (int i = 0; i < countOriginal; i++) {
      if (strcmp(strArrayTemp[count - 1], strArray[i]) == 0) {
        space = i;
      }
    }
    append(L, space);

    count--;
    space = 0;
  }

  moveFront(L);
  for (int i = 0; i < length(L); i++) {
    fprintf(outfile, "%s\n", strArray[get(L)]);
    moveNext(L);
  }
  // printList(outfile, L);

  free(strArray);
  free(strArrayTemp);
  freeList(&L);
  fclose(infile);
  fclose(outfile);

  return 0;
}
