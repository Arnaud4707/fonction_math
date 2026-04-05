#include "fonction_math.h"

int main(void)
{
	t_controller core;

	memset(&core, 0, sizeof(t_controller));
	core.mlx = mlx_init();
	core.vars = malloc(sizeof(t_vars));
	vars_init(core.vars, &core);
	// core.tars = malloc(sizeof(t_vars));
	// vars_init(core.tars, &core);

	// f_sin_x(-20, core.vars, &core); //2 win
	// f_cos_x(-20, core.vars);
	// f_tan_x(-20, core.vars);
	// f_cercle(4, 0, core.vars);
	// f_ellipse(4, 0, 2, -1, core.vars);
	// f_spirale_archimede(15, 0.65, 0, core.vars);
	// f_spirale_hyperbolique(10, 25, core.vars);
	// f_spirale_log(15, 0.05, 1.16, core.vars);
	// f_spirale_archimede(15, 1.1673849, 0, core.vars);
	// f_log_base(-4, 2, core.vars);
	// f_spirale_asymptote(20, 20, 0, 15, core.vars);
	// f_asymptote(-10, 0, 1, 1, 1, core.vars);
	// f_exp_canon_simple(-4, 2, -1, 2, core.vars);
	// f_exp_canon(-4, 2, -1, 2, 3, 1, core.vars);
	// f_diff_ax(0, 0.5, core.vars);
	// f_diff_ax(-10, 3, core.vars);
	// f_diff_ax_plus_b(0, 1, 0.5, core.vars);
	// f_diff_ax_plus_b(0, 0.7, 0.4, core.vars);
	// f_diff_ax_plus_b(0, 0.1, -0.7, core.vars);
	// f_diff_ax(-50, -0.5, core.vars);
	// f_clothoide(3, 3, 1, core.vars);

	// printf("%f %f\n", core.vars->scale_h, core.vars->scale_w);

	mlx_hook(core.vars->win, ON_DESTROY, (1L), f_close, &core);
	mlx_hook(core.vars->win, ON_KEYDOWN, (1L), event_key, &core);

	// mlx_hook(core.tars->win, ON_DESTROY, (1L >> 0), f_close, &core);
	// mlx_hook(core.tars->win, ON_KEYDOWN, (1L << 0), event_key, &core);
	mlx_loop_hook(core.mlx, render_loop, &core);
	// mlx_put_image_to_window(core.mlx, core.tars->win, core.tars->img->img, 0, 0);
	mlx_loop(core.mlx);
	return (0);
}