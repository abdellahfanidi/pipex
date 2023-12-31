#include "pipex_bonus.h"

static void	path_lines(char *path[])
{
	path[0] = "/usr/local/bin/";
	path[1] = "/usr/bin/";
	path[2] = "/bin/";
	path[3] = "/usr/sbin/";
	path[4] = "/sbin/";
	path[5] = NULL;
}

char	*get_path_cmd(char **cmd_total)
{
	char	*path[6];
	char	*cmd;
	int		i;

	i = 0;
	path_lines(path);
	cmd = NULL;
	while (path[i] != NULL && cmd_total[0])
	{
		cmd = ft_strjoin(path[i++], cmd_total[0]);
		if (access(cmd, X_OK) != -1)
			return (cmd);
		free(cmd);
		cmd = NULL;
	}
	return (cmd);
}



char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = 0;
	return (str);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;
	int		size;

	size = ft_strlen(src);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}