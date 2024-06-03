/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 14:36:23 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/03 15:23:47 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"

t_token	*tokenizer(char *input)
{
	t_token	*head;
	t_token	*current;

	head = (t_token *)ft_calloc(1, sizeof(t_token));
	current = head;
	while (current)
	{
		
	}
}

t_command	parse_input(char *input)
{
	t_usr_input	usr_input;

	usr_input.input = ft_strdup(input);
	usr_input.token = tokenizer(usr_input.input);
}
