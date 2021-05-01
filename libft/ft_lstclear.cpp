/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:41:14 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/29 01:09:23 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *cur_elem;

	if (del)
	{
		while (*lst != NULL)
		{
			cur_elem = *lst;
			*lst = cur_elem->next;
			del(cur_elem->content);
			free(cur_elem);
		}
	}
}
