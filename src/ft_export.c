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

	new_entry = ft_strjoin(l_value,r_value);
    new_env = ft_increnv(env,new_entry);
    ft_free(new_entry);
    return (new_env);
}

char **ft_fusion(char **exp, char **exp_tab)
{
	int j;
	int k;
	char **new;

	j = -1;
	k = -1;
	while(exp[++j])
		;
	while(exp_tab[++k])
        ;
	new = malloc(sizeof(char **) *(j+k)+1);
	j = -1;
	while(exp[++j])
		new[j] = ft_strdup(exp[j]);
	k = -1;
	while(exp_tab[++k])
	{
		new[j] = ft_strdup(exp_tab[k]);
		j++;
	}
	new[j] = NULL;
	return(new);
}

char **add_exp_var(char *l_value, char *r_value, char **exp)
{
    static int k;
    int i;
	char *new_entry;
	static char **exp_tab;

    i = -1;
    new_entry = ft_strjoin(l_value,r_value);
    if(!k)
        k = 0;
    while(exp[++i])
       ;
    if(!exp_tab)
    {
        exp_tab = malloc(sizeof(char **) * (i + 32));
        exp_tab[k] = ft_strdup(new_entry);
    }
    exp_tab[k] = ft_strdup(new_entry);
    exp_tab = ft_triAlpha(exp_tab);
    ft_free(new_entry);
    k++;
    return (exp_tab);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export
char **ft_export(char **args, char **env)
{
    char    	*l_value;
    char    	*r_value;
	char		**new_env;
    char        **new_exp;
	static char	**exp_lst;
    int     	i;

    i = -1;
	if (!exp_lst)
    	exp_lst = init_exp(env);
	if (args[1] == NULL)
	{
			while (exp_lst && exp_lst[++i])
				printf("declare -x %s\n", exp_lst[i]);
		return (env);
	}
	i = 0;
	while (args[++i])
	{
        if (!ft_strchr(args[i],'='))
			new_exp = add_exp_var(args[i],"",exp_lst);
        else
        {
            //bug
            l_value = get_variable_name(args[i]);
            r_value = get_env_variable_value(args[i]);
            new_env = add_env_var(l_value, r_value, env);
            new_exp = add_exp_var(l_value, r_value, exp_lst);
        }
	}
    exp_lst = ft_fusion(exp_lst,new_exp);
    return (new_env);
}
