/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 21:37:52 by kfumiya           #+#    #+#             */
/*   Updated: 2022/03/10 15:23:39 by kfumiya          ###   ########.fr       */
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

# define END             "\033[0m"
# define BOLD            "\033[1m"
# define BLACK           "\033[30m"
# define RED             "\033[31m"
# define GREEN           "\033[32m"
# define YELLOW          "\033[33m"
# define BLUE            "\033[34m"
# define MAGENTA         "\033[35m"
# define CYAN            "\033[36m"
# define WHITE           "\033[37m"
# define UNDERLINE       "\033[4m"
# define BOLD_UNDERLINE  "\033[1;4m"

# define TRUE			1
# define FALSE			0
# define MS_PROMPT		"\033[1m\033[32mminishell$ \033[0m"
# define DELIMITERS		"|<> \t"

enum e_token_type
{
	WORD,
	PIPE,
	LESSER,
	D_LESSER,
	GREATER,
	D_GREATER,
};

typedef struct	s_token
{
	char				*str;
	enum e_token_type	type;
	struct s_token		*prev;
	struct s_token		*next;
}				t_token;

typedef enum	e_redirect_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND_OUTPUT,
	REDIR_HEREDOC
}				t_redirect_type;

typedef struct	s_heredoc
{
	t_token	*contents;
	bool	is_expand;
	int		d_lesser;
	t_token *eof_list;
}			t_heredoc;

typedef struct			s_redirect
{
	int					fd_io;
	int					fd_file;
	int					fd_backup;
	t_redirect_type		type;
	t_token				*filename;
	bool				is_heredoc;
	t_heredoc			*heredoc;
	struct s_redirect	*next;
	struct s_redirect	*prev;
}						t_redirect;

typedef struct			s_command
{
	t_token				*args;
	t_redirect			*redirects;
	pid_t				pid;
	struct s_command	*next;
}						t_command;

typedef enum	e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
}				t_node_type;

typedef struct	s_node
{
	t_node_type		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

typedef enum e_exit_cd
{
	SCCSS = 0,
	GNRL_ERR = 1,
	DENIED = 13,
	CMD_NOT_EXEC = 126,
	CMD_NOT_FND = 127,
	INVLD_EXT_ARG = 128,
	OUT_OF_EXT_STS = 255,
	INVLD_SYNTX = 258,
} t_exit_cd;

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

typedef struct	s_environ
{
	char				*key;
	char				*value;
	int					is_env;
	struct s_environ	*next;
}				t_environ;

typedef struct s_master
{
	t_environ			*environs;
	t_exit_cd			exit_cd;
	t_token				*tokens;
} t_master;

#endif
