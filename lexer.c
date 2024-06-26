/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 14:36:23 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/12 14:42:16 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "my_error.h"
#include "libft/libft.h"

t_error	lexer(t_command **output, char *input)
{
	t_usr_input	usr_input;
	t_error		error;
	//t_command	*commands;

	error = ERR_OK;
	usr_input.str = ft_strdup(input);
	if (!usr_input.str)
		return (ERR_MALLOC);
	error = parse_input(&usr_input.args, usr_input.str);
	if (error)
		return (free(usr_input.str), error);
	error = tokenizer(&usr_input);
	*output = get_commands(usr_input);
	free(usr_input.str);
	free_args(&usr_input.args);
	free_tokens(&usr_input.token);
	(void)output;
	return (ERR_OK);
}
