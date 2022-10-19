#include "../include/minishell.h"

static void	add_new_tokens(char **new, int *j, char *token, char *c)
{
	new[++*j] = ft_strdup(c);
	if (token[1])
		new[++*j] = ft_strdup(&token[1]);
}

static void	add_double(char **new, int *j, char *token, char *c)
{
	new[++*j] = ft_strdup(c);
	if (token[2])
		new[++*j] = ft_strdup(&token[2]);
}

//Warning: Don't split >>, && and ||
//Check if tokens[i][++z] isn't empty!
char	**split_metachar(char **tokens)
{
	int		i;
	int		j;
	char	**new;

	i = -1;
	j = -1;
	new = malloc(sizeof(char) * 2048);
	while (tokens[++i])
	{
		if (tokens[i][0] == '"' || tokens[i][0] == '\'')
			new[++j] = ft_strdup(tokens[i]);
		else if (tokens[i][0] == '|' && tokens[i][1] == '|')
			add_double(new, &j, tokens[i], "||");
		else if (tokens[i][0] == '|')
			add_new_tokens(new, &j, tokens[i], "|");
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			add_double(new, &j, tokens[i], "<<");
		else if (tokens[i][0] == '<')
			add_new_tokens(new, &j, tokens[i], "<");
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			add_double(new, &j, tokens[i], ">>");
		else if (tokens[i][0] == '>')
			add_new_tokens(new, &j, tokens[i], ">");
		else
			new[++j] = ft_strdup(tokens[i]);
	}
	new[++j] = NULL;
	return (new);
}
