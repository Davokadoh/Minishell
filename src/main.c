#include "../minishell.h"

int	launch_minishell(char *cmdline,t_envp *env)
{
	char	**tokens;
    int     len;
    //char    *home;

    //ft_setenv("HOME","shadow/of/colossus",env);
    //home = ft_getenv("HOME",env);
    //printf("%s \n",home);
	tokens = lex(cmdline); //Warning: Check some syntax errors beforehand
    len = ft_strlen(tokens[0]);
    //printf("TOKENS: %s",tokens[0]);
	//expand(tokens); //Warning: Don't expand inside single quotes + $?
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i]);
    if (ft_strncmp(tokens[0],"env",3) == 0)
        ft_env(env);
    else
        printf("minishell: command not found: %s\n", tokens[0]);
    /*
	if get_key(token) => printf value
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
    t_envp *env;
	(void) envp;
	errno = 0;
	signal = -1;
    // avant de lunch minishell initialiser ft_envp qui contient les envp
    env = init_envp(envp);
    // les variables d'environement ne s'affiche que si il ya un $
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], env));
    welcome();
    // env -i ./minishell
    while (signal != EXIT)
	{
		line = rl_gets();
        if(!line || !*line)
            return (0);
		errno = launch_minishell(line, env);
		//printf("%s\n", line);
		ft_free(line);
		//signal += 1;
	}
	return (errno);
}