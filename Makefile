# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 12:04:25 by kfumiya           #+#    #+#              #
#    Updated: 2022/02/15 18:14:21 by ytomiyos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

SRCDIR		:= ./src

# ファイル名は明示しないといけないらしいのでSRCSは最後に変更します。
SRCS		:= $(shell find $(SRCDIR) -name "*.c")
OBJS		:= $(SRCS:.c=.o)
DEPS		:= $(OBJS:.o=.d)
LIBFT		:= ./libft/libft.a
INCLUDES	:= -I./includes -I./libft/includes

RM			:= rm -rf

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror $(INCLUDES) -MMD -MP

all:		$(NAME)

-include $(DEPS)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -lreadline $^ -o $@

$(LIBFT):
	make -C $(LIBFTDIR)

clean:
	$(RM) $(OBJS) $(DEPS)
	make clean -C $(LIBFTDIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: all clean fclean re
