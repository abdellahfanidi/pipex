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

void    error_cmd(char *cmd)
{
    ft_putstr_fd("\033[31mError: command not found : ",2);
    ft_putstr_fd(cmd,2);
    ft_putstr_fd("\e[0m\n",2);
}
void	error(void)
{
	perror("\033[31mError\e[0m");
	exit(1);
}