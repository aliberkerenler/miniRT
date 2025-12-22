#include "../include/render.h"
#include "../include/vec3.h"
#include "../libft/libft.h"
#include <stdio.h>
#include <assert.h>

#define EPSILON 0.0001

static int	double_equals(double a, double b)
{
	double diff;

	diff = a - b;
	if (diff < 0)
		diff = -diff;
	return (diff < EPSILON);
}

void	test_hit_plane_perpendicular(void)
{
	t_plane			plane;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_plane (perpendicular)... ", 1);
	plane.point = vec3(0, 0, -5);
	plane.normal = vec3(0, 0, 1);
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_plane(&plane, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.t, 5.0));
	ft_putendl_fd("OK", 1);
}

void	test_hit_plane_angle(void)
{
	t_plane			plane;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_plane (angle)... ", 1);
	plane.point = vec3(0, 0, 0);
	plane.normal = vec3(0, 1, 0);
	r = ray(vec3(0, 5, 0), vec3(0, -1, 0));
	hit = hit_plane(&plane, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.t, 5.0));
	ft_putendl_fd("OK", 1);
}

void	test_hit_plane_parallel(void)
{
	t_plane			plane;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_plane (parallel)... ", 1);
	plane.point = vec3(0, 0, 0);
	plane.normal = vec3(0, 1, 0);
	r = ray(vec3(0, 5, 0), vec3(1, 0, 0));
	hit = hit_plane(&plane, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

void	test_hit_plane_behind(void)
{
	t_plane			plane;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_plane (behind)... ", 1);
	plane.point = vec3(0, 0, 5);
	plane.normal = vec3(0, 0, 1);
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_plane(&plane, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

void	test_hit_plane_normal(void)
{
	t_plane			plane;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_plane (normal direction)... ", 1);
	plane.point = vec3(0, 0, 0);
	plane.normal = vec3(0, 1, 0);
	r = ray(vec3(0, 5, 0), vec3(0, -1, 0));
	hit = hit_plane(&plane, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.normal.y, 1.0) || double_equals(rec.normal.y, -1.0));
	ft_putendl_fd("OK", 1);
}

int	main(void)
{
	ft_putendl_fd("\n=== Hit Plane Tests ===\n", 1);
	
	test_hit_plane_perpendicular();
	test_hit_plane_angle();
	test_hit_plane_parallel();
	test_hit_plane_behind();
	test_hit_plane_normal();
	
	ft_putendl_fd("\n=== All Plane Tests Passed! ===\n", 1);
	return (0);
}

