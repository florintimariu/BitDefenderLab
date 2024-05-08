#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BUFF_LEN 4096

uint8_t cautaChar(char* cript,char c){
    for (uint8_t i = 0; i < 16; ++i) {
        if (cript[i] == c)
            return i;
    }
}

int main(void) {
    char *path = "C:\\test_encrypt\\_DSC4699.jpg";
    FILE *fp = fopen(path,"rb");

    char buffer[BUFF_LEN*2];
    char *pathDecrypted = "C:\\test_encrypt\\decriptat.jpg";
    FILE *fpDecrypted = fopen(pathDecrypted,"wb");

    char cript[] = "AkjsSHwiE27.[$+#";
    unsigned long long bytesRead= fread(buffer, 1, BUFF_LEN*2, fp);
    while (bytesRead){
        char bufferWrite[BUFF_LEN] = {"\0"};
        for (int i = 0; i < bytesRead/2; i++) {

            bufferWrite[i] = (char)((cautaChar(cript,buffer[i*2]) << 4) | cautaChar(cript,buffer[i*2+1]));
        }
        fwrite(bufferWrite,bytesRead/2,1,fpDecrypted);
        bytesRead= fread(buffer, 1, BUFF_LEN*2, fp);
    }

    fclose(fp);
    fclose(fpDecrypted);
    return 0;
}
