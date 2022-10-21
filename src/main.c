#include "../include/scene.h"
#include "../include/trace.h"
#include "../include/print.h"

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
	world = new_object(SP, new_sphere(point3(-2, 0, -5), 2));
	oadd(&world, new_object(SP, new_sphere(point3(2, 1, -5), 3)));
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
			pixel_color = ray_sphere_color(&ray, world);
			write_color(pixel_color);
        	++i;
        }
    	--j;
    }
    return (0);
}
