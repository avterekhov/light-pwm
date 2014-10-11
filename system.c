#include <stdio.h>
#include <glob.h>
#include <string.h>
#include "system.h"

int glob_path(const char* pattern, char* buffer) {
  glob_t globbuf;
  int status = 0;
  if (glob(pattern, 0, NULL, &globbuf)) {
    if (status & GLOB_ABORTED)
      printf("GLOB_ABORTED\n");
    if (status & GLOB_NOMATCH)
      printf("GLOB_NOMATCH\n");
    if (status & GLOB_NOSPACE)
      printf("GLOB_NOSPACE\n");
    return 0;
  }
  if (globbuf.gl_pathc == 1) {
    strcpy(buffer, globbuf.gl_pathv[0]);
    status = -1;
  }
  else {
    printf("Ambiguous input\n");
    status = 0;
  }
  globfree(&globbuf);
  return status;
}
