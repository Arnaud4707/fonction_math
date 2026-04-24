#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

// --- utils ---

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int	i = 0;
	int	sign = 1;
	int	res = 0;

	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		res = res * 10 + (str[i++] - '0');
	return (res * sign);
}

// skip ",0x...."
void	skip_color(const char *line, int *i)
{
	if (line[*i] == ',')
	{
		(*i)++;
		while (line[*i] && line[*i] != ' ')
			(*i)++;
	}
}

// count numbers in a line
int	count_cols(const char *line)
{
	int	i = 0;
	int	count = 0;

	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i] && (ft_isdigit(line[i]) || line[i] == '-' || line[i] == '+'))
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
		}
	}
	return (count);
}

// parse one line into int*
int	*parse_line(const char *line, int cols)
{
	int	*row = malloc(sizeof(int) * cols);
	int	i = 0, j = 0;

	if (!row)
		return (NULL);

	while (line[i] && j < cols)
	{
		while (line[i] == ' ')
			i++;
		row[j++] = ft_atoi(&line[i]);
		while (line[i] && line[i] != ' ' && line[i] != ',')
			i++;
		skip_color(line, &i);
	}
	return (row);
}

// simple getline (à remplacer par get_next_line si tu veux)
char	*read_line(int fd)
{
	char	*line = malloc(10000);
	int		i = 0;
	char	c;

	if (!line)
		return (NULL);
	while (read(fd, &c, 1) > 0)
	{
		if (c == '\n')
			break;
		line[i++] = c;
	}
	if (i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

// count rows
int	count_rows(const char *filename)
{
	int		fd = open(filename, O_RDONLY);
	int		rows = 0;
	char	*line;

	if (fd < 0)
		return (-1);
	while ((line = read_line(fd)))
	{
		rows++;
		free(line);
	}
	close(fd);
	return (rows);
}

// --- MAIN PARSER ---

int	**parse_fdf(const char *filename, int *out_rows, int *out_cols)
{
	int		fd;
	int		rows;
	int		cols = -1;
	int		i = 0;
	int		**map;
	char	*line;

	rows = count_rows(filename);
	if (rows <= 0)
		return (NULL);

	fd = open(filename, O_RDONLY);
	map = malloc(sizeof(int *) * rows);
	if (!map || fd < 0)
		return (NULL);

	while ((line = read_line(fd)))
	{
		if (cols == -1)
			cols = count_cols(line);
		map[i] = parse_line(line, cols);
		free(line);
		i++;
	}
	close(fd);

	*out_rows = rows;
	*out_cols = cols;
	return (map);
}

// int main(void)
// {
// 	int rows, cols;
// 	int **map = parse_fdf("42.fdf", &rows, &cols);

// 	for (int i = 0; i < rows; i++)
// 	{
// 		for (int j = 0; j < cols; j++)
// 			printf("%d ", map[i][j]);
// 		printf("\n");
// 	}
// }