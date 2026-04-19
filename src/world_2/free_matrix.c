#include "../../include/fonction_math.h"

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