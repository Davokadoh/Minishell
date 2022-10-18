#include "../../include/minishell.h"

void    ft_env(t_envp *env)
{
    int i;

    i = -1;
    while (env->env[++i])
        printf("%s\n", env->env[i]);
}

void    ft_setenv(char *var, char *var2, t_envp *env)
{
    int i;
    int n;
    char *sub;
    char *sub2;

    i = -1;
    n = ft_strlen(var);
    sub = ft_strjoin(var,"=");
    sub2 = ft_strjoin(sub,var2);
    while (env->env[++i])
    {
        if (ft_strnstr(env->env[i], var,n))
        {
            env->env[i] = sub2;
            break;
        }
    }
}

char	*ft_getenv(char *var, t_envp *env)
{
    // fonction ft_getenv qui doit chercher dans notre copie de envp
    int	i;
    int	n2;

    i = -1;
    n2 = ft_strlen(var);
    while (env->env[++i])
    {
        if (ft_strnstr(env->env[i], var,n2))
            return (ft_substr(env->env[i], n2 + 1, ft_strlen(env->env[i])));
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
    else
    {
        getcwd(env->env[0], 256);
        env->env[0] = ft_strjoin("PWD=", env->env[0]);
        env->env[1] = ft_strdup("SHLVL=1");
        env->env[2] = ft_strdup("_=/usr/bin/env");
    }
    // si envp est vide afficher getcwd(), SHLVL = 1 sinon SHLVL +1 et afficher "_" + le chemin de la derniere commande tapee
    //else
    //  getcwd(env->pwd,256);
    return (env);
}