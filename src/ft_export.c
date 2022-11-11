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

int	add_env_var(char *l_value, char *r_value, t_envp *envp)
{
    char *new_entry;

	new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
    envp->env = ft_increnv(envp->env, l_value, new_entry);
    ft_free(new_entry);
    return (0);
}

int	add_exp_var(char *l_value, char *r_value, t_envp *envp)
{
    static int k;
	char *new_entry;
	int i;
	
	i = - 1;

    new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
    if (!k && !envp->exp_lst) // bug
	{
		k = 0;
		envp->exp_lst = malloc(sizeof(char **) + 2);
		envp->exp_lst[k] = ft_strdup(new_entry);
		envp->exp_lst[k+1] = NULL;
		ft_free(new_entry);
	}
    else
	{
		while(envp->exp_lst[++k])
       		;
		envp->exp_lst = realloc(envp->exp_lst, (k + 2) * sizeof(char **));
		while(envp->exp_lst[++i])
		{
			if(ft_strnstr(envp->exp_lst[i],l_value,ft_strlen(l_value)))
			{
				envp->exp_lst[i] = ft_strdup(new_entry);
				envp->exp_lst[k] = NULL;
				envp->exp_lst = ft_triAlpha(envp->exp_lst);
    			ft_free(new_entry);
				return (0);
			}
		}
		envp->exp_lst[k] = ft_strdup(new_entry);
		envp->exp_lst[k+1] = NULL;
    	envp->exp_lst = ft_triAlpha(envp->exp_lst);
    	ft_free(new_entry);
		return (0);
	}
	return (0);
}
// ajoute un element au tableau de variable d'environnement et au tableau d'export

int	ft_export(char **args, t_envp  *envp)
{
    char    	*l_value;
    char    	*r_value;
	static int	a;
    int     	i;

    i = -1;
	a = 0;
	if(!a)
	{
		envp->exp_init = init_exp(envp->env);
		a = 1;
	}
	if (args[1] == NULL)
	{
		while (envp->exp_init && envp->exp_init[++i])
			printf("declare -x %s\n", envp->exp_init[i]);
		i = -1;
		while(envp->exp_lst && envp->exp_lst[++i])
			printf("declare -x %s\n", envp->exp_lst[i]);
		return (0);
	}
	i = 0;
	while (args[++i])
	{
		if(!ft_isalpha(args[i][0]))
		{
			printf("export: %s: not a valid identifier \n",args[i]);
			return (1);
		}
        if (!ft_strchr(args[i],'='))
			add_exp_var(args[i],"",envp);
        else
        {
            l_value = get_variable_name(args[i]);
            r_value = get_env_variable_value(args[i]);
            add_env_var(l_value, r_value, envp);
            add_exp_var(l_value, r_value,envp);
        }
	}
    return (0);
}
