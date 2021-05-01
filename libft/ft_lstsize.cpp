/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:43:05 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/22 23:43:07 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		length;
	t_list	*cur_elem;

	cur_elem = lst;
	length = 0;
	while (cur_elem != NULL)
	{
		cur_elem = cur_elem->next;
		length++;
	}
	return (length);
}
