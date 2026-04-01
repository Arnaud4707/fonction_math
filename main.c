#include "sinus.h"

int main(void)
{
	t_controller control;

	memset(&control, 0, sizeof(t_controller));
	control.mlx = mlx_init();
	control.vars = malloc(sizeof(t_vars));
	vars_init(control.vars, &control);
	// control.tars = malloc(sizeof(t_vars));
	// vars_init(control.tars, &control);

	// f_ax(1, 1, control.vars);
	// f_ax_plus_b(0, -2, -2, control.vars);
	// f_sin_x(-20, control.vars, &control); //2 win
	// f_cos_x(-20, control.vars);
	// f_tan_x(-20, control.vars);
	// f_cercle(4, 0, control.vars);
	// f_ellipse(4, 0, 2, -1, control.vars);
	// f_spirale_archimede(15, 0.65, 0, control.vars);
	// f_spirale_hyperbolique(10, 25, control.vars);
	// f_spirale_log(15, 0.05, 1.16, control.vars);
	// f_spirale_archimede(15, 1.1673849, 0, control.vars);
	// f_exp_base(-4, 2, control.vars);
	// f_log_base(-4, 2, control.vars);
	// f_spirale_asymptote(20, 20, 0, 15, control.vars);
	// f_asymptote(-10, 0, 1, 1, 1, control.vars);
	// f_exp_canon_simple(-4, 2, -1, 2, control.vars);
	// f_exp_canon(-4, 2, -1, 2, 3, 1, control.vars);
	// f_ax2(-9.99, 0.5, control.vars);
	// f_ax2_puls_bx_plus_c(-9.99, -3, 1.3, 0, control.vars);
	// f_diff_ax(0, 1, control.vars);
	// f_diff_ax(0, 0.5, control.vars);
	f_diff_ax(-10, 3, control.vars);
	// f_diff_ax_plus_b(0, 1, 0.5, control.vars);
	// f_diff_ax_plus_b(0, 0.7, 0.4, control.vars);
	// f_diff_ax_plus_b(0, 0.1, -0.7, control.vars);
	// f_diff_ax(-50, -0.5, control.vars);
	// f_clothoide(3, 3, 1, control.vars);

	for (int i = 0; i < control.vars->height; i++){

		for (int j = 0; j < control.vars->width; j++){

			if (i == (control.vars->height / 2) || j == (control.vars->width / 2))
				my_mlx_pixel_put(control.vars->img, j, i, 0x00000000);
		}
	}

	mlx_hook(control.vars->win, ON_DESTROY, (1L >> 0), f_close, &control);
	mlx_hook(control.vars->win, ON_KEYDOWN, (1L << 0), event_key, &control);

	// mlx_hook(control.tars->win, ON_DESTROY, (1L >> 0), f_close, &control);
	// mlx_hook(control.tars->win, ON_KEYDOWN, (1L << 0), event_key, &control);

	mlx_put_image_to_window(control.mlx, control.vars->win, control.vars->img->img, 0, 0);
	// mlx_put_image_to_window(control.mlx, control.tars->win, control.tars->img->img, 0, 0);
	mlx_loop(control.mlx);
	return (0);
}