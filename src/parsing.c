# include "../include/minirt.h"
#include "../include/render.h"

typedef struct s_parse
{
	bool	L;
	bool	C;
	bool	A;
	char	**token_line;
	int		count;
}	t_parse;


void	parse_token(char *line, t_parse *parse_struct)
{
	char	*new;
	int		i;
	int		t;

	i = 0;
	parse_struct->count = 0;
	new = ft_strtrim(line, " ");
	//combien token
	while(new[i])
	{
		if(new[i] == ' ')
			parse_struct->count++;
		while(new[i] == ' '&& new[i + 1])
			i++;
		i++;
	}
	parse_struct->count++;
	//malloc le nb
	parse_struct->token_line = ft_calloc(parse_struct->count + 1, sizeof (char*));
	//attribuer chaque token
	i = 0;
	t = 0;
	while(new[i])
	{
		parse_struct->token_line[t] = new + i;
		while (new[i] != ' ' && new[i])
			i++;
		while (new[i] == ' ')
		{
			new[i] = '\0';
			i++;
		}
		printf("%d %s\n", t, parse_struct->token_line[t]);
		t++;
	}
	//sortir de la function et passer a l'attribution
	
}

int parse_nb_token(char *file)
{
	char *line;
	char *new_line;
	int fd_rt;
	int nb_token;

	open(file, O_RDONLY);
	nb_token = 0;
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		exit(1);
	}
	while(1)
	{
		line = get_next_line(fd_rt);
		if (line == NULL);
			return(nb_token);
		new_line = ft_strtrim(line, ' ');
		if (new_line[0] != '\n');
			nb_token++;
		free(line);
		free(new_line);
	}
}

void	parse(char *file, t_data *data)
{
	char *line;
	int fd_rt;
	int nb_token;
	t_parse parse_struct;

	nb_token = parse_nb_token();
	int fd_rt = open(file, O_RDONLY);
	if(fd_rt < 0)
	{
		printf("Impossible to open %s", file);
		exit(1);
	}
	//read line
	line = get_next_line(fd_rt);
	//create token for the line
	parse_token(line, &parse_struct);
	struct_attribution(&parse_struct);
	//create struct with the attribute
	//do it again
	//check if everything in the token is ok
	while(line != NULL)
	{
		free(line);
		line = NULL;
		line = get_next_line(fd_rt);
	}
}

int main(int argc, char **argv)
{
	if(argc != 2)
		return(printf("Wrong number of arguments"), 0);
	t_data *data = get_data();
	parse(argv[1], data);
}