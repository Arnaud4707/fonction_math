#ifndef	MATRICE_H
#define	MATRICE_H

#include	"struct_fonction.h"
#define SCALE_XY 1
#define SCALE_Z 1
typedef	struct	s_maps	t_maps;
struct	s_maps
{
	char *line;
	t_maps *next;
};

t_maps	*init_maps(char *file);
void	free_maps(t_maps *map);
void	display_cube(t_controller *core, t_vect object[8], int color[12]);
void	change_param_matrice(int key, t_controller* core);
void	init_matrice(t_matrice* matrice);
void	init_mat_identite(t_mat *mat);
void	init_mat_scale(t_mat* mat, double scaleX, double scaleY, double scaleZ);
void	init_mat_rotate_x(t_mat *m, double a);
void	init_mat_rotate_y(t_mat *m, double a);
void	init_mat_rotate_z(t_mat *m, double a);
void	init_projection_ortho(t_mat *m, double left, double right, double bottom,double top, double near, double far);
void	init_project_perspective(t_mat *m, double fov, double aspect, double far, double near);
void	build_matrix_view_look_at(t_mat *m, t_vect eye, t_vect target, t_vect up);
void	build_matrix_view_fps(t_mat *view, t_camera *cam);
void	init_projection_ortho(t_mat *m, double left, double right, double bottom,double top, double near, double far);
void	build_matrix_world(t_matrice *m);
void	move_forward_fps(t_camera* cam, double speed);
void	move_right_fps(t_camera* cam, double speed);
void	move_up(t_camera* cam, double speed);
void	rotate_fps(t_camera *cam, double dx, double dy);
int		event_mouse_move_matrix_rotation(int x, int y, void* core_);
t_vect	add(t_vect a, t_vect b);
t_vect	mul(t_vect v, double s);
t_vect	mul_mat_vect(t_mat *mat, t_vect v);
t_mat	mul_mat_mat(t_mat *a, t_mat *b);
t_vect	get_forward(double pitch, double yaw);
t_vect	get_right(t_vect forward);
void	init_mat_translation(t_mat *m, double x, double y, double z);
int		render_loop_matrice(void* core_);
int		apply_shading(int color, double intensity);

static inline double edge(t_vect a, t_vect b, t_vect c)
{
	return (c.x - a.x)*(b.y - a.y) - (c.y - a.y)*(b.x - a.x);
}

static inline void draw_triangle(t_vect v0, t_vect v1, t_vect v2, int color, t_controller *core)
{
	unsigned int* buff = (unsigned int*)(core->vars->img->addr);

	double area = edge(v0, v1, v2);
	if (area == 0) return; // triangle dégénéré

	int minX = fmax(0, floor(fmin(v0.x, fmin(v1.x, v2.x))));
	int maxX = fmin(WIDTH-1, ceil(fmax(v0.x, fmax(v1.x, v2.x))));
	int minY = fmax(0, floor(fmin(v0.y, fmin(v1.y, v2.y))));
	int maxY = fmin(HEIGHT-1, ceil(fmax(v0.y, fmax(v1.y, v2.y))));

	for (int y = minY; y <= maxY; y++)
	{
		for (int x = minX; x <= maxX; x++)
		{
			t_vect p = {x + 0.5, y + 0.5, 0, 1};

			double w0 = edge(v1, v2, p);
			double w1 = edge(v2, v0, p);
			double w2 = edge(v0, v1, p);

			// test inside robuste
			if ((w0 >= 0 && w1 >= 0 && w2 >= 0 && area > 0) ||
				(w0 <= 0 && w1 <= 0 && w2 <= 0 && area < 0))
			{
				// normalisation barycentrique
				w0 /= area;
				w1 /= area;
				w2 /= area;

				// interpolation profondeur
				double w_inv = w0*v0.w + w1*v1.w + w2*v2.w; // Interpolation de 1/W
				double z = 1.0 / w_inv;

				if ( z < core->vars->matrice.zbuffer[y][x])
				{
					core->vars->matrice.zbuffer[y][x] = z;
					buff[y * WIDTH + x] = color;
				}
			}
		}
	}
}

#endif