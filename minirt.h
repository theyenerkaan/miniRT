/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yenyilma <yyenerkaan1@student.42.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:19:09 by yenyilma          #+#    #+#             */
/*   Updated: 2025/12/25 15:25:26 by yenyilma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "src/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define WIDTH 800
# define HEIGHT 600
# define EPSILON 1e-6

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}	t_ray;

typedef struct s_ambient
{
	double		ratio;
	t_color		color;
}	t_ambient;

typedef struct s_camera
{
	t_vec3		pos;
	t_vec3		dir;
	double		fov;
	t_vec3		right;
	t_vec3		up;
	t_vec3		lower_left;
	double		vp_width;
	double		vp_height;
}	t_camera;

typedef struct s_light
{
	t_vec3		pos;
	double		ratio;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_vec3		center;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef enum e_obj_type
{
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER
}	t_obj_type;

typedef struct s_object
{
	t_obj_type		type;
	void			*data;
	struct s_object	*next;
}	t_object;

typedef struct s_scene
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	int			has_ambient;
	int			has_camera;
	int			has_light;
	int			object_count;
}	t_scene;

typedef struct s_hit
{
	double		t;
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
}	t_hit;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}	t_mlx;

typedef struct s_minirt
{
	t_mlx		mlx;
	t_scene		scene;
}	t_minirt;

t_vec3	vec3_new(double x, double y, double z);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 v, double t);
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);
double	vec3_len(t_vec3 v);
double	vec3_len_sq(t_vec3 v);
t_vec3	vec3_normalize(t_vec3 v);
t_color	color_new(double r, double g, double b);
t_color	color_add(t_color a, t_color b);
t_color	color_mult(t_color a, t_color b);
t_color	color_scale(t_color c, double t);
int		color_to_int(t_color c);
t_color	color_clamp(t_color c);
t_ray	ray_new(t_vec3 origin, t_vec3 dir);
t_vec3	ray_at(t_ray r, double t);
void	error_exit(char *msg);
void	free_scene(t_scene *scene);
t_scene	*parse_scene(char *filename);
void	setup_camera(t_camera *cam);
void	render_scene(t_minirt *rt);
int		close_window(void *param);
int		key_press(int keycode, void *param);
double	ft_atof(const char *str);
t_vec3	parse_vec3(char *str);
t_color	parse_color(char *str);
int		is_empty_file(int fd);
void	free_parts(char **parts);
void	process_line(t_scene *scene, char *line);
void	set_parse_context(t_scene *scene);
void	set_current_line(char *line);
void	clear_current_line(void);
void	set_current_parts(char **parts);
void	clear_current_parts(void);
void	cleanup_parse_context(void);
int		hit_sphere(t_ray ray, t_sphere *sp, double t_min, t_hit *hit);
int		hit_plane(t_ray ray, t_plane *pl, double t_min, t_hit *hit);
int		hit_cylinder(t_ray ray, t_cylinder *cy, double t_min, t_hit *hit);
int		trace_ray(t_ray ray, t_scene *scene, t_hit *closest);
int		is_in_shadow(t_hit *hit, t_scene *scene);
t_color	compute_lighting(t_hit *hit, t_scene *scene, t_vec3 light_dir);

#endif
