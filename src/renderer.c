#include "../fonction_math.h"
#include "../grilles.h"

int render_loop(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;
	// void(*tab_cercle[1])(double x_, double y_, t_vars *vars) = {f_cercle};

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

    fill_background(core->vars->img, BLEU_CIEL, core->vars->width, core->vars->height);
	// grille_point(core);
	for (double j = core->vars->greed.y_min; j < core->vars->greed.y_max; j += 2)
		background_sinus(core->vars->greed.x_min, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, j, NOIR, core->vars);
	// grille_orthonorme(core);
	// for (double i = 0; i <= core->vars->greed.x_max; i += 2)
	// 	background_sinus_concentrique(2, i, core->vars->fonction.trigo.b, core->vars);
	// drawLine(core->vars->fonction.test.x0, core->vars->fonction.test.y0, core->vars->fonction.test.x1, core->vars->fonction.test.y1, (50 << 16 | 200 << 8 | 13 ), core);

	if (core->vars->id_fonction == 1)
		f_ax_plus_b(0, core->vars->fonction.al.a, core->vars->fonction.al.b, core->vars);
	else if (core->vars->id_fonction == 2)
		f_ax2_puls_bx_plus_c(-9.99, core->vars->fonction.al.a, core->vars->fonction.al.b, core->vars->fonction.al.c, core->vars);
	else if (core->vars->id_fonction == 3)
		f_a_power_x(-10, core->vars->fonction.al.a, core->vars);
	else if (core->vars->id_fonction == 4)
		f_diff_ax(-3, core->vars->fonction.al.a, core->vars->fonction.al.c, core->vars);
	else if (core->vars->id_fonction == 5)
		f_diff_ax_plus_b(-3, core->vars->fonction.al.a, core->vars->fonction.al.b, core->vars->fonction.al.c, core->vars);
	else if (core->vars->id_fonction == 6)
		f_cercle(core->vars->fonction.trigo.a, core->vars->fonction.trigo.b, core->vars);
	else if (core->vars->id_fonction == 7)
		f_spirale_archimede(20, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b, core->vars);
	else if (core->vars->id_fonction == 8)
		f_spirale_hyperbolique(20, core->vars->fonction.trigo.a, core->vars);
	else if (core->vars->id_fonction == 9)
		f_spirale_asymptote(20, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b, core->vars->fonction.trigo.h, core->vars);
	else if (core->vars->id_fonction == 10)
		f_spirale_log(20, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b, core->vars);
	else if (core->vars->id_fonction == 11)
		f_sin_x(core->vars->fonction.trigo.x, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, core->vars->fonction.trigo.k, core->vars);
	else if (core->vars->id_fonction == 12)
		f_cos_x(core->vars->fonction.trigo.x, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, core->vars->fonction.trigo.k, core->vars);
	else if (core->vars->id_fonction == 13)
		f_tan_x(core->vars->fonction.trigo.x, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, core->vars->fonction.trigo.k, core->vars);
	else if (core->vars->id_fonction == 14)
		animation_sinus(core->vars->fonction.trigo.x, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, core->vars->fonction.trigo.k, core->vars);
	else if (core->vars->id_fonction == 15)
		animation_sinus_concentrique(core->vars->fonction.trigo.a, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b, core->vars);

	// tab_cercle[core->vars->id_fonction](2, 0, core->vars);

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	__int16_t fps = 1000000 / t;
	printf("time of prosses: %d x0: %d\n", t, core->vars->fonction.test.x0);
	char buff[20];
	if (t < 20000)
	{
		fps = 1000000 / 20000;
		t = 20000 - t;
	}
	sprintf(buff, "FPS: %d", fps);
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00000000, buff);
	affiche_param(core);
	if (t < 20000)
		usleep(t);
	return (0);
}
