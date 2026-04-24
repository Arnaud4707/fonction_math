#include "../../include/fonction_math.h"

void	draw_triangle_gouraud(t_vertex v0, t_vertex v1, t_vertex v2, int color, t_controller *core)
{
	unsigned int	*buff;
	double			area;
	int				minX;
	int				maxX;
	int				minY;
	int				maxY;

	buff = (unsigned int *)core->vars->img->addr;

	area = edge(v0.screen, v1.screen, v2.screen);
	if (area == 0.0)
		return;

	minX = fmax(0, floor(fmin(v0.screen.x, fmin(v1.screen.x, v2.screen.x))));
	maxX = fmin(WIDTH - 1, ceil(fmax(v0.screen.x, fmax(v1.screen.x, v2.screen.x))));
	minY = fmax(0, floor(fmin(v0.screen.y, fmin(v1.screen.y, v2.screen.y))));
	maxY = fmin(HEIGHT - 1, ceil(fmax(v0.screen.y, fmax(v1.screen.y, v2.screen.y))));

	if (minX > maxX || minY > maxY)
    	return;

	for (int y = minY; y <= maxY; y++)
	{
		unsigned int *row = buff + y * WIDTH;

		for (int x = minX; x <= maxX; x++)
		{
			t_vect	p = {x + 0.5, y + 0.5, 0, 1};
			double	w0 = edge(v1.screen, v2.screen, p);
			double	w1 = edge(v2.screen, v0.screen, p);
			double	w2 = edge(v0.screen, v1.screen, p);

			if (!((w0 >= 0 && w1 >= 0 && w2 >= 0 && area > 0) ||
				  (w0 <= 0 && w1 <= 0 && w2 <= 0 && area < 0)))
				continue;

			w0 /= area;
			w1 /= area;
			w2 /= area;

			double inv_w =
				w0 * v0.inv_w +
				w1 * v1.inv_w +
				w2 * v2.inv_w;

			if (inv_w <= 0.0000001)
				continue;

			double depth =
				(w0 * v0.depth * v0.inv_w +
				 w1 * v1.depth * v1.inv_w +
				 w2 * v2.depth * v2.inv_w) / inv_w;

			if (depth < core->vars->matrice.zbuffer[y][x])
			{
				core->vars->matrice.zbuffer[y][x] = depth;

				double intensity =
					(w0 * v0.intensity * v0.inv_w +
					 w1 * v1.intensity * v1.inv_w +
					 w2 * v2.intensity * v2.inv_w) / inv_w;

				row[x] = apply_shading(color, intensity);
			}
		}
	}
}

void	draw_triangle_flat(t_vertex v0, t_vertex v1, t_vertex v2, int color, t_controller *core)
{
	unsigned int	*buff;
	double			area;
	int				minX;
	int				maxX;
	int				minY;
	int				maxY;

	buff = (unsigned int *)core->vars->img->addr;

	area = edge(v0.screen, v1.screen, v2.screen);
	if (area == 0.0)
		return;

	minX = fmax(0, floor(fmin(v0.screen.x, fmin(v1.screen.x, v2.screen.x))));
	maxX = fmin(WIDTH - 1, ceil(fmax(v0.screen.x, fmax(v1.screen.x, v2.screen.x))));
	minY = fmax(0, floor(fmin(v0.screen.y, fmin(v1.screen.y, v2.screen.y))));
	maxY = fmin(HEIGHT - 1, ceil(fmax(v0.screen.y, fmax(v1.screen.y, v2.screen.y))));

	if (minX > maxX || minY > maxY)
    	return;

	for (int y = minY; y <= maxY; y++)
	{
		unsigned int *row = buff + y * WIDTH;

		for (int x = minX; x <= maxX; x++)
		{
			t_vect	p = {x + 0.5, y + 0.5, 0, 1};
			double	w0 = edge(v1.screen, v2.screen, p);
			double	w1 = edge(v2.screen, v0.screen, p);
			double	w2 = edge(v0.screen, v1.screen, p);

			if (!((w0 >= 0 && w1 >= 0 && w2 >= 0 && area > 0) ||
				  (w0 <= 0 && w1 <= 0 && w2 <= 0 && area < 0)))
				continue;

			w0 /= area;
			w1 /= area;
			w2 /= area;

			double inv_w =
				w0 * v0.inv_w +
				w1 * v1.inv_w +
				w2 * v2.inv_w;

			if (inv_w <= 0.0001)
				continue;

			double depth =
				(w0 * v0.depth * v0.inv_w +
				 w1 * v1.depth * v1.inv_w +
				 w2 * v2.depth * v2.inv_w) / inv_w;

			if (depth < core->vars->matrice.zbuffer[y][x])
			{
				core->vars->matrice.zbuffer[y][x] = depth;

				double intensity =
					(w0 * v0.intensity * v0.inv_w +
					 w1 * v1.intensity * v1.inv_w +
					 w2 * v2.intensity * v2.inv_w) / inv_w;

				row[x] = apply_shading(color, intensity);
			}
		}
	}
}

