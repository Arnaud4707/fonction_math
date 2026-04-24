#include "../../include/fonction_math.h"

static int	clamp_int(int v, int min, int max)
{
	if (v < min)
		return (min);
	if (v > max)
		return (max);
	return (v);
}

static int	rgb(int r, int g, int b)
{
	r = clamp_int(r, 0, 255);
	g = clamp_int(g, 0, 255);
	b = clamp_int(b, 0, 255);
	return ((r << 16) | (g << 8) | b);
}

static int	lerp_color(int c1, int c2, double t)
{
	int r1 = (c1 >> 16) & 0xFF;
	int g1 = (c1 >> 8) & 0xFF;
	int b1 = c1 & 0xFF;

	int r2 = (c2 >> 16) & 0xFF;
	int g2 = (c2 >> 8) & 0xFF;
	int b2 = c2 & 0xFF;

	int r = (int)(r1 + (r2 - r1) * t);
	int g = (int)(g1 + (g2 - g1) * t);
	int b = (int)(b1 + (b2 - b1) * t);

	return (rgb(r, g, b));
}

static int	sample_skybox(t_vect dir)
{
	double	ax;
	double	ay;
	double	az;
	double	t;

	ax = fabs(dir.x);
	ay = fabs(dir.y);
	az = fabs(dir.z);

	/*
	 * Sky simple :
	 * - haut : bleu clair -> bleu profond
	 * - bas : sol sombre
	 * - côtés : teintes de ciel
	 */
	if (ay >= ax && ay >= az)
	{
		if (dir.y > 0.0)
		{
			t = dir.y;
			return (lerp_color(rgb(135, 206, 235), rgb(20, 60, 170), t));
		}
		else
		{
			t = -dir.y;
			return (lerp_color(rgb(40, 50, 60), rgb(10, 10, 20), t));
		}
	}
	else if (ax >= ay && ax >= az)
	{
		if (dir.x > 0.0)
			return (lerp_color(rgb(80, 140, 220), rgb(140, 200, 255), 0.4));
		else
			return (lerp_color(rgb(60, 120, 210), rgb(120, 180, 255), 0.4));
	}
	else
	{
		if (dir.z > 0.0)
			return (lerp_color(rgb(90, 160, 235), rgb(150, 210, 255), 0.5));
		else
			return (lerp_color(rgb(70, 130, 220), rgb(140, 190, 255), 0.5));
	}
}

void	render_skybox(t_controller *core)
{
	unsigned int	*buff;
	t_camera		*cam;
	t_vect			forward;
	t_vect			world_up;
	t_vect			right;
	t_vect			up;
	double			aspect;
	double			tan_half_fov;
	int				x;
	int				y;

	buff = (unsigned int *)core->vars->img->addr;
	cam = &core->vars->matrice.cam;

	/*
	 * Base caméra
	 * forward = direction de la caméra
	 * right + up = base orthonormée caméra
	 */
	forward = get_forward(cam->pitch, cam->yaw);
	world_up = (t_vect){0, 1, 0, 0};
	right = normalize(cross(world_up, forward));
	up = normalize(cross(forward, right));

	aspect = (double)WIDTH / (double)HEIGHT;
	tan_half_fov = tan(M_PI / 6.0); // 60° de FOV

	for (y = 0; y < HEIGHT; y++)
	{
		unsigned int *row = buff + y * WIDTH;

		for (x = 0; x < WIDTH; x++)
		{
			double ndc_x;
			double ndc_y;
			t_vect ray_cam;
			t_vect ray_world;

			/*
			 * Pixel -> rayon dans l'espace caméra
			 * caméra regarde vers -Z
			 */
			ndc_x = (2.0 * ((double)x + 0.5) / (double)WIDTH - 1.0);
			ndc_y = (1.0 - 2.0 * ((double)y + 0.5) / (double)HEIGHT);

			ray_cam.x = ndc_x * aspect * tan_half_fov;
			ray_cam.y = ndc_y * tan_half_fov;
			ray_cam.z = -1.0;
			ray_cam.w = 0.0;

			/*
			 * Camera space -> world space
			 * world = right * x + up * y + forward * (-z)
			 */
			ray_world.x = right.x * ray_cam.x + up.x * ray_cam.y + forward.x * (-ray_cam.z);
			ray_world.y = right.y * ray_cam.x + up.y * ray_cam.y + forward.y * (-ray_cam.z);
			ray_world.z = right.z * ray_cam.x + up.z * ray_cam.y + forward.z * (-ray_cam.z);
			ray_world.w = 0.0;

			ray_world = normalize(ray_world);
			row[x] = sample_skybox(ray_world);
		}
	}
}