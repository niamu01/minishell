/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:09 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 15:03:29 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i++])
	{
		free(paths[i]);
	}
	free(paths);
}

char	*find_path(char **envp, char *cmd)
{
	int			i;
	char		*value;
	char		*path;
	char		**paths;
	struct stat	path_info;

	if (!*cmd)
		return (0);
	value = find_env(envp, "PATH");
	paths = ft_split(value, ':');
	i = -1;
	while (paths[++i])
	{
		value = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], value);
		free(value);
		if (stat(path, &path_info) == 0)
		{
			free_paths(paths);
			return (path);
		}
		if (stat(path, &path_info) == -1)
			free(path);
	}
	return (0);
}
