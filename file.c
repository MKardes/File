#include <get_next_line.h>
#include <libft.h>
#include <stdio.h>

void	join_file(int join_fd, char *path)
{
	char	**file = calloc(sizeof(char *), 500);
	int	i = 2, fd;

	fd = open(path, O_RDONLY);
	file[0] = ft_strdup("\n");
	file[1] = get_next_line(fd);
	while (file[1])
        {
		if (file[1] && (file[1][0] != '\0' && file[1][0] != 10))
                        break;
		printf("x\n");
		if (file[1])
			free(file[1]);
		file[1] = get_next_line(fd);
        }
	if (!file[1])
	{
		free(file[0]);
		free(file[1]);
		free(file);
		close(fd);
		return ;
	}
	while (i < 500)
	{
		file[i] = get_next_line(fd);
		if (!file[i])
			break ;
		i++;
	}
	close(fd);
	int j = 0;
	while (j < i)
	{
		write(join_fd, file[j], ft_strlen(file[j]));
		free(file[j]);
		j++;
	}
	free(file);
}

void	join(char *dest_file, char **argv, int ac)
{
	int	i = 3;
	int	dest_fd = open(dest_file, O_CREAT | O_WRONLY, 0777);
	
	while (i < ac)
	{
		join_file(dest_fd, argv[i]);
		i++;
	}
	close(dest_fd);
	printf("Joined Files Successfully\n");
}

void	detect(char *del, char *path)
{
	char	**file = calloc(sizeof(char *), 500);
	char	*needle;
	int	i = 0, fd;

	fd = open(path, O_RDONLY);
	while (i < 500)
	{
		file[i] = get_next_line(fd);
		if (!file[i])
			break ;
		needle = ft_strnstr(file[i], del, ft_strlen(file[i]));
		if (needle)
		{
			free(file[i]);
			i--;
		}
		i++;
	}
	close(fd);
	remove(path);
	fd = open(path, O_CREAT | O_WRONLY, 0777);
	int j = 0;
	while (j < i)
	{
		write(fd, file[j], ft_strlen(file[j]));
		free(file[j]);
		j++;
	}
	free(file);
	close(fd);
}


void	del(char *del_wrd, char **argv, int ac)
{
	int	i = 3;
	while (i < ac)
	{
		detect(del_wrd, argv[i]);
		i++;
	}
	printf("Deleted Successfully!\n");
}

int	main(int ac, char **argv)
{
	if (ft_strstr(argv[1], "del"))
	{
		del(argv[2], argv, ac);
	}
	else if (ft_strstr(argv[1], "join"))
	{
		join(argv[2], argv, ac);
	}
	else
		return (1);
	return (0);
}
