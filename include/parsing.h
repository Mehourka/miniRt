#ifndef PARSING_H
# define PARSING_H

typedef struct s_parse
{
	int		L;
	int		C;
	int		A;
	char	**token_line;
	int		count;
}	t_parse;

double	ft_atod(char *str);

#endif