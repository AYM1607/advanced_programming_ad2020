#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int main() {
  struct Agent *head = NULL;
  char option = 0;
  char *buffer = (char *)malloc(32 * sizeof(char));

  printf("Welcome to the missions system!\n");

  while (option != 'q') {
    printf("Please type one of the following options and press enter: \n"
           "a) Print the agents in the system.\n"
           "b) Add a new agent.\n"
           "c) Add assets to an agent.\n"
           "d) Dump current structure to encrypted file.\n"
           "e) Load from encrypted.\n"
           "q) Exit.\n");
    option = getchar();
    // Flush the extra enter.
    getchar();

    switch (option) {
    case 'a':
      printAgents(head);
      break;
    case 'b':
      if (head == NULL) {
        head = readAgent();
      } else {
        addAgentToList(head, readAgent());
      }
      printf("Done!\n");
      break;
    case 'c':
      printf("Please type the position of the agent and press enter.\n");
      readString(buffer, 32);
      enum ReturnCode code = addAssetsToAgent(head, atoi(buffer));
      if (code == NULL_LIST) {
        printf("\nOops, no agents in the system yet.\n\n");
      } else if (code == OUT_OF_BOUNDS) {
        printf("\nOops, make sure the provided position is valid.\n\n");
      }
      break;
    case 'd':
      printf("Dumping info to file...\n\n");
      dumpEncryptedFile(head);
      printf("content dumped\n\n");
      break;
    case 'e':
      if (head == NULL) {
        head = loadEncryptedFile();
      } else {
        addAgentToList(head, loadEncryptedFile());
      }
      printf("Done loading!\n");
      break;
    case 'q':
      // Do nothing.
      break;
    default:
      printf("Opps, not a valid option!\n");
    }
  }
  // TODO: release memory.
  free(buffer);
  return 0;
}
