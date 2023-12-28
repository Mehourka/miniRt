#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

typedef struct s_parse
{
	int		L;
	int		C;
	int		A;
	char	**token;
	int		count;
	int		i;
}	t_parse;

double	ft_atod(char *str);
void	parse_color(char *line, int *j, double *color);
void	parse_var(char *line, int *j, double *var);
void	ft_parse_rgb(t_color3 *color, char *line);
void	ft_parse_orig_dir(t_vec3 *orig_dir, char *line);
void	parse_ratio(double *ratio, char *nb);
void	parse_length(double *length, char *nb);
void	parse_ambiant_light(t_data *data, t_parse *parse);
void	parse_light(t_data *data, t_parse *parse);
void	parse_camera(t_data *data, t_parse *parse);
void	parse_sphere(t_data *data, t_parse *parse);
void	parse_plane(t_data *data, t_parse *parse);
void	parse_cylinder(t_data *data, t_parse *parse);
void	parse_count_atribute(char *new, t_parse *parse);
int		parse_comma(char *line);
int		dot_digit(char *str);
void	parse_limit(int *checker, int max, char *type);
void	create_object(t_data *data, t_parse *parse);
void	parsing(char *file, t_data *data);
void	parse_token(char *line, t_parse *parse);
int		parse_nb_token(char *file);
void	dot_rt(char *file);

#endif