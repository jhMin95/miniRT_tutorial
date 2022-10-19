#include "../../../include/trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

    ray.orig = orig;
    ray.dir = vunit(dir);
    return (ray);
}

//ray origin point 부터 방향벡터 ray dir * t 만큼 떨어진 점.
t_point3    ray_at(t_ray *ray, double t)
{
    t_point3 at;

    at = vplus(ray->orig, vmult(ray->dir, t));
    return (at);
}

t_ray	ray_primary(t_camera *cam, double u,  double v)
{
	t_ray	ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	
	return (ray);
}

t_color3	ray_color(t_ray	*r)
{
	double	t;

	t = 0.5 * (r->dir.y + 1.0);
	return (vplus(vmult(new_color3(1, 1, 1), 1.0 - t), vmult(new_color3(0.5, 0.7, 1.0), t)));
}

t_color3	ray_spere_color(t_ray *ray, t_sphere *sphere)
{
	if (hit_sphere(sphere, ray))
		return (new_color3(0, 0, 1));
	else
		return (ray_color(ray));
}