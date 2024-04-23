#include <stdio.h>
#include <stdint.h>

#define BUFF_LEN 100

int main(void) {
    char *path = "C:\\test_encrypt\\not_enc.png";
    FILE *fp = fopen(path,"rb");

    char buffer[BUFF_LEN];
    char *pathDecrypted = "C:\\test_encrypt\\decriptat.png";
    FILE *fpDecrypted = fopen(pathDecrypted,"wb");

    unsigned long long bytesRead= fread(buffer, 1, 1, fp);

    while (bytesRead){

        //printf("%llu\n",bytesRead);
        for (int i = 0; i < bytesRead; ++i) {
            uint8_t caracter = buffer[i];
            caracter = caracter ^ 0x44;
            caracter = (caracter << 4) | (caracter >> 4);

            buffer[i] = (char)caracter;
        }
        fwrite(buffer,bytesRead,1,fpDecrypted);
        bytesRead= fread(buffer, 1, 1, fp);
    }

    fclose(fp);
    fclose(fpDecrypted);
    return 0;
}