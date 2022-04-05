#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    char buf[100];
    int bufLenght;
    int fileDescriptor;
    int writeInfo;
    int seekInfo;
    int readInfo;

    fileDescriptor = open("MPW46D.txt", O_RDWR);
    if(fileDescriptor == -1){
        perror("open() hiba: ");
        exit(fileDescriptor);
    }

    printf("FileDescriptor erteke: %d\n", fileDescriptor);

    seekInfo = lseek(fileDescriptor, 0, SEEK_SET);
    if(seekInfo == -1){
        perror("A pozicionalas nem volt sikeres: ");
        exit(seekInfo);

    }
    printf("A read() erteke: %d\n", readInfo);
    printf("A beolvasott ertek: %s", buf);

    strcpy(buf, "Ez egy teszt");
    bufLenght = strlen(buf);
    writeInfo = write(fileDescriptor, buf, bufLenght);

    if(writeInfo == -1){
        perror("Az iras nem volt sikeres: ");
        exit(writeInfo);
    }
    printf("A write()-al beirt byte-ok szama: %d", writeInfo);

    return 0;
}
