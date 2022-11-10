/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:03:53 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/25 12:45:58 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void unset_exp(char **args, t_envp *envp)
{
	int	i;
	int j;
	int k;
	char *name;

	i = 0;
	j = -1;
	k = -1;
	while(envp->exp_lst[++k])
		;
	while(args[++i])
	{
		while(envp->env[++j])
		{
			name = get_variable_name(args[i]);
			if(ft_strnstr(name,get_variable_name(envp->exp_lst[j]),ft_strlen(envp->exp_lst[j])))
			{
				while(envp->exp_lst[j])
				{
					envp->exp_lst[j] = envp->exp_lst[j+1];
					j++;
				}
				envp->exp_lst[j] = NULL;
			}
		}
		j = -1;
	}
}



// enleve un element de la liste d'env et exp
// retourne 0 en cas de succes et 1 en cas d'erreur
int ft_unset(char **args, t_envp *envp)
{
	int	i;
	int j;
	int k;
	char *name;

	i = 0;
	j = -1;
	k = -1;
	//unset_exp(args, envp);
	while(envp->env[++k])
		;
	while(args[++i])
	{
		while(envp->env[++j])
		{
			name = get_variable_name(args[i]);
			if(ft_strnstr(name,get_variable_name(envp->env[j]),ft_strlen(envp->env[j])))
			{
				while(envp->env[j])
				{
					envp->env[j] = envp->env[j+1];
					j++;
				}
				envp->env[j] = NULL;
			}
		}
		j = -1;
	}
	
	while(envp->env[++j])
		;
	if( k > j)
		return(0);
	return (-1);
}
