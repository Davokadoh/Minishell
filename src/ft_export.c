/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:41:12 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/02 18:27:17 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
export trie une liste de variable a l'initialisation
puis ajoute a la fin de cette liste une nouvelle liste triee
d'elements exporte si une variable se trouve deja dans cette seconde liste
elle est remplace si elle est suivie par =
*/

char **init_exp(char **env)
{
    char **exp;
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (env[i])
        i++;
    exp = malloc(sizeof(char **) * (i + 2));
	if(!exp)
		exit(0);
    while (env[j])
    {
		if(ft_strncmp(env[j],"_=",2) != 0)
        	exp[j] = ft_strdup(env[j]);
        j++;
    }
	//TODO trier par ordre alpha
    exp[j] = NULL;
    return (exp);
}

char **add_env_var(char *l_value, char *r_value, char **env)
{
    char *new_entry;
	char **new_env;

    new_entry = ft_strjoin(l_value," ");
    new_entry = ft_strjoin(new_entry,r_value);
    new_env = ft_increnv(env,new_entry);
    ft_free(new_entry);
    return (new_env);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export
char **ft_export(char **args, char **env)
{
    char    	*l_value;
    char    	*r_value;
	char		**new_env;
	static char	**exp_lst;
    int     	i;

    i = 0;
	if (!exp_lst)
    	exp_lst = init_exp(env);
	if (args[1] == NULL)
	{
			while (exp_lst && exp_lst[i])
			{
				
				printf("declare -x %s\n", exp_lst[i]);
				i++;
			}
		return (env);
	}
	i = 0;
	while (args[++i])
	{
        if (!ft_strchr(args[i],'='))
		{
			exp_lst = add_env_var(args[i],"",exp_lst);
			return (env);
		}
    	l_value = get_variable_name(args[i]);
    	r_value = get_env_variable_value(args[i]);
    	new_env = add_env_var(l_value,r_value,env);
		exp_lst = add_env_var(l_value,r_value,exp_lst);
	}
    return (new_env);
}
