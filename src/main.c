#include "../minishell.h"

int	launch_minishell(char *cmdline,t_envp *env)
{
	char	**tokens;
    int     len;
    char    *pwd;

    pwd = ft_getenv("_",env);
    printf("%s \n",pwd);
	tokens = lex(cmdline); //Warning: Check some syntax errors beforehand
    len = ft_strlen(tokens[0]);
    //printf("TOKENS: %s",tokens[0]);
	//expand(tokens); //Warning: Don't expand inside single quotes + $?
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i]);
    // a mettre dans l'executor car c'est une commande
    for (int i = 0; i < len; i++)
        tokens[0][i] = ft_toupper(tokens[0][i]);
    if(getenv(tokens[0]))
        printf("%s\n", getenv(tokens[0]));
    else
        printf("minishell: command not found: %s\n", tokens[0]);
	/*
	 * if get_key(token) => printf value
	split_metachar(tokens); //Warning: Don't split >>, && and ||
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?
	*/
	return (0);
}

char	*ft_getenv(char *var, t_envp *envp)
{
    // fonction ft_getenv qui doit chercher dans notre copie de envp
	int	i;
	int	n2;

	i = -1;
    n2 = ft_strlen(var);
	while (envp->env[++i])
    {
        if (ft_strnstr(envp->env[i], var,n2))
            return (ft_substr(envp->env[i], n2 + 1, ft_strlen(envp->env[i])));
    }
	return (NULL);
}

t_envp *init_envp(char **envp)
{
    t_envp *env;
    int i = -1;
    env = malloc(sizeof(t_envp));
    if(!env)
        return (NULL);
    if (envp != NULL && *envp != NULL)
    {
        while(envp[++i])
            env->env[i] = envp[i];
    }
        // si envp est vide afficher getcwd(), SHLVL = 1 sinon SHLVL +1 et afficher "_" + le chemin de la derniere commande tapee
    //else
      //  getcwd(env->pwd,256);
    return (env);
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
    // TODO ft_getenv
    // les variables d'environement ne s'affiche que si il ya un $
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], env));
    welcome();
    //ft_getenv("User",envp);
    // env -i ./minshell
    while (signal != EXIT)
	{
		line = rl_gets();
        if(!line || !*line)
            return (0);
		errno = launch_minishell(line, env);
		//printf("%s\n", line);
		ft_free(line);
		signal += 1;
	}
	return (errno);
}