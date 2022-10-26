/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:57:03 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/24 15:02:31 by btchiman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin(char **tokens, char ***env)
{
	if (ft_strncmp(tokens[0],"env",3) == 0)
		ft_env(*env);
	if (ft_strncmp(tokens[0],"pwd",3) == 0)
		ft_pwd();
	if (ft_strncmp(tokens[0],"echo",4) == 0)
		ft_echo(tokens);
	if (ft_strncmp(tokens[0],"export",6) == 0)
		*env = ft_export(tokens,*env);
	if (ft_strncmp(tokens[0],"unset",5) == 0)
		*env = ft_unset(tokens,*env);
	/*if (ft_strncmp(tokens[0],"cd",2) == 0)
		ft_cd(tokens, *env);*/
	if (ft_strncmp(tokens[0],"exit",4) == 0)
		ft_exit();
	return (0);
}


