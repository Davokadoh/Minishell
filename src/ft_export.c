/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:41:12 by btchiman          #+#    #+#             */
/*   Updated: 2022/11/07 17:37:04 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	export trie une liste de variable d'environement a l'initialisation
	puis ajoute a la fin de cette liste une nouvelle liste triee
	d'elements exporte si une variable se trouve deja dans cette seconde liste
	elle est remplace si elle est suivie par =
*/
int	add_exp_var(char *l_value, char *r_value, t_envp *envp)
{
	char *new_entry;
	
    new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
	//envp->exp_lst = ft_increnv(envp->exp_lst, l_value, new_entry);
	envp->exp_lst = incr(envp->exp_lst, l_value, new_entry);
	envp->exp_lst = ft_triAlpha(envp->exp_lst);
    ft_free(new_entry);
	return (0);
}

int	add_env_var(char *l_value, char *r_value, t_envp *envp)
{
    char *new_entry;

	new_entry = ft_strjoin(l_value,"=");
	new_entry = ft_strjoin(new_entry, r_value);
    //envp->env = ft_increnv(envp->env, l_value, new_entry);
	envp->env = incr(envp->env, l_value, new_entry);
    ft_free(new_entry);
    return (0);
}

void arg_loop(int i, char **args, t_envp *envp)
{
	char *l_value;
	char *r_value;

	if(!ft_isalpha(args[i][0]))
	{
		printf("export: %s: not a valid identifier \n",args[i]);
		return;
	}
    if (!ft_strchr(args[i],'='))
		add_exp_var(args[i],"",envp);
    else
    {
        l_value = get_variable_name(args[i]);
        r_value = get_env_variable_value(args[i]);
        add_env_var(l_value, r_value, envp);
        add_exp_var(l_value, r_value, envp);
    }
}

// ajoute un element au tableau de variable d'environnement et au tableau d'export
int	ft_export(char **args, t_envp  *envp)
{
	static int	a = 0;
    int     	i;

    i = -1;

	if(!a)
	{
		envp->exp_init = init_exp(envp->env);
		envp->exp_lst = malloc(sizeof(char **) * (1));
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
		arg_loop(i, args, envp);
	}
    return (0);
}
