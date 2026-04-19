#include "core.h"

int main(void)
{
	t_controller core;

	// memset(&core, 0, sizeof(t_controller));
	core.mlx = mlx_init();
	core.vars = malloc(sizeof(t_vars));
	vars_init(core.vars, &core);
	// {
	// t_maps* map =  init_maps("42.fdf");
	// if (!map)
	// 	return (0);
	// while (map)
	// {
	// 	printf("%s", map->line);
	// 	map = map->next;
	// }
	// free_maps(map);}
	if (WORLD == 1)
	{
		mlx_hook(core.vars->win, ON_KEYDOWN, (1L), event_key_fonction, &core);
		mlx_loop_hook(core.mlx, render_loop, &core);
	}
	else if (WORLD == 2)
	{
		mlx_hook(core.vars->win, ON_KEYDOWN, (1L), event_key_matrice, &core);
		mlx_hook(core.vars->win, ON_MOUSEMOVE, (1L << 6), event_mouse_move_matrix_rotation, &core);
		mlx_loop_hook(core.mlx, render_loop_matrice, &core);
	}
	else
	{
		mlx_hook(core.vars->win, ON_KEYDOWN, (1L), event_key_game_of_life, &core);
		mlx_mouse_hook(core.vars->win, event_mouse_game_of_life, &core);
		mlx_loop_hook(core.mlx, render_loop_game_of_life, &core);
		mlx_hook(core.vars->win, ON_MOUSEMOVE, (1L << 6), event_mose_move_gol_pen, &core);
	}
	mlx_hook(core.vars->win, ON_DESTROY, (1L), f_close, &core);

    // mlx_put_image_to_window(core.mlx, core.vars->win, core.vars->img->img, 0, 0);
	mlx_loop(core.mlx);
	return (0);
}