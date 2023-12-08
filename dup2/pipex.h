#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
char    **ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
#endif