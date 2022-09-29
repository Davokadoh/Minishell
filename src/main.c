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

t_envp		envp = {{"KEY1", "USER", "KEY2"}, {"VAL1", "jleroux", "VAL2"}};

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
	while (cmds[i])
	{
		expand_errno(cmds[i]);
		strip_quotes(tokens); //Warning: Don't remove quotes inside quotes
		execute(cmds[i]);
	}
}
*/

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
	//handle_signals();
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2]));
	while (signal != EXIT)
	{
		line = rl_gets();
		//errno = launch_minishell(line);
		printf("%s\n", line);
		free(line);
		signal += 1;
	}
	return (errno);
}
