#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

char	*get_path_cmd(char **cmd_total);
//void	pipex(int fd1, int fd2, char **av);
int     existence_last_file(char *f);
void	execute_cmd(char *arg);

void	here_doc_execution(char **av);
void	parent_ps_doc(char **av, int *desc);
void    child_ps_doc(char **av,int *desc);

void	error_cmd(char *cmd);
void	error(void);
void    error_fd(int fd, char *file, int free);
void	bad_arguments(int a);


int 	ft_strcmp(char *s,char *s2);
void	ft_free(char **tab);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
#endif
