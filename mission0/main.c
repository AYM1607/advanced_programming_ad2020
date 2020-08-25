#include <stdio.h>

#include "util.h"

int main() {
  struct AssetListNode *assetList = readAssets();
  while (assetList != NULL) {
    printf("Found asset with id %s\n", assetList->assetId);
    assetList = assetList->next;
  }
  return 0;
}
