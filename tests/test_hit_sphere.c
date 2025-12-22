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

/* Test: Küre ile ışın kesişimi (isabet) */
void	test_hit_sphere_hit(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_sphere (hit)... ", 1);
	sphere.center = vec3(0, 0, -5);
	sphere.radius = 1.0;
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.t, 4.0));
	ft_putendl_fd("OK", 1);
}

/* Test: Küre ile ışın kesişimi (ıskalama) */
void	test_hit_sphere_miss(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_sphere (miss)... ", 1);
	sphere.center = vec3(0, 0, -5);
	sphere.radius = 1.0;
	r = ray(vec3(0, 0, 0), vec3(1, 0, 0));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

/* Test: Küre ile ışın kesişimi (teğet) */
void	test_hit_sphere_tangent(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_sphere (tangent)... ", 1);
	sphere.center = vec3(0, 0, -5);
	sphere.radius = 1.0;
	r = ray(vec3(0, 1, 0), vec3(0, 0, -1));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.point.y, 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test: Küre içinden ışın */
void	test_hit_sphere_inside(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_sphere (inside)... ", 1);
	sphere.center = vec3(0, 0, 0);
	sphere.radius = 1.0;
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.t, 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test: Küre arkada (negatif t) */
void	test_hit_sphere_behind(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: hit_sphere (behind)... ", 1);
	sphere.center = vec3(0, 0, 5);
	sphere.radius = 1.0;
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

/* Test: Normal vektör kontrolü */
void	test_hit_sphere_normal(void)
{
	t_sphere		sphere;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;
	double			normal_length;

	ft_putstr_fd("Test: hit_sphere (normal)... ", 1);
	sphere.center = vec3(0, 0, -5);
	sphere.radius = 1.0;
	r = ray(vec3(0, 0, 0), vec3(0, 0, -1));
	hit = hit_sphere(&sphere, &r, &rec);
	assert(hit == true);
	normal_length = vec3_length(rec.normal);
	assert(double_equals(normal_length, 1.0));
	assert(double_equals(rec.normal.z, 1.0));
	ft_putendl_fd("OK", 1);
}

int	main(void)
{
	ft_putendl_fd("\n=== Hit Sphere Tests ===\n", 1);
	
	test_hit_sphere_hit();
	test_hit_sphere_miss();
	test_hit_sphere_tangent();
	test_hit_sphere_inside();
	test_hit_sphere_behind();
	test_hit_sphere_normal();
	
	ft_putendl_fd("\n=== All Sphere Tests Passed! ===\n", 1);
	return (0);
}

