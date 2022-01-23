/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:25 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:26 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *s1, char *errormessage, int err_no)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd(errormessage, 2);
	return (err_no);
}

int	print_type_error(char *type, char *s1)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(": '", 2);
	ft_putstr_fd(s1, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

void	ft_putstr_len(char *s, int len)
{
	if (s == NULL)
		return ;
	write(1, s, len);
}
