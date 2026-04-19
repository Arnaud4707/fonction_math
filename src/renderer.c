#include "../include/fonction_math.h"

t_vect cube[8] = {
    {-1,-1,-1,1}, {1,-1,-1,1},
    {1,1,-1,1},  {-1,1,-1,1},
    {-1,-1,1,1}, {1,-1,1,1},
    {1,1,1,1},   {-1,1,1,1}
};
// int triangles[12][3] = {
//     // Face AVANT (z = -1) - Vue de devant : horaire
//     {0, 3, 2}, {0, 2, 1},
//     // Face ARRIÈRE (z = 1) - Vue de derrière : horaire
//     {5, 6, 7}, {5, 7, 4},
//     // Face GAUCHE (x = -1)
//     {4, 7, 3}, {4, 3, 0},
//     // Face DROITE (x = 1)
//     {1, 2, 6}, {1, 6, 5},
//     // Face HAUT (y = 1)
//     {3, 7, 6}, {3, 6, 2},
//     // Face BAS (y = -1)
//     {4, 0, 1}, {4, 1, 5}
// };

int render_loop(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;
	// void(*tab_cercle[1])(double x_, double y_, t_vars *vars) = {f_cercle};

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

    fill_background(core->vars->img, BLEU_CIEL);
	
	// grille_isometrique(core, BLANC);
	if (core->vars->id_fonction == -1)
		for (double j = core->vars->greed.y_min; j < core->vars->greed.y_max; j += 2)
			background_sinus(core->vars->greed.x_min, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
				core->vars->fonction.trigo.h, j, BLEU, core->vars);
	else if (core->vars->id_fonction == 0)
		for (double i = 0; i <= core->vars->greed.x_max; i += 2)
			background_sinus_concentrique(4, i, core->vars->fonction.trigo.b, BLEU, core->vars);
	else
		grille_orthonorme(core);

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
		{animation_sinus(core->vars->fonction.trigo.x, core->vars->fonction.trigo.a, core->vars->fonction.trigo.b,
			core->vars->fonction.trigo.h, core->vars->fonction.trigo.k, core->vars); if (core->vars->fonction.trigo.b == 0) core->vars->fonction.trigo.b = 0.25;}
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
	sprintf(buff, "Fonction: %d", core->vars->id_fonction);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00000000, buff);
	affiche_param(core);
	if (t < 20000)
		usleep(t);
	return (0);
}

int render_loop_matrice(void* core_)
{

    struct timeval 	start_tv;
    struct timeval 	end_tv;
	int color[6] = {
	0x00FF0000,
	0x00FF0000,
	0x000000FF,
	0x000000FF,
	0x0000FF00,
	0x0000FF00
};

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);
	int size = WIDTH * HEIGHT;
    fill_background(core->vars->img, NOIR);
	for (int i = 0; i < size; i++)
    	((float*)core->vars->matrice.zbuffer)[i] = 1000;
	display_cube(core, cube, color);

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
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFF00, buff);
	if (core->vars->matrice.mode == 1)
	{
		sprintf(buff, "Mode isomérie");
		mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00000000, buff);
	}
	else
	{
		sprintf(buff, "Mode perspective");
		mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00000000, buff);
	}
	if (t < 20000)
		usleep(t);
	return (0);
}

int	render_loop_game_of_life(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

	display_map_game_of_life(core);

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	__int16_t fps = 1000000 / t;
	char buff[20];
	if (t < 20000)
	{
		fps = 1000000 / 20000;
		t = 20000 - t;
	}
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFFFF, buff);
	sprintf(buff, "Generation: %d", 0);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFFFF, buff);
	if (t < 20000)
		usleep(t);
	return (0);
}

int	render_loop_game_of_life_generation(void* core_)
{

    struct timeval start_tv;
    struct timeval end_tv;

	gettimeofday(&start_tv, NULL);
	t_controller* core = (t_controller*)(core_);

	generation_game_of_life(&(core->vars->gol));
	display_map_game_of_life(core);
	core->vars->gol.start--;
	if (core->vars->gol.start == 0)
		mlx_loop_hook(core->mlx, render_loop_game_of_life, core);

	gettimeofday(&end_tv, NULL);
	int t = diff_time(&start_tv, &end_tv);
	t = 250000 - t;
	int fps = 1000000 / t;
	char buff[20];
	sprintf(buff, "Generation: %d", core->vars->gol.gen - core->vars->gol.start);
	mlx_put_image_to_window(core->mlx, core->vars->win, core->vars->img->img, 0, 0);
	mlx_string_put(core->mlx, core->vars->win, 0, 40, 0x00FFFFFF, buff);
	sprintf(buff, "FPS: %d", fps);
	mlx_string_put(core->mlx, core->vars->win, 0, 20, 0x00FFFFFF, buff);
	if (t < 250000)
		usleep(t);
	return (0);
}