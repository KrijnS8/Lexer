/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 13:33:19 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/11 12:13:20 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "my_error.h"
#include "lexer.h"
#include <stdbool.h>

static t_token_type	get_type(t_arg arg, char *str)
{
	if (arg.quote == '"')
		return (TOK_D_QUOTE);
	if (arg.quote == '\'')
		return (TOK_S_QUOTE);
	if (str[0] == '$')
		return (TOK_VAR);
	if (ft_strcmp(str, "|") == 0)
		return (TOK_PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (TOK_INPUT_RE);
	if (ft_strcmp(str, ">") == 0)
		return (TOK_OUTPUT_RE);
	if (ft_strcmp(str, "<<") == 0)
		return (TOK_HEREDOC);
	if (ft_strcmp(str, ">>") == 0)
		return (TOK_APPEND);
	return (TOK_STRING);
}

void free_tokens(t_token **head) {
	t_token *current;
	t_token *tmp;

	current = *head;
	while (current)
	{
		if (current->str)
			free(current->str);
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*head = NULL;
}

t_error tokenizer(t_usr_input *usr_input)
{
	t_token *head;
	t_token	*current_tok;
	t_arg   *current_arg;

	head = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!head)
		return (ERR_MALLOC);
	current_tok = head;
	current_arg = usr_input->args;
	while (current_arg)
	{
		current_tok->str = ft_substr(usr_input->str, current_arg->start, current_arg->end - current_arg->start + 1);
		if (!current_tok->str)
			return (free_tokens(&head), ERR_MALLOC);
		current_tok->type = get_type(*current_arg, current_tok->str);
		if (current_arg->next)
		{
			current_tok->next = (t_token *)ft_calloc(1, sizeof(t_token));
			if (!current_tok->next)
				return (free_tokens(&head), ERR_MALLOC);
			current_tok = current_tok->next;
		}
		current_arg = current_arg->next;
	}
	current_tok = NULL;
	usr_input->token = head;
	return (ERR_OK);
}
