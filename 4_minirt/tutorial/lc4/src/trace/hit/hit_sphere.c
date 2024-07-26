#include "structures.h"
#include "utils.h"

t_bool hit_sphere(t_sphere *sp, t_ray *ray)
{
	t_vec3 oc;
	double a;
	double b;

	oc = vminus(ray->orig, sp->center);
	a = pow(vdot(ray->dir, oc), 2) + sp->radius2;
	b = vdot(oc, oc);
	if (a < b)
		return (TRUE);
	return (FALSE);
}
