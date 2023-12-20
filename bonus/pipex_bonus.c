#include "pipex_bonus.h"

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




// void    child_ps(char **av,int *desc)
// {
//     char buff[4096];
//     char *limiter;
//     int bytes;
//     int fd;

//     fd = open("temp",O_CREAT | O_RDWR ,0644);
//     if (fd < 0)
//     {
//     	perror("error create temp file");
// 	    exit(1);
//     }
//     limiter = ft_strjoin(av[2], "\n");
//     close(desc[0]);
//     while(1)
//     {
// 	ft_putstr_fd("heredoc> ",1);
//     	bytes = read(0, buff, sizeof(buff));
// 	buff[bytes] = '\0';
// 	if(bytes == -1)
// 	{
//  	    free(limiter);
// 	    perror("Error read from stdin");
//         exit(1);
// 	}
//     if (ft_strcmp(buff,limiter) == 0)
// 	{
// 		free(limiter);
// 		break;
// 	}
// 	write(fd,buff,bytes);
//     }
//     dup2(desc[1],1);
//     close(desc[1]);
//     dup2(fd,0);
//     close(fd);
//     execute_cmd(av[3]);
// }

void	do_pipe(char *cmd)
{
	pid_t	pid;
	int		desc[2];

	if (pipe(desc) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
	{
		close(desc[0]);
		dup2(desc[1], 1);
        execute_cmd(cmd);
	}
	else
	{
		close(desc[1]);
		dup2(desc[0], 0);
	}
}


void    parent_ps(char **av,int *desc, int i)
{
    int     fd;
    char    *file;

    close(desc[1]);
    if (av[i + 3])
    file = ft_strdup(av[i + 2]);
    unlink(av[i + 2]);
    fd = open(file,O_CREAT | O_WRONLY,0644);
    if (fd < 0) {
        perror(file);
        free(file);
        exit(1);
    }
    dup2(desc[0],0);
    close(desc[0]);
    dup2(fd,1);
    close(fd);
    execute_cmd(av[i + 1]);
}


int main(int ac, char **av)
{
    int fd_in,fd_out;
    int i = 2;

    if(ac >= 5)
    {
        fd_in = open(av[1],O_RDONLY);
        fd_out = open(av[ac - 2],O_CREAT | O_WRONLY,0644);
        // function gerer les error des fichiers !! open_file(char *file);
        dup2(fd_in, 0);
        close(fd_in);

        while (i < ac - 2)
        {

        }
        dup(fd_out, 1);
        close(fd_out);
        execute_cmd(av[ac - 2]);
    }
    else
    {
        ft_putstr_fd("\033[31mError: Bad arguments\e[0m\n",2);
		ft_putstr_fd("Ex: ./pipex here_doc LIMITER cmd1 cmd2 file2\n",2);
        ft_putstr_fd("or \nEx: ./pipex here_doc LIMITER cmd1 cmd2 file2\n",2);
    }

    // if (ac == 6  && !ft_strcmp(av[1], "here_doc") && ft_strlen(av[1]) == 8)
    // {
	// if (pipe(desc) == -1)
    //         error();
    //     pid = fork();
    //     if (pid < 0)
    //         error();
    //     if (pid == 0)
    //         child_ps(av,desc);
    //     else
    //     {  
    //         wait(NULL);
    //         parent_ps(av,desc);
    //     }
    // }
    // else
    // {
    //     ft_putstr_fd("\033[31mError: Bad arguments\e[0m\n",2);
	// 	ft_putstr_fd("Ex: ./pipex here_doc LIMITER cmd1 cmd2 file2\n",2);
    // }
}
