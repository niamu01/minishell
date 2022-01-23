/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:24 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:24 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	noncanonical_terminal(t_shell *sh)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 1;
	tcsetattr(0, TCSANOW, &sh->term.noncanon);
}

void	canonical_terminal(t_shell *sh)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	tcsetattr(0, TCSANOW, &sh->term.basic);
}
