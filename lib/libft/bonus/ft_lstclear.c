/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleroux <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:35:40 by jleroux           #+#    #+#             */
/*   Updated: 2021/10/27 15:07:48 by jleroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst | !*lst)
		return ;
	if ((*lst)->next != NULL)
		ft_lstclear(&(*lst)->next, *del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}
