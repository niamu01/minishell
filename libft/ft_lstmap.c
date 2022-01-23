/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:44:34 by yeju              #+#    #+#             */
/*   Updated: 2021/10/15 01:01:02 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;

	if (lst == NULL)
		return (NULL);
	temp = ft_lstnew(f(lst->content));
	if (lst->next != NULL)
		temp->next = ft_lstmap(lst->next, f, del);
	return (temp);
}
