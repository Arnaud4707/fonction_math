#include"../fonction_math.h"

int render_loop(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);
	unsigned int *buffer = (unsigned int *)core->vars->img->addr;

	fill_background(core->vars->img, 0X00FFFFFF, core->vars->width, core->vars->height);
	for (int i = floor(core->vars->greed.x_min); i <= ceil(core->vars->greed.x_max); i++){
		int x = (i - core->vars->greed.x_min) * core->vars->scale_w;
		
		int color = 0X00CCCCCC;
		if (x >= 0 && x < core->vars->width)
		{
			if (i == 0)
				color = 0X00000000;
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int y = 0; y < core->vars->height; y++)
				buffer[y * core->vars->width + x] = color;
		}
	}
	for (int i = floor(core->vars->greed.y_min); i <= ceil(core->vars->greed.y_max); i++){
		int y = (core->vars->greed.y_max - i) * core->vars->scale_h;
		
		if (y >= 0 && y < core->vars->height)
		{
			int color = 0x00CCCCCC;
			if (i == 0)
				color = 0X00000000;
			else if (i % 5 == 0)
				color = 0X00A0A0A0;
			for (int x = 0; x < core->vars->width; x++)
				buffer[y * core->vars->width + x] = color;
		}
	}

	f_cos_x(core->vars->fonction.sin.x, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
			core->vars->fonction.sin.h, core->vars->fonction.sin.k, core->vars);

	if (core->vars->id_fonction == 1)
		f_ax_plus_b(0, 1, 1, core->vars);
	else if (core->vars->id_fonction == 2)
		f_ax2_puls_bx_plus_c(-9.99, 1, 1.3, 0, core->vars);
	else if (core->vars->id_fonction == 3)
		f_a_power_x(-10, 1.1, core->vars);
	else if (core->vars->id_fonction == 4)
		f_spirale_asymptote(20, 20, 0, 15, core->vars);
	else if (core->vars->id_fonction == 5)
		f_diff_ax(-3, 0.75, -0.5, core->vars);
	else if (core->vars->id_fonction == 6)
		f_diff_ax_plus_b(-3, 0.75, 0.5, 1.2, core->vars);
	else if (core->vars->id_fonction == 7)
		f_sin_x(core->vars->fonction.sin.x, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
			 core->vars->fonction.sin.h, core->vars->fonction.sin.k, core->vars);

	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	gettimeofday(&end_tv, NULL);
	printf("time in microsec: %ld\n", diff_time(&start_tv, &end_tv));
	int t = diff_time(&start_tv, &end_tv);
	if (t < 20000)
		usleep(20000 - t); // 
	return (0);
}