void	display_cube_triangles(t_controller *core, t_vect object[8], int color[6])
{
	int triangles[12][3] = {
		{0, 3, 2}, {0, 2, 1},
		{5, 6, 7}, {5, 7, 4},
		{4, 7, 3}, {4, 3, 0},
		{1, 2, 6}, {1, 6, 5},
		{3, 7, 6}, {3, 6, 2},
		{4, 0, 1}, {4, 1, 5}
	};

	t_vertex	vtx[8];
	t_vect		view_pos[8];
	t_vect		normals[8];
	t_vect		light;

	for (int i = 0; i < 8; i++)
		normals[i] = (t_vect){0, 0, 0, 0};

	light = normalize((t_vect){-1, 1, 1, 0});

	for (int i = 0; i < 8; i++)
	{
		t_vect v;

		v = mul_mat_vect(&core->vars->matrice.mat_world, object[i]);
		v = mul_mat_vect(&core->vars->matrice.mat_view, v);

		view_pos[i] = v;
		vtx[i].depth = -v.z;

		v = mul_mat_vect(&core->vars->matrice.mat_projection, v);
		vtx[i].inv_w = 1.0 / v.w;

		v.x *= vtx[i].inv_w;
		v.y *= vtx[i].inv_w;
		v.z *= vtx[i].inv_w;

		ndc_screen_point(&vtx[i].screen, v, HEIGHT, WIDTH);
	}

	// norme des sommets
	for (int i = 0; i < 12; i++)
	{
		int a = triangles[i][0];
		int b = triangles[i][1];
		int c = triangles[i][2];

		t_vect p0 = view_pos[a];
		t_vect p1 = view_pos[b];
		t_vect p2 = view_pos[c];

		t_vect face_n = normalize(cross(sub(p1, p0), sub(p2, p0)));

		normals[a] = add(normals[a], face_n);
		normals[b] = add(normals[b], face_n);
		normals[c] = add(normals[c], face_n);
	}

	for (int i = 0; i < 8; i++)
		normals[i] = normalize(normals[i]);

	for (int i = 0; i < 8; i++)
	{
		vtx[i].normal = normals[i];
		vtx[i].intensity = fmax(0.0, dot(normals[i], light));
	}

	// rasterisation + back face
	for (int i = 0; i < 12; i++)
	{
		int a = triangles[i][0];
		int b = triangles[i][1];
		int c = triangles[i][2];

		t_vertex v0 = vtx[a];
		t_vertex v1 = vtx[b];
		t_vertex v2 = vtx[c];

		if (v0.inv_w <= 0 || v1.inv_w <= 0 || v2.inv_w <= 0)
    		continue;
		if (v0.depth <= 0 || v1.depth <= 0 || v2.depth <= 0)
    		continue;
			
		// culling
		t_vect face_n;
		{
			t_vect e1 = sub(view_pos[b], view_pos[a]);
			t_vect e2 = sub(view_pos[c], view_pos[a]);
			face_n = cross(e1, e2);

			if (face_n.z <= 1e-10)
				continue;
		}
		face_n = normalize(face_n);
		double intensity = fmax(0.0, dot(face_n, light));
		int shaded = apply_shading(color[i / 2], intensity);
		draw_triangle_gouraud(v0, v1, v2, shaded, core);
	}
}