#include "../minishell.h"

char	*find_var(const char *str)
{
	int	i;

	i = -1;
	while (envp.key[++i])
	{
		if (!ft_strncmp(str + 1, envp.key[i], ft_strlen(envp.key[i]) + 1))
			return(envp.value[i]);
	}
	return (NULL);
}

char	*expand(const char *str)
{
	char	*var;

	while (*str)
	{
		if (*str == '$' && *str + 1 != '?')
			var = find_var(str);
		str++;
	}
	return (var);
}


int	launch_minishell(char *cmdline)
{
	(void) cmdline;
	/*
	tokens = lex(cmdline); //Warning: Check some syntax errors beforehand
	expand(tokens); //Warning: Don't expand inside single quotes + $?
	split_metachar(tokens); //Warning: Don't split >>, && and ||
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?
	*/
	return (0);
}

//Warnings!
//Try to run w/o env: env -i ./minishell
#define EXIT 1
int	main(int ac, char **av, char **envp)
{
	char	*line;
	int		errno;
	int		signal;

	(void) envp;
	errno = 0;
	signal = -1;
	welcome();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2]));
	while (signal != EXIT)
	{
		line = rl_gets();
		//errno = launch_minishell(line);
		printf("%s\n", line);
		free(line);
		//signal += 1;
	}
	return (errno);
}
