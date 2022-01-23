/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujikim <sujikim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 14:03:31 by sujikim           #+#    #+#             */
/*   Updated: 2022/01/23 14:07:23 by sujikim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include "libft.h"
# define IN 0
# define OUT 1

enum e_token {
	word = 0,
	blank,
	filepath,
	semicolon,
	pipeline,
	redirection_input,
	redirection_output,
	redirection_heredoc,
	redirection_append,
};

typedef struct s_token {
	enum e_token	type;
	char			*str;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd {
	char			**argv;
	int				in;
	int				out;
	int				is_in_pipe;
	int				order;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_term {
	int				init;
	struct termios	basic;
	struct termios	noncanon;
}					t_term;

typedef struct s_shell {
	char			**env;
	char			*readln;
	char			error_flag;
	t_token			*token;
	t_cmd			*cmd;
	int				exit_status;
	t_term			term;
}					t_shell;

extern void	rl_replace_line(const char *text, int clear_undo);
char		**copy_inherit_env(char **inherit);
char		*find_env(char **env, char *name);
void		setting_signals(void);
void		ignore_signals(void);
void		subshell_signal(void);
void		noncanonical_terminal(t_shell *sh);
void		canonical_terminal(t_shell *sh);
void		check_closing_quote(t_shell *sh);
void		tokenize_string(t_shell *sh);
void		rearrange_token(t_shell *sh);
void		alias_and_remove_quote(t_shell *sh);
char		*skip_quote(char *str, char quote);
void		substitute_env(t_shell *sh, t_token *token, char *str);
void		without_space(char *spot, char *name, char *value, t_token *token);
void		substitute_status_code(int status, char **origin);
void		remove_empty_token(t_shell *sh, t_token *token, t_token *prev);
void		make_command_setting(t_shell *sh);
void		try_redirection(t_shell *sh, t_cmd *cmd, t_token *token);
int			open_here_document(t_shell *sh, char *endpoint);
void		go_to_next_cmd(t_cmd **address, char ***arg);
void		change_stream(int stream, int *old, int new);

int			is_builtin_function(t_cmd *cmd);
int			pwd_function(t_shell *sh);
int			export_func(t_shell *sh, t_cmd *cmd);
int			unset_func(t_shell *sh, t_cmd *cmd);
int			cd_function(t_shell *sh, t_cmd *cmd);
int			env_function(char **env);
int			echo_function(t_cmd *cmd);

void		execute_command(t_shell *sh);
int			execute_with_path(t_shell *sh, t_cmd *cmd);

void		update_pwd(t_shell *sh);
void		init_pwd(t_shell *sh);
void		init_shlvl(t_shell *sh);

char		*find_path(char **envp, char *cmd);
int			export_only(t_shell *sh);
int			print_error(char *s1, char *errormessage, int err_no);
int			print_type_error(char *type, char *s1);
void		ft_putstr_len(char *s, int len);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalnumsign(int c);
int			check_export_input(char *node);

int			unset_function(t_shell *sh, char *delnode);
char		**delete_node(char **envp, char *delnode, int count);
int			check_node(char **envp, char *delnode);
int			export_function(t_shell *sh, char **envp, char *addnode);
int			t_name_len(char *s1, char *s2);

void		close_fd(t_cmd *cmd);
void		free_readline_memory(t_shell *sh);
void		free_all_memory(t_shell *sh);
int			exit_function(t_shell *sh, t_cmd *cmd, int message);

#endif
