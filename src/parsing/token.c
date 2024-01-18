#include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	read_n_analyze_line(t_parse *parse, int *i)
{
	char	*line;

	line = get_next_line(parse->fd_rt);
	if (line == NULL)
	{
		close(parse->fd_rt);
		*i = parse->nb_token;
	}
	else
	{
		analyse_line(parse, line, i);
		free(line);
	}
}

void	analyse_line(t_parse *parse, char *line, int *i)
{
	char	*new_line;
	t_data	*data;

	data = get_data();
	new_line = ft_strtrim(line, " ");
	if (new_line && new_line[0] != '\n' && new_line[0] != '#')
	{
		parse_token(line, parse);
		create_object(data, parse);
		if(parse->token)
			free(parse->token);
		parse->token = NULL;
		(*i)++;
	}
	free(new_line);
}

void	tokenization(t_parse *parse)
{
	int		i;

	i = 0;
	while (i < parse->nb_token)
	{
		if (i >= 103)
		{
			close(parse->fd_rt);
			ft_error_message("A maximum of 100 objects is allowed");
		}
		read_n_analyze_line(parse, &i);
	}
}

void	parse_token(char *line, t_parse *parse)
{
	char	*new;
	int		i;
	int		t;

	i = 0;
	t = 0;
	parse->count = 0;
	new = ft_strtrim(line, " \n");
	parse_count_atribute(new, parse);
	parse->token = ft_calloc(parse->count + 1, sizeof(char *));
	while (new[i])
	{
		parse->token[t] = new + i;
		while (new[i] != ' ' && new[i])
			i++;
		while (new[i] == ' ')
		{
			new[i] = '\0';
			i++;
		}
		t++;
	}
}

int	parse_nb_token(char *file)
{
	char	*line;
	char	*new_line;
	int		fd_rt;
	int		nb_token;

	fd_rt = open(file, O_RDONLY);
	nb_token = 0;
	if (fd_rt < 0)
	{
		printf("Error\n");
		printf("Impossible to open %s", file);
		close(fd_rt);
		exit(1);
	}
	while (1)
	{
		line = get_next_line(fd_rt);
		if (line == NULL)
			return (close(fd_rt), nb_token);
		new_line = ft_strtrim(line, " ");
		if (new_line[0] != '\n' || new_line[0] != '#')
			nb_token++;
		free(line);
		free(new_line);
	}
}
