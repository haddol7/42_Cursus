#include "../../inc/map.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

t_point3	check_coordinate(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	if (split[3] != NULL)
		error_exit("check_coordinate\n");
	free_split(split);
	return (point3(x, y, z));
}

t_vec3	check_normalize_vector(char *coor)
{
	double	x;
	double	y;
	double	z;
	char	**split;

	split = ft_split(coor, ',');
	x = ft_atof(split[0]);
	y = ft_atof(split[1]);
	z = ft_atof(split[2]);
	if (split[3] != NULL)
		error_exit("check_normalize vector\n");
	free_split(split);
	return (vec3(x, y, z));
}

t_color3	check_color(char *color)
{
	double	r;
	double	g;
	double	b;
	char	**split;

	split = ft_split(color, ',');
	// printf("%s %s %s\n", split[0], split[1], split[2]);
	r = ft_atof(split[0]);
	g = ft_atof(split[1]);
	b = ft_atof(split[2]);
	if (split[3] != NULL)
		error_exit("check_color\n");
	free_split(split);
	return (color3(r, g, b));
}

t_object	*is_valid_sp(char **split)
{
	t_point3	center;
	t_color3	color;
	double		radius;

	center = check_coordinate(split[1]);
	radius = ft_atof(split[2]);
	color = check_color(split[3]);
	if (split[4] != NULL)
		error_exit("check_is_valid_sp\n");
		//TODO 이미지 파일 검증 추가
	return (object(SP, sphere(center, radius), color));
}

t_object	*is_valid_cy(char **split)
{
	t_point3	center;
	t_vec3		normalize;
	double		radius;
	double		height;
	t_color3	color;

	center = check_coordinate(split[1]);
	normalize = check_normalize_vector(split[2]);
	radius = ft_atof(split[3]);
	height = ft_atof(split[4]);
	color = check_color(split[5]);
	if (split[6] != NULL)
		error_exit("is_valid_cy\n");
				//TODO 이미지 파일 검증 추가
	return (object(CY, cylinder(center, normalize, radius, height), color));
}

t_object	*is_valid_pl(char **split)
{
	t_point3	center;
	t_vec3		normalize;
	t_color3	color;

	center = check_coordinate(split[1]);
	normalize = check_normalize_vector(split[2]);
	color = check_color(split[3]);
	if (split[4] != NULL)
		error_exit("is_valid_pl\n");
				//TODO 이미지 파일 검증 추가
	return (object(PL, plane(center, normalize), color));
}

t_object	*is_valid_A(char **split, t_scene *scene)
{
	static int	count = 0;
	
	scene->ka = ft_atof(split[1]);
	scene->ambient = vmult(check_color(split[2]), scene->ka);
	if (split[3] != NULL || count != 0)
		error_exit("is_valid_A\n");
	count++;
	return (0);
}

t_object	*is_valid_C(char **split, t_scene *scene)
{
	static int	count = 0;
	double		theta;
	double      viewport_height;

	scene->camera.lookfrom = check_coordinate(split[1]);
	scene->camera.w = check_normalize_vector(split[2]);
	scene->camera.vfov = ft_atof(split[3]);
	scene->camera.lookat = point3(0, 0, 0);
	scene->camera.vup = vec3(0, 1, 0);
    scene->camera.focal_len = 1;
	theta = scene->camera.vfov * (3.141592) / 180;
    viewport_height = tan(theta / 2) * 2 * scene->camera.focal_len;
    scene->camera.viewport_w = viewport_height * scene->canvas.aspect_ratio;
    scene->camera.viewport_h = viewport_height;
	scene->camera.u = vunit(vcross(scene->camera.vup, scene->camera.w));
	scene->camera.v = vcross(scene->camera.w, scene->camera.u);
    scene->camera.orig = scene->camera.lookfrom;
    scene->camera.horizontal = vmult(scene->camera.u, scene->camera.viewport_w);
    scene->camera.vertical = vmult(scene->camera.v, scene->camera.viewport_h);
	scene->camera.left_bottom = vminus(vminus(scene->camera.orig, vmult(scene->camera.w, scene->camera.focal_len)), vplus(vdivide(scene->camera.vertical, 2), vdivide(scene->camera.horizontal, 2)));
	scene->camera.samples_per_pixel = ANTI_SAMPLE;
	if (split[4] != NULL || count != 0)
		error_exit("is_valild_c\n");
	count++;
	return (0);
}

t_object	*is_valid_L(char **split, t_scene *scene)
{
	static int	count = 0;
	t_point3	point;
	t_color3	color;
	double		ratio;
	t_object	*light;

	point = check_coordinate(split[1]);
	ratio = ft_atof(split[2]);
	color = check_color(split[3]);
	if (split[4] != NULL || count != 0)
		error_exit("is_valid_L\n");//TODO 흠.. 라이트는 하나??
	light = object(LIGHT_POINT, light_point(point, color, ratio), color);
	scene->light = light;
	return (0);
}
