#ifndef MATRICE_FONCTION
#define MATRICE_FONCTION

#include "matrice.h"


static inline t_vect	sub(t_vect a, t_vect b)
{
	t_vect r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	r.w = 0;
	return (r);
}

static inline t_vect	cross(t_vect a, t_vect b)
{
	t_vect r;

	r.x = a.y * b.z - a.z * b.y;
	r.y = a.z * b.x - a.x * b.z;
	r.z = a.x * b.y - a.y * b.x;
	r.w = 0;
	return (r);
}

static inline t_vect	normalize(t_vect v)
{
	double len;
	t_vect r;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (len == 0)
		return (v);
	r.x = v.x / len;
	r.y = v.y / len;
	r.z = v.z / len;
	r.w = 0;
	return (r);
}

static inline double	dot(t_vect a, t_vect b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

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
        unsigned int *row = buff + y * WIDTH;
		for (int x = minX; x <= maxX; x++)
		{
			t_vect p = {x + 0.5, y + 0.5, 0, 1};
			double w0 = edge(v1, v2, p);
			double w1 = edge(v2, v0, p);
			double w2 = edge(v0, v1, p);

			// lecturen dans les 2 sens 
			if ((w0 >= 0 && w1 >= 0 && w2 >= 0 && area > 0)
				|| (w0 <= 0 && w1 <= 0 && w2 <= 0 && area < 0)) { // normalisation barycentrique 

				w0 /= area;
				w1 /= area;
				w2 /= area; // interpolation profondeur 
				double w_inv = w0*v0.w + w1*v1.w + w2*v2.w; // Interpolation de 1/W 
				double z = 1.0 / w_inv;

				if ( z < core->vars->matrice.zbuffer[y][x])
				{
					core->vars->matrice.zbuffer[y][x] = z;
					row[x] = color;
				}
			}
		}
	}
}

static inline double	rasterazer(t_vect v0, t_vect v1, t_vect v2)
{
	t_vect line1 = sub(v1, v0); // calcul de la normale
	t_vect line2 = sub(v2, v0);
	t_vect normal = normalize(cross(line1, line2));

	t_vect light_dir = {1, 1, -1, 1}; // direction de la lumière
	light_dir = normalize(light_dir);

	return (dot(normal, light_dir)); // produit scalaire pour l'intensité
}

#endif