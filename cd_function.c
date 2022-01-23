/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_function.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:34 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:35 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_alias_path(t_shell *sh, t_cmd *cmd, char **path)
{
	char	*str;

	if (!cmd->argv[1] || !ft_strncmp(cmd->argv[1], "~", 2))
	{
		str = find_env(sh->env, "HOME");
		if (!*str)
			return (print_error("cd: ", "HOME not set", 1));
		*path = str;
	}
	else if (!ft_strncmp(cmd->argv[1], "-", 2))
	{
		str = find_env(sh->env, "OLDPWD");
		if (!*str)
			return (print_error("cd: ", "OLDPWD not set", 1));
		*path = str;
	}
	return (0);
}

int	cd_function(t_shell *sh, t_cmd *cmd)
{
	char	*str;
	int		status;

	if (!cmd->argv || !cmd->argv[0])
		return (-1);
	str = cmd->argv[1];
	if (cd_alias_path(sh, cmd, &str))
		return (1);
	status = chdir(str);
	if (status)
	{
		str = ft_strjoin("cd: ", cmd->argv[1]);
		print_error(str, ": No such file or directory", 1);
		free(str);
		return (1);
	}
	update_pwd(sh);
	return (status);
}
