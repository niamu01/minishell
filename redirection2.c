/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:02:42 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:02:42 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_until_endpoint(char *endpoint, int fd)
{
	char	*str;

	str = ft_strdup("");
	while (1)
	{
		free(str);
		str = readline("> ");
		if (!str)
			write(0, "\033[A\033[C\033[C", 9);
		if (!ft_strncmp(endpoint, str, ft_strlen(endpoint) + 1))
			break ;
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
	free(str);
}

int	open_here_document(t_shell *sh, char *endpoint)
{
	int			fd[2];
	int			status;
	pid_t		pid;

	pipe(fd);
	pid = fork();
	if (pid)
	{
		close(fd[1]);
		waitpid(pid, &status, 0);
		canonical_terminal(sh);
		if (WEXITSTATUS(status))
			sh->error_flag = 1;
		ignore_signals();
		return (fd[0]);
	}
	close(fd[0]);
	subshell_signal();
	read_until_endpoint(endpoint, fd[1]);
	close(fd[1]);
	exit(0);
}
