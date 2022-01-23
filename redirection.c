/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:44 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:04:18 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_stream(int stream, int *old, int new)
{
	if (*old < 0)
		return ;
	if (*old > stream)
		close(*old);
	*old = new;
}

void	open_error(t_shell *sh, char *filepath)
{
	sh->error_flag = 1;
	print_error(filepath, ": No such file of directory", 1);
	sh->exit_status = 1;
}

void	open_filepath_and_set_fd(t_shell *sh, t_cmd *cmd, \
								enum e_token type, t_token *next)
{
	int		openfd;
	int		open_mode;
	char	*filepath;

	filepath = next->str;
	if (type == redirection_heredoc)
		openfd = open_here_document(sh, filepath);
	else
	{
		open_mode = O_RDWR;
		if (type == redirection_output)
			open_mode |= O_TRUNC | O_CREAT;
		else if (type == redirection_append)
			open_mode |= O_APPEND | O_CREAT;
		openfd = open(filepath, open_mode, S_IRWXU | S_IRWXG | S_IRWXO);
		if (openfd < 0)
			open_error(sh, filepath);
	}
	if (type == redirection_input || type == redirection_heredoc)
		change_stream(IN, &cmd->in, openfd);
	else
		change_stream(OUT, &cmd->out, openfd);
}

void	open_pipe_and_set_fd(t_shell *sh, t_cmd *cmd)
{
	int		fd[2];
	int		check;

	check = pipe(fd);
	if (check)
	{
		sh->exit_status = print_error("pipe: ", strerror(errno), 1);
		sh->error_flag = 1;
		return ;
	}
	if (cmd->out == 1)
		change_stream(OUT, &cmd->out, fd[1]);
	else
		close(fd[1]);
	change_stream(IN, &cmd->next->in, fd[0]);
}

void	try_redirection(t_shell *sh, t_cmd *cmd, t_token *token)
{
	char	**arg;

	while (token)
	{
		if (token->type == semicolon)
			go_to_next_cmd(&cmd, &arg);
		else if (token->type == pipeline && cmd->next)
		{
			open_pipe_and_set_fd(sh, cmd);
			go_to_next_cmd(&cmd, &arg);
		}
		else if (token->type > filepath && token->next)
			open_filepath_and_set_fd(sh, cmd, token->type, token->next);
		token = token->next;
	}
}
