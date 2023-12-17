#include "pipex.h"
// free for split if path_cmd is not valid !!
// closing same fds
// opening file : if (fd == -1) error();
// failing execve :if (execve(path, cmd, envp) == -1) error();
// check for cmd is execte in main using access not in execution child or parent .



void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		        return ;
    write(fd, s, ft_strlen(s));
}


void execute_cmd(char *arg)
{
    char    **cmd_total;
    char    *path_cmd;
    cmd_total = ft_split(arg,' ');
     path_cmd = get_path_cmd(cmd_total);
    if (path_cmd != NULL)
    {
        if(execve(path_cmd,cmd_total,NULL) == -1)
        {
            ft_free(cmd_total);
            free(path_cmd);
            error();
        }
    }
    else
    {
        error_cmd(cmd_total[0]);
        ft_free(cmd_total);
    }
}


void    child_ps(char **av,int *desc)
{
    int     fd1;

    fd1 = open(av[1],O_RDONLY);
    if (fd1 < 0) {
        perror(av[1]);
        exit(1);
    }
    close(desc[0]);
    dup2(desc[1],1);
    close(desc[1]);
    dup2(fd1,0);
    close(fd1);
    execute_cmd(av[2]);
}

void    parent_ps(char **av,int *desc)
{
    int     fd;
    char    *file;

    close(desc[1]);
    file = ft_strdup(av[4]);
    unlink(av[4]);
    fd = open(file,O_CREAT | O_WRONLY,0644);
    if (fd < 0) {
        perror(file);
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
        else
        {  
            wait(NULL);
            parent_ps(av,desc);
        }
    }
    else
    {
        ft_putstr_fd("\033[31mError: Bad arguments\e[0m\n",2);
		ft_putstr_fd("Ex: ./pipex file1 cmd1 cmd2 file2\n",2);
    }
}
