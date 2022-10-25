/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: btchiman <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:04:58 by btchiman          #+#    #+#             */
/*   Updated: 2022/10/25 14:10:19 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_pwd(void)
{
	char *cwd;
	cwd = getcwd(NULL,0);
    if(!cwd)
    {
        perror("Error PWD");
        exit(EXIT_FAILURE);
    }
	printf("%s\n",cwd);
	ft_free(cwd);
}
