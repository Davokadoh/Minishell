#include "../include/minishell.h"

int	launch_minishell(char *cmdline,char ***env)
{
	char	**tokens;

	tokens = lex(cmdline);
    for (int i = 0; tokens[i]; i++)
        expand(&tokens[i]);
    builtin(tokens,env);
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
    char    **env;
	(void) envp;
	errno = 0;
	signal = -1;
    // avant de lunch minishell initialiser ft_envp qui contient les envp
    env = init_envp(envp);
    //printf("envp; %s",env[0]);
    // les variables d'environement ne s'affiche que si il ya un $
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], &env));
    welcome();
    // env -i ./minishell
    while (signal != EXIT)
	{
		line = rl_gets();
        if(!line || !*line)
            return (0);
		errno = launch_minishell(line, &env);
		ft_free(line);
		//signal += 1;
	}
	return (errno);
}
