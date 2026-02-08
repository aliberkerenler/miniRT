#include "../include/render.h"
#include "../include/vec3.h"
#include "../libft/libft.h"
#include <assert.h>
#include <math.h>

static bool	double_equals(double a, double b)
{
	return (fabs(a - b) < 0.0001);
}

static bool	vec_equals(t_vector a, t_vector b) __attribute__((unused));

static bool	vec_equals(t_vector a, t_vector b)
{
	return (double_equals(a.x, b.x) && double_equals(a.y, b.y)
		&& double_equals(a.z, b.z));
}

/* Test 1: Yandan direkt vuruş */
void	test_cylinder_side_hit(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder side hit... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(3, 0, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.t, 2.0));
	assert(double_equals(rec.point.x, 1.0));
	assert(double_equals(vec3_length(rec.normal), 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 2: Üstten aşağı (kapak vuruşu) */
void	test_cylinder_top_down(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder top-down (cap hit)... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(0, 5, 0), vec3(0, -1, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	// Top cap at y=2. Ray start y=5. t=3.
	assert(double_equals(rec.t, 3.0));
	assert(double_equals(rec.point.y, 2.0));
	assert(double_equals(rec.point.x, 0.0));
	assert(double_equals(rec.point.z, 0.0));
	assert(double_equals(rec.normal.y, 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 2b: Alttan yukarı (alt kapak vuruşu) */
void	test_cylinder_bottom_up(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder bottom-up (cap hit)... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	// Bottom cap at y=-2. Ray from y=-5 looking up.
	r = ray(vec3(0, -5, 0), vec3(0, 1, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	// t=3 again (-5 to -2)
	assert(double_equals(rec.t, 3.0));
	assert(double_equals(rec.point.y, -2.0));
	assert(double_equals(rec.normal.y, -1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 3: Açılı vuruş */
void	test_cylinder_angle_hit(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder angle hit... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(2, 0, 0), vec3_normalize(vec3(-1, 0.5, 0)));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(vec3_length(rec.normal), 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 4: Yükseklik sınırları dışında */
void	test_cylinder_outside_height(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder outside height... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 2.0;
	r = ray(vec3(3, 5, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

/* Test 5: Silindirin içinden */
void	test_cylinder_inside(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder from inside... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(0, 0, 0), vec3(1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.point.x, 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 6: Teğet geçiş */
void	test_cylinder_tangent(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder tangent... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(-1, 0, 5), vec3(0, 0, -1));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(vec3_length(rec.normal), 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 7: Yatay silindir */
void	test_cylinder_horizontal(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: horizontal cylinder... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(1, 0, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(0, 3, 0), vec3(0, -1, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.point.y, 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 8: Çapraz silindir */
void	test_cylinder_diagonal(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;

	ft_putstr_fd("Test: diagonal cylinder... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3_normalize(vec3(1, 1, 0));
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(0, 0, 3), vec3(0, 0, -1));
	if (hit_cylinder(&cy, &r, &rec))
		assert(double_equals(vec3_length(rec.normal), 1.0));
	ft_putendl_fd("OK", 1);
}

/* Test 9: Normal vektör kontrolü */
void	test_cylinder_normal_direction(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;
	double			dot_product;

	ft_putstr_fd("Test: cylinder normal direction... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(3, 0, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	// Normal eksenle dik olmalı
	dot_product = vec3_dot(rec.normal, cy.axis);
	assert(double_equals(dot_product, 0.0));
	ft_putendl_fd("OK", 1);
}

/* Test 10: Sıfır yarıçap (dejenere durum) */
void	test_cylinder_zero_radius(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder zero radius... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 0.0;
	cy.height = 4.0;
	r = ray(vec3(1, 0, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == false);
	ft_putendl_fd("OK", 1);
}

/* Test 11: Çok küçük silindir */
void	test_cylinder_small(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: very small cylinder... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 0.1;
	cy.height = 0.2;
	r = ray(vec3(0.5, 0, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	ft_putendl_fd("OK", 1);
}

/* Test 12: Yükseklik sınırında vuruş */
void	test_cylinder_at_boundary(void)
{
	t_cylinder		cy;
	t_ray			r;
	t_hit_record	rec;
	bool			hit;

	ft_putstr_fd("Test: cylinder at height boundary... ", 1);
	cy.center = vec3(0, 0, 0);
	cy.axis = vec3(0, 1, 0);
	cy.radius = 1.0;
	cy.height = 4.0;
	r = ray(vec3(3, 2, 0), vec3(-1, 0, 0));
	hit = hit_cylinder(&cy, &r, &rec);
	assert(hit == true);
	assert(double_equals(rec.point.y, 2.0));
	ft_putendl_fd("OK", 1);
}

int	main(void)
{
	ft_putendl_fd("\n=== Cylinder Hit Tests ===\n", 1);
	
	test_cylinder_side_hit();
	test_cylinder_top_down();
	test_cylinder_bottom_up();
	test_cylinder_angle_hit();
	test_cylinder_outside_height();
	test_cylinder_inside();
	test_cylinder_tangent();
	test_cylinder_horizontal();
	test_cylinder_diagonal();
	test_cylinder_normal_direction();
	test_cylinder_zero_radius();
	test_cylinder_small();
	test_cylinder_at_boundary();
	
	ft_putendl_fd("\n=== All Cylinder Tests Passed! ===\n", 1);
	return (0);
}
