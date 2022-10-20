#include "../include/minishell.h"

int	g_errno = 0;

#define test 0
void	print_tab(char **tokens, char *part_name)
{
	if (test)
	{
		printf("%s:\n", part_name);
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
	print_tab(tokens, "LEXER");
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i], envp);
	print_tab(tokens, "EXPANDER");
	metatokens = split_metachar(tokens);
	ft_free_tab(tokens);
	ft_free(tokens);
	print_tab(metatokens, "METACHAR");
	cmds = parse(metatokens); //Create a list of cmds w/ corresponding i/o
	ft_free_tab(metatokens);
	ft_free(metatokens);
	int i = -1;
	if (test)
	{
		printf("PARSER:\n");
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
	if (!isatty(0))
	{
		g_errno = launch_minishell(readline(NULL), envp);
		printf("\033[A\33[2K\r");
		fflush(0);
		return (g_errno);
	}
	welcome();
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
