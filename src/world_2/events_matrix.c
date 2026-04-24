#include "../../include/fonction_math.h"

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
	else if (key == 112)
	{
		core->vars->matrice.scale.scaleZ += 0.1;
		init_mat_scale(&(core->vars->matrice.mat_scale), core->vars->matrice.scale.scaleXY, core->vars->matrice.scale.scaleXY, core->vars->matrice.scale.scaleZ);
		build_matrix_world(&(core->vars->matrice));
	}
	else if (key == 109)
	{
		core->vars->matrice.scale.scaleZ -= 0.1;
		init_mat_scale(&(core->vars->matrice.mat_scale), core->vars->matrice.scale.scaleXY, core->vars->matrice.scale.scaleXY, core->vars->matrice.scale.scaleZ);
		build_matrix_world(&(core->vars->matrice));
	}
	if (core->vars->matrice.mode == 1)
		init_projection_ortho(&(core->vars->matrice.mat_projection), -10, 10, -10, 10, 0.1, 100);
	else
		init_project_perspective(&(core->vars->matrice.mat_projection), M_PI / 3, (double)WIDTH / HEIGHT, 1000.0, 0.1);
}
