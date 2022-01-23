/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:10 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 15:17:42 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_node(char **envp, char *delnode)
{
	int		i;
	int		name_len;
	char	*equal_pos;

	i = -1;
	while (envp[++i])
	{
		equal_pos = ft_strchr(envp[i], '=');
		name_len = t_name_len(envp[i], equal_pos);
		if (ft_strncmp(delnode, envp[i], name_len) == 0)
			return (1);
	}
	return (0);
}

int	pass_node(char *envp, char *delnode)
{
	int		name_len;
	char	*equal_pos;

	equal_pos = ft_strchr(envp, '=');
	name_len = t_name_len(envp, equal_pos);
	if (ft_strncmp(delnode, envp, name_len) == 0)
		return (1);
	return (0);
}

char	**delete_node(char **envp, char *delnode, int count)
{
	int		i;
	int		j;
	char	**ret_envp;

	ret_envp = (char **)ft_calloc(count, sizeof(char *));
	i = 0;
	j = -1;
	while (envp[i] != NULL)
	{
		if (!pass_node(envp[i], delnode))
			ret_envp[++j] = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	ret_envp[++j] = NULL;
	free(envp);
	return (ret_envp);
}

int	t_name_len(char *s1, char *s2)
{
	int	len;

	if (!s2)
		return (ft_strlen(s1));
	len = ft_strlen(s1) - ft_strlen(s2);
	if (len < 0)
		return (len * -1);
	return (len);
}
