/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 14:00:21 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/03 15:04:44 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_token_type
{
	TOK_STRING,
	TOK_S_QUOTE,
	TOK_D_QUOTE,
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
	struct t_token	*next;
	struct t_token	*previous;
}	t_token;

typedef struct s_usr_input
{
	char	*input;
	t_token	*token;
}	t_usr_input;

typedef struct s_command
{
	char				**argv;
	char				*infile;
	char				*outfile;
	int					fd_in;
	int					fd_out;
	int					pipe[2];
	int					pid;
	struct t_command	*next;
}	t_command;

#endif
