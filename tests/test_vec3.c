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

static int	vec_equals(t_vector a, t_vector b)
{
	return (double_equals(a.x, b.x) && 
			double_equals(a.y, b.y) && 
			double_equals(a.z, b.z));
}

/* ========== Test: Vektör Oluşturma ========== */

void	test_vec3_creation(void)
{
	t_vector	v;

	ft_putstr_fd("Test: vec3 creation... ", 1);
	v = vec3(1.0, 2.0, 3.0);
	assert(double_equals(v.x, 1.0));
	assert(double_equals(v.y, 2.0));
	assert(double_equals(v.z, 3.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_zero(void)
{
	t_vector	v;

	ft_putstr_fd("Test: vec3_zero... ", 1);
	v = vec3_zero();
	assert(double_equals(v.x, 0.0));
	assert(double_equals(v.y, 0.0));
	assert(double_equals(v.z, 0.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_one(void)
{
	t_vector	v;

	ft_putstr_fd("Test: vec3_one... ", 1);
	v = vec3_one();
	assert(double_equals(v.x, 1.0));
	assert(double_equals(v.y, 1.0));
	assert(double_equals(v.z, 1.0));
	ft_putendl_fd("OK", 1);
}

/* ========== Test: Temel İşlemler ========== */

void	test_vec3_add(void)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;

	ft_putstr_fd("Test: vec3_add... ", 1);
	a = vec3(1.0, 2.0, 3.0);
	b = vec3(4.0, 5.0, 6.0);
	result = vec3_add(a, b);
	assert(vec_equals(result, vec3(5.0, 7.0, 9.0)));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_sub(void)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;

	ft_putstr_fd("Test: vec3_sub... ", 1);
	a = vec3(5.0, 7.0, 9.0);
	b = vec3(1.0, 2.0, 3.0);
	result = vec3_sub(a, b);
	assert(vec_equals(result, vec3(4.0, 5.0, 6.0)));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_mul(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_mul... ", 1);
	v = vec3(1.0, 2.0, 3.0);
	result = vec3_mul(v, 2.0);
	assert(vec_equals(result, vec3(2.0, 4.0, 6.0)));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_div(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_div... ", 1);
	v = vec3(2.0, 4.0, 6.0);
	result = vec3_div(v, 2.0);
	assert(vec_equals(result, vec3(1.0, 2.0, 3.0)));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_div_by_zero(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_div by zero... ", 1);
	v = vec3(1.0, 2.0, 3.0);
	result = vec3_div(v, 0.0);
	assert(vec_equals(result, vec3_zero()));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_negate(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_negate... ", 1);
	v = vec3(1.0, -2.0, 3.0);
	result = vec3_negate(v);
	assert(vec_equals(result, vec3(-1.0, 2.0, -3.0)));
	ft_putendl_fd("OK", 1);
}

/* ========== Test: Vektör Özellikleri ========== */

void	test_vec3_length(void)
{
	t_vector	v;
	double		len;

	ft_putstr_fd("Test: vec3_length... ", 1);
	v = vec3(3.0, 4.0, 0.0);
	len = vec3_length(v);
	assert(double_equals(len, 5.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_length_squared(void)
{
	t_vector	v;
	double		len_sq;

	ft_putstr_fd("Test: vec3_length_squared... ", 1);
	v = vec3(3.0, 4.0, 0.0);
	len_sq = vec3_length_squared(v);
	assert(double_equals(len_sq, 25.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_dot(void)
{
	t_vector	a;
	t_vector	b;
	double		result;

	ft_putstr_fd("Test: vec3_dot... ", 1);
	a = vec3(1.0, 2.0, 3.0);
	b = vec3(4.0, 5.0, 6.0);
	result = vec3_dot(a, b);
	assert(double_equals(result, 32.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_cross(void)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;

	ft_putstr_fd("Test: vec3_cross... ", 1);
	a = vec3(1.0, 0.0, 0.0);
	b = vec3(0.0, 1.0, 0.0);
	result = vec3_cross(a, b);
	assert(vec_equals(result, vec3(0.0, 0.0, 1.0)));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_normalize(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_normalize... ", 1);
	v = vec3(3.0, 4.0, 0.0);
	result = vec3_normalize(v);
	assert(vec_equals(result, vec3(0.6, 0.8, 0.0)));
	assert(double_equals(vec3_length(result), 1.0));
	ft_putendl_fd("OK", 1);
}

void	test_vec3_normalize_zero(void)
{
	t_vector	v;
	t_vector	result;

	ft_putstr_fd("Test: vec3_normalize zero vector... ", 1);
	v = vec3_zero();
	result = vec3_normalize(v);
	assert(vec_equals(result, vec3_zero()));
	ft_putendl_fd("OK", 1);
}

/* ========== Test: Renk İşlemleri ========== */

void	test_color_creation(void)
{
	t_color	c;

	ft_putstr_fd("Test: color creation... ", 1);
	c = color(1.0, 0.5, 0.0);
	assert(double_equals(c.x, 1.0));
	assert(double_equals(c.y, 0.5));
	assert(double_equals(c.z, 0.0));
	ft_putendl_fd("OK", 1);
}

void	test_color_to_int(void)
{
	t_color	c;
	int		rgb;

	ft_putstr_fd("Test: color_to_int... ", 1);
	c = color(1.0, 0.0, 0.0);
	rgb = color_to_int(c);
	assert(rgb == 0xFF0000);
	c = color(0.0, 1.0, 0.0);
	rgb = color_to_int(c);
	assert(rgb == 0x00FF00);
	c = color(0.0, 0.0, 1.0);
	rgb = color_to_int(c);
	assert(rgb == 0x0000FF);
	ft_putendl_fd("OK", 1);
}

/* ========== Test: Ray İşlemleri ========== */

void	test_ray_creation(void)
{
	t_ray		r;
	t_point		origin;
	t_vector	direction;

	ft_putstr_fd("Test: ray creation... ", 1);
	origin = vec3(1.0, 2.0, 3.0);
	direction = vec3(0.0, 0.0, -1.0);
	r = ray(origin, direction);
	assert(vec_equals(r.origin, origin));
	assert(vec_equals(r.direction, direction));
	ft_putendl_fd("OK", 1);
}

void	test_ray_at(void)
{
	t_ray	r;
	t_point	p;

	ft_putstr_fd("Test: ray_at... ", 1);
	r = ray(vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0));
	p = ray_at(r, 5.0);
	assert(vec_equals(p, vec3(5.0, 0.0, 0.0)));
	ft_putendl_fd("OK", 1);
}

/* ========== Ana Test Fonksiyonu ========== */

int	main(void)
{
	ft_putendl_fd("\n=== Vector Library Tests ===\n", 1);
	
	ft_putendl_fd(">> Creation Tests:", 1);
	test_vec3_creation();
	test_vec3_zero();
	test_vec3_one();
	
	ft_putendl_fd("\n>> Basic Operations:", 1);
	test_vec3_add();
	test_vec3_sub();
	test_vec3_mul();
	test_vec3_div();
	test_vec3_div_by_zero();
	test_vec3_negate();
	
	ft_putendl_fd("\n>> Vector Properties:", 1);
	test_vec3_length();
	test_vec3_length_squared();
	test_vec3_dot();
	test_vec3_cross();
	test_vec3_normalize();
	test_vec3_normalize_zero();
	
	ft_putendl_fd("\n>> Color Operations:", 1);
	test_color_creation();
	test_color_to_int();
	
	ft_putendl_fd("\n>> Ray Operations:", 1);
	test_ray_creation();
	test_ray_at();
	
	ft_putendl_fd("\n=== All Tests Passed! ===\n", 1);
	return (0);
}

