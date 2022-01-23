# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/23 15:22:42 by yeju              #+#    #+#              #
#    Updated: 2022/01/23 15:34:40 by yeju             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAG = -Wall -Werror -Wextra
CLUSTER_INCLUDE = -I -I${HOME}/.brew/opt/readline/include -I./libft
CLUSTER_LINK = -L./libft -lft -L${HOME}/.brew/opt/readline/lib -lreadline
LIBFT = ./libft/

SRCS = readline.c signal.c tokenize.c tokenize2.c append_input.c \
		free_memory.c command_set.c redirection.c env.c redirection2.c \
		alias.c alias2.c alias_and_remove_quote.c \
		execute_command.c execute_command2.c \
		exit_function.c export_function.c unset_function.c unset_function2.c \
		sort_env.c init_env.c error.c find_path.c terminal.c builtin_function.c\
		cd_function.c

OBJS = $(SRCS:.c=.o)

%o : %c
	@gcc $(CFLAG) $(CLUSTER_INCLUDE) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) bonus -C $(LIBFT)
	@gcc $(CFLAG) $(CLUSTER_INCLUDE) $(CLUSTER_LINK) $(OBJS) -o $(NAME)

clean :
	@$(MAKE) clean -C $(LIBFT)
	@rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) fclean -C $(LIBFT)
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
