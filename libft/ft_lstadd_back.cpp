/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:40:45 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/28 22:00:26 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_elem;

	cur_elem = *lst;
	if (lst == NULL || *lst == NULL)
		*lst = new;
	else
	{
		while (cur_elem->next != NULL)
			cur_elem = cur_elem->next;
		cur_elem->next = new;
	}
}
