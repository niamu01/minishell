/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:39 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:40 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **count1, char **count2)
{
	char	*temp;

	temp = *count1;
	*count1 = *count2;
	*count2 = temp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	split_equal_and_print(char *env)
{
	char	*equal_pos;
	int		print_len;

	print_len = 0;
	equal_pos = NULL;
	if (ft_strchr(env, '='))
	{
		equal_pos = ft_strchr(env, '=');
		print_len = (ft_strlen(env) - ft_strlen(equal_pos));
	}
	else if (!ft_strchr(env, '='))
		print_len = ft_strlen(env);
	ft_putstr_len(env, print_len);
	if (equal_pos)
	{
		ft_putstr_len(equal_pos, 1);
		ft_putchar_fd('\"', 1);
		ft_putstr_fd(equal_pos + 1, 1);
		ft_putendl_fd("\"", 1);
	}
	else if (!equal_pos)
		ft_putchar_fd('\n', 1);
	return ;
}

void	sort_env(char **origin_env)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	while (origin_env[count])
		count++;
	if (count == 0 | count == 1)
		return ;
	i = -1;
	while (++i < count)
	{
		j = -1;
		while (++j < count - 1)
		{
			if (ft_strcmp(origin_env[j], origin_env[j + 1]) > 0)
				ft_swap(&origin_env[j], &origin_env[j + 1]);
		}
	}
}

int	export_only(t_shell *sh)
{
	char	**env;
	int		count;

	env = copy_inherit_env(sh->env);
	sort_env(env);
	count = -1;
	while (env[++count])
	{
		ft_putstr_fd("declare -x ", 1);
		split_equal_and_print(env[count]);
	}
	count = -1;
	while (env[++count])
		free(env[count]);
	free(env);
	return (0);
}
