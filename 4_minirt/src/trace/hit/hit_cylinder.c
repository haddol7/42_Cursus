#include "libft.h"
#include "structures.h"
#include "utils.h"
#include "trace.h"

void	debug(char *str, t_vec3 vec)
{
	dprintf(2, "%s -> %f %f %f\n", str, vec.x, vec.y, vec.z);
}

t_discriminant cal_discriminant(t_cylinder *cy, t_ray *ray)
{
	t_discriminant dis;
	t_point3		oc;

	ft_memset(&dis, 0, sizeof(t_discriminant));
	oc = vminus(ray->orig, cy->center);
	dis.a = vdot(ray->dir, ray->dir) - (vdot(ray->dir, cy->normal) * vdot(ray->dir, cy->normal));
	dis.half_b = vdot(ray->dir, oc) - vdot(ray->dir, cy->normal) * vdot(oc, cy->normal);
	dis.c = vdot(oc, oc) - (vdot(oc, cy->normal) * vdot(oc, cy->normal)) - cy->radius2;
	dis.discriminant = (dis.half_b * dis.half_b )- (dis.a * dis.c);
	if (dis.discriminant >= 0)
		dis.sqrtd = sqrt(dis.discriminant);
	return (dis);
}

t_bool is_root_valid(t_hit_record *rec, t_ray *ray, t_object *cy_obj, double root)
{//TODO ㅅㅐㅇ가ㄱ해보니까 height가 -이면 안되는 조건도 파싱에 포함해야..]
//TODO 파싱에서 파일 확장자도 확인
	double  dot_len;
	t_cylinder  *cy;
	t_hit_record temp_rec;

	cy = cy_obj->element;
	temp_rec = *rec;
	temp_rec.t = root;
	temp_rec.p = ray_at(ray, root);
	dot_len = vdot(vminus(temp_rec.p, cy->center), cy->normal);
	if (dot_len >= 0 && dot_len <= cy->height)
	{
		temp_rec.normal = vunit(vminus(vminus(temp_rec.p, cy->center), vmult(cy->normal, dot_len)));
		set_face_normal(ray, &temp_rec);
		temp_rec.albedo = cy_obj->albedo;
		*rec = temp_rec;
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	t_cylinder *cy;
	t_discriminant  dis;
	double  root[2];
	
	cy = cy_obj->element;
	cy->normal = vunit(cy->normal);
	dis = cal_discriminant(cy, ray);
	if (dis.discriminant < 0)
		return (FALSE);
	root[0] = ((-dis.half_b) - dis.sqrtd) / dis.a;
	root[1] = ((-dis.half_b) + dis.sqrtd) / dis.a;
	if ((root[0] < rec->tmin || root[0] > rec->tmax) && \
			(root[1] < rec->tmin || root[1] > rec->tmax))
		return (FALSE);
	if (is_root_valid(rec, ray, cy_obj, root[0]) == TRUE)
		return (TRUE);
	else if (is_root_valid(rec, ray, cy_obj, root[1]) == TRUE)
		return (TRUE);
	else
		return (FALSE);
}

// t_bool	hit_cylinder_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_cylinder	*cy;
// 	t_vec3			circle_center;
// 	double			root;

// 	cy = cy_obj->element;
// 	// circle_center = 
// 	root = vdot(vminus(cy->center, ray->orig), cy->)
// }
