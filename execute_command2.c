/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:18 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:19 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *sh, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (echo_function(cmd));
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (cd_function(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (pwd_function(sh));
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (export_func(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (unset_func(sh, cmd));
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (env_function(sh->env));
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (exit_function(sh, cmd, 0));
	return (0);
}

int	is_builtin(t_cmd *cmd)
{
	if (!ft_strncmp(cmd->argv[0], "echo", 5))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "pwd", 4))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "env", 4))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (1);
	return (0);
}

int	is_relative_or_absolute_path(char *str)
{
	if (*str && *str == '/')
		return (1);
	if (*str && *str == '.')
	{
		str++;
		if (!*str || *str == '/')
			return (1);
		if (*str == '.' && *(str + 1) && *(str + 1) == '/')
			return (1);
	}
	return (0);
}

int	execute_relative_or_absolute_path(t_shell *sh, t_cmd *cmd, char flag)
{
	int			status;
	struct stat	info;

	status = stat(cmd->argv[0], &info);
	if (S_ISDIR(info.st_mode))
		return (print_error(cmd->argv[0], ": is a directory", 126));
	if (status && flag)
		return (print_error(cmd->argv[0], ": No such file or directory", 127));
	if (status)
		return (print_error(cmd->argv[0], ": command not found", 127));
	status = execve(cmd->argv[0], cmd->argv, sh->env);
	if (status >= 0)
		return (status);
	return (print_error(cmd->argv[0], ": Permission denied", 126));
}

int	execute_with_path(t_shell *sh, t_cmd *cmd)
{
	char		*path;
	char		flag;

	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (is_builtin(cmd))
		return (execute_builtin(sh, cmd));
	flag = is_relative_or_absolute_path(cmd->argv[0]);
	if (!flag)
	{
		path = find_path(sh->env, cmd->argv[0]);
		if (path)
			return (execve(path, cmd->argv, sh->env));
	}
	return (execute_relative_or_absolute_path(sh, cmd, flag));
}
