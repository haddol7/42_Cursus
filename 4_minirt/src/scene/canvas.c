#include "scene.h"

t_canvas canvas(int width, int height)
{
	t_canvas canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.aspect_ratio = (double)width / (double)height;
	return (canvas);
}

t_camera    camera(t_canvas *canvas, t_point3 orig)
{
    t_camera    cam;
    double      viewport_height;
	double		theta;

	cam.lookfrom = orig;
	//cam.lookat = vminus(cam.lookfrom, point3(0, 0, -1));
	cam.lookat = point3(0, 0, -1);
	cam.vup = vec3(0, 1, 0);
    cam.focal_len = vlength(vminus(cam.lookfrom, cam.lookat));
	
	cam.vfov = 90;
	theta = cam.vfov * (3.141592) / 180;
    viewport_height = tan(theta / 2) * 2 * cam.focal_len;
    cam.viewport_w = viewport_height * canvas->aspect_ratio;
    cam.viewport_h = viewport_height;

	cam.w = vunit(vminus(cam.lookfrom, cam.lookat));
	cam.u = vunit(vcross(cam.vup, cam.w));
	cam.v = vcross(cam.w, cam.u);

    cam.orig = cam.lookfrom;
    cam.horizontal = vmult(cam.u, cam.viewport_w);
    cam.vertical = vmult(cam.v, cam.viewport_h);
	//center - (focal_len * w) - (viewport_u / 2 + viewport_v / 2)
    cam.left_bottom = vminus(vminus(cam.orig, vmult(cam.w, cam.focal_len)), vplus(vdivide(cam.vertical, 2), vdivide(cam.horizontal, 2)));
	cam.samples_per_pixel = ANTI_SAMPLE;

    return (cam);
}
