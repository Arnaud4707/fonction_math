#include"../fonction_math.h"

int render_loop(void* core_)
{
	t_controller* core = (t_controller*)(core_);

	for (int y = 0; y < core->vars->height; y++){
		for (int x = 0; x < core->vars->width; x++){
			my_mlx_pixel_put(core->vars->img, x, y, 0x00AAAAAA);

			double cx = core->vars->greed.x_min + (x / core->vars->scale_w);
			double cy = core->vars->greed.y_max - (y / core->vars->scale_h);

			double eps_x = 1.0 / core->vars->scale_w;
			double eps_y = 1.0 / core->vars->scale_h;

			if (fabs(cx - round(cx)) < eps_x || fabs(cy - round(cy)) < eps_y)
				my_mlx_pixel_put(core->vars->img, x, y, 0x00A0A0A0);

			if (fabs(cx) < eps_x || fabs(cy) < eps_y)
				my_mlx_pixel_put(core->vars->img, x, y, 0x000000);
		}
	}

	if (core->vars->id_fonction == 1)
		f_ax_plus_b(0, 1, 1, core->vars);
	else if (core->vars->id_fonction == 2)
		f_ax2_puls_bx_plus_c(-9.99, 1, 1.3, 0, core->vars);
	else if (core->vars->id_fonction == 3)
		f_a_power_x(0, 2, core->vars);
	else if (core->vars->id_fonction == 4)
		f_spirale_asymptote(20, 20, 0, 15, core->vars);
	else if (core->vars->id_fonction == 5)
		f_diff_ax(-3, 0.75, -0.5, core->vars);
	else if (core->vars->id_fonction == 6)
		f_diff_ax_plus_b(-3, 0.75, 0.5, 1.2, core->vars);
	else if (core->vars->id_fonction == 7)
		f_sin_x(core->vars->fonction.sin.x, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
			 core->vars->fonction.sin.h, core->vars->fonction.sin.k, core->vars, core);

	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	usleep(20000);
	return (0);
}
