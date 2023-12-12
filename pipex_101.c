#include "pipex.h"
// free for split if path_cmd is not valid !!
// closing same fds
// opening file : if (fd == -1) error();
// failing execve :if (execve(path, cmd, envp) == -1) error();
// check for cmd is execte in main using access not in execution child or parent .

void    error_cmd(char *cmd)
{
    printf("\033[31mError: command not found : %s\e[0m\n",cmd);
    exit(1);
}
void	error(void)
{
	perror("\033[31mError\e[0m");
	exit(1);
}

void execute_cmd(char *arg)
{
    char    **cmd_total;
    char    *path_cmd;
    cmd_total = ft_split(arg,' ');
     path_cmd = get_path_cmd(cmd_total);
    if (path_cmd != NULL)
        execve(path_cmd,cmd_total,NULL);
    else
        error_cmd(cmd_total[0]);
}


void    child_ps(char **av,int *desc)
{
    int     fd1;

    fd1 = open(av[1],O_RDONLY);
    close(desc[0]);
    dup2(desc[1],1);
    close(desc[1]);
    dup2(fd1,0);
    close(fd1);
    execute_cmd(av[2]);
}

void    parent_ps(char **av,int *desc)
{
    /*
    char buff[10000];
    read(desc[0],buff,10000);
        printf("%s",buff);*/
    close(desc[1]);

    int     fd;
    fd = open(av[4],O_CREAT | O_WRONLY,0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }
    
    dup2(desc[0],0);
    close(desc[0]);

    dup2(fd,1);
    close(fd);
    
    execute_cmd(av[3]);
}



int main(int ac, char **av)
{
    int pid;
    int desc[2];
    if (ac == 5)
    {
        if (pipe(desc) == -1)
            error();
        pid = fork();
        if (pid < 0)
            error();
        if (pid == 0)
            child_ps(av,desc);
        
        wait(NULL);
        parent_ps(av,desc);
    }
    else
    {
        printf("\033[31mError: Bad arguments\e[0m\n");
		printf("Ex: ./pipex file1 cmd1 cmd2 file2\n");
    }
    system("leaks");
}
