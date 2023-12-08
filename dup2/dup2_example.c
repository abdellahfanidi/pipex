
#include "pipex.h"
// int main()
// {
//      printf("1\n");
//     int fd = open("file.txt",O_WRONLY);
    
//     // creation d'un fils:
//     int pid  = fork();
//     if (pid == 0)
//     {
//         // duplicate file descripteur 
//         printf("2");
//         fflush(stdout);
//         dup2(fd,STDOUT_FILENO);
//         printf("3");
//         //execl("./usethis","usethis",NULL);
//     }
//     // wait fils
//     wait(NULL);
//     printf("4\n");
//     close(fd);
// }


//duplicate : STDIN_FILENO
// int main()
// {
//     int saved_stdin = dup(0);
//     int fd = open("file.txt", O_RDWR);

//     int num;
//     printf("welcome in this programme : \n");

//     dup2(fd, 0);
//     scanf("%d",&num);
//     printf("ok value in file = %d;\n" ,num);
//     dup2(saved_stdin,0);
//     scanf("%d",&num);
//     printf("this value from user = %d;\n" ,num);
// }


// duplicate : STDOUT_FILENO
// int main()
// {
//     int saved_stdout = dup(1);
//     int fd = open("file.txt", O_RDWR);
//     printf("welcome in this programme :\n");
//     dup2(fd, 1);
//     printf("ok -> file\n");

//     dup2(saved_stdout,1);
//     printf("ok -> terminal\n");
// }

// execution cmd and redirection to file using execve ; system call loads a new programm into a process's memory
//execve(pathname, argv, envp)
// pathname :  of cmmd to execute
//argv  : the arguments to pass to the new programm
//envp : the environment list 


// int main(int ac, char **av)
// {
//         char *path = getenv("PATH");
//     char cmd[]= "/bin/ls";
//     if (ac < 2) return(-1);
//     //char *argv[] = {"ls","-l",NULL};
//     char **argv = ft_split(av[1],' ');
//     if (execve(cmd,argv,NULL) == -1)
//         perror("could not execute  execve");
//     printf("Oops, something went wrong!");

//     printf("\n %s",path);
// }




//function access : check if cmd_path is executable access(cmd_path , mode)
// int main()
// {
//     char cmd_path[] = "/bin/ls";
//     char *argv[] = {"ls","-l",NULL};
//     if (access(cmd_path, X_OK)!= -1)
//     {
//         execve(cmd_path,argv,NULL);
//     }

//     printf("error");
// }




//argument av[1] = "ls -l" > split and get "ls" > search what is cmd_path 
int main(int ac, char **av)
{
    char    *PATH[]={"/usr/local/bin", "/usr/bin", "/bin", "/usr/sbin", "/sbin",NULL};
    char    **CMD_TOTAL = ft_split(av[1], ' ');
    char *CMD_PATH;
    if (CMD_TOTAL == NULL || CMD_TOTAL[0] == NULL) {
        printf("No arguments provided.\n");
        return 1;
    }

    int i,found;
    i = 0;
    found = 0;
    while (PATH[i] != NULL)
    {
        CMD_PATH = ft_strjoin(PATH[i],CMD_TOTAL[0]);
        if (access(CMD_PATH, X_OK)!= -1)
        {
            found = 1;
            break;
        }
        free(CMD_PATH);
        CMD_PATH = NULL;
        i++;
    }

    if (found)
        printf("->  find  :  %s , for cmd : %s",CMD_PATH,CMD_TOTAL[0]);


    //free
    free(CMD_PATH);
        CMD_PATH = NULL;
        system("leaks");
}