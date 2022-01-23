/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:45:37 by yeju              #+#    #+#             */
/*   Updated: 2021/10/15 00:26:56 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*new_s;
	unsigned char	find;

	new_s = (unsigned char *)s;
	find = c;
	i = 0;
	while (i < n)
	{
		if (new_s[i] == find)
			return ((new_s + i));
		i++;
	}
	return (0);
}
