#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_STR_LEN 4096

int main(void) {
    //
    char *path = "C:\\Users\\Florin\\Desktop\\lab03\\test_encrypt\\olly.txt";
    FILE *fp = fopen(path,"rb");

    char buffer[MAX_STR_LEN];
    char *pathDecrypted = "C:\\test_encrypt\\test_decrypted.txt";
    FILE *fpDecrypted = fopen(pathDecrypted,"wb");
    unsigned long long bytesRead = fread(buffer, 1, MAX_STR_LEN, fp);
    while (bytesRead){
        for (int i = 0; i < strlen(buffer); ++i) {
            uint8_t caracter = buffer[i];
            caracter = ((caracter << 6) | (caracter >> 2));
            if ((caracter >= 0x30) && (caracter <= 0x39)){
                caracter = 0x69 - caracter;
            }
            if ((caracter >= 0x5B) && (caracter <= 0x60)){
                caracter = 0xBB - caracter ;
            }
            if ((caracter >= 0x41) && (caracter <= 0x7A)) {
                caracter = 0xBB - caracter;
            }
            buffer[i] = (char) caracter;
        }
        fwrite(buffer,1,bytesRead,fpDecrypted);
        bytesRead = fread(buffer, 1, MAX_STR_LEN, fp);
    }

    fclose(fp);
    fclose(fpDecrypted);
    return 0;
}

/*  char* string = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
    for (int i = 0; i < strlen(string); ++i) {
        uint8_t caracter = string[i];
        caracter = ((caracter << 2) | (caracter >> 6));
        printf("%X %X\n",string[i],caracter);
    }*/
