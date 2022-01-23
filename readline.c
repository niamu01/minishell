/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:50 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:51 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_null_input(t_shell *sh)
{
	rl_on_new_line();
	rl_redisplay();
	write(0, "\033[A", 3);
	exit_function(sh, 0, 1);
}

void	get_user_input(t_shell *sh)
{
	sh->readln = readline("minishell : ");
	if (!sh->readln)
		is_null_input(sh);
	else if (*sh->readln)
	{
		ignore_signals();
		check_closing_quote(sh);
		tokenize_string(sh);
		if (sh->token && sh->token->str)
			add_history(sh->readln);
		if (sh->token && sh->token->str && !sh->error_flag)
		{
			alias_and_remove_quote(sh);
			if (!sh->error_flag)
				make_command_setting(sh);
			if (!sh->error_flag)
				execute_command(sh);
		}
	}
	free_readline_memory(sh);
}

void	init_minishell(t_shell *sh, char **envp)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	ft_memset(sh, 0, sizeof(t_shell));
	sh->env = copy_inherit_env(envp);
	init_pwd(sh);
	init_shlvl(sh);
	tcgetattr(0, &sh->term.basic);
	ft_memcpy(&sh->term.noncanon, &sh->term.basic, sizeof(struct termios));
	sh->term.noncanon.c_lflag &= ~ECHOCTL;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		sh;

	if (argc > 1)
	{
		printf("no argument needed : %s\n", argv[1]);
		return (0);
	}
	init_minishell(&sh, envp);
	while (1)
	{
		setting_signals();
		get_user_input(&sh);
	}
}
