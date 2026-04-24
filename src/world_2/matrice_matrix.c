#include "../../include/fonction_math.h"

void	build_projection_isometrique(t_matrice *m)
{
	t_mat tmp;

	tmp = mul_mat_mat(&(m->mat_rotateZ), &(m->mat_scale));
	tmp = mul_mat_mat(&(m->mat_rotateY), &tmp);
	m->mat_world = mul_mat_mat(&(m->mat_rotateX), &tmp);
}

void	init_mat_scale(t_mat *m, double scaleX, double scaleY, double scaleZ)
{
	init_mat_identite(m);
	m->mat[0][0] = scaleX;
	m->mat[1][1] = scaleY;
	m->mat[2][2] = scaleZ;
	m->mat[3][3] = 1.0;
}

void	init_mat_rotate_z(t_mat *m, double a)
{
	init_mat_identite(m);
	m->mat[0][0] = cos(a);
	m->mat[0][1] = -sin(a);
	m->mat[1][0] = sin(a);
	m->mat[1][1] = cos(a);
}

void	init_mat_rotate_y(t_mat *m, double a)
{
	init_mat_identite(m);
	m->mat[0][0] = cos(a);
	m->mat[0][2] = sin(a);
	m->mat[2][0] = -sin(a);
	m->mat[2][2] = cos(a);
}

void	init_mat_rotate_x(t_mat *m, double a)
{
	init_mat_identite(m);
	m->mat[1][1] = cos(a);
	m->mat[1][2] = -sin(a);
	m->mat[2][1] = sin(a);
	m->mat[2][2] = cos(a);
}

void	init_mat_translation(t_mat *m, double x, double y, double z)
{
	init_mat_identite(m);
	m->mat[0][3] = x;
	m->mat[1][3] = y;
	m->mat[2][3] = z;
}

void	build_matrix_world(t_matrice *m)
{
	t_mat tmp;

	tmp = mul_mat_mat(&(m->mat_scale), &(m->mat_rotateX));
	tmp = mul_mat_mat(&(m->mat_rotateY), &tmp);
	tmp = mul_mat_mat(&(m->mat_rotateZ), &tmp);
	m->mat_world = mul_mat_mat(&(m->mat_translation), &tmp);
}

void	init_project_perspective(t_mat *m, double fov, double aspect, double far, double near)
{
	init_mat_identite(m);
	m->mat[0][0] = 1.0 / (tan(fov / 2) * aspect);
	m->mat[1][1] = 1.0 / tan(fov / 2);
	m->mat[2][2] = (far + near) / (near - far);
	m->mat[2][3] = (2 * far * near) / (near - far);
	m->mat[3][2] = -1.0;
}

void	build_matrix_view_fps(t_mat *view, t_camera *cam)
{
	t_vect forward = get_forward(cam->pitch, cam->yaw);
	t_vect target = add(cam->position, forward);
	t_vect up = {0, 1, 0, 0};

	build_matrix_view_look_at(view, cam->position, target, up);
}

void	build_matrix_view_look_at(t_mat *m, t_vect eye, t_vect target, t_vect up)
{
	t_vect zaxis = normalize(sub(eye, target));
	t_vect xaxis = normalize(cross(up, zaxis));
	t_vect yaxis = cross(zaxis, xaxis);

	init_mat_identite(m);

	m->mat[0][0] = xaxis.x;
	m->mat[0][1] = xaxis.y;
	m->mat[0][2] = xaxis.z;

	m->mat[1][0] = yaxis.x;
	m->mat[1][1] = yaxis.y;
	m->mat[1][2] = yaxis.z;

	m->mat[2][0] = zaxis.x;
	m->mat[2][1] = zaxis.y;
	m->mat[2][2] = zaxis.z;

	m->mat[0][3] = -dot(xaxis, eye);
	m->mat[1][3] = -dot(yaxis, eye);
	m->mat[2][3] = -dot(zaxis, eye);
}

void	init_projection_ortho(t_mat *m, double left, double right, double bottom,double top, double near, double far)
{
	init_mat_identite(m);
	m->mat[0][0] = 2.0 / (right - left);
	m->mat[1][1] = 2.0 / (top - bottom);
	m->mat[2][2] = -2.0 / (far - near);
	m->mat[0][3] = -(right + left) / (right - left);
	m->mat[1][3] = -(top + bottom) / (top - bottom);
	m->mat[2][3] = -(far + near) / (far - near);
}

void	ndc_screen_point(t_vect* d, t_vect s, int h, int w)
{
	d->x = (s.x + 1) * 0.5 * w;
	d->y = (1 - s.y) * 0.5 * h;
}

t_vect	mul_mat_vect(t_mat *mat, t_vect v)
{
	t_vect r;

	r.x = mat->mat[0][0] * v.x + mat->mat[0][1] * v.y + mat->mat[0][2] * v.z + mat->mat[0][3] * v.w;
	r.y = mat->mat[1][0] * v.x + mat->mat[1][1] * v.y + mat->mat[1][2] * v.z + mat->mat[1][3] * v.w;
	r.z = mat->mat[2][0] * v.x + mat->mat[2][1] * v.y + mat->mat[2][2] * v.z + mat->mat[2][3] * v.w;
	r.w = mat->mat[3][0] * v.x + mat->mat[3][1] * v.y + mat->mat[3][2] * v.z + mat->mat[3][3] * v.w;
	return r;
}

