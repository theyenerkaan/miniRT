/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/22 21:33:42 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_normal_vector(t_vec3 vec, char *error_msg);
void	add_object(t_scene *scene, t_object *new_obj);

void	parse_sphere(t_scene *scene, char **parts)
{
	t_sphere	*sphere;
	t_object	*obj;

	if (!parts[1] || !parts[2] || !parts[3])
		error_exit("Sphere: missing parameters (sp x,y,z diameter R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3])
		error_exit("Sphere: empty parameters");
	if (parts[4])
		error_exit("Sphere: too many parameters");
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit("Memory allocation failed");
	sphere->center = parse_vec3(parts[1]);
	sphere->diameter = ft_atof(parts[2]);
	if (sphere->diameter <= 0.0)
		error_exit("Sphere diameter must be positive");
	sphere->color = parse_color(parts[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		error_exit("Memory allocation failed");
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	obj->next = NULL;
	add_object(scene, obj);
	scene->object_count++;
}

void	parse_plane(t_scene *scene, char **parts)
{
	t_plane		*plane;
	t_object	*obj;
	t_vec3		normal;

	if (!parts[1] || !parts[2] || !parts[3])
		error_exit("Plane: missing parameters (pl x,y,z nx,ny,nz R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3])
		error_exit("Plane: empty parameters");
	if (parts[4])
		error_exit("Plane: too many parameters");
	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit("Memory allocation failed");
	plane->point = parse_vec3(parts[1]);
	normal = parse_vec3(parts[2]);
	validate_normal_vector(normal, "Plane normal must be normalized");
	plane->normal = vec3_normalize(normal);
	plane->color = parse_color(parts[3]);
	obj = malloc(sizeof(t_object));
	if (!obj)
		error_exit("Memory allocation failed");
	obj->type = OBJ_PLANE;
	obj->data = plane;
	obj->next = NULL;
	add_object(scene, obj);
	scene->object_count++;
}

static t_cylinder	*create_cylinder(char **parts)
{
	t_cylinder	*cyl;
	t_vec3		axis;

	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		error_exit("Memory allocation failed");
	cyl->center = parse_vec3(parts[1]);
	axis = parse_vec3(parts[2]);
	validate_normal_vector(axis, "Cylinder axis must be normalized");
	cyl->axis = vec3_normalize(axis);
	cyl->diameter = ft_atof(parts[3]);
	cyl->height = ft_atof(parts[4]);
	if (cyl->diameter <= 0.0 || cyl->height <= 0.0)
		error_exit("Cylinder diameter and height must be positive");
	cyl->color = parse_color(parts[5]);
	return (cyl);
}

void	parse_cylinder(t_scene *scene, char **parts)
{
	t_cylinder	*cyl;
	t_object	*obj;

	if (!parts[1] || !parts[2] || !parts[3] || !parts[4] || !parts[5])
		error_exit("Cylinder: missing parameters (cy x,y,z ax,ay,az d h R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3] || !*parts[4] || !*parts[5])
		error_exit("Cylinder: empty parameters");
	if (parts[6])
		error_exit("Cylinder: too many parameters");
	cyl = create_cylinder(parts);
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(cyl);
		error_exit("Memory allocation failed");
	}
	obj->type = OBJ_CYLINDER;
	obj->data = cyl;
	obj->next = NULL;
	add_object(scene, obj);
	scene->object_count++;
}
