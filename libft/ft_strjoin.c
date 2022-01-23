/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 16:48:04 by yeju              #+#    #+#             */
/*   Updated: 2021/10/15 00:46:10 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	string = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (string)
	{
		index = 0;
		while (*s1)
		{
			string[index++] = *s1;
			s1++;
		}
		while (*s2)
		{
			string[index++] = *s2;
			s2++;
		}
		string[index] = '\0';
	}
	return (string);
}
