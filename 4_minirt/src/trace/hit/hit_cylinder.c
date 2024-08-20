#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

void	debug(char *str, t_vec3 vec)
{
	dprintf(2, "%s -> %f %f %f\n", str, vec.x, vec.y, vec.z);
}

t_discriminant cal_discriminant(t_vec3 oc, t_cylinder *cy, t_ray *ray)
{
	t_discriminant dis;

	dis.a = vlength2(ray->dir) - pow(ray->dir.y, 2);
	dis.half_b = vdot(oc, ray->dir) - oc.y * ray->dir.y;
	dis.c = vlength2(oc) - pow(oc.y, 2) - cy->radius2;
	dis.discriminant = dis.half_b * dis.half_b - dis.a * dis.c;
	dis.sqrtd = sqrt(dis.discriminant);
	return (dis);
}

t_bool is_root_valid(t_hit_record *rec, t_ray *ray, t_object *cy_obj, double root)
{
	double  dot_len;
	t_cylinder  *cy;

	cy = cy_obj->element;
	rec->p = ray_at(ray, root);
	dot_len = vdot(vminus(rec->p, cy->center), cy->normal);
	if (dot_len >= 0 && dot_len <= cy->height / 2)
	{
		rec->t = root;
		rec->normal = vunit(vminus(vminus(rec->p, cy->center), vmult(cy->normal, dot_len)));
		set_face_normal(ray, rec);
		rec->albedo = cy_obj->albedo;
		//debug("albedo",rec->albedo);
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_vec3  oc;
	t_cylinder *cy;
	t_discriminant  dis;
	double  root[2];
	
	cy = cy_obj->element;
	oc = vminus(ray->orig, cy->center);

	dis = cal_discriminant(oc, cy, ray);
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = (-dis.half_b - dis.sqrtd) / dis.a;
	root[1] = (-dis.half_b + dis.sqrtd) / dis.a;
	if (is_root_valid(rec, ray, cy_obj, root[0]) == TRUE)
	{
		if (is_root_valid(rec, ray, cy_obj, root[1]) == TRUE)
			return (TRUE);
	}
	// else if (is_root_valid(rec, ray, cy_obj, root[1]) == TRUE)
	// 	return (TRUE);
	else
		return (FALSE);
	return (FALSE);
}
