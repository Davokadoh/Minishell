#include "../inc/minishell.h"

struct	s_cmd
{
	char	*argv;
	char	*input_name;
	char	*output_name;
	int		input_fd;
	int		output_fd;
}		t_cmd;

//t_cmd	cmdlist[];

int	launch_minishell(char *line)
{
	char	**tokens;

	tokens = lex(line); //Warning: Check some syntax errors beforehand
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i]);
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	/*
	split_metachar(tokens); //Warning: Don't split >>, && and ||
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?

	pipex(parse(expand(lex(line))));
	*/
	return (0);
}

#define EXIT 1

//Warnings!
//env -i ./minishell
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		errno;
	int		signal;

	(void) envp;
	errno = 0;
	signal = -1;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3)) // || stdin)
		return (launch_minishell(av[2]));
	welcome();
	while (signal != EXIT)
	{
		line = rl_gets();
		if (!line)
			return (0);
		errno = launch_minishell(line);
		//printf("%s\n", line);
		free(line);
		signal ++;
	}
	return (errno);
}
