#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

t_bool hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
	t_plane *pl;
	t_vec3  oc;
	double  root;

	pl = pl_obj->element;
	oc = pl->center;
	root = (vdot(oc, pl->normal) - vdot(ray->orig, pl->normal)) / vdot(ray->dir, pl->normal);
	if (root < 0)
		return (FALSE);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = pl->normal;
	set_face_normal(ray, rec);
	rec->albedo = pl_obj->albedo;
	if (rec->t < rec->tmin || rec->t > rec->tmax)
		return (FALSE);
	return (TRUE);
}