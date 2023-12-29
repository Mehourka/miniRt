# include "../include/minirt.h"
#include "../include/render.h"
#include "../include/parsing.h"

void	parse_token(char *line, t_parse *parse)
{
	char	*new;
	int		i;
	int		t;

	i = 0;
	parse->count = 0;
	new = ft_strtrim(line, " \n");
	parse_count_atribute(new, parse);
	parse->token = ft_calloc(parse->count + 1, sizeof (char*));
	t = 0;
	while(new[i])
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

int parse_nb_token(char *file)
{
	char *line;
	char *new_line;
	int fd_rt;
	int nb_token;

	fd_rt = open(file, O_RDONLY);
	nb_token = 0;
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		close(fd_rt);
		exit(1);
	}
	while(1)
	{
		line = get_next_line(fd_rt);
		if (line == NULL)
			return(close(fd_rt), nb_token);
		new_line = ft_strtrim(line, " ");
		if (new_line[0] != '\n')
			nb_token++;
		free(line);
		free(new_line);
	}
}