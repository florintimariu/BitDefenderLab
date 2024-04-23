#include <stdio.h>
#include <stdint.h>

#define BUFF_LEN 100

int main(void) {
    char *path = "C:\\test_encrypt\\Idei.docx";
    FILE *fp = fopen(path,"rb");

    char buffer[BUFF_LEN];
    char *pathDecrypted = "C:\\test_encrypt\\decriptat.docx";
    FILE *fpDecrypted = fopen(pathDecrypted,"wb");

    unsigned long long bytesRead= fread(buffer, 1, 1, fp);

    while (bytesRead){
        //printf("%llu\n",bytesRead);
        for (int i = 0; i < bytesRead; ++i) {
            uint8_t caracter = buffer[i];
            caracter = caracter ^ 0xC1;
            caracter += 0x4D;
            caracter = caracter ^ 0x8B;
            caracter -= 0x05;

            buffer[i] = (char)caracter;
        }

        fwrite(buffer,bytesRead,1,fpDecrypted);
        bytesRead= fread(buffer, 1, 1, fp);
    }

    fclose(fp);
    fclose(fpDecrypted);
    return 0;
}