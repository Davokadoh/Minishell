#include "../include/minishell.h"

int	g_errno = 0;

#define test 1
void	print_tab(char **tokens)
{
	if (test)
	{
		for (int i = 0; tokens[i]; i++)
			printf("%s\n", tokens[i]);
		printf("\n");
	}
}

static int	launch_minishell(char *line, char **envp)
{
	char	**tokens;
	char	**metatokens;
	t_cmd	*cmds;

	tokens = lex(line); //Warning: Check some syntax errors beforehand
	printf("LEXER:\n");
	print_tab(tokens);
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i], envp);
	printf("EXPANDER:\n");
	print_tab(tokens);
	metatokens = split_metachar(tokens);
	ft_free_tab(tokens);
	ft_free(tokens);
	printf("METACHAR:\n");
	print_tab(metatokens);
	cmds = parse(metatokens); //Create a list of cmds w/ corresponding i/o
	ft_free_tab(metatokens);
	ft_free(metatokens);
	printf("PARSER:\n");
	int i = -1;
	if (test)
	{
		while (cmds[++i].argv[0])
		{
			int j = -1;
			while (cmds[i].argv[++j])
				printf("cmd[%i] argv[%i] %s\n", i, j, cmds[i].argv[j]);
		}
		printf("\n");
	}
	else
		while (cmds[++i].argv[0]);
	execute(cmds, envp);
	for (int i = 0; cmds[i].argv[0]; i++)
	{
		ft_free_tab(cmds[i].argv);
		ft_free(cmds[i].argv);
	}
	ft_free_tab(cmds[i].argv);
	ft_free(cmds[i].argv);
	ft_free(cmds);
	/*
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?
	pipex(parse(expand(lex(line))));
	*/
	return (0);
}

#define EXIT 3

//Warnings!
//env -i ./minishell
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		signal;
	int		n;

	signal = 0;
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], envp));
	if (isatty(0))
		welcome();
	else
		signal = EXIT - 1; //Hack to run only one command if reading from stdin
	while (signal != EXIT)
	{
		line = rl_gets();
		if (!*line)
		{
			ft_free(line);
			return (0);
		}
		g_errno = launch_minishell(line, envp);
		ft_free(line);
		signal++;
	}
	rl_clear_history();
	return (g_errno);
}
