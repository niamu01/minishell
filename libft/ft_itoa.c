/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:43:16 by yeju              #+#    #+#             */
/*   Updated: 2021/10/15 00:43:36 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_printnum(long int num)
{
	if (num < 0)
		return (-num);
	return (num);
}

static int	ft_len(long int num)
{
	int	len;

	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num != 0)
	{
		num = num / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	int		minus;
	char	*c;

	if (n < 0)
		minus = -1;
	else
		minus = 1;
	len = ft_len(n);
	c = (char *)malloc(sizeof(char) * len + 1);
	if (c == NULL)
		return (0);
	c[len] = '\0';
	while (len--)
	{
		c[len] = '0' + ft_printnum(n % 10);
		n = ft_printnum(n / 10);
	}
	if (minus == -1)
		c[0] = '-';
	return (c);
}
