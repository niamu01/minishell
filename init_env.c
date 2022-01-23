/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:02 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:04 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_shell *sh)
{
	char	*new_pwd;
	char	*new_oldpwd;
	char	*cur_location;

	cur_location = getcwd(NULL, 0);
	if (!cur_location)
	{
		ft_putendl_fd("cd : error retrieving current directory: \
getcwd: cannot access parent directories: No such file or directory", 2);
		cur_location = ft_strjoin(find_env(sh->env, "PWD"), "/.");
	}
	new_oldpwd = ft_strjoin("OLDPWD=", find_env(sh->env, "PWD"));
	export_function(sh, sh->env, new_oldpwd);
	new_pwd = ft_strjoin("PWD=", cur_location);
	export_function(sh, sh->env, new_pwd);
	free(cur_location);
	free(new_oldpwd);
	free(new_pwd);
}

void	init_pwd(t_shell *sh)
{
	unset_function(sh, "OLDPWD");
	export_function(sh, sh->env, "OLDPWD");
}

void	init_shlvl(t_shell *sh)
{
	int		temp;
	char	*value;
	char	*ret_shlvl;

	value = find_env(sh->env, "SHLVL");
	temp = ft_atoi(value);
	value = ft_itoa(temp + 1);
	ret_shlvl = ft_strjoin("SHLVL=", value);
	export_function(sh, sh->env, ret_shlvl);
	free(ret_shlvl);
	free(value);
}
