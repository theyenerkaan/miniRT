/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/09 16:50:13 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		validate_normal_vector(t_vec3 vec, char *error_msg);
void		add_object(t_scene *scene, t_object *new_obj);
void		create_sphere_obj(t_scene *scene, t_vec3 ctr, double d, t_color c);

static void	check_sphere_params(char **parts)
{
	if (!parts[1] || !parts[2] || !parts[3])
		error_exit("Sphere: missing parameters (sp x,y,z diameter R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3])
		error_exit("Sphere: empty parameters");
	if (parts[4])
		error_exit("Sphere: too many parameters");
}

void	parse_sphere(t_scene *scene, char **parts)
{
	t_vec3		center;
	double		diameter;
	t_color		color;

	check_sphere_params(parts);
	center = parse_vec3(parts[1]);
	diameter = ft_atof(parts[2]);
	if (diameter <= 0.0)
		error_exit("Sphere diameter must be positive");
	color = parse_color(parts[3]);
	create_sphere_obj(scene, center, diameter, color);
}

static void	check_cylinder_params(char **parts)
{
	if (!parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5])
		error_exit("Cylinder: missing params (cy x,y,z ax,ay,az d h R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3] || !*parts[4] || !*parts[5])
		error_exit("Cylinder: empty parameters");
	if (parts[6])
		error_exit("Cylinder: too many parameters");
}

static void	create_cyl_obj(t_scene *s, t_cylinder *cy)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(cy);
		error_exit("Memory allocation failed");
	}
	obj->type = OBJ_CYLINDER;
	obj->data = cy;
	obj->next = NULL;
	add_object(s, obj);
	s->object_count++;
}

void	parse_cylinder(t_scene *scene, char **parts)
{
	t_cylinder	*cyl;
	t_vec3		axis;

	check_cylinder_params(parts);
	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		error_exit("Memory allocation failed");
	register_temp_alloc(cyl);
	cyl->center = parse_vec3(parts[1]);
	axis = parse_vec3(parts[2]);
	validate_normal_vector(axis, "Cylinder axis must be normalized");
	cyl->axis = vec3_normalize(axis);
	cyl->diameter = ft_atof(parts[3]);
	cyl->height = ft_atof(parts[4]);
	if (cyl->diameter <= 0.0 || cyl->height <= 0.0)
	{
		unregister_temp_alloc(cyl);
		free(cyl);
		error_exit("Cylinder diameter and height must be positive");
	}
	cyl->color = parse_color(parts[5]);
	unregister_temp_alloc(cyl);
	create_cyl_obj(scene, cyl);
}
