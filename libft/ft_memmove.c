/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:46:15 by yeju              #+#    #+#             */
/*   Updated: 2021/10/15 00:28:00 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*new_dest;
	unsigned char	*new_src;

	if (dst == src || len == 0)
		return (dst);
	new_dest = (unsigned char *)dst;
	new_src = (unsigned char *)src;
	if (dst < src)
	{
		while (len--)
			*(new_dest++) = *(new_src++);
	}
	else
	{
		while (len--)
			*(new_dest + len) = *(new_src + len);
	}
	return (dst);
}
