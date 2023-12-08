#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main()
{
    int id;
    char buff_lire[50],buff_ecrire[50];
    int desc[1];
    int p = pipe(desc);
    int pid = fork();
    if (p == -1)
    {
        perror("Erreur lors de la création du tube");
        return (-1);
    }
    if (pid == 0)
    {
        id = 0;
        close(desc[1]);
        read(desc[0],buff_lire,50);
        printf("\n->j'ai recu une chaine : \"%s\"\n->pid de fils (pid_fils= %d)\n",buff_lire,getpid());
    }
    else{
        id = 1;
        close(desc[0]);
         sprintf(buff_ecrire,"hello world 2023");
        write(desc[1],buff_ecrire,50);
        printf("j'ai envoye une chaine :\"%s\"\n->pid de pere (pid_pere= %d)\n",buff_ecrire,getpid());
        wait(NULL);
    }
    printf("\n=> desc[%d] = %d",id, desc[id]);
}