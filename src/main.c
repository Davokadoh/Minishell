#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"

typedef struct	s_envp
{
	char	*key[3];
	char	*value[3];
}				t_envp;

char	*rl_gets()
{
	static char	*line_read = (char *) NULL;
	static char	*previous_line;
	char		*prmpt;

	prmpt = ft_strjoin(getenv("USER"), "@minishell> ");
	line_read = readline(prmpt);
	ft_free(prmpt);
	if (line_read && *line_read)
	{
		if (!previous_line)
			add_history(line_read);
		else
			if (ft_strncmp(previous_line, line_read, ft_strlen(line_read)))
				add_history(line_read);
		ft_free(previous_line);
		previous_line = ft_strdup(line_read);
	}
	return (line_read);
}

/*
void	pipex(t_cmd *cmds)
{
	int	i;

	create_pipes();
	i = -1;
	while (cmds[0][i])
	{
		expand_errno(cmds[0][i]);
		strip_quotes(tokens); //Warning: Don't remove quotes inside quotes
		execute(cmds[0][i]);
	}
}
*/

struct	s_cmd
{
	char	*argv;
	char	*input_name;
	char	*output_name;
	int		input_fd;
	int		output_fd;
}		t_cmd;

//t_cmd	cmdlist[];

char	*ft_strinsert(const char *str1, const char *str2, int start, int end)
{
	char	*ptr;
	char	*new_str;

	new_str = ft_substr(str1, 0, start);
	ptr = new_str;
	new_str = ft_strjoin(new_str, str2);
	ft_free(ptr);
	ptr = new_str;
	new_str = ft_strjoin(new_str, &str1[end]);
	ft_free(ptr);
	//ft_free(str1);
	//ft_free(str2);
	return (new_str);
}

int	get_var_end(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '"')
		i++;
	return (i);
}


char	*expand(char **str)
{
	int		i;
	char	*var;

	i = -1;
	while (str[0][++i])
	{
		if (str[0][i] == '$' && str[0][i + 1] != '?')
		{
			var = ft_substr(*str, i + 1, get_var_end(&str[0][i + 1]));
			*str = ft_strinsert(*str, getenv(var), i, i + ft_strlen(var) + 1);
			ft_free(var);
		}
	}
	return (*str);
}

char	**lex(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	s_quote;
	unsigned int	d_quote;
	unsigned int	nb;
	char			**list;

	if (!s)
		return (NULL);
	start = 0;
	nb = 0;
	s_quote = 0;
	d_quote = 0;
	list = malloc(1024);//(1 + nb_words(s, c)) * sizeof(char *));
	if (!list)
		return (NULL);
	while (s[start])
	{
		while (s[start] == ' ')
			start++;
		end = start;
		while (s[end] && (s[end] != ' ' || s_quote || d_quote))
		{
			if (s[end] == '"' && !s_quote)
				d_quote = (d_quote + 1) % 2;
			else if (s[end] == '\'' && !d_quote)
				s_quote = (s_quote + 1) % 2;
			end++;
		}
		list[nb++] = ft_substr(s, start, end - start);
		start = end;
	}
	list[nb] = NULL;
	return (list);
}

int	launch_minishell(char *line)
{
	char	**tokens;

	tokens = lex(line); //Warning: Check some syntax errors beforehand
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i]);
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	/*
	(void) line;
	expand(tokens); //Warning: Don't expand inside single quotes + $?
	split_metachar(tokens); //Warning: Don't split >>, && and ||
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?

	pipex(parse(expand(lex(line))));
	*/
	return (0);
}

#define EXIT 1

//Warnings!
//Try to run w/o env: env -i ./minishell
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		errno;
	int		signal;

	(void) envp;
	errno = 0;
	signal = 0;
	//handle_signals();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2]));
	while (signal != EXIT)
	{
		line = rl_gets();
		errno = launch_minishell(line);
		//printf("%s\n", line);
		free(line);
		signal ++;
	}
	return (errno);
}
