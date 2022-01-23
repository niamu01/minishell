/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:40 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:40 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_input(t_shell *sh)
{
	char	*old;
	char	*newline;
	char	*append;

	append = readline("> ");
	old = sh->readln;
	newline = ft_strjoin(old, "\n");
	sh->readln = ft_strjoin(newline, append);
	free(append);
	free(newline);
	free(old);
}

void	check_closing_quote(t_shell *sh)
{
	char	*str;
	char	flag;
	char	quote;

	str = sh->readln;
	flag = 0;
	while (*str)
	{
		if (*str == '"' || *str == '\'')
		{
			flag = 1;
			quote = *str++;
			while (*str && *str != quote)
				str++;
			if (*str == quote)
				flag = 0;
		}
		if (*str)
			str++;
	}
	if (flag)
	{
		append_input(sh);
		check_closing_quote(sh);
	}
}
