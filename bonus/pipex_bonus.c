#include "pipex_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

void	execute_cmd(char *arg)
{
	char	**cmd_total;
	char	*path_cmd;

	cmd_total = ft_split(arg, ' ');
	path_cmd = get_path_cmd(cmd_total);
	if (path_cmd != NULL)
	{
		if (execve(path_cmd, cmd_total, NULL) == -1)
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



void	my_pipe(char *cmd)
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




int	main(int ac, char **av)
{
	int	fd_in;
	int	fd_out;
	int	i;

	i = 2;
	if (ac >= 5)
	{
		if (!ft_strcmp(av[1], "here_doc") && ft_strlen(av[1]) == 8)
		{
			if (ac != 6)
				bad_arguments(1);
			here_doc_execution(av);
		}
		fd_in = open(av[1], O_RDONLY);
		error_fd(fd_in, av[1], 0);
		fd_out = existence_last_file(av[ac - 1]);
		dup2(fd_in, 0);
		close(fd_in);
		while (i < ac - 2)
			my_pipe(av[i++]);
		dup2(fd_out, 1);
		close(fd_out);
		execute_cmd(av[ac - 2]);
	}
	else
		bad_arguments(2);
}