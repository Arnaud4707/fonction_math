#include"../sinus.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int render_loop(void* core_)
{
	t_controller* core = (t_controller*)(core_);

	for (int i = 0; i < core->vars->height; i++){
		for (int j = 0; j < core->vars->width; j++){
			if (i == (core->vars->height / 2) || j == (core->vars->width / 2))
			{
				my_mlx_pixel_put(core->vars->img, j, i, 0x00000000);
			}
			else
			{
				my_mlx_pixel_put(core->vars->img, j, i, 0xAAAAAA);
				if (((i % (int)(core->vars->scale_h)) == 0) || (j % (int)(core->vars->scale_w) == 0))
					my_mlx_pixel_put(core->vars->img, j, i, 0x00A0A0A0);
			}

		}
	}

	if (core->vars->f == 1)
		f_ax_plus_b(0, 1, 1, core->vars);
	else if (core->vars->f == 2)
		f_ax2_puls_bx_plus_c(-9.99, 1, 1.3, 0, core->vars);
	else if (core->vars->f == 3)
		
	else if (core->vars->f == 4)
		f_spirale_asymptote(20, 20, 0, 15, core->vars);
		

	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	usleep(20000);
	return (0);
}
