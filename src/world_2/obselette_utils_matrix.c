#include "../../include/fonction_math.h"


// void	init_matrix_view(t_mat *m, double cx, double cy, double cz)
// {
// 	init_mat_identite(m);
// 	m->mat[0][3] = -cx;
// 	m->mat[1][3] = -cy;
// 	m->mat[2][3] = -cz;
// }


// Pitch must be in the range of [-90 ... 90] degrees and 
// yaw must be in the range of [0 ... 360] degrees.
// Pitch and yaw variables must be expressed in radians.
// void	build_matrix_view_fps(t_mat *m, t_vect eye, double pitch, double yaw)
// {
// 	double	cosPitch = cos(pitch);
// 	double	sinPitch = sin(pitch);
// 	double	cosYaw = cos(yaw);
// 	double	sinYaw = sin(yaw);

// 	t_vect	xaxis = { cosYaw, 0, -sinYaw , 0};
// 	t_vect	yaxis = { sinYaw * sinPitch, cosPitch, cosYaw * sinPitch, 0};
// 	t_vect	zaxis = { sinYaw * cosPitch, -sinPitch, cosPitch * cosYaw, 0};

// 	init_mat_identite(m);

// 	m->mat[0][0] = xaxis.x;
// 	m->mat[0][1] = xaxis.y;
// 	m->mat[0][2] = xaxis.z;

// 	m->mat[1][0] = yaxis.x;
// 	m->mat[1][1] = yaxis.y;
// 	m->mat[1][2] = yaxis.z;

// 	m->mat[2][0] = zaxis.x;
// 	m->mat[2][1] = zaxis.y;
// 	m->mat[2][2] = zaxis.z;

// 	m->mat[0][3] = -dot(xaxis, eye);
// 	m->mat[1][3] = -dot(yaxis, eye);
// 	m->mat[2][3] = -dot(zaxis, eye);
// }


// void	move_forward(t_camera* cam, double speed)
// {
// 	t_vect forward = normalize(sub(cam->target, cam->position));
// 	cam->position = add(cam->position, mul(forward, speed));
// 	cam->target = add(cam->target, mul(forward, speed));	
// }

// void	move_right(t_camera* cam, double speed)
// {
// 	t_vect up = {0, 1, 0, 0};
// 	t_vect forward = normalize(sub(cam->target, cam->position));
// 	t_vect right = normalize(cross(up, forward));
// 	cam->position = add(cam->position, mul(right, speed));
// 	cam->target   = add(cam->target,   mul(right, speed));
// }



// void	rotate_camera(t_camera* cam, double angle)
// {
// 	t_vect dir = sub(cam->target, cam->position);

// 	double cosA = cos(angle);
// 	double sinA = sin(angle);

// 	double newX = dir.x * cosA - dir.z * sinA;
// 	double newZ = dir.x * sinA + dir.z * cosA;

// 	dir.x = newX;
// 	dir.z = newZ;

// 	cam->target = add(cam->position, dir);
// }


// void display_cube(t_controller *core, t_vect object[], int size)
// {
// 	int edges[12][2] = {
//     {0,1}, {1,2}, {2,3}, {3,0}, // face avant
//     {4,5}, {5,6}, {6,7}, {7,4}, // face arrière
//     {0,4}, {1,5}, {2,6}, {3,7}  // connexions
// 	};
// 	for (int i = 0; i < size; i++)
// 	{
// 		t_vect r;
// 		t_vect base = object[i];
// 		t_screen_point proj1; t_screen_point proj2; t_screen_point proj3;
// 		r = mul_mat_vect(&(core->vars->matrice.mat_world), base);
// 		r = mul_mat_vect(&(core->vars->matrice.mat_view), r);
// 		r = mul_mat_vect(&(core->vars->matrice.mat_projection), r);
// 		div_projection(&(r));
// 		ndc_screen_point(&(proj1), &(r), HEIGHT, WIDTH);

// 		if (i < (size - 1))
// 		{
// 			base = object[i];
// 			base.x += 1;
// 			base.z += 1;
// 			r = mul_mat_vect(&(core->vars->matrice.mat_world), base);
// 			r = mul_mat_vect(&(core->vars->matrice.mat_view), r);
// 			r = mul_mat_vect(&(core->vars->matrice.mat_projection), r);
// 			div_projection(&(r));
// 			ndc_screen_point(&(proj2), &(r), HEIGHT, WIDTH);
// 		}
// 		if (j < 2)
// 		{
// 			c = base;
// 			c.y += 1;
// 			c.z = test[j + 1][i];
// 			r = mul_mat_vect(&(core->vars->matrice.mat_world), &(c));
// 			r = mul_mat_vect(&(core->vars->matrice.mat_view), &(r));
// 			r = mul_mat_vect(&(core->vars->matrice.mat_projection), &(r));
// 			div_projection(&(r));
// 			ndc_screen_point(&(proj3), &(r), HEIGHT, WIDTH);
// 		}
		
// 		if (i < 2 && proj1.x >= 0 && proj1.x < WIDTH && proj1.y >= 0 && proj1.y < HEIGHT && proj2.x >= 0 && proj2.x < WIDTH)
// 			drawLine(proj1.x, proj1.y, proj2.x, proj2.y, BLANC, core);
// 		if (j < 2 && proj1.x >= 0 && proj1.x < WIDTH && proj1.y >= 0 && proj1.y < HEIGHT && proj3.y >= 0 && proj3.y < HEIGHT)
// 			drawLine(proj1.x, proj1.y, proj3.x, proj3.y, BLANC, core);
// 	}
// }

/*

void	display_cube(t_controller *core, t_vect object[8], int color, double zbuffer[HEIGHT][WIDTH])
{
	(void)zbuffer;
	int edges[12][2] = {
    {0,1}, {1,2}, {2,3}, {3,0}, // face avant
    {4,5}, {5,6}, {6,7}, {7,4}, // face arrière
    {0,4}, {1,5}, {2,6}, {3,7}  // connexions
	};
	t_vect projected[8];

	for (int i = 0; i < 8; i++)
	{
		projected[i] = mul_mat_vect(&(core->vars->matrice.mat_world), object[i]);
		projected[i] = mul_mat_vect(&(core->vars->matrice.mat_view), projected[i]);
		projected[i] = mul_mat_vect(&(core->vars->matrice.mat_projection), projected[i]);
		div_projection(&(projected[i]));
		ndc_screen_point(&(projected[i]), projected[i], HEIGHT, WIDTH);
	}
	for (int i = 0; i < 12; i++)
	{
		int a = edges[i][0];
		int b = edges[i][1];

		drawLine(projected[a].x, projected[a].y, projected[b].x, projected[b].y, color, core);
	}
}


*/