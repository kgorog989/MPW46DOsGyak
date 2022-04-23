#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main(){
    int fd1, fd2;
    int i;
    printf("Adja meg a bemeneti adatok db szamat!\n");
    scanf("%d", &i);

    printf("Adja meg a bemeneti adatokat!\n");

    char buf[50], input[100];
    scanf("\n%[^\n]", buf);
    snprintf(input, 100, "%d\n%s\n", i, buf);
    printf("\n%s", input);

    printf("\nBemeneti fifo megnyitasa...\n");
    if((fd1 = open("bemeneti_file", O_WRONLY)) < 0){
            printf("A bemeneti FIFO megnyitasa sikertelen!\n");
            exit(1);


        } else {

            printf("A bemeneti FIFO irasra megnyitva, iras folyamatban\n");
            write(fd1, &input, sizeof(input));

        }

    printf("\nAkimeneti fifo megnyitasa...\n");
    if((fd2 = open("kimeneti_file", O_RDONLY)) < 0 ){

            printf("A kimeneti FIFO megnyitasa sikertelen!\n");
            exit(1);

        } else {

            char solution[100];
            printf("A kimeneti FIFO olvasasra megnyitva, olvasas folyamatban\n");
            read(fd2, &solution, sizeof(solution));
            printf("A kiolvasott ertekek a b c x y formatumban:\n");
            printf("%s\n", solution);
        }
    return 0;
}
