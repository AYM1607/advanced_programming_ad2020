struct AssetListNode {
  char *assetId;
  struct AssetListNode *next;
};

struct Agent {
  char *name;
  char *lastName;
  unsigned int age;
  char gender;
  struct AssetListNode *assignedAssets;
  char *mission;
};

