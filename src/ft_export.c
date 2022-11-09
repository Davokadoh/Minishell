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

void print(char **v)
{
	int k;
	k = -1;
	while(v[++k])
		printf("string value: %s\n",v[k]);
}

char **init_exp(char **env)
{
    char **exp;
    int i;
    int j;
    
    i = -1;
    j = 0;
    while (env[++i])
        ;
    exp = malloc(sizeof(char **) * (i + 2));
	if(!exp)
		exit(0);
    while (env[j])
    {
		if(ft_strncmp(env[j],"_=",2) != 0)
			exp[j] = ft_strdup(env[j]);
        j++;
    }
	exp[j-1] = NULL;
	exp = ft_triAlpha(exp);
    return (exp);
}

char **add_env_var(char *l_value, char *r_value, char **env)
{
    char *new_entry;
	char **new_env;

	new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
    new_env = ft_increnv(env, l_value, new_entry);
    ft_free(new_entry);
    return (new_env);
}

char **add_exp_var(char *l_value, char *r_value)
{
    static int k;
	char *new_entry;
	static char **exp_tab;
	int i;
	
	i = - 1;

    new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
    if (!k && !exp_tab)
	{
		k = 0;
		exp_tab = malloc(sizeof(char **) + 2);
		exp_tab[k] = ft_strdup(new_entry);
		exp_tab[k+1] = NULL;
	}
    else
	{
		while(exp_tab[++k])
       		;
		exp_tab = realloc(exp_tab, (k + 2) * sizeof(char **));
		//printf("l value %s \n",l_value);
		while(exp_tab[++i])
		{
			if(ft_strnstr(exp_tab[i],l_value,ft_strlen(l_value)))
			{
				exp_tab[i] = ft_strdup(new_entry);
				exp_tab[k] = NULL;
				exp_tab = ft_triAlpha(exp_tab);
    			ft_free(new_entry);
				return (exp_tab);
			}
		}
		exp_tab[k] = ft_strdup(new_entry);
		exp_tab[k+1] = NULL;
    	exp_tab = ft_triAlpha(exp_tab);
    	ft_free(new_entry);
		return (exp_tab);
	}
	return (exp_tab);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export

char **ft_export(char **args, char **env)
{
    char    	*l_value;
    char    	*r_value;
	static char	**new_env;
    static char **new_exp;
	static char	**exp_lst;
    int     	i;

    i = -1;
	if(!new_env)
		new_env = init_envp(env);
	if(!new_exp)
		new_exp = NULL;
	if (!exp_lst)
    	exp_lst = init_exp(env);
	if (args[1] == NULL)
	{
		while (exp_lst && exp_lst[++i])
			printf("declare -x %s\n", exp_lst[i]);
		i = -1;
		while(new_exp && new_exp[++i])
			printf("declare -x %s\n", new_exp[i]);
		return (env);
	}
	i = 0;
	while (args[++i])
	{
		if(!ft_isalpha(args[i][0]))
		{
			printf("export: %s: not a valid identifier \n",args[i]);
			return (env);
		}
        if (!ft_strchr(args[i],'='))
			new_exp = add_exp_var(args[i],"");
        else
        {
            l_value = get_variable_name(args[i]);
            r_value = get_env_variable_value(args[i]);
            new_env = add_env_var(l_value, r_value, env);
            new_exp = add_exp_var(l_value, r_value);
        }
	}
    return (new_env);
}
