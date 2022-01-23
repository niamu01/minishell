/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:15 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:16 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_space(char *str)
{
	int		i;
	int		len;
	int		left;
	int		right;
	char	*no_space;

	i = 0;
	left = 0;
	while (str[i] && str[i] == ' ')
		left = ++i;
	right = 0;
	i = 0;
	len = ft_strlen(str);
	while (i > len - 1 && str[len - 1 - i] && str[len - 1 - i] == ' ')
		right = ++i;
	if (len < left + right)
		return (ft_strdup(str));
	no_space = (char *)ft_calloc(len - left - right + 1, sizeof(char));
	ft_memcpy(no_space, str + left, len - left - right);
	return (no_space);
}

int	is_numeric_error(char *str, unsigned long long abs)
{
	char	minus;

	minus = 0;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			minus = 1;
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (1);
		str++;
	}
	if ((!minus && abs > LLONG_MAX) || \
		(minus && abs > (unsigned long long)LLONG_MAX + 1))
		return (1);
	return (0);
}

char	ft_atoll(char *str, unsigned long long *abs)
{
	unsigned long long	num;
	char				minus;

	minus = 0;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			minus = 1;
		str++;
	}
	num = 0;
	while (*str && *str >= 48 && *str <= 57)
	{
		num = num * 10 + (*str - 48);
		str++;
	}
	*abs = num;
	if (minus)
		return ((char)(num * -1));
	return ((char) num);
}

void	exit_numeric_error(char *arg, int *status)
{
	char	*str;

	str = ft_strjoin("exit: ", arg);
	print_error(str, ": numeric argument required", 255);
	free(str);
	*status = 255;
}

int	exit_function(t_shell *sh, t_cmd *cmd, int message)
{
	unsigned long long	abs;
	int					status;
	char				*no_space;

	status = sh->exit_status;
	if (message)
		write(2, "exit\n", 5);
	if (cmd && cmd->argv[1])
	{
		no_space = remove_space(cmd->argv[1]);
		status = ft_atoll(no_space, &abs);
		if (is_numeric_error(no_space, abs))
			exit_numeric_error(cmd->argv[1], &status);
		else if (cmd->argv[2])
		{
			print_error("exit: ", "too many arguments", 1);
			free(no_space);
			return (1);
		}
		free(no_space);
	}
	free_all_memory(sh);
	exit(status);
}
