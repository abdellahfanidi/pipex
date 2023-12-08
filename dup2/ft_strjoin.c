#include "pipex.h"
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
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	char	*temp;

	temp = s1;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (*s1)
		str[i++] = *(s1++);
	while (*s2)
		str[i++] = *(s2++);
	str[i] = 0;
	free(temp);
	temp = NULL;
	return (str);
}