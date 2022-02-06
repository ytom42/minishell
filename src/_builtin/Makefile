# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 05:47:17 by kfumiya           #+#    #+#              #
#    Updated: 2022/01/19 09:26:29 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libblt.a

ifndef RL_PATH
	RL_PATH	:=/usr/local/opt/readline
endif

SRCDIR		:= ./src
OBJDIR		:= ./obj

SRCS		:= $(SRCDIR)/create_env.c \
			$(SRCDIR)/blt_utils.c
			# $(SRCDIR)/preset_env.c \

OBJS		:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -I$(RL_PATH)/include/

LIBFTDIR	:= libft
LIBFT		:= $(LIBFTDIR)/libft.a
RFLAGS		:= -L$(RL_PATH)/lib
LFLAGS		:= -lreadline -lhistory
# DEPS		:= $(SRCS:%.c=%.d)

RM			:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then echo "mkdir -p $(OBJDIR)" && mkdir -p $(OBJDIR); fi
	$(CC) $(CFLAGS) -Iincludes -o $@ -c $<


# -include $(DEPS)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	# $(RM) $(NAME)
	$(RM) ./*.a

re: fclean all

.PHONY: all clean fclean re
