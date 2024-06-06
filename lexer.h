/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 14:00:21 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/06 14:43:29 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_error	t_error;

typedef enum e_token_type
{
	TOK_STRING,
	TOK_S_QUOTE,
	TOK_D_QUOTE,
	TOK_VAR,
	TOK_PIPE,
	TOK_INPUT_RE,
	TOK_OUTPUT_RE,
	TOK_HEREDOC,
	TOK_APPEND
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*str;
	struct s_token	*next;
}	t_token;

typedef struct s_arg
{
	int				start;
	int				end;
	char			quote;
	struct s_arg	*next;
}	t_arg;

typedef struct s_usr_input
{
	char	*str;
	t_arg	*args;
	t_token	*token;
}	t_usr_input;

typedef struct s_pipe_data
{
	int	fd_in;
	int	fd_out;
	int	pipe[2];
}	t_pipe_data;

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					pid;
	t_pipe_data			*pipe_data;
	struct s_command	*next;
}	t_command;

extern t_error	lexer(t_command *output, char *input);

extern t_error	tokenizer(t_usr_input *usr_input);
extern void		free_tokens(t_token **head);

extern t_error	parse_input(t_arg **output, char *str);
extern void		print_args(char *str, t_arg *args);
extern void		free_args(t_arg **args);

#endif
