/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 17:00:00 by yenyilma          #+#    #+#             */
/*   Updated: 2026/01/09 16:50:13 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_normal_vector(t_vec3 vec, char *error_msg);
void	add_object(t_scene *scene, t_object *new_obj);

void	create_sphere_obj(t_scene *scene, t_vec3 ctr, double d, t_color c)
{
	t_sphere	*sphere;
	t_object	*obj;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		error_exit("Memory allocation failed");
	sphere->center = ctr;
	sphere->diameter = d;
	sphere->color = c;
	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(sphere);
		error_exit("Memory allocation failed");
	}
	obj->type = OBJ_SPHERE;
	obj->data = sphere;
	obj->next = NULL;
	add_object(scene, obj);
	scene->object_count++;
}

static void	create_plane_obj(t_scene *scene, t_plane *plane)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		free(plane);
		error_exit("Memory allocation failed");
	}
	obj->type = OBJ_PLANE;
	obj->data = plane;
	obj->next = NULL;
	add_object(scene, obj);
	scene->object_count++;
}

void	parse_plane(t_scene *scene, char **parts)
{
	t_plane		*plane;
	t_vec3		normal;
	t_vec3		point;
	t_color		color;

	if (!parts[1] || !parts[2] || !parts[3])
		error_exit("Plane: missing params (pl x,y,z nx,ny,nz R,G,B)");
	if (!*parts[1] || !*parts[2] || !*parts[3])
		error_exit("Plane: empty parameters");
	if (parts[4])
		error_exit("Plane: too many parameters");
	point = parse_vec3(parts[1]);
	normal = parse_vec3(parts[2]);
	validate_normal_vector(normal, "Plane normal must be normalized");
	color = parse_color(parts[3]);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		error_exit("Memory allocation failed");
	plane->point = point;
	plane->normal = vec3_normalize(normal);
	plane->color = color;
	create_plane_obj(scene, plane);
}
