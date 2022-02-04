# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 12:04:25 by kfumiya           #+#    #+#              #
#    Updated: 2022/01/15 08:50:36 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

ifndef RL_PATH
	RL_PATH	:=/usr/local/opt/readline
endif

SRCDIR		:= ./src
OBJDIR		:= ./obj

SRCS		:= $(SRCDIR)/main.c


OBJS		:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

RM			:= rm -rf

CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror -I$(RL_PATH)/include/

RFLAGS		:= -L$(RL_PATH)/lib
LFLAGS		:= -lreadline -lhistory
# DEPS		:= $(SRCS:%.c=%.d)

LIBFTDIR	:= libft
LIBFT		:= $(LIBFTDIR)/libft.a
LIBANADIR	:= $(SRCDIR)/analyzer
LIBANA		:= $(LIBANADIR)/libana.a
LIBBLTDIR	:= $(SRCDIR)/builtin
LIBBLT		:= $(LIBBLTDIR)/libblt.a
LIBEXEDIR	:= $(SRCDIR)/execute
LIBEXE		:= $(LIBEXEDIR)/libexe.a
LIBUTIDIR	:= $(SRCDIR)/utils
LIBUTI		:= $(LIBUTIDIR)/libuti.a


all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) $(LIBANA) $(LIBBLT) $(LIBEXE) $(LIBUTI)
	$(CC) $(CFLAGS) $(RFLAGS) $(LFLAGS) -Iincludes $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then echo "mkdir -p $(OBJDIR)" && mkdir -p $(OBJDIR); fi
	$(CC) $(CFLAGS) -Iincludes -o $@ -c $<

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

$(LIBANA):
	$(MAKE) -C $(LIBANADIR)

$(LIBBLT):
	$(MAKE) -C $(LIBBLTDIR)

$(LIBEXE):
	$(MAKE) -C $(LIBEXEDIR)

$(LIBUTI):
	$(MAKE) -C $(LIBUTIDIR)

# -include $(DEPS)

clean:
	$(RM) $(OBJDIR)
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(LIBANADIR)
	$(MAKE) clean -C $(LIBBLTDIR)
	$(MAKE) clean -C $(LIBEXEDIR)
	$(MAKE) clean -C $(LIBUTIDIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(LIBFTDIR)
	$(MAKE) fclean -C $(LIBANADIR)
	$(MAKE) fclean -C $(LIBBLTDIR)
	$(MAKE) fclean -C $(LIBEXEDIR)
	$(MAKE) fclean -C $(LIBUTIDIR)

re: fclean all

.PHONY: all clean fclean re
