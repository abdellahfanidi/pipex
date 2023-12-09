#include "pipex.h"

int main(int ac, char **av)
{
    // ac = 5
    char **cmd_total = ft_split(av[2],' ');
    char *path_cmd = get_path_cmd(cmd_total);
    if (path_cmd != NULL)
    {
          execve(path_cmd,addStringMatrix(cmd_total, av[1]),NULL); 
    }
    else
    {
            printf("command not found : %s\n",cmd_total[0]);
            return (0);
    }

}