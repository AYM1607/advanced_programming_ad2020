#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util.h"

const unsigned int NamesBuffSize = 64;

/**
 * readString
 *
 * Reads a string and saves it to the provided buffer.
 */
void readString(char *buffer, unsigned int buffSize) {
  // Make sure the stdin buffer is clean.
  fflush(stdin);
  // Read until a valid string is read.
  while (fgets(buffer, buffSize, stdin) == NULL || (*buffer) == '\n') {
    printf("Please introduce a valid string and keep it under 64 characters\n");
    // Ignore extra input in the next run if the string was longer than
    // expected.
    fflush(stdin);
  }

  // Delete the trailing newline character left by fgets.
  buffer[strcspn(buffer, "\n")] = 0;
}

/**
 * readName
 *
 * Reads and validates an agents name from the command line.
 */
char *readName() {
  // Assume that the name will be 64 characters or smaller.
  char *buffer = (char *)malloc(NamesBuffSize * sizeof(char));

  printf("Write the agent's first name\n");

  readString(buffer, NamesBuffSize);

  return buffer;
}

/**
 * readLastName
 *
 * Reads and validates an agents last name from the commmand line
 */
char *readLastName() {
  // Assume that the last name will be 64 characters or smaller.
  char *buffer = (char *)malloc(NamesBuffSize * sizeof(char));

  printf("Write the agent's last name\n");

  readString(buffer, NamesBuffSize);

  return buffer;
}

/**
 * readAge
 *
 * Reads and validates the age of an agent.
 */
unsigned int readAge() {
  int age;
  printf("Enter the age of the agent and then press enter.\n");
  do {
    scanf("%u", &age);
    if (age <= 0) {
      printf("The age of the agent must be larger than 0\n");
    }
  } while (age <= 0);
  return age;
}

/**
 * readGender
 *
 * Reads and validates the gender of an agent.
 */
char readGender() {
  char gender = 0;

  printf("Enter the gender of the agent (valid options are M, F, m and f)\n");

  while (TRUE) {
    gender = getchar();
    if (gender == 'M' || gender == 'F') {
      break;
    } else if (gender == 'm' || gender == 'f') {
      gender -= 'a' - 'A';
      break;
    } else if (gender == '\n') {
      // Avoid printing the validation message twice.
      // Needed because terminals usually buffer the input until the enter
      // key is pressed.
      continue;
    } else {
      printf("Please enter a valid option.\n");
    }
  }

  return gender;
}

/**
 * validateId
 *
 * Validates a generic id composed by an arbitrary number of
 * alpha characters at the start followed by an arbitrary number
 * of digit characters.
 */
BOOL validateId(char *id, int alphaCount, int digitCount) {
  int i;
  BOOL isValid = TRUE;

  for (i = 0; i < alphaCount + digitCount + 1; i++) {
    if (i < alphaCount) {
      // The first `alphaCount` characters must be alpha.
      if (!isalpha(*(id + i))) {
        isValid = FALSE;
        break;
      }
    } else if (i < alphaCount + digitCount) {
      // The next characters until the `alphaCount + digitCount`
      // character must be digits.
      if (!isdigit(*(id + i))) {
        isValid = FALSE;
        break;
      }
    } else if (*(id + i) != '\0') {
      // Validate that the string is of the desired length.
      isValid = FALSE;
    }
  }

  return isValid;
}

/**
 * validateMissionId
 *
 * Validates tha the provided string starts with 3 alpha
 * characters followed by 9 digits and nothing else.
 * Prints a message if the string is invalid.
 */
BOOL validateMissionId(char *missionId) {
  BOOL isValid = validateId(missionId, 3, 9);

  if (!isValid) {
    printf("The mission id is not valid, try a new one.\n");
  }
  return isValid;
}

/**
 * validateAssetId
 *
 * Validates that the provided string starts with 4 alpha
 * characters followed by 9 digits and nothing else.
 * Prints a message if the string is invalid.
 */
BOOL validateAssetId(char *assetId) {
  BOOL isValid = validateId(assetId, 4, 9);

  if (!isValid) {
    printf("The asset id is not valid, try a new one.\n");
  }
  return isValid;
}

/**
 * readAsset
 *
 * Reads a single asset id and returns it in an AssetListNode.
 */
struct AssetListNode *readAsset() {
  struct AssetListNode *node =
      (struct AssetListNode *)malloc(sizeof(struct AssetListNode));
  node->next = NULL;

  // The id is 13 characters but we have to add the null character and newline
  // character that `fgets` also uses.
  char *buffer = (char *)malloc(15 * sizeof(char));

  printf("Enter an asset id with the format ABCD012345678\n");

  do {
    readString(buffer, 15);
  } while (!validateAssetId(buffer));

  node->assetId = buffer;

  return node;
}

/**
 * readAssets
 *
 * Reads and validates an arbitrary number of assets and
 * returns them in a linked list format.
 */
struct AssetListNode *readAssets() {
  BOOL isFirst = TRUE;
  struct AssetListNode *head = NULL;
  struct AssetListNode *current = NULL;

  do {
    struct AssetListNode *new = readAsset();
    if (isFirst) {
      head = new;
      current = new;
      isFirst = FALSE;
    } else {
      current->next = new;
      current = new;
    }
    printf("If you wish to add another asset press y and ENTER, otherswhise "
           "press any other key and then ENTER\n");
  } while (getchar() == 'y');

  // Make sure we don't leave any dangling input.
  fflush(stdin);

  return head;
}

/**
 * readMission
 *
 * Reads and validates a mission.
 */
char *readMission() {
  // The id is 12 characters but we have to add the null character and newline
  // character that `fgets` also uses.
  char *buffer = (char *)malloc(14 * sizeof(char));
  printf("Enter a mission id with the format ABC012345678\n");
  do {
    readString(buffer, 14);
  } while (!validateMissionId(buffer));

  return buffer;
}
