#include "trace.h"

t_ray	ray(t_point3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = vunit(dir);
	return (ray);
}

t_point3 ray_at(t_ray *ray, double t)
{
	t_point3	at;

	at = vplus(ray->orig, vmult(ray->dir, t));
	return (at);
}

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray ray;

	ray.orig = cam->orig;
	ray.dir = vunit(vminus(vplus(vplus(cam->left_bottom, vmult(cam->horizontal, u)), vmult(cam->vertical, v)), cam->orig));
	return (ray);
}

t_hit_record record_init(void)
{
	t_hit_record record;

	record.tmin = EPSILON;
	record.tmax = INFINITY;
	return (record);
}

t_color3    ray_color(t_scene *scene, t_color3 color)
{
    double	t;
	
    scene->rec = record_init();
    if (hit(scene->world, &scene->ray, &scene->rec))
        return (vplus(phong_lighting(scene), color));
    else
    {
        t = 0.5 * (scene->ray.dir.y + 1.0);
        return (vplus(vplus(vmult(color3(1, 1, 1), 1.0 - t), vmult(color3(0.5, 0.7, 1.0), t)), color));
    }
}

t_vec3	sample_square(void)
{
	return (vec3(random_double() - 0.5, random_double() - 0.5, 0));
}

