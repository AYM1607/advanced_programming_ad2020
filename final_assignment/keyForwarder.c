#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include </usr/local/include/ncftp.h>

#define CLOCKS_PER_MILLIS (CLOCKS_PER_SEC * 0.001)

struct ThreadParams {
  FILE *fileToTransfer;
  unsigned finishedFlag;
};

void delay(int millis) {
  int clocks = millis * CLOCKS_PER_MILLIS;
  clock_t tick = clock();
  while (clock() - tick < clocks)
    ;
}

void *transferFile(void *param) {
  struct ThreadParams *threadParams = (struct ThreadParams *)param;
  FTPLibraryInfo li;
  FTPConnectionInfo ci;

  FTPInitLibrary(&li);
  FTPInitConnectionInfo(&li, &ci, kDefaultFTPBufSize);

  strcpy(ci.user, "mariano");
  strcpy(ci.pass, "PASS");
  strcpy(ci.host, "192.168.0.9");

  if (FTPOpenHost(&ci) < 0) {
    printf("Could not open ftp connection");
    return NULL;
  }

  FTPPutOneFile(&ci, "./patch_instructions.txt", "./patch_instructions.txt");

  FTPCloseHost(&ci);
  threadParams->finishedFlag = 1;
  return NULL;
}

int main() {
  FILE *patchFile = fopen("./patch_instructions.txt", "r");

  if (patchFile == NULL) {
    printf("It looks like the patch file was deleted, aborting...\n");
    return 0;
  }

  printf("The patch file was created or updated, proceeding to send it through "
         "the network\n");

  // Send the file in a separate thread.
  struct ThreadParams threadParams = {patchFile, 0};
  pthread_t threadHandle;

  if (pthread_create(&threadHandle, NULL, transferFile, &threadParams)) {
    printf("Internal error, the file could not be sent.\n");
    return 1;
  }

  while (!threadParams.finishedFlag) {
    printf("Transmitting file...\n");
    delay(1000);
  }

  printf("Done transmitting file...\n");

  pthread_join(threadHandle, NULL);
  fclose(patchFile);
  return 0;
}
