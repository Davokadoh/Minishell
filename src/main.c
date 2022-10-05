#include "../minishell.h"

int	launch_minishell(char *cmdline)
{
	char	**tokens;

	tokens = lex(cmdline); //Warning: Check some syntax errors beforehand
	expand(tokens); //Warning: Don't expand inside single quotes + $?
	for (int i = 0; tokens[i]; i++)
		expand(&tokens[i]);
	for (int i = 0; tokens[i]; i++)
		printf("%s\n", tokens[i]);
	/*
	split_metachar(tokens); //Warning: Don't split >>, && and ||
	cmds = parse(tokens); //Create a list of cmds w/ corresponding i/o
	pipex(cmds); //Warning: Be sure to execute OUR built-ins + $?
	*/
	return (0);
}

t_envp *get_key(char **env)
{
    int		i;
    char    *key;

    t_envp *envp;

    envp = malloc(100);
    i = 0;
    while (!ft_strchr(env[i], '=') && env && env[i])
    {
        if (ft_strchr(env[i], '='))
            key = ft_strchr(env[i],'=');
        i++;
    }
    envp->key = key;
    printf("%s",envp->key);
    return (envp);
}
/*
char *get_value(char *key, char **env)
{
    char	**paths;
    char	*path;
    int		i;
    int     k;

    k = ft_strlen(key);
    key = *ft_split(key, ' ');
    i = 0;

    paths = get_env(env);
    paths = ft_split(env[i] + k+1, '=');
    i = -1;
    while (paths[++i])
    {
            return (path);

    }
}*/
/*
t_envp init_env()
{



    return (env);
}*/
//Warnings!
//Try to run w/o env: env -i ./minishell
#define EXIT 1
int	main(int ac, char **av, char **envp)
{
	//char	*line;
	int		errno;
	//int		signal;

	(void) envp;
	errno = 0;
	//signal = -1;
    get_key(envp);

	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2]));/*
    welcome();
    get_env("User",envp);
    while (signal != EXIT)
	{
		line = rl_gets();
        if(!line)
            return (0);
		errno = launch_minishell(line);
		//printf("%s\n", line);
		ft_free(line);
		signal += 1;
	}*/
	return (errno);
}

/*char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
		if (n2 < ft_strchr_i(envp[i], '='))
			n2 = ft_strchr_i(envp[i], '=');
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

char	**mini_setenv(char *var, char *value, char **envp, int n)
{
	int		i[2];
	char	*aux[2];

	if (n < 0)
		n = ft_strlen(var);
	i[0] = -1;
	aux[0] = ft_strjoin(var, "=");
	aux[1] = ft_strjoin(aux[0], value);
	free(aux[0]);
	while (!ft_strchr(var, '=') && envp && envp[++i[0]])
	{
		i[1] = n;
		if (i[1] < ft_strchr_i(envp[i[0]], '='))
			i[1] = ft_strchr_i(envp[i[0]], '=');
		if (!ft_strncmp(envp[i[0]], var, i[1]))
		{
			aux[0] = envp[i[0]];
			envp[i[0]] = aux[1];
			free(aux[0]);
			return (envp);
		}
	}
	envp = ft_extend_matrix(envp, aux[1]);
	free(aux[1]);
	return (envp);
}*/