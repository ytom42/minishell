# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/08 17:03:43 by kfumiya           #+#    #+#              #
#    Updated: 2022/01/18 10:32:59 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libft.a

SRCDIR		:= ./src
OBJDIR		:= ./obj

SRCS		:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
			ft_isascii.c ft_isdigit.c ft_isprint.c\
			ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memset.c\
			ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
			ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c\
			ft_tolower.c ft_toupper.c\
			ft_substr.c ft_putnbr_fd.c ft_putchar_fd.c ft_itoa.c ft_strjoin.c\
			ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strtrim.c ft_strmapi.c\
			ft_lstsize.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c\
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c\
			ft_atoll.c ft_intlen.c ft_strsub.c ft_strnew.c ft_in_set.c ft_strcmp.c\
			ft_strndup.c\
			get_next_line.c get_next_line_utils.c

OBJS		:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra

RM			:= rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then echo "mkdir -p $(OBJDIR)" && mkdir -p $(OBJDIR); fi
	$(CC) $(CFLAGS) -Iincludes -o $@ -c $<

clean:
	$(RM) $(OBJDIR)

fclean: clean
	# $(RM) $(NAME)
	$(RM) ./*.a
	

re: fclean all

.PHONY:	all clean fclean re
