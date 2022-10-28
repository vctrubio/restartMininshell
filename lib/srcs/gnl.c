#include "../libft.h"

static int	ft_strsave(int fd, char **line, char **store)
{
	int		i;
	char	*tmp;

	i = 0;
	while (store[fd][i] != '\n' && store[fd][i] != '\0')
		i++;
	if (store[fd][i] == '\n')
	{
		*line = ft_substr(store[fd], 0, i);
		tmp = ft_substr(store[fd], i + 1, ft_strlen(store[fd] - i));
		free(store[fd]);
		store[fd] = tmp;
		return (1);
	}
	else
	{
		*line = ft_strdup(store[fd]);
		free(store[fd]);
		store[fd] = 0;
		return (0);
	}
}
// strsave has to check for \n o \0, 
// i counter ++, tmp
// if new line, line substr until new line,
// tmp becomes rest
// free store[fd]
// return 1

// return-quick check not -1 or line is not NULL
static int	ft_check_return(int fd, char **line, char **storage, int reader)
{
	if (reader == -1)
		return (-1);
	if (!(reader) && storage[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	return(ft_strsave(fd, line, storage));
}

	// buff equal no null and readc
	// if no store, duplicate
	// tmp join string af what we have
	// free
	// new store of temp
	// if - temp (ie store) has new line, break and call return

int			get_next_line(int fd, char **line)
{
	static char	*storage[1000];
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			reader;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	while ((reader = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[reader] = '\0';
		if (!storage[fd])
			storage[fd] = ft_strdup("");
		tmp = ft_strjoin(storage[fd], buffer);
		free(storage[fd]);
		storage[fd] = tmp;
		if (ft_strchr(storage[fd], '\n'))
			break;
	}
	return(ft_check_return(fd, line, storage, reader));
}