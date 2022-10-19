#include "../../include/structures.h"

t_sphere	new_sphere(t_point3 center, double radius)
{
	t_sphere sp;
	
	sp.center = center;
	sp.radius = radius;
	sp.radius2 = radius * radius;
	return (sp);
}
