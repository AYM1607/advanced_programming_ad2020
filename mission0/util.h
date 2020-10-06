#include "Agent.h"
#include "stdio.h"

enum ReturnCode { SUCCESS, NULL_LIST, OUT_OF_BOUNDS, COULD_NOT_OPEN_FILE };

void readString(char *buffer, unsigned int buffSize);
struct Agent *readAgent();
void printAgents(struct Agent *agentsList);
enum ReturnCode addAgentToList(struct Agent *agentsList,
                               struct Agent *newAgent);
enum ReturnCode addAssetsToAgent(struct Agent *agentsList, int position);
enum ReturnCode dumpEncryptedFile(struct Agent *agentList);
struct Agent *loadEncryptedFile();
