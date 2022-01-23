/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:06 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:07 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_memory(t_token *token)
{
	t_token	*save;

	while (token)
	{
		if (token->str)
			free(token->str);
		save = token->next;
		free(token);
		token = save;
	}
}

void	free_cmd_memory(t_cmd *cmd)
{
	t_cmd	*save;

	while (cmd)
	{
		if (cmd->argv)
			free(cmd->argv);
		if (cmd->pid && !kill(cmd->pid, 0))
			kill(cmd->pid, 9);
		save = cmd->next;
		free(cmd);
		cmd = save;
	}
}

void	close_fd(t_cmd *cmd)
{
	if (cmd->in > 0)
		close(cmd->in);
	if (cmd->out > 1)
		close(cmd->out);
}

void	free_readline_memory(t_shell *sh)
{
	if (!sh || !sh->readln)
		return ;
	if (sh->readln)
		free(sh->readln);
	free_token_memory(sh->token);
	free_cmd_memory(sh->cmd);
	sh->readln = 0;
	sh->error_flag = 0;
	sh->token = 0;
	sh->cmd = 0;
}

void	free_all_memory(t_shell *sh)
{
	char	**env;

	free_readline_memory(sh);
	env = sh->env;
	if (env)
	{
		while (*env)
			free(*env++);
		free(sh->env);
	}
}
