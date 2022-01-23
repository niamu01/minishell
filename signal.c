/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:34 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:34 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

void	sub_sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
}

void	subshell_signal(void)
{
	signal(SIGINT, sub_sighandler);
}

void	setting_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}
