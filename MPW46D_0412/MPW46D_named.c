#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


int main(){

    int fd;
    pid_t p;

    if((mkfifo("MPW46D", S_IRUSR | S_IWUSR)) < 0)
    {
        printf("FIFO letrehozas sikertelen!\n");
        exit(1);
    }
    else{
    printf("FIFO sikeresen letrehozva!\n");
    }

    if((p = fork()) < 0){
        printf("Fork sikertelen!\n");
        exit(1);
    }


    if(p == 0){
        char *uzenet = "Gorog Krisztina Erzsebet";


        if((fd = open("MPW46D", O_WRONLY)) < 0){
            printf("Gyerek: FIFO megnyitasa sikertelen!\n");
            exit(1);


        } else {

            printf("Gyerek: FIFO irasra megnyitva, iras folyamatban\n");
            write(fd, uzenet, strlen(uzenet));

        }
    }


    if(p > 0){
        char buf[256];
        if((fd = open("MPW46D", O_RDONLY)) < 0 ){

            printf("Szulo: FIFO megnyitasa sikertelen!\n");
            exit(1);

        } else {

            printf("Szulo: FIFO olvasasra megnyitva, olvasas folyamatban\n");
            read(fd, buf, sizeof(buf));
            printf("Szulo: Kiolvasott adat: %s\n", buf);

        }
        if((unlink("MPW46D")) < 0 || (close(fd)) < 0){

            printf("Rendszer: FIFO torlese sikertelen!\n");

        } else {

            printf("FIFO sikeresen torolve\n\nKILEPES\n");
        }
}
    return 0;
}
