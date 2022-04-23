#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int main(){

    //letrehozzuk a fajlokat
    int fd1, fd2;

    if((mkfifo("bemeneti_file", S_IRUSR | S_IWUSR)) < 0)
    {
        printf("A bemeneti FIFO letrehozasa sikertelen!\n");
        exit(1);
    }
    else{
        printf("A bemeneti FIFO sikeresen letrehozva!\n");
    }

    if((mkfifo("kimeneti_file", S_IRUSR | S_IWUSR)) < 0)
    {
        printf("A kimeneti FIFO letrehozas sikertelen!\n");
        exit(1);
    }
    else{
    printf("A kimeneti FIFO sikeresen letrehozva!\n");
    }


    //kiolvassuk az adatokat a bemeneti fajlbol
    char input[100];
    if((fd1 = open("bemeneti_file", O_RDONLY)) < 0 ){

            printf("A bemeneti FIFO megnyitasa sikertelen!\n");
            exit(1);

        } else {

            printf("A bemeneti FIFO olvasasra megnyitva, olvasas folyamatban\n");
            read(fd1, &input, sizeof(input));
            printf("Kiolvasott adatok: \n%s\n", input);

        }


    if((unlink("bemeneti_file")) < 0 || (close(fd1)) < 0){

            printf("A bemeneti FIFO torlese sikertelen!\n");

    } else {
             printf("A bemeneti FIFO sikeresen torolve\n");
    }

    // eloszor az i-t nezzuk meg, attol fuggoen szedjuk szet a bemeneti adatokat a b c-re
    int i;
    char bemeneti_adatok[100];
    sscanf(input, "%d\n%[^\n]", &i, bemeneti_adatok);

    double a, b, c;
    if(i == 3){

        sscanf(bemeneti_adatok, "%lf %lf %lf", &a, &b, &c);
    }else if(i == 2){
        sscanf(bemeneti_adatok, "%lf %lf", &a, &b);
        c = 0;
    }else if(i == 1){
        sscanf(bemeneti_adatok, "%lf", &a);
        b = 0;
        c = 0;
    }else{
        printf("\nHiba! A bemeneti adatok szama ennyi nem lehet!\n");
        exit(1);
    }


    //kimeneti fajl megnyitasa, majd kiszamoljuk az eredmenyeket, beleirjuk a fajlba
    printf("A kimeneti fifo megnyitasa...\n");
    if((fd2 = open("kimeneti_file", O_WRONLY)) < 0){
                printf("A kimeneti FIFO megnyitasa sikertelen!\n");
                exit(1);
    } else {

            char solution[100];
            if((b*b-4*a*c)<0){
                snprintf(solution, 100, "\n%lf %lf %lf Az egyenletnek nincs valos gyoke!", a, b, c);
                printf("Az egyenletnek nincs valos gyoke!\n");
            }else{
                    double x, y;
                    if(i == 1){
                        x = 0;
                        y = 0;
                        //A vegeredmeny minden i=1 eseten 0, mert 0 negyzete mindig 0
                    }else{
                        x = (((-1)*b - sqrt(b*b-4*a*c))/(2*a));
                        y = (((-1)*b + sqrt(b*b-4*a*c))/(2*a));
                    }
                    snprintf(solution, 100, "\n%lf %lf %lf %lf %lf", a, b, c, x, y);
                    printf("A kapott ertekek: %lf %lf\n", x, y);
            }
                printf("A kimeneti FIFO irasra megnyitva, iras folyamatban\n");
                write(fd2, solution, sizeof(solution));
                printf("\nAz iras sikerult\n");

            }



    if((unlink("kimeneti_file")) < 0 || (close(fd1)) < 0){

            printf("A kimeneti FIFO torlese sikertelen!\n");

        } else {

            printf("A kimeneti FIFO sikeresen torolve\n\nKILEPES\n");
        }


    return 0;
}
