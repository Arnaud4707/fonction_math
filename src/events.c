#include "../include/fonction_math.h"

int event_key_fonction(int key, t_controller* core)
{
	if (key == 65307)
		f_close(core);
	if (key == 121)
	{
		core->vars->id_fonction++;
		if (core->vars->id_fonction == 11)
			core->vars->fonction.trigo.b = 0.25;
	}
	else if (key == 116)
		core->vars->id_fonction--;
	else if (key == 112) //65451
		zoom(1, core);
	else if (key == 109)
		zoom(-1, core);

	if (key >= 65361 && key <= 65364)
		arrow(key, core);

	if (key == 113 || key == 100 || key == 97 || key == 101 || key == 119
		|| key == 99 || key == 122 || key == 115)
	{
			if (core->vars->id_fonction > 0 && core->vars->id_fonction < 6 )
				change_param_algebre(key, core);
			else
				change_param_trigo(key, core);
	}

	if (core->vars->id_fonction > core->vars->nb_fonction)
		core->vars->id_fonction = -1;
	else if (core->vars->id_fonction < -1)
		core->vars->id_fonction = core->vars->nb_fonction;

	// printf("key: %d, f: %d\n", key, core->vars->id_fonction);
	return(0);
}

int event_key_matrice(int key, t_controller* core)
{
	if (key == 65307)
		f_close(core);

	if (key == 32)
	{
		if (core->vars->matrice.mode == 1)
		{
			core->vars->matrice.mode = 2;
			init_project_perspective(&(core->vars->matrice.mat_projection), M_PI / 3, (double)WIDTH / HEIGHT, 1000.0, 0.1);
		}
		else
		{
			core->vars->matrice.mode = 1;
			init_projection_ortho(&(core->vars->matrice.mat_projection), -10, 10, -10, 10, 0.1, 100);
		}
	}
	if (key >= 97 && key <= 122)
	{
		change_param_matrice(key, core);
	}

	// printf("key: %d\n", key);
	return(0);
}

int		event_mouse_move_matrix_rotation(int x, int y, void* core_)
{
	t_controller*	core = (t_controller*)(core_);
	
	static int last_x = -1;
	static int last_y = -1;

	if (last_x == -1)
	{
		last_x = x;
		last_y = y;
		return 0;
	}

	int dx = x - last_x;
	int dy = y - last_y;

	last_x = x;
	last_y = y;

	rotate_fps(&(core->vars->matrice.cam), dx, dy);
	build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	return (0);
}


int 	event_key_game_of_life(int key, t_controller* core)
{
	if (key == 65307)
		f_close(core);
	if (key == 32){
		if (core->vars->gol.start != 0)
		{
			core->vars->gol.start = 0;
			mlx_loop_hook(core->mlx, render_loop_game_of_life, core);
		}
		else
		{
			core->vars->gol.start = core->vars->gol.gen;
			mlx_loop_hook(core->mlx, render_loop_game_of_life_generation, core);
		}
	}
	return(0);
}

int		event_mose_move_gol_pen(int x, int y, void* core_)
{
	t_controller*	core = (t_controller*)(core_);
	int i = x / core->vars->gol.tail_cell;
	int j = y / core->vars->gol.tail_cell;
	if (core->vars->gol.pen == 1)
		core->vars->gol.map[j][i] = 'A';
	else if (core->vars->gol.pen == -1)
		core->vars->gol.map[j][i] = 'D';
	return (0);
}

int		event_mouse_game_of_life(int button, int x, int y, void* core_)
{
	t_controller* core = (t_controller*)(core_);
	(void)core;(void)x;(void)y;
	if (button == 1)
	{
		if (core->vars->gol.pen != 1)
			core->vars->gol.pen = 1;
		else
			core->vars->gol.pen = 0;
	}
	else if (button == 3)
	{
		if (core->vars->gol.pen != -1)
			core->vars->gol.pen = -1;
		else
			core->vars->gol.pen = 0;
	}
	return (0);
}

