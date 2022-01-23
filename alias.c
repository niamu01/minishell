/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:45 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 15:06:42 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env_name_and_value(char *str, char **env, char **name, char **value)
{
	int		len;
	char	*s;
	char	flag;

	s = str;
	len = 0;
	flag = 0;
	if (*s && ft_isdigit(*s))
	{
		len++;
		flag = 1;
	}
	while (!flag && *s && (ft_isalnum(*s) || *s == '_'))
	{
		len++;
		s++;
	}
	*name = (char *)ft_calloc(len + 1, sizeof(char));
	ft_memcpy(*name, str, len);
	if (!flag)
	{
		*value = find_env(env, *name);
		return ;
	}
	*value = *name + 1;
}

void	substitute_string(char **origin, int start, char *name, char *value)
{
	char	*change;
	char	*str;
	int		end;

	end = start + ft_strlen(name);
	change = (char *)ft_calloc(ft_strlen(*origin) - ft_strlen(name) \
							+ ft_strlen(value) + 1, sizeof(char));
	ft_memcpy(change, *origin, start);
	str = change + start;
	ft_memcpy(str, value, ft_strlen(value));
	str += ft_strlen(value);
	if ((int) ft_strlen(*origin) > end + 1)
		ft_memcpy(str, *origin + end + 1, ft_strlen(*origin) - end - 1);
	free(*origin);
	*origin = change;
}

void	alias_env(t_shell *sh, t_token *token, char *str, char flag)
{
	char	*name;
	char	*value;
	char	*temp;

	get_env_name_and_value(str, sh->env, &name, &value);
	if (!flag && ft_strchr(value, ' '))
	{
		without_space(str, name, value, token);
		free(name);
		return ;
	}
	if (!*value && token->type == filepath)
	{
		temp = ft_strjoin("$", name);
		print_error(temp, ": ambiguous redirect", 1);
		free(temp);
		sh->error_flag = 1;
		sh->exit_status = 1;
	}
	substitute_string(&token->str, str - token->str - 1, name, value);
	free(name);
	substitute_env(sh, token, token->str);
}

void	substitute_env(t_shell *sh, t_token *token, char *str)
{
	char	flag;

	flag = 0;
	while (*str)
	{
		if (!flag && *str == '\'')
			str = skip_quote(str, *str);
		if (*str == '\"')
			flag ^= 1;
		else if (*str == '$' && *(str + 1) && \
			 (ft_isalnum(*(str + 1)) || *(str + 1) == '_'))
		{
			alias_env(sh, token, ++str, flag);
			return ;
		}
		str++;
	}
}

void	substitute_status_code(int status, char **origin)
{
	char	*start;
	char	*number;

	start = ft_strnstr(*origin, "$?", ft_strlen(*origin));
	if (start)
	{
		number = ft_itoa(status);
		substitute_string(origin, start - *origin, "?", number);
		free(number);
		substitute_status_code(status, origin);
	}
}
