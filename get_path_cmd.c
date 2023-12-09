/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afanidi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 14:12:35 by afanidi           #+#    #+#             */
/*   Updated: 2023/12/09 14:12:39 by afanidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void path_lines(char *path[])
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
	int 	i;

	i = 0;
	path_lines(path);
	cmd = NULL;
	while (path[i] != NULL && cmd_total[0])
	{
		cmd = ft_strjoin(path[i++],cmd_total[0]);
		if (access(cmd, X_OK)!= -1)
			return(cmd);
		free(cmd);
		cmd = NULL;
	}
	return (cmd);
}

char	**addStringMatrix(char **matrix, char *str)
{
	int		i;
	char	**new_p;

	i = 0;
	while(matrix[i] != NULL)
		i++;
	new_p = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while(matrix[i] != NULL)
	{
		new_p[i] = ft_strdup(matrix[i]);
		i++;
	}
	new_p[i++] = ft_strdup(str);
	new_p[i] = NULL;
	return (new_p);
}
