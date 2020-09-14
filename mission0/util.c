#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "util.h"

const int MaxBuffSize = 64;
const int AssetBuffSize = 15;
const int MissionBuffSize = 14;
const int AgeBuffSize = 10;
const int GenderBuffSize = 3;

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
    printf("Please introduce a valid string and keep\n");
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
  char *buffer = (char *)malloc(MaxBuffSize * sizeof(char));

  printf("Write the agent's first name\n");

  readString(buffer, MaxBuffSize);

  return buffer;
}

/**
 * readLastName
 *
 * Reads and validates an agents last name from the commmand line
 */
char *readLastName() {
  // Assume that the last name will be 64 characters or smaller.
  char *buffer = (char *)malloc(MaxBuffSize * sizeof(char));

  printf("Write the agent's last name\n");

  readString(buffer, MaxBuffSize);

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

/**
 * readAgent
 *
 * Prompts the user for all the information realted to an agent.
 * Stores it in an Agent struct and returns a pointer to it.
 */
struct Agent *readAgent() {
  struct Agent *newAgent = (struct Agent *)malloc(sizeof(struct Agent));

  newAgent->name = readName();
  newAgent->lastName = readLastName();
  newAgent->age = readAge();
  newAgent->gender = readGender();
  newAgent->mission = readMission();
  newAgent->assignedAssets = readAssets();

  return newAgent;
}

/**
 * printAgent
 *
 * Pretty prints the provided agent on the console.
 */
void printAgent(struct Agent *agent) {
  printf("Agent's name is: %s %s\n", agent->name, agent->lastName);
  printf("Age: %d, Gender: %c\n", agent->age, agent->gender);
  printf("Mission: %s\n", agent->mission);
  printf("Assets: ");

  // Deal with the assets.
  BOOL isFirst = TRUE;
  struct AssetListNode *currentAsset = agent->assignedAssets;
  while (currentAsset != NULL) {
    if (isFirst) {
      isFirst = FALSE;
    } else {
      printf(", ");
    }
    printf("%s", currentAsset->assetId);
    currentAsset = currentAsset->next;
  }
  printf("\n");
}

/**
 * printAgents
 * Pretty prints all the agents in the provided list.
 */
void printAgents(struct Agent *agentsList) {
  if (agentsList == NULL) {
    printf("\nOops, no agents in the system yet\n\n");
    return;
  }

  struct Agent *currentAgent = agentsList;
  int agentPosition = 0;

  while (currentAgent != NULL) {
    printf("---------------------------------- Position %d\n", agentPosition);
    printAgent(currentAgent);
    currentAgent = currentAgent->next;
    agentPosition++;
  }
  printf("----------------------------------------------\n");
}

/**
 * addAgentToList
 *
 * Adds the provided agent at the end of the provided lsit.
 */
enum ReturnCode addAgentToList(struct Agent *head, struct Agent *newAgent) {
  // Error case.
  if (head == NULL) {
    return NULL_LIST;
  }

  struct Agent *currentAgent = head;

  while (currentAgent->next != NULL) {
    currentAgent = currentAgent->next;
  }

  currentAgent->next = newAgent;

  return SUCCESS;
}

/**
 * addAssetsToAgent
 *
 * Adds assets to the agent in the provided
 * position in the list.
 */
enum ReturnCode addAssetsToAgent(struct Agent *agentsList, int position) {
  if (agentsList == NULL) {
    return NULL_LIST;
  } else if (position < 0) {
    return OUT_OF_BOUNDS;
  }

  int currentPosition = 0;
  struct Agent *currentAgent = agentsList;

  while (position != currentPosition) {
    currentPosition++;
    if (currentAgent == NULL) {
      return OUT_OF_BOUNDS;
    }
    currentAgent = currentAgent->next;
  }

  struct AssetListNode *newAssets = readAssets();
  struct AssetListNode *currentAsset = currentAgent->assignedAssets;

  while (currentAsset->next != NULL) {
    currentAsset = currentAsset->next;
  }

  currentAsset->next = newAssets;

  return SUCCESS;
}

void crypt(char *string, BOOL encrypt) {
  // Asumes that the string will be a maximum of "MaxBuffSize" in lenght.
  const unsigned char cipherNumber = 12;
  int i = 0;

  for (; i < MaxBuffSize && string[i] != '\0'; i++) {

    string[i] += encrypt ? cipherNumber : -cipherNumber;
  }
}

void dumpEncryptedAgent(FILE *fp, struct Agent *agent) {
  char *buffer = (char *)malloc(MaxBuffSize * sizeof(char));

  // Dump first name.
  strcpy(buffer, agent->name);
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);
  // Dump last name.
  strcpy(buffer, agent->lastName);
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);
  // Dump age.
  sprintf(buffer, "%d", agent->age);
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);
  // Dump gender.
  sprintf(buffer, "%c", agent->gender);
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);
  // Dump mission.
  strcpy(buffer, agent->mission);
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);

  // Dump assets.
  struct AssetListNode *currentAsset = agent->assignedAssets;
  while (currentAsset != NULL) {
    strcpy(buffer, currentAsset->assetId);
    crypt(buffer, TRUE);
    fprintf(fp, "%s\n", buffer);
    currentAsset = currentAsset->next;
  }
  free(buffer);
}

/**
 * dumpEncryptedFile
 *
 * dumps all the current information into an encrypted file
 */
enum ReturnCode dumpEncryptedFile(struct Agent *agentsList) {
  char buffer[32];

  if (agentsList == NULL) {
    printf("\nOops, no agents in the system yet\n\n");
    return NULL_LIST;
  }

  FILE *fp = fopen("./EncryptedData.txt", "w");
  if (fp == NULL) {
    return COULD_NOT_OPEN_FILE;
  }

  struct Agent *currentAgent = agentsList;
  int agentPosition = 0;

  while (currentAgent != NULL) {
    dumpEncryptedAgent(fp, currentAgent);
    currentAgent = currentAgent->next;
    if (currentAgent != NULL) {
      strcpy(buffer, "AgentEnd");
      crypt(buffer, TRUE);
      fprintf(fp, "%s\n", buffer);
    }
    agentPosition++;
  }
  strcpy(buffer, "FileEnd");
  crypt(buffer, TRUE);
  fprintf(fp, "%s\n", buffer);

  fclose(fp);

  return SUCCESS;
}

/**
 * readFileLine
 *
 * Reads a single line from the provided file pointer and stores it in
 * buffer.
 * Return TRUE if the line was read successfully and FALSE otherwhise.
 */
BOOL readFileLine(char *buffer, unsigned int buffSize, FILE *stream) {
  // Make sure the stdin buffer is clean.
  fflush(stream);

  if (fgets(buffer, buffSize, stream) == NULL) {
    return FALSE;
  }

  // Delete the trailing newline character left by fgets.
  buffer[strcspn(buffer, "\n")] = 0;

  return TRUE;
}
/**
 * loadEncryptedFile
 *
 * Returns a pointer to a linked list of the agents read from the file.
 * Returns NULL if th file doesn't exist.
 */
struct Agent *loadEncryptedFile() {
  FILE *fp = fopen("./EncryptedData.txt", "r");
  if (fp == NULL) {
    return NULL;
  }

  BOOL done = FALSE;
  struct Agent *head = NULL;
  struct Agent *current = NULL;

  while (done == FALSE) {
    struct Agent *newAgent = (struct Agent *)malloc(sizeof(struct Agent));
    // Name
    char *nameBuff = (char *)malloc(MaxBuffSize * sizeof(char));
    readFileLine(nameBuff, MaxBuffSize, fp);
    crypt(nameBuff, FALSE);
    newAgent->name = nameBuff;
    // Last name
    char *lastNameBuff = (char *)malloc(MaxBuffSize * sizeof(char));
    readFileLine(lastNameBuff, MaxBuffSize, fp);
    crypt(lastNameBuff, FALSE);
    newAgent->lastName = lastNameBuff;
    // Age
    char *ageBuff = (char *)malloc(AgeBuffSize * sizeof(char));
    readFileLine(ageBuff, AgeBuffSize, fp);
    crypt(ageBuff, FALSE);
    newAgent->age = atoi(ageBuff);
    // Gender
    char *genderBuff = (char *)malloc(GenderBuffSize * sizeof(char));
    readFileLine(genderBuff, GenderBuffSize, fp);
    crypt(genderBuff, FALSE);
    newAgent->gender = genderBuff[0];
    // Misison
    char *missionBuff = (char *)malloc(MissionBuffSize * sizeof(char));
    readFileLine(missionBuff, MissionBuffSize, fp);
    crypt(missionBuff, FALSE);
    newAgent->mission = missionBuff;
    // Assets
    struct AssetListNode *assetsHead = NULL;
    struct AssetListNode *currentAsset = NULL;
    while (TRUE) {
      struct AssetListNode *newAsset =
          (struct AssetListNode *)malloc(sizeof(struct AssetListNode));

      char *assetBuff = (char *)malloc(AssetBuffSize * sizeof(char));
      readFileLine(assetBuff, AssetBuffSize, fp);
      crypt(assetBuff, FALSE);

      if (strcmp(assetBuff, "AgentEnd") == 0) {
        break;
      } else if (strcmp(assetBuff, "FileEnd") == 0) {
        done = TRUE;
        break;
      }

      newAsset->assetId = assetBuff;
      newAsset->next = NULL;

      if (assetsHead == NULL) {
        assetsHead = newAsset;
        currentAsset = newAsset;
      } else {
        currentAsset->next = newAsset;
        currentAsset = newAsset;
      }
    }
    newAgent->assignedAssets = assetsHead;

    if (head == NULL) {
      head = newAgent;
      current = newAgent;
    } else {
      current->next = newAgent;
      current = newAgent;
    }
  }
  return head;
}
