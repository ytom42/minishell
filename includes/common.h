/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:37:52 by kfumiya           #+#    #+#             */
/*   Updated: 2022/01/14 11:29:07 by kfumiya          ###   ########.fr       */
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

# define MS_SUCCUSE		0
# define MS_FALSE		1
# define MS_PROMPT		"$ "
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

typedef struct s_token
{
	char				*token;
	enum e_token_type	type;
	struct s_token		*next;
} t_token;

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
