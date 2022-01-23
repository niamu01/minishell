/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:32 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:33 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmd_list(t_cmd *cmd, t_token *token)
{
	int		order;

	order = 0;
	cmd->out = 1;
	while (token)
	{
		if (token->type == semicolon || token->type == pipeline)
		{
			cmd->next = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
			if (token->type == pipeline)
			{
				cmd->is_in_pipe = 1;
				cmd->next->is_in_pipe = 1;
			}
			cmd = cmd->next;
			cmd->out = 1;
		}
		if (token->type == semicolon)
			order++;
		cmd->order = order;
		token = token->next;
	}
}

void	make_argv_from_token(t_cmd *cmd, t_token *token)
{
	int		len;

	len = 0;
	while (token)
	{
		if (token->type == semicolon || token->type == pipeline)
		{
			cmd->argv = (char **)ft_calloc(len + 1, sizeof(char *));
			cmd = cmd->next;
			len = 0;
		}
		else if (token->type == word)
			len++;
		token = token->next;
	}
	if (len)
		cmd->argv = (char **)ft_calloc(len + 1, sizeof(char *));
}

void	go_to_next_cmd(t_cmd **address, char ***arg)
{
	t_cmd	*cmd;

	if (!*address)
		return ;
	cmd = *address;
	cmd = cmd->next;
	if (cmd)
		*arg = cmd->argv;
	*address = cmd;
}

void	save_args(t_cmd *cmd, t_token *token)
{
	char	**arg;

	arg = cmd->argv;
	while (token)
	{
		if (token->type == word)
			*arg++ = token->str;
		else if (token->type == semicolon \
			|| (token->type == pipeline && cmd->next))
			go_to_next_cmd(&cmd, &arg);
		token = token->next;
	}
}

void	make_command_setting(t_shell *sh)
{
	sh->cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	sh->cmd->out = 1;
	make_cmd_list(sh->cmd, sh->token);
	try_redirection(sh, sh->cmd, sh->token);
	make_argv_from_token(sh->cmd, sh->token);
	save_args(sh->cmd, sh->token);
}
