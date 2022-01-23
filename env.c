/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:28 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:29 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_inherit_env(char **inherit)
{
	int		i;
	char	**env;

	i = 0;
	while (inherit[++i] != NULL)
		i++;
	env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = -1;
	while (inherit[++i])
		env[i] = ft_strdup(inherit[i]);
	env[i] = NULL;
	return (env);
}

char	*find_env(char **env, char *name)
{
	int	i;

	if (!*name)
		return ("");
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)) \
			&& !ft_strncmp(env[i] + ft_strlen(name), "=", 1))
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return ("");
}

int	env_function(char **env)
{
	while (*env++ != NULL)
	{
		if (ft_strchr(*env, '='))
			ft_putendl_fd(*env, 1);
	}
	return (0);
}
