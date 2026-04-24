#ifndef	MATRICE_H
#define	MATRICE_H

#include	"struct_fonction.h"
#define SCALE_XY 1
#define SCALE_Z 1

void	display_cube(t_controller *core, t_vect object[8], int color[6]);
void	display_fdf(t_controller *core);
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
void	build_projection_isometrique(t_matrice *m);
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
void	display_cube_triangles(t_controller *core, t_vect object[8], int color[6]);
void	ndc_screen_point(t_vect* d, t_vect s, int h, int w);
void	draw_triangle_flat(t_vertex v0, t_vertex v1, t_vertex v2, int color, t_controller *core);
void	render_skybox(t_controller *core);
int     **parse_fdf(const char *filename, int *out_rows, int *out_cols);

static	inline	void	projection_iso(t_mat* transfo, t_vect* coord, t_screen_point* proj)
{
	proj->x = transfo->mat[0][0] * coord->x + transfo->mat[0][1] * coord->y + transfo->mat[0][2] * coord->z;
	proj->y = transfo->mat[1][0] * coord->x + transfo->mat[1][1] * coord->y + transfo->mat[1][2] * coord->z;
}

#endif