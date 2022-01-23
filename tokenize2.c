/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:17 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:17 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_error(t_shell *sh, t_token *token, char next)
{
	char	*str;

	if (!next)
		str = ft_strjoin(token->str, "\'");
	else if (token->next)
		str = ft_strjoin(token->next->str, "\'");
	else
		str = ft_strdup("newline\'");
	print_error("syntax error near unexpected token `", str, 1);
	free(str);
	sh->error_flag = 1;
	sh->exit_status = 258;
}

int	no_command_after(t_token *token)
{
	if (!token->next)
		return (1);
	token = token->next;
	while (token && token->type != pipeline && token->type != semicolon)
	{
		if (token->type == word)
			return (0);
		token = token->next;
	}
	return (1);
}

void	rearrange_token(t_shell *sh)
{
	t_token	*token;

	token = sh->token;
	if (token->type == semicolon || token->type == pipeline)
		token_error(sh, token, 0);
	while (token && !sh->error_flag)
	{
		if (token->type > pipeline && token->next && token->next->type == word)
			token->next->type = filepath;
		if (token->type > pipeline && (!token->next \
			|| token->next->type != filepath))
			token_error(sh, token, 1);
		else if (token->type == pipeline && no_command_after(token))
			token_error(sh, token, 0);
		else if (token->type > filepath && token->next \
		&& (token->next->type == semicolon || token->next->type == pipeline))
			token_error(sh, token, 1);
		token = token->next;
	}
}
