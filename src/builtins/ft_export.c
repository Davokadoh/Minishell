/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:41:12 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/21 17:22:07 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **init_exp(char **env)
{
    char **exp;
    int i;
    int j;
    // ou est passe path ??
    i = 0;
    j = 0;
    while (env[i])
        i++;
    exp = malloc(sizeof(char **) * i);
    while (env[j])
    {
        if(ft_strnstr(env[j],"PATH",4))
            exp[j] = ft_strdup(env[j]);
        if(ft_strncmp(env[j],"_=",2) != 0)
            exp[j] = ft_strdup(env[j]);
        j++;
    }
    exp[i] = NULL;
    return (exp);
}

char **add_env_var(char *l_value, char *r_value, char **env)
{
    char *new_entry;
	char **new_env;

    new_entry = ft_strjoin(l_value,"=");
    new_entry = ft_strjoin(new_entry,r_value);
    new_env = ft_increnv(env,new_entry);
    ft_free(new_entry);
    return (new_env);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export
char **ft_export(char **args, char **env)
{
    char    *l_value;
    char    *r_value;
	char	**new_env;
	static char	**exp_lst;
    int     i;

    i = -1;
    if (exp_lst == NULL)
        exp_lst = init_exp(env);
	if (args[1] == NULL)
	{
        while (exp_lst[++i])
            printf("%s\n", exp_lst[i]);
	}
	if (args[1])
	{
        if (!ft_strchr(args[1],'='))
            return (add_env_var(args[1],"",exp_lst));
    	l_value = get_variable_name(args[1]);
    	r_value = get_env_variable_value(args[1]);
        exp_lst = add_env_var(l_value,r_value,exp_lst);
    	new_env = add_env_var(l_value,r_value,env);
		return (new_env);
	}
    return (env);
}