#include <stdio.h>
#include <unistd.h>

int main()
{
	int array[2];
	pid_t p;

	if(pipe(array) == -1){
		perror("Pipe Error\n");
		return 1;
	}
	p = fork();

	if(p > 0){
		char s[1024];
		close(array[1]);
		read(array[0], s, sizeof(s));
		printf("%s", s);

		close(array[0]);
	}else if(p == 0 ){
		close(array[0]);
		write(array[1],"\nGorog Krisztina Erzsebet, MPW46D\n",40);
		close(array[1]);
    }else{
          perror("Fork failed");
          return 1;
	}
    return 0;
}
