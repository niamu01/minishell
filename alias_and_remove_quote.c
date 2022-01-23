/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_and_remove_quote.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 21:35:14 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:52 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_target_to_remove(char *str)
{
	char	c;
	char	c2;

	if (!*str)
		return (0);
	c = *str;
	if (c == '"' || c == '\'' || c == '\\')
		return (1);
	if (!*(str + 1))
		return (0);
	c2 = *(str + 1);
	if (c == '$' && (c2 == '\'' || c2 == '"'))
		return (1);
	return (0);
}

int	count_quote_and_escape(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			i++;
			str = skip_quote(str, *str);
		}
		if (is_target_to_remove(str))
			i++;
		if (*str)
			str++;
	}
	return (i);
}

char	*remove_quote(char *str, int i)
{
	char	*new;
	char	save;

	new = (char *)ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	i = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			save = *str;
			while (*++str != save)
				new[i++] = *str;
		}
		if (!is_target_to_remove(str))
			new[i++] = *str;
		if (*str)
			str++;
	}
	return (new);
}

void	remove_quote_and_escape(char **origin)
{
	int		i;
	char	*new;

	i = count_quote_and_escape(*origin);
	if (!i)
		return ;
	if (i == (int) ft_strlen(*origin))
		new = ft_strdup("");
	else
		new = remove_quote(*origin, i);
	free(*origin);
	*origin = new;
}

void	alias_and_remove_quote(t_shell *sh)
{
	t_token	*token;
	t_token	*prev;

	token = sh->token;
	prev = 0;
	while (token)
	{
		substitute_status_code(sh->exit_status, &token->str);
		substitute_env(sh, token, token->str);
		if (!*token->str)
			remove_empty_token(sh, token, prev);
		prev = token;
		token = token->next;
	}
	token = sh->token;
	while (token)
	{
		remove_quote_and_escape(&token->str);
		token = token->next;
	}
}
