/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 13:59:42 by yeju              #+#    #+#             */
/*   Updated: 2022/01/23 13:59:43 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*save_first_words(t_token *token, char *spot, char *word)
{
	char	*str;
	char	*save;

	save = token->str;
	str = (char *)ft_calloc(spot - save + ft_strlen(word) + 1, 1);
	token->str = str;
	ft_memcpy(str, save, spot - save - 1);
	str += spot - save - 1;
	ft_memcpy(str, word, ft_strlen(word));
	return (save);
}

char	*save_last_words(char *spot, char *name, char *word)
{
	char	*str;
	char	*save;

	str = (char *)ft_calloc(ft_strlen(spot) - ft_strlen(name) \
							+ ft_strlen(word) + 1, sizeof(char));
	save = str;
	ft_memcpy(str, word, ft_strlen(word));
	str += ft_strlen(word);
	ft_memcpy(str, spot + ft_strlen(name), ft_strlen(spot) - ft_strlen(name));
	return (save);
}

void	without_space(char *spot, char *name, char *value, t_token *token)
{
	char	**words;
	char	*prev;
	t_token	*next;
	int		i;

	words = ft_split(value, ' ');
	prev = save_first_words(token, spot, words[0]);
	i = 1;
	next = token->next;
	while (words[i] && words[i + 1])
	{
		token->next = (t_token *)ft_calloc(1, sizeof(t_token));
		token = token->next;
		token->str = words[i];
		i++;
	}
	token->next = (t_token *)ft_calloc(1, sizeof(t_token));
	token = token->next;
	token->next = next;
	token->str = save_last_words(spot, name, words[i]);
	free(words[0]);
	free(words[i]);
	free(words);
	free(prev);
}

void	remove_empty_token(t_shell *sh, t_token *token, t_token *prev)
{
	t_token	*save;

	save = 0;
	free(token->str);
	token->str = 0;
	if (!token->next)
	{
		if (!prev)
		{
			sh->error_flag = 1;
			sh->exit_status = 0;
			return ;
		}
		free(token);
		prev->next = 0;
		return ;
	}
	save = token->next->next;
	token->str = token->next->str;
	token->type = token->next->type;
	free(token->next);
	token->next = save;
}
