# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 12:04:25 by kfumiya           #+#    #+#              #
#    Updated: 2022/03/30 11:24:14 by ytomiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRCDIR		:= ./src
LIBFTDIR	:= ./libft

BUILTIN		:=	builtin.c \
				builtin_utils.c \
				cd.c \
				cd_utils.c \
				echo.c \
				env.c \
				env_utils.c \
				exit.c \
				export.c \
				export_utils_1.c \
				export_utils_2.c \
				pwd.c \
				unset.c \

EXECUTE		:=	check_executable.c \
				create_path.c \
				error_1.c \
				error_2.c \
				error_3.c \
				exec.c \
				exec_cmd.c \
				exec_utils.c \
				exec_utils_2.c \
				heredoc.c \
				heredoc_utils.c \
				pipe.c \
				redirect.c \
				require_expansion.c \
				wait_process.c \

EXPANSION	:=	expand.c \
				expand_rmquote.c \
				expand_str.c \
				expand_token.c \
				expand_utils_1.c \
				expand_utils_2.c \
				expand_var.c \
				expand_filename.c \

LEXER		:=	lexer.c \
				lexer_lst.c \
				lexer_token.c \
				lexer_utils.c \

PARSER		:=	node.c \
				parser.c \
				parser_command.c \
				parser_pipe.c \

UTILS		:=	env_utils.c \
				free_1.c \
				free_2.c \
				path.c \
				path_canonicalisation.c \
				str.c \
				init.c

SRCS		:= $(SRCDIR)/main.c \
				$(addprefix   $(SRCDIR)/builtin/, $(BUILTIN)) \
				$(addprefix   $(SRCDIR)/execute/, $(EXECUTE)) \
				$(addprefix $(SRCDIR)/expansion/, $(EXPANSION)) \
				$(addprefix     $(SRCDIR)/lexer/, $(LEXER)) \
				$(addprefix    $(SRCDIR)/parser/, $(PARSER)) \
				$(addprefix     $(SRCDIR)/utils/, $(UTILS))
OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)
LIBFT		:= ./libft/libft.a
INCLUDES	:= -I./includes -I./libft/includes -I$(HOME)/.brew/opt/readline/include
# INCLUDES	:= -I./includes -I./libft/includes -I/usr/local/opt/readline/include
RM			:= rm -rf

CC			:= gcc
READLINE	:= -L$(HOME)/.brew/opt/readline/lib -lreadline
# READLINE	:= -L/usr/local/opt/readline/lib -lreadline
# CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES) -MMD -MP 
CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES) -MMD -MP -g

all:		$(NAME)

-include $(DEPS)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(READLINE) $^ -o $@
	echo "set echo-control-characters off" > ~/.inputrc

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS) $(DEPS) *.o *.d
	$(RM) $(SRCDIR)/*.o $(SRCDIR)/*.d $(SRCDIR)/*/*.o $(SRCDIR)/*/*.d
	make clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)*
	make fclean -C $(LIBFTDIR)
	$(RM) ~/.inputrc

re: fclean all

.PHONY: all clean fclean re
