#include "../include/fonction_math.h"

int f_close(t_controller *core)
{
	if (core && core->vars)
	{
		if (core->vars->img && core->vars->img->img)
		{
			mlx_destroy_image(core->mlx, core->vars->img->img);
			free(core->vars->img);
		}
		if (core->vars->win)
			mlx_destroy_window(core->mlx, core->vars->win);
		free(core->vars);
	}
	if (core->mlx)
		mlx_destroy_display(core->mlx);
	free(core->mlx);

	exit(0);
	return (0);
}

unsigned long diff_time(struct timeval *st, struct timeval *end)
{
	return (((end->tv_sec - st->tv_sec) * 1000000 + (end->tv_usec - st->tv_usec)));
}

t_maps*		init_maps(char *file)
{
	FILE *fd;
	t_maps *map;
	char *line = NULL;
	int read;
	size_t size = 1000;
	int size_line;
	t_maps* head;

	fd = fopen(file, "r");
	if (!fd)
		return(NULL);
	map = malloc(sizeof(t_maps));
	head = map;
	read = getline(&line, &size, fd);
	if (read <= 0)
	{
		dprintf(2, "Error: Can't read file\n");
		return (NULL);
	}
	size_line = read;
	map->line = strdup(line);
	map->next = NULL;
	read = getline(&line, &size, fd);
	while (read == size_line)
	{
		map->next = malloc(sizeof(t_maps));
		map->next->line = strdup(line);
		map->next->next = NULL;
		map = map->next;
		read = getline(&line, &size, fd);
	}
	free(line);
	return (head);
}

void	free_maps(t_maps* map)
{
	t_maps* tmp;

	while (map)
	{
		tmp = map->next;
		free(map->line);
		free(map);
		map = tmp;
	}
}
