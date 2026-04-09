#include "fonction_math.h"

int main(void)
{
	t_controller core;

	memset(&core, 0, sizeof(t_controller));
	core.mlx = mlx_init();
	core.vars = malloc(sizeof(t_vars));
	vars_init(core.vars, &core);
	
	mlx_hook(core.vars->win, ON_DESTROY, (1L), f_close, &core);
	mlx_hook(core.vars->win, ON_KEYDOWN, (1L), event_key, &core);

	mlx_loop_hook(core.mlx, render_loop, &core);
	mlx_loop(core.mlx);
	return (0);
}