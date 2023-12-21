#include "pipex_bonus.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	error_cmd(char *cmd)
{
	ft_putstr_fd("\033[31mError: command not found : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\e[0m\n", 2);
}
void	error(void)
{
	perror("\033[31mError\e[0m");
	exit(1);
}

void	error_fd(int fd, char *file, int free_allocation)
{
	if (fd < 0)
	{
		perror(file);
		if (free_allocation)
			free(file);
		exit(1);
	}
}

void	bad_arguments(int a)
{
	ft_putstr_fd("\033[31mError: Bad arguments\e[0m\n", 2);
	if (a == 1)
		ft_putstr_fd("Ex: ./pipex here_doc LIMITER cmd1 cmd2 file2\n", 2);
	else
		ft_putstr_fd("Ex: ./pipex cmd1 cmd2 ... file2\n", 2);
	exit(1);
}