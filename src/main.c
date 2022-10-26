#include "../include/scene.h"
#include "../include/trace.h"
#include "../include/print.h"

t_scene *scene_init(void)
{
    t_scene     *scene;
    t_object    *world;
    t_object    *lights;
    double      ka; // 8.4 에서 설명

	if ((scene = malloc(sizeof(t_scene))) == NULL)
        return (NULL);
    scene->canvas = new_canvas(400, 300);
    scene->camera = new_camera(&scene->canvas, point3(0, 0, 0));
    world = new_object(SP, new_sphere(point3(-2, 0, -5), 2), color3(0.5, 0, 0)); // world 에 구1 추가
    oadd(&world, new_object(SP, new_sphere(point3(2, 0, -5), 2), color3(0, 0.5, 0))); // world 에 구2 추가
    oadd(&world, new_object(SP, new_sphere(point3(0, -1000, 0), 999), color3(1, 1, 1))); // world 에 구3 추가
    scene->world = world;
    lights = new_object(LIGHT_POINT, new_light_point(point3(0, 5, 0), color3(1, 1, 1), 0.5), color3(0, 0, 0)); // 더미 albedo
    scene->light = lights;
    ka = 0.1; // 8.4 에서 설명
    scene->ambient = vmult(color3(1,1,1), ka); // 8.4 에서 설명
    return (scene);
}

int	main(void)
{
    int     i;
    int     j;
	double	u;
	double	v;
	t_color3	pixel_color;
	t_canvas	canv;
	t_camera	cam;
	t_ray		ray;
	t_object	*world;

	canv = new_canvas(400, 300);
	cam = new_camera(&canv, point3(0, 0, 0));
	world = new_object(SP, new_sphere(point3(-2, 0, -5), 2), color3(0, 0.5, 0));
	oadd(&world, new_object(SP, new_sphere(point3(2, 1, -5), 3), color3(1, 1, 1)));
    // 랜더링
    // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
    printf("P3\n%d %d\n255\n", canv.width, canv.height);
    j = canv.height - 1;
    while (j >= 0)
    {
        i = 0;
        while (i < canv.width)
        {
            u = (double)i / (canv.width - 1);
            v = (double)j / (canv.height - 1);
			ray = ray_primary(&cam, u, v);
			pixel_color = ray_sphere_color(scene);
			// 여기 수정하다 끝냈음. 8.3.1
			write_color(pixel_color);
        	++i;
        }
    	--j;
    }
    return (0);
}
