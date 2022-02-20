/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytomiyos <ytomiyos@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:37:52 by kfumiya           #+#    #+#             */
/*   Updated: 2022/02/20 16:01:09 by ytomiyos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

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
# define DELIMITERS		"|<> \t"

enum e_token_type
{
	TYPE_R_RDRCT,
	TYPE_RR_RDRCT,
	TYPE_L_RDRCT,
	TYPE_LL_RDRCT,
	TYPE_PIPE,
	TYPE_STR,
	TYPE_EXPDBL,
	INV,
};

enum e_meta_char
{
	SGL_QT = '\'',
	DBL_QT = '\"',
	R_RDRCT = '>',
	L_RDRCT = '<',
	// SLSH = '/',
	// B_SLSH = '\\',
	// PERIOD = '.',
	// HYPHEN = '-',
	// DLL = '$',
	// SPC = ' ',
	// QSTN = '?',
};

typedef struct	s_token
{
	char	*str;
	// enum e_token_type	type;
	// struct s_tokens	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_environ
{
	char				*key;
	char				*value;
	int					is_env;
	struct s_environ	*next;
} t_environ;

typedef struct s_master
{
	t_environ			*environ;
	char				*pwd;
	char				*old_pwd;
	t_token				*tokens;
} t_master;

#endif