void	change_param_matrice(int key, t_controller* core)
{
	double	angle_object = M_PI / 180.0 * 5; // 5 degrés
	if (key == 97) //avancer
	{
		move_forward_fps(&(core->vars->matrice.cam), -0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 101)
	{
		move_forward_fps(&(core->vars->matrice.cam), 0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 113)
	{
		move_right_fps(&(core->vars->matrice.cam), -0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 100)
	{
		move_right_fps(&(core->vars->matrice.cam), 0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 119)
	{
		move_up(&(core->vars->matrice.cam), -0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 99)
	{
		move_up(&(core->vars->matrice.cam), 0.5);
		build_matrix_view_fps(&(core->vars->matrice.mat_view), &(core->vars->matrice.cam));
	}
	else if (key == 116)
	{
		core->vars->matrice.angles.angleY -= angle_object;
		init_mat_rotate_y(&(core->vars->matrice.mat_rotateY), core->vars->matrice.angles.angleY);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 121)
	{
		core->vars->matrice.angles.angleY += angle_object;
		init_mat_rotate_y(&(core->vars->matrice.mat_rotateY), core->vars->matrice.angles.angleY);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 102)
	{
		core->vars->matrice.angles.angleX -= angle_object;
		init_mat_rotate_x(&(core->vars->matrice.mat_rotateX), core->vars->matrice.angles.angleX);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 103)
	{
		core->vars->matrice.angles.angleX += angle_object;
		init_mat_rotate_x(&(core->vars->matrice.mat_rotateX), core->vars->matrice.angles.angleX);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 98)
	{
		core->vars->matrice.angles.angleZ -= angle_object;
		init_mat_rotate_z(&(core->vars->matrice.mat_rotateZ), core->vars->matrice.angles.angleZ);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 110)
	{
		core->vars->matrice.angles.angleZ += angle_object;
		init_mat_rotate_z(&(core->vars->matrice.mat_rotateZ), core->vars->matrice.angles.angleZ);
		build_matrix_world(&(core->vars->matrice));
	}
	if (core->vars->matrice.mode == 1)
		init_projection_ortho(&(core->vars->matrice.mat_projection), -10, 10, -10, 10, 0.1, 100);
	else
		init_project_perspective(&(core->vars->matrice.mat_projection), M_PI / 3, (double)WIDTH / HEIGHT, 1000.0, 0.1);
}

void	change_param_trigo(int key, t_controller* core)
{
	double	step = 0.25;
	if (key == 97)
		core->vars->fonction.trigo.a -= step;
	else if (key == 101)
		core->vars->fonction.trigo.a += step;
	else if (key == 113)
		core->vars->fonction.trigo.b -= step;
	else if (key == 100)
		core->vars->fonction.trigo.b += step;
	else if (key == 119)
		core->vars->fonction.trigo.h -= step;
	else if (key == 99)
		core->vars->fonction.trigo.h += step;
	else if (key == 122)
		core->vars->fonction.trigo.k -= step;
	else if (key == 115)
		core->vars->fonction.trigo.k += step;
}

void	change_param_algebre(int key, t_controller* core)
{
	double	step = 0.25;
	if (key == 97)
		core->vars->fonction.al.a -= step;
	else if (key == 101)
		core->vars->fonction.al.a += step;
	else if (key == 113)
		core->vars->fonction.al.b -= step;
	else if (key == 100)
		core->vars->fonction.al.b += step;
	else if (key == 119)
		core->vars->fonction.al.c -= step;
	else if (key == 99)
		core->vars->fonction.al.c += step;
	else if (key == 122)
		core->vars->fonction.al.d -= step;
	else if (key == 115)
		core->vars->fonction.al.d += step;
}

void zoom(int a, t_controller* core)
{
	double cx = (core->vars->greed.x_min + core->vars->greed.x_max) / 2;
	double cy = (core->vars->greed.y_min + core->vars->greed.y_max) / 2;

	double zoom = (a == -1) ? 1.1 : 0.9;
	
	core->vars->greed.x_min = cx + (core->vars->greed.x_min - cx) * zoom;
	core->vars->greed.x_max = cx + (core->vars->greed.x_max - cx) * zoom;
	core->vars->greed.y_min = cy + (core->vars->greed.y_min - cy) * zoom;
	core->vars->greed.y_max = cy + (core->vars->greed.y_max - cy) * zoom;
	core->vars->greed.scale_x = core->vars->greed.x_max - core->vars->greed.x_min;
	core->vars->greed.scale_y = core->vars->greed.y_max - core->vars->greed.y_min;

	double scale = fmin(core->vars->width / core->vars->greed.scale_x,
		core->vars->height / core->vars->greed.scale_y);
	core->vars->scale_w = scale;
	core->vars->scale_h = scale;
}

void	arrow(int key, t_controller* core)
{
	double step_x = (core->vars->greed.x_max - core->vars->greed.x_min) * 0.05;
	double step_y = (core->vars->greed.y_max - core->vars->greed.y_min) * 0.05;

	if (key == 65361)
		move(-step_x, 0, core->vars);
	else if (key == 65363)
		move(step_x, 0, core->vars);
	else if (key == 65362)
		move(0, step_y, core->vars);
	else if (key == 65364)
		move(0, -step_y, core->vars);
}

void	move(double dx, double dy, t_vars *vars)
{
    vars->greed.x_min += dx;
    vars->greed.x_max += dx;
    vars->greed.y_min += dy;
    vars->greed.y_max += dy;
}
