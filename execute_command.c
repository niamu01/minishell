/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:22 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 14:51:15 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mornitoring_and_wait(t_cmd *cmd, int order)
{
	int		status;

	while (cmd && order == cmd->order)
	{
		close_fd(cmd);
		if (cmd->argv && cmd->argv[0] && cmd->argv[1] && \
			!ft_strncmp(cmd->argv[1], "/dev/random", 13))
		{
			usleep(5000);
			kill(cmd->pid, 9);
		}
		else
			waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(2, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit: 3\n", 8);
		return (128 + status);
	}
	return (WEXITSTATUS(status));
}

void	close_fds(t_cmd *save)
{
	while (save)
	{
		close_fd(save);
		save = save->next;
	}
}

void	execute_in_subshell(t_shell *sh, t_cmd *cmd)
{
	pid_t	pid;
	t_cmd	*save;
	int		order;

	order = cmd->order;
	save = cmd;
	while (cmd && order == cmd->order)
	{
		pid = fork();
		if (!pid)
		{
			subshell_signal();
			dup2(cmd->in, 0);
			dup2(cmd->out, 1);
			close_fds(save);
			if (cmd->argv[0])
				exit(execute_with_path(sh, cmd));
			exit(0);
		}
		cmd->pid = pid;
		cmd = cmd->next;
	}
	sh->exit_status = mornitoring_and_wait(save, order);
}

void	execute_in_current(t_shell *sh, t_cmd *cmd)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		status = cd_function(sh, cmd);
	else if (!ft_strncmp(cmd->argv[0], "exit", 5))
		status = exit_function(sh, cmd, 1);
	else if (!ft_strncmp(cmd->argv[0], "unset", 6))
		status = unset_func(sh, cmd);
	else if (!ft_strncmp(cmd->argv[0], "export", 7))
		status = export_func(sh, cmd);
	sh->exit_status = status;
	close_fd(cmd);
}

void	execute_command(t_shell	*sh)
{
	int		order;
	t_cmd	*cmd;

	cmd = sh->cmd;
	while (cmd)
	{
		order = cmd->order;
		if (is_builtin_function(cmd))
			execute_in_current(sh, cmd);
		else
			execute_in_subshell(sh, cmd);
		while (cmd && order == cmd->order)
			cmd = cmd->next;
	}
}
