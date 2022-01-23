/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:37 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:38 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_function(t_shell *sh)
{
	char	*pwd;
	char	*env_pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, 1);
	if (!pwd)
	{
		env_pwd = find_env(sh->env, "PWD");
		ft_putendl_fd(env_pwd, 1);
	}
	free(pwd);
	return (0);
}

int	is_option(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str++ != '-')
		return (0);
	while (*str)
		if (*str++ != 'n')
			return (0);
	return (1);
}

int	echo_function(t_cmd *cmd)
{
	char	**argv;
	int		option;

	argv = ++cmd->argv;
	option = is_option(*argv);
	while (*argv && is_option(*argv))
		argv++;
	while (*argv)
	{
		write(1, *argv, ft_strlen(*argv));
		if (*++argv)
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}

int	is_builtin_function(t_cmd *cmd)
{
	if (cmd->is_in_pipe)
		return (0);
	if (!cmd->argv || !cmd->argv[0])
		return (0);
	if (!ft_strncmp(cmd->argv[0], "cd", 3))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "export", 7))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "unset", 6))
		return (1);
	if (!ft_strncmp(cmd->argv[0], "exit", 5))
		return (1);
	return (0);
}
