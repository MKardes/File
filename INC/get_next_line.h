#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

size_t	gl_strlen(const char *s);
char	*gl_strchr(const char *s, int c);
char	*gl_strjoin(char *s1, char *s2);
char	*get_main_line(char *putline);
char	*get_putten(char *putline);
char	*get_read(int fd, char *putline);
char	*get_next_line(int fd);

char	*get_putten(char *putline)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
		i++;
	if (!putline[i])
	{
		free(putline);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (gl_strlen(putline) - i));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (putline[i + j] != '\0')
	{
		str[j] = putline[j + i];
		j++;
	}
	str[j] = '\0';
	free(putline);
	return (str);
}

char	*get_main_line(char *putline)
{
	int		i;
	char	*str;

	i = 0;
	if (!putline[i])
		return (NULL);
	while (putline[i] != '\0' && putline[i] != '\n')
		i++;
	str = (char *)malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (putline[i] != '\0' && putline[i] != '\n')
	{
		str[i] = putline[i];
		i++;
	}
	if (putline[i] == '\n')
	{
		str[i] = putline[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_read(int fd, char *putline)
{
	char	*buff;
	int		reader;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	reader = 1;
	while (!gl_strchr(putline, '\n') && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			return (NULL);
		}			
		buff[reader] = '\0';
		putline = gl_strjoin(putline, buff);
	}
	free(buff);
	return (putline);
}

char	*get_next_line(int fd)
{
	char		*mainline;
	static char	*putline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	putline = get_read(fd, putline);
	if (!putline)
		return (NULL);
	mainline = get_main_line(putline);
	putline = get_putten(putline);
	return (mainline);
}

size_t	gl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*gl_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

char	*gl_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s3 = (char *)malloc(gl_strlen(s1) + gl_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i] != 0)
		s3[i] = s1[i];
	j = -1;
	while (s2[++j] != 0)
	{
		s3[i + j] = s2[j];
	}
	s3[i + j] = 0;
	free(s1);
	return (s3);
}

#endif
