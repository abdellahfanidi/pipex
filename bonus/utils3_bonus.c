#include "pipex_bonus.h"
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

int	existence_last_file(char *f)
{
	int fd_out;
	char *file;

	if (access(f, F_OK) != -1)
	{
		file = ft_strdup(f);
		unlink(f);
		fd_out = open(file, O_CREAT | O_WRONLY, 0644);
		error_fd(fd_out, file, 1);
	}
	else
		fd_out = open(f, O_CREAT | O_WRONLY, 0644);
	error_fd(fd_out, f, 0);
	return (fd_out);
}


void    child_ps_doc(char **av,int *desc)
{
    char buff[4096];
    char *limiter;
    int bytes;
    int fd;

    fd = open("temp",O_CREAT | O_RDWR ,0644);
    error_fd(fd,"temp",0);
    limiter = ft_strjoin(av[2], "\n");
    close(desc[0]);
    while(1)
    {
	ft_putstr_fd("piep heredoc> ",0);
    	bytes = read(0, buff, sizeof(buff));
	buff[bytes] = '\0';
	if(bytes == -1)
	{
 	    free(limiter);
	    perror("Error read from stdin");
        exit(1);
	}
    	if (ft_strcmp(buff,limiter) == 0)
	{
		free(limiter);
		break;
	}
	write(fd,buff,bytes);
    }
    dup2(fd, 0);
    close(fd);
    dup2(desc[1],1);
    close(desc[1]);
    execute_cmd(av[3]);
}

void    parent_ps_doc(char **av,int *desc)
{
    int     fd;

    unlink("temp");
    close(desc[1]);
    fd = open(av[5],O_CREAT | O_WRONLY | O_APPEND,0644);
    if (fd < 0) {
        perror(av[5]);
        exit(1);
    }
    char buff[1000];
	    read(desc[0],buff,sizeof(buff));
	    printf("->%s",buff);
    dup2(desc[0],0);
    close(desc[0]);
    dup2(fd,1);
    close(fd);
    execute_cmd(av[4]);
}


void	here_doc_execution(char **av)
{
	int desc[2];
	int pid;

	if (pipe(desc) == -1)
		error();
	pid = fork();
	if (pid == 0)
	{
		child_ps_doc(av,desc);
	}
	else
	{
		wait(NULL);
        parent_ps_doc(av,desc);
	}
	exit(1);
}





// void    child_ps_doc(char **av,int *desc)
// {
//     char buff[4096];
//     char *limiter;
//     int bytes;
//     int fd;

//     fd = open("temp",O_CREAT | O_RDWR ,0644);
//     if (fd < 0)
//     {
//     	perror("error create temp file");
// 			exit(1);
//     }
//     limiter = ft_strjoin(av[2], "\n");
//     close(desc[0]);
//     while(1)
//     {
// 	ft_putstr_fd("pipe heredoc> ",1);
//     	bytes = read(0, buff, sizeof(buff));
// 	buff[bytes] = '\0';
// 	if(bytes == -1)
// 	{
//  			free(limiter);
// 			perror("Error read from stdin");
//         exit(1);
// 	}
//     if (ft_strcmp(buff,limiter) == 0)
// 	{
// 		free(limiter);
// 		break ;
// 	}
// 	write(fd,buff,bytes);
//     }
//     dup2(desc[1],1);
//     close(desc[1]);
//     dup2(fd,0);
//     close(fd);
//     execute_cmd(av[3]);
// }

// void	parent_ps_doc(char **av, int *desc)
// {
// 	int		fd;

// 	close(desc[1]);
// 	fd = open(av[5], O_CREAT | O_WRONLY, 0644);
// 	error_fd(fd,av[5],0);
// 	dup2(desc[0], 0);
// 	close(desc[0]);
// 	dup2(fd, 1);
// 	close(fd);
// 	execute_cmd(av[4]);
// }
