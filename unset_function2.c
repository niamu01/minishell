/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_function2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:05 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 15:17:22 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_input(char *node)
{
	int	i;
	int	count;

	count = 0;
	while (node[count] != '\0')
		++count;
	if (count == 0)
		return (print_type_error("unset", node));
	i = -1;
	while (!(node[++i] == '\0'))
	{
		if (ft_isalnumsign(node[i]) == 0)
			return (print_type_error("unset", node));
		if (ft_isalnumsign(node[count - i]) == 3)
			return (print_type_error("unset", node));
		if (ft_isalnumsign(node[0]) == 2)
			return (print_type_error("unset", node));
		if (node[i] == '=')
			return (print_type_error("unset", node));
	}
	return (0);
}

int	check_export_input(char *node)
{
	int	i;
	int	count;

	count = 0;
	while (node[count] != '\0')
		++count;
	if (count == 0)
		return (print_type_error("export", node));
	i = -1;
	while (!(node[++i] == '\0'))
	{
		if (ft_isalnumsign(node[i]) == 0)
			return (print_type_error("export", node));
		if (ft_isalnumsign(node[count - i]) == 3)
			return (print_type_error("export", node));
		if (ft_isalnumsign(node[0]) == 2)
			return (print_type_error("export", node));
		if (node[0] == '=')
			return (print_type_error("export", node));
		if (node[i] == '=')
			break ;
	}
	return (0);
}

int	unset_function(t_shell *sh, char *delnode)
{
	int	count;
	int	err_code;

	err_code = check_unset_input(delnode);
	if (err_code)
		return (err_code);
	count = 0;
	while (sh->env[count])
		count++;
	if (count < 1)
		return (0);
	if (check_node(sh->env, delnode))
		sh->env = delete_node(sh->env, delnode, count);
	return (0);
}

int	unset_func(t_shell *sh, t_cmd *cmd)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (cmd->argv[++i])
		status |= unset_function(sh, cmd->argv[i]);
	return (status);
}

int	ft_isalnumsign(int c)
{
	if (('a' <= c && 'z' >= c) || ('A' <= c && 'Z' >= c) \
		|| c == '_' || c == '=')
		return (1);
	else if ('0' <= c && c <= '9')
		return (2);
	else if (c == '#')
		return (3);
	else
		return (0);
}
