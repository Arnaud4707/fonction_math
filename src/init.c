#include "../include/fonction_math.h"

void	vars_init(t_vars *vars, t_controller *core)
{
	vars->width = 1200;
	vars->height = 600;
	// mlx_get_screen_size(core->mlx, &(vars->width), &(vars->height));
	vars->greed.x_min = -50;
	vars->greed.x_max = 50;
	vars->greed.y_min = -25;
	vars->greed.y_max = 25;
	vars->world = 2;
	if (vars->world == 3)
	{
		vars->width = 700;
		vars->height = 700;
	}
	vars->id_fonction = 0;
	vars->nb_fonction = 15;
	vars->greed.scale_x = vars->greed.x_max - vars->greed.x_min;
	vars->greed.scale_y = vars->greed.y_max - vars->greed.y_min;
	vars->scale_h = vars->height / vars->greed.scale_y;
	vars->scale_w = vars->width / vars->greed.scale_x;
	vars->win = mlx_new_window(core->mlx, vars->width, vars->height, "Fonction Mathématique");
	vars->img = malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(core->mlx, vars->width, vars->height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
										&(vars->img->bpp), &(vars->img->line_length), &(vars->img->endian));
	init_function(core);
	init_matrice(&(core->vars->matrice));
	init_map_game_of_life(100, 100, 60, core);
}

void	init_function(t_controller *core)
{
	core->vars->fonction.trigo.x = 0;
	core->vars->fonction.trigo.a = 4;
	core->vars->fonction.trigo.b = 0;
	core->vars->fonction.trigo.h = 0;
	core->vars->fonction.trigo.k = 0;
	core->vars->fonction.al.a = 1;
	core->vars->fonction.al.b = 1.3;
	core->vars->fonction.al.c = 1;
	core->vars->fonction.al.d = 1;
	core->vars->fonction.test.x0 = 0;
	core->vars->fonction.test.x1 = 100;
	core->vars->fonction.test.y0 = 0;
	core->vars->fonction.test.y1 = 100;
}

void	init_mat_identite(t_mat *mat)
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			mat->mat[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++){
		mat->mat[i][i] = 1;
	}
}

void	init_param_cam_lookat(t_camera* cam)
{
	cam->position.x = 0;
	cam->position.y = 0;
	cam->position.z = 10;
	cam->position.w = 1;
}

void	init_matrice(t_matrice *matrice)
{
	matrice->mode = 1; // 1: isométrie 2: perspective
	matrice->offsetX = WIDTH / 2;
	matrice->offsetY = HEIGHT / 2;
	matrice->scale.scaleXY = 1;
	matrice->scale.scaleZ = 1;
	//---------
	matrice->angles.angleY = M_PI / 4;
	matrice->angles.angleX = atan(1.0 / sqrt(2));
	matrice->angles.angleZ = 0;
	init_mat_rotate_x(&(matrice->mat_rotateX), matrice->angles.angleX);
	init_mat_rotate_y(&(matrice->mat_rotateY), matrice->angles.angleY);
	init_mat_rotate_z(&(matrice->mat_rotateZ), matrice->angles.angleZ);
	init_mat_scale(&(matrice->mat_scale), matrice->scale.scaleXY, matrice->scale.scaleXY, matrice->scale.scaleZ);
	init_mat_translation(&(matrice->mat_translation), 0, 0, -10);
	build_matrix_world(matrice);
	matrice->cam.pitch = 10 * M_PI / 180.0;
	matrice->cam.yaw = 10 * M_PI / 180.0;
	init_param_cam_lookat(&(matrice->cam));
	if (matrice->mode == 1)
		init_projection_ortho(&(matrice->mat_projection), -10, 10, -10, 10, 0.1, 100);
	else
		init_project_perspective(&(matrice->mat_projection), M_PI / 3, (double)WIDTH / HEIGHT, 1000.0, 0.1);
	build_matrix_view_fps(&(matrice->mat_view), &( matrice->cam));
}

void	init_map_game_of_life(int nb_caseX, int nb_caseY, int gen,t_controller *core)
{
	char **map;

	map = malloc(nb_caseY * (sizeof(char *)));
	if (!map)
		return;
	int i = 0;
	while (i < nb_caseY)
	{
		map[i] = malloc(nb_caseX * sizeof(char));
		int j = 0;
		while (j < nb_caseX)
		{
			map[i][j] = 'D';
			j++;
		}
		i++;
	}
	core->vars->gol.map = map;
	core->vars->gol.height = nb_caseY;
	core->vars->gol.width = nb_caseX;
	core->vars->gol.tail_cell = core->vars->width / nb_caseX;
	core->vars->gol.gen = gen;
	core->vars->gol.start = 0;
}