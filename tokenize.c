/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:21 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:22 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == ' ')
		return (blank);
	if (c == ';')
		return (semicolon);
	if (c == '|')
		return (pipeline);
	if (c == '<')
		return (redirection_input);
	if (c == '>')
		return (redirection_output);
	return (word);
}

void	set_new_token(t_token **address, enum e_token type, \
						char *start, size_t len)
{
	t_token	*token;

	token = *address;
	if (token->str)
	{
		token->next = (t_token *)ft_calloc(1, sizeof(t_token));
		*address = token->next;
		token = token->next;
	}
	token->type = type;
	token->str = ft_calloc(len + 1, sizeof(char));
	ft_memcpy(token->str, start, len);
}

char	*skip_quote(char *str, char quote)
{
	++str;
	while (*str && *str != quote)
		str++;
	return (str);
}

void	cut_string_to_token(t_token *token, char *str)
{
	char		*save;

	while (*str)
	{
		save = str;
		while (*str && !is_operator(*str))
		{
			if (*str == '"' || *str == '\'')
				str = skip_quote(str, *str);
			str++;
		}
		if (str != save)
			set_new_token(&token, word, save, str - save);
		if (*str && is_operator(*str) > pipeline \
			&& *(str + 1) && is_operator(*str) == is_operator(*(str + 1)))
		{
			set_new_token(&token, is_operator(*str) + 2, str, 2);
			str++;
		}
		else if (*str && is_operator(*str) > blank)
			set_new_token(&token, is_operator(*str), str, 1);
		if (*str)
			str++;
	}
}

void	tokenize_string(t_shell *sh)
{
	sh->token = (t_token *)ft_calloc(1, sizeof(t_token));
	cut_string_to_token(sh->token, sh->readln);
	rearrange_token(sh);
}
