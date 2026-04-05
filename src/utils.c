#include "../fonction_math.h"

int f_close(t_controller* core)
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
	// if (con)
	// {
	// 	if (core->tars->img && core->tars->img->img)
	// 	{
	// 		mlx_destroy_image(core->mlx, core->tars->img->img);
	// 		free(core->tars->img);
	// 	}
	// 	if (core->tars->win)
	// 	{
	// 		mlx_destroy_window(core->mlx, core->tars->win);
	// 		free(core->tars);
	// 	}
	// }
	if (core->mlx)
		mlx_destroy_display(core->mlx);
	free(core->mlx);

	exit(0);
	return(0);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

