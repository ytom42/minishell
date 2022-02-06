# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/10 05:03:54 by kfumiya           #+#    #+#              #
#    Updated: 2022/01/18 10:17:41 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libana.a

ifndef RL_PATH
	RL_PATH	:=/usr/local/opt/readline
endif

SRCDIR		:= ./src
OBJDIR		:= ./obj

SRCS		:= $(SRCDIR)/create_token.c \
			$(SRCDIR)/debug.c \
			$(SRCDIR)/request.c \
			$(SRCDIR)/token.c \
			$(SRCDIR)/an_utils1.c \
			$(SRCDIR)/an_utils2.c \
			$(SRCDIR)/an_utils3.c

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