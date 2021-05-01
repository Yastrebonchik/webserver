/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcedra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 23:42:22 by kcedra            #+#    #+#             */
/*   Updated: 2020/05/23 15:37:54 by kcedra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cur_elem;

	if (lst == NULL)
		return (NULL);
	cur_elem = lst;
	while (cur_elem->next != NULL)
		cur_elem = cur_elem->next;
	return (cur_elem);
}
