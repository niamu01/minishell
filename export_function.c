/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:12 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:13 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	same_name_in_env(char **envp, char *addnode, int name_len)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], addnode, name_len) \
			&& (envp[i][name_len] == '=' || envp[i][name_len] == '\0'))
			return (1);
	}
	return (0);
}

char	**change_node(char **envp, char *addnode, int name_len)
{
	int		j;
	int		count;
	char	**ret_envp;

	count = 0;
	while (envp[count])
		count++;
	ret_envp = (char **)ft_calloc(count + 1, sizeof(char *));
	j = -1;
	while (envp[++j])
	{
		ret_envp[j] = ft_strdup(envp[j]);
		if (!ft_strncmp(envp[j], addnode, name_len) \
			&& (envp[j][name_len] == '=' || envp[j][name_len] == '\0'))
		{
			free(ret_envp[j]);
			ret_envp[j] = ft_strdup(addnode);
		}
	}
	ret_envp[j] = NULL;
	return (ret_envp);
}

char	**insert_node(char **envp, char *addnode, int name_len, int same_name)
{
	int		i;
	char	**ret_envp;

	i = -1;
	while (envp[++i])
	{
		if (same_name)
		{
			ret_envp = change_node(envp, addnode, name_len);
			return (ret_envp);
		}
	}
	ret_envp = (char **)ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (envp[++i])
		ret_envp[i] = ft_strdup(envp[i]);
	ret_envp[i] = ft_strdup(addnode);
	ret_envp[++i] = NULL;
	return (ret_envp);
}

int	export_function(t_shell *sh, char **envp, char *addnode)
{
	int		err_code;
	int		count;
	int		same;
	char	*equal_pos;
	char	**new;

	new = 0;
	err_code = check_export_input(addnode);
	if (err_code)
		return (err_code);
	equal_pos = ft_strchr(addnode, '=');
	same = same_name_in_env(envp, addnode, t_name_len(addnode, equal_pos));
	if (equal_pos || !same)
		new = insert_node(envp, addnode, t_name_len(addnode, equal_pos), same);
	if (new)
	{
		count = -1;
		while (envp[++count])
			free(envp[count]);
		free(envp);
		sh->env = new;
		return (0);
	}
	return (1);
}

int	export_func(t_shell *sh, t_cmd *cmd)
{
	int	i;
	int	status;

	status = 0;
	if (!cmd->argv[1])
		return (export_only(sh));
	i = 0;
	while (cmd->argv[++i])
		status |= export_function(sh, sh->env, cmd->argv[i]);
	return (status);
}
