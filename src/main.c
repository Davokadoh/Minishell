#include "../minishell.h"

int	launch_minishell(char *cmdline,t_envp *env)
{
	char	**tokens;
    int     len;

    printf("ENV HOME : %s",env->home);
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

int	ft_strcmp(const char *s1, const char *s2)
{
    const unsigned char	*buf1;
    const unsigned char	*buf2;

    buf1 = (const unsigned char *)s1;
    buf2 = (const unsigned char *)s2;
    if (*buf1 != *buf2)
        return (*buf1 - *buf2);
    while (*buf1 && *buf2)
    {
        if (*buf1 != *buf2)
            return (*buf1 - *buf2);
        buf1++;
        buf2++;
    }
    if (*buf1 == '\0' && *buf2 != '\0')
        return (0 - *buf2);
    else if (*buf2 == '\0' && *buf1 != '\0')
        return (*buf1);
    return (0);
}

char	*mini_getenv(char *var, char **envp, int n)
{
	int	i;
	int	n2;
    int str_len;

	i = 0;
	if (n < 0)
		n = ft_strlen(var);
	while (!ft_strchr(var, '=') && envp && envp[i])
	{
		n2 = n;
        str_len = ft_strlen(ft_strchr(envp[i], '='));
		if (n2 < str_len)
			n2 = str_len;
		if (!ft_strncmp(envp[i], var, n2))
			return (ft_substr(envp[i], n2 + 1, ft_strlen(envp[i])));
		i++;
	}
	return (NULL);
}

t_envp *init_envp(char **envp)
{
    t_envp *env;

    env = malloc(sizeof(t_envp));
    if(!env)
        return (NULL);
    if (envp != NULL && *envp != NULL)
    {
        env->envp = envp;
        env->path = mini_getenv("PATH", envp, -1);
        env->pwd = mini_getenv("PWD", envp, -1);
        env->oldpwd = mini_getenv("OLDPWD", envp, -1);
        env->home = mini_getenv("HOME", envp, -1);
        env->user = mini_getenv("USER", envp, -1);
        env->shlvl = mini_getenv("SHLVL", envp, -1);
    }
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
    // TODO init_envp
    env = init_envp(envp);
    // TODO see getcwd()
    // si envp est vide afficher getcwd(), SHLVL = 1 sinon SHLVL +1 et afficher "_" + le chemin de la derniere commande tapee
    // TODO get_envp
    // les variables d'environement ne s'affiche que si il ya un $
    //get_key(envp);
    // avant de lunch minishell initialiser ft_envp qui contient les envp
    // fonction ft_get_env qui doit chercher dans ft_envp
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
		return (launch_minishell(av[2], env));
    welcome();
    //get_env("User",envp);
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