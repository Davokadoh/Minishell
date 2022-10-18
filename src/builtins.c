/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Blaze <Blaze@42lausanne.ch>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:57:03 by Blaze             #+#    #+#             */
/*   Updated: 2022/10/16 15:01:05 by Blaze            ###    42Lausanne.ch    */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	builtin(char **tokens, t_envp *env)
{
    int i;

    i = 0;
    while (tokens[i])
    {
        if (ft_strncmp(tokens[i],"env",3) == 0)
            ft_env(env);
        if (ft_strncmp(tokens[i],"pwd",3) == 0)
            ft_pwd();
        if (ft_strncmp(tokens[i],"echo",4) == 0)
            ft_echo(tokens);
        i++;
    }
    return (0);
}