t_mat	mul_mat_mat(t_mat *a, t_mat *b)
{
	t_mat tmp;
	int i;
	int j;
	int k;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			tmp.mat[i][j] = 0;
			for (k = 0; k < 4; k++)
			tmp.mat[i][j] += a->mat[i][k] * b->mat[k][j];
		}
	}
	return (tmp);
}

void	div_projection(t_vect *v, double w)
{
	v->x *= w;
    v->y *= w;
    v->z *= w;
    v->w = w;
}

t_vect get_forward(double pitch, double yaw)
{
	t_vect f;

	f.x = cos(pitch) * sin(yaw);
	f.y = sin(pitch);
	f.z = -cos(pitch) * cos(yaw);

	f.w = 0;
	return normalize(f);
}

t_vect	get_right(t_vect forward)
{
	t_vect up = {0, 1, 0, 0};
	return normalize(cross(forward, up));
}

void	move_forward_fps(t_camera* cam, double speed)
{
	t_vect forward = get_forward(cam->pitch, cam->yaw);
	cam->position = add(cam->position, mul(forward, speed));
}

void	move_right_fps(t_camera* cam, double speed)
{
	t_vect forward = get_forward(cam->pitch, cam->yaw);
	t_vect up = {0,1,0,0};
	t_vect right = normalize(cross(up, forward));

	cam->position = add(cam->position, mul(right, speed));
}

void	move_up(t_camera* cam, double speed)
{
	cam->position.y += speed;
}

void	rotate_fps(t_camera *cam, double dx, double dy)
{
	double sensitivity = 0.002;

	cam->yaw += dx * sensitivity;
	cam->pitch += dy * sensitivity;

	if (cam->pitch > M_PI / 2)
		cam->pitch = M_PI / 2;
	if (cam->pitch < -M_PI / 2)
		cam->pitch = -M_PI / 2;
}

t_vect	add(t_vect a, t_vect b)
{
	t_vect r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	r.w = 1;
	return (r);
}

t_vect	mul(t_vect v, double s)
{
	t_vect r;
	r.x = v.x * s;
	r.y = v.y * s;
	r.z = v.z * s;
	r.w = 0;
	return (r);
}

int apply_shading(int color, double intensity)
{
    if (intensity < 0.2) intensity = 0.2; // Lumière ambiante minimum
    if (intensity > 1.0) intensity = 1.0;

    int r = ((color >> 16) & 0xFF) * intensity;
    int g = ((color >> 8) & 0xFF) * intensity;
    int b = (color & 0xFF) * intensity;

    return (r << 16 | g << 8 | b);
}

void	display_fdf(t_controller *core)
{
	for (int j = 0; j < core->vars->matrice.fdf.height; j++){
		for (int i = 0; i < core->vars->matrice.fdf.width; i++){
			t_vect r;
			t_vect base;
			base.w = 1;
			base.x = i;
			base.y = j;
			base.z = core->vars->matrice.fdf.map[j][i];
			t_vect proj1; t_vect proj2; t_vect proj3;
			r = mul_mat_vect(&(core->vars->matrice.mat_world), base);
			r = mul_mat_vect(&(core->vars->matrice.mat_view), r);
			double w = r.w;
			r = mul_mat_vect(&(core->vars->matrice.mat_projection), r);
			div_projection(&(r), w);
			ndc_screen_point(&(proj1), r, HEIGHT, WIDTH);

			if (i < core->vars->matrice.fdf.width - 1)
			{
				r = base;
				r.x += 1;
				r.z = core->vars->matrice.fdf.map[j][i + 1];
				r = mul_mat_vect(&(core->vars->matrice.mat_world), r);
				r = mul_mat_vect(&(core->vars->matrice.mat_view), r);
				w = r.w;
				r = mul_mat_vect(&(core->vars->matrice.mat_projection), r);
				div_projection(&(r), w);
				ndc_screen_point(&(proj2), r, HEIGHT, WIDTH);
			}
			if (j < core->vars->matrice.fdf.height - 1)
			{
				r = base;
				r.y += 1;
				r.z = core->vars->matrice.fdf.map[j + 1][i];
				r = mul_mat_vect(&(core->vars->matrice.mat_world), r);
				r = mul_mat_vect(&(core->vars->matrice.mat_view), r);
				w = r.w;
				r = mul_mat_vect(&(core->vars->matrice.mat_projection), r);
				div_projection(&(r), w);
				ndc_screen_point(&(proj3), r, HEIGHT, WIDTH);
			}
			
			if (i < core->vars->matrice.fdf.width - 1 && proj1.x >= 0 && proj1.x < WIDTH && proj1.y >= 0 && proj1.y < HEIGHT && proj2.x >= 0 && proj2.x < WIDTH)
				drawLine(proj1.x, proj1.y, proj2.x, proj2.y, BLANC, core);
			if (j < core->vars->matrice.fdf.height - 1 && proj1.x >= 0 && proj1.x < WIDTH && proj1.y >= 0 && proj1.y < HEIGHT && proj3.y >= 0 && proj3.y < HEIGHT)
				drawLine(proj1.x, proj1.y, proj3.x, proj3.y, BLANC, core);
		}
	}
}