#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFF_LEN 4096

long int getFileSize(const char *filename) {
    FILE *file = fopen(filename, "rb"); // Open the file in binary mode

    if (file == NULL) {
        // Error handling: File not found or unable to open
        perror("Error opening file");
        return -1; // Return -1 to indicate an error
    }

    // Move the file pointer to the end of the file
    if (fseek(file, 0, SEEK_END) != 0) {
        // Error handling: Unable to move the file pointer
        perror("Error seeking file");
        fclose(file); // Close the file before returning
        return -1; // Return -1 to indicate an error
    }

    // Get the current position of the file pointer, which is the file size
    long int size = ftell(file);

    if (size == -1) {
        // Error handling: Unable to determine file size
        perror("Error getting file size");
        fclose(file); // Close the file before returning
        return -1; // Return -1 to indicate an error
    }

    fclose(file); // Close the file
    return size;
}

int main(void) {
    char *path = "C:\\test_encrypt\\ProiectSEF.pdf";
    FILE *fp = fopen(path,"rb");

    uint8_t buffer[BUFF_LEN];
    char *pathDecrypted = "C:\\test_encrypt\\decriptat.pdf";
    FILE *fpDecrypted = fopen(pathDecrypted,"wb");

    srand(getFileSize(path));
    uint8_t prev = 0;
    unsigned long long bytesRead= fread(buffer, 1, BUFF_LEN, fp);
    //buffer[1] = 0xFF;
    while (bytesRead){

        for (int i = 0; i < bytesRead; i++) {
            uint8_t caracter = buffer[i];
            uint8_t random = rand() & 0xFF;
            caracter = caracter - prev;
            caracter = caracter ^ random;

            prev = buffer[i];
            buffer[i] = (char)caracter;
        }

        fwrite(buffer,bytesRead,1,fpDecrypted);
        bytesRead= fread(buffer, 1, BUFF_LEN, fp);
    }

    fclose(fp);
    fclose(fpDecrypted);
    return 0;
}
