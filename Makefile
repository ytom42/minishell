# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 12:04:25 by kfumiya           #+#    #+#              #
#    Updated: 2022/03/24 13:54:45 by ytomiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRCDIR		:= ./src
LIBFTDIR	:= ./libft

# ファイル名は明示しないといけないらしいのでSRCSは最後に変更します。
SRCS		:= $(shell find $(SRCDIR) -name "*.c")
OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)
LIBFT		:= ./libft/libft.a
INCLUDES	:= -I./includes -I./libft/includes -I$(HOME)/.brew/opt/readline/include
# INCLUDES	:= -I./includes -I./libft/includes -I/usr/local/opt/readline/include

RM			:= rm -rf

CC			:= gcc

READLINE	:= -L$(HOME)/.brew/opt/readline/lib -lreadline
# READLINE	:= -L/usr/local/opt/readline/lib -lreadline
CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES) -MMD -MP -g
# CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES) -MMD -MP -g -fsanitize=address

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
