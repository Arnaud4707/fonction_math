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


void	vars_init(t_vars *vars, t_controller *core)
{
	vars->width = 1200;
	vars->height = 600;
	// mlx_get_screen_size(core->mlx, &(vars->width), &(vars->height));
	vars->win = mlx_new_window(core->mlx, vars->width, vars->height, "MUGT Multi Usage Graphic ToolBox");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(core->mlx, vars->width, vars->height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
										&(vars->img->bpp), &(vars->img->line_length), &(vars->img->endian));
	init_function_math(core);
	init_matrice(&(core->vars->matrice));
	init_map_game_of_life(10, 60, core);
}

unsigned long diff_time(struct timeval *st, struct timeval *end)
{
	return (((end->tv_sec - st->tv_sec) * 1000000 + (end->tv_usec - st->tv_usec)));
}

