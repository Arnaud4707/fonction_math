#include "../fonction_math.h"
#include "../grilles.h"

int render_loop(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;
	// static int8_t i = 160;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

	// core->vars->col->color = core->vars->col->name[i++];

    fill_background(core->vars->img, 0x00EEEEEE, core->vars->width, core->vars->height);
	// grille_point(core);
	grille_orthonorme(core);
	// f_cos_x(core->vars->fonction.sin.x, core->vars->fonction.sin.a, core->vars->fonction.sin.b,
	// 		core->vars->fonction.sin.h, core->vars->fonction.sin.k, core->vars);

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

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	__int16_t fps = 1000000 / t;
	printf("time of prosses: %d\n", t);
	char buff[20];
	if (t < 20000)
	{
		fps = 1000000 / 20000;
		t = 20000 - t;
	}
	sprintf(buff, "FPS: %d", fps);
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00000000, buff);
	if (t < 20000)
		usleep(t);
	return (0);
}
