#include "../../include/fonction_math.h"

void	init_map_game_of_life(int tail, int gen, t_controller *core)
{
	char**	map;
	int**	buff_color;
	int y = core->vars->height / tail;
	int x = core->vars->width / tail;

	map = malloc(y * (sizeof(char *)));
	if (!map)
		return;
	buff_color = malloc(y * (sizeof(int *)));
	if (!buff_color)
		return;
	int i = 0;
	while (i < y)
	{
		map[i] = malloc(x * sizeof(char));
		buff_color[i] = malloc(x * sizeof(int));
		int j = 0;
		while (j < x)
		{
			map[i][j] = 0;
			buff_color[i][j] = 0x00000000;
			j++;
		}
		i++;
	}
	core->vars->gol.map = map;
	core->vars->gol.buff_color = buff_color;
	core->vars->gol.height = y;
	core->vars->gol.width = x;
	core->vars->gol.tail_cell = tail;
	core->vars->gol.gen = gen;
	core->vars->gol.start = 0;
}