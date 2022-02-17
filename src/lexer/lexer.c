/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:48:00 by ytomiyos          #+#    #+#             */
/*   Updated: 2022/02/15 18:25:40 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include "libft.h"

#define END             "\033[0m"
#define BOLD            "\033[1m"
#define BLACK           "\033[30m"
#define RED             "\033[31m"
#define GREEN           "\033[32m"
#define YELLOW          "\033[33m"
#define BLUE            "\033[34m"
#define MAGENTA         "\033[35m"
#define CYAN            "\033[36m"
#define WHITE           "\033[37m"
#define UNDERLINE       "\033[4m"
#define BOLD_UNDERLINE  "\033[1;4m"

# define MS_SUCCUSE		0
# define MS_FALSE		1
# define MS_PROMPT		"\033[1m\033[32mminishell$ \033[0m"
# define DELIMITERS		" \t|<>"

typedef struct	s_token
{
	char	*str;
	// enum e_token_type	type;
	// struct s_tokens	*prev;
	struct s_token	*next;
}				t_token;

typedef enum	e_token_state{
	IN_DQUOTE,
	IN_QUOTE,
	GENERAL,
}				t_token_state;

t_token	*token_lstnew(char *str)
{
	t_token	*new;

	new = (t_token*)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	// new->prev = NULL;
	new->str = str;
	new->next = NULL;
	return (new);
}

t_token	*token_lstlast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_token	*token_lstaddback(t_token *lst, t_token *new)
{
	t_token *last;

	if (!lst)
	{
		lst = new;
	}
	else
	{
		last = token_lstlast(lst);
		last->next = new;
	}
	return (lst);
}

void	token_lstclear(t_token *lst)
{
	t_token	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->str);
		free(tmp);
	}
}

int		is_delimiter(char c)
{
	int		i;

	i = 0;
	while (DELIMITERS[i])
	{
		if (DELIMITERS[i] == c)
			return (MS_SUCCUSE);
		i++;
	}
	return (MS_FALSE);
}

typedef struct	s_toker
{
	t_token			*list;
	t_token			*new_token;
	t_token_state	state;
}				t_toker;

void	toker_init(t_toker *toker)
{
	toker->list = NULL;
}

int		is_space(char c)
{
	c = 0;
	printf("%s\n", DELIMITERS);
	return (0);
}

void	skip_space(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		*i += 1;
}

t_token	*get_token(char *line, int *i)
{
	int		size;
	char	*str;
	t_token	*new_token;

	size = 0;
	skip_space(line, i);
	while (is_delimiter(line[*i + size]) && line[*i + size])
		size++;
	str = ft_substr(&line[*i], 0, size);
	new_token = token_lstnew(str);
	*i += size;
	return (new_token);
}

t_token *tokenise(char *line)
{
	int		i;
	t_token	*token_list;
	t_token	*new_token;

	if (!line)
		return (NULL);
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		new_token = get_token(line, &i);
		token_list = token_lstaddback(token_list, new_token);
	}
	return (token_list);
}

char	*get_line()
{
	char *line;

	line = readline(MS_PROMPT);
	add_history(line);
	return (line);
}

void	print_token(t_token *lst)
{
	int	i;

	i = 1;
	while (lst)
	{
		printf("token[%02d]: %s\n", i, lst->str);
		lst = lst->next;
		i++;
	}
}

int main()
{
	char	*line;
	t_token	*token_list;

	while (1)
	{
		line = get_line();
		token_list = tokenise(line);
		print_token(token_list);
		free(line);
	}
	printf("exit\n");
	return (0);
}