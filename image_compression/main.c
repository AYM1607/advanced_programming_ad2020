#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char BOOL;

#define TRUE 1
#define FALSE 0

// Used so the structure takes the right amount of bytes.
#pragma pack(push, 1)

struct FileHeader {
  uint16_t fileType;
  uint32_t fileSize;
  uint32_t reserved;
  uint32_t offset;
};

struct InfoHeader {
  uint32_t size;  // In pixels.
  int32_t width;  // In pixels.
  int32_t height; // In pixels, positive if bottom up, negative otherwise.

  uint16_t planes;
  uint16_t bitCount;
  uint32_t compression;
  uint32_t imageSize;
  int32_t xDensity;
  int32_t yDensity;
  uint32_t usedColors;
  uint32_t importantColors;
};

struct ColorHeader {
  uint32_t redMask;
  uint32_t greenMask;
  uint32_t blueMask;
  uint32_t alphaMask;
  uint32_t colorSpaceType;
  uint32_t unused[16];
};

#pragma pack(pop)

struct Image {
  struct FileHeader fileHeader;
  struct InfoHeader infoHeader;
  struct ColorHeader colorHeader;
  char *buffer;
};

unsigned int convertPixelToInt(const char *pixelBuffer,
                               unsigned char byteCount) {
  unsigned int result = 0;
  unsigned char i;
  for (i = 0; i < byteCount; i++) {
    result |= *(pixelBuffer + i) << (i * 8);
  }
  return result;
}

void writeImage(struct Image *image, unsigned long dataByteCount,
                const char *filename) {
  // Store the compreesed image:
  FILE *fpc = fopen(filename, "w");
  if (fpc == NULL) {
    printf("Could not save compressed image\n");
  }
  // Write the headers.
  fwrite(&(image->fileHeader), sizeof(struct FileHeader), 1, fpc);
  fwrite(&(image->infoHeader), sizeof(struct InfoHeader), 1, fpc);
  fwrite(&(image->colorHeader), sizeof(struct ColorHeader), 1, fpc);
  // Write the data.
  fwrite(image->buffer, dataByteCount, 1, fpc);
  fclose(fpc);
}

int readImageHeaders(struct Image *image, FILE *fp) {
  // Read the file header.
  fread(&(image->fileHeader), sizeof(struct FileHeader), 1, fp);

  if (image->fileHeader.fileType != 19778) {
    return -1;
  }

  // Read info header.
  fread(&(image->infoHeader), sizeof(struct InfoHeader), 1, fp);

  // Read the color table header.
  fread(&(image->colorHeader), sizeof(struct ColorHeader), 1, fp);
  return 0;
}

void compressImage(const char *fileName) {
  struct Image image;
  FILE *fp = fopen(fileName, "r");

  if (fp == NULL) {
    printf("Could not open image file\n");
    return;
  }

  if (readImageHeaders(&image, fp) != 0) {
    printf("There was an error with the image\n");
    return;
  }
  uint8_t pixelSize, pixelBytesSize, compressedBlockSize;

  pixelSize = image.infoHeader.bitCount;
  pixelBytesSize = pixelSize / 8;
  compressedBlockSize = pixelBytesSize + 4;

  printf("Before compression\nDimensions of the image: %d, %d\nTotal size (in "
         "bytes): %d\n",
         image.infoHeader.width, image.infoHeader.height,
         image.infoHeader.imageSize);

  // In the worst case scenario, RLE requires double the space of the original
  // image, so we'll allocate that.
  // The "amount", part of RLE will always use 32 bits.
  const uint32_t pixelCount = image.infoHeader.width * image.infoHeader.height;
  image.buffer = (char *)malloc(pixelCount * (pixelBytesSize + 4));

  // We'll set the compression flag in the header as 0xFF to
  // signal that we're using our custom compression.
  image.infoHeader.compression = 0xFF;

  // Compress the image and save it in the buffer.
  char *pixelBuffer = (char *)malloc(pixelBytesSize);
  uint32_t currentColorCount = 1;
  unsigned long previousValue, newValue, pixelIndex, bufferIndex = 0,
                                                     totalByteCount = 0;
  BOOL isFirst = TRUE;

  for (pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++) {
    // Read pixel.
    fread(pixelBuffer, pixelBytesSize, 1, fp);
    newValue = convertPixelToInt(pixelBuffer, pixelBytesSize);
    // Only try to compress if not the first pixel.
    if (isFirst) {
      previousValue = newValue;
      isFirst = FALSE;
      continue;
    }

    // Store the pixel if the color changed.
    if (newValue != previousValue) {
      memcpy(image.buffer + bufferIndex, pixelBuffer, pixelBytesSize);
      memcpy(image.buffer + bufferIndex + pixelBytesSize, &currentColorCount,
             4);
      currentColorCount = 1;
      bufferIndex += compressedBlockSize;
      totalByteCount += compressedBlockSize;
    } else {
      currentColorCount++;
    }
    previousValue = newValue;
  }
  printf("\nAfter compression\nTotal size (in bytes): %lu\n", totalByteCount);
  fclose(fp);

  writeImage(&image, totalByteCount, "./compressed.bin");
  printf("\nCompressed image was saved in \"compressed.bin\"\n");
  free(pixelBuffer);
  free(image.buffer);
}

void decompressImage() {
  struct Image image;
  FILE *fp = fopen("./compressed.bin", "r");
  if (fp == NULL) {
    printf("Could not open image file\n");
    return;
  }
  if (readImageHeaders(&image, fp) != 0) {
    printf("There was a problem with the image\n");
    return;
  }

  unsigned long pixelCount = image.infoHeader.width * image.infoHeader.height;
  unsigned long pixelBytesSize = image.infoHeader.bitCount / 8;
  unsigned long compressedBlockSize = pixelBytesSize + 4;
  unsigned long readPixels = 0, bufferIndex = 0;

  image.buffer = (char *)malloc(pixelCount * (pixelBytesSize + 4));

  uint32_t currentColorCount;
  char *pixelBuffer = (char *)malloc(pixelBytesSize);

  while (readPixels < pixelCount) {
    fread(pixelBuffer, pixelBytesSize, 1, fp);
    fread(&currentColorCount, 4, 1, fp);
    // printf("Found: %d pixels with color: %d\n", currentColorCount,
    //       convertPixelToInt(pixelBuffer, pixelBytesSize));
    int i = 0;
    for (; i < currentColorCount; i++, bufferIndex += pixelBytesSize) {
      memcpy(image.buffer + bufferIndex, pixelBuffer, pixelBytesSize);
    }
    readPixels += currentColorCount;
  }

  image.infoHeader.compression = 0;
  printf("Read: %lu pixels\n", readPixels);
  writeImage(&image, image.infoHeader.imageSize, "./decompressed.bmp");
  printf("\nDecompressed image was saved in \"decompressed.bmp\"\n");

  free(pixelBuffer);
  free(image.buffer);
}

int main(int argc, char *argv[]) {
  int i;
  char fileName[50];
  for (i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "-d")) {
      decompressImage();
      break;
    } else if (!strcmp(argv[i], "-c")) {
      strcpy(fileName, argv[i + 1]);
      compressImage(fileName);
      break;
    }
  }
  // char test[] = {0, 1, 0, 0};
  // printf("Test of the transform: %d\n", convertPixelToInt(test, 32));
  return 0;
}
