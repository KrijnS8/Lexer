/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 12:16:04 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/12 14:55:38 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "my_error.h"
#include "lexer.h"
#include "libft/libft.h"

#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

t_error	add_infile(t_token **head, t_command *command)
{
	t_token_type	next_type;

	if (!(*head)->next || !command)
		return (ERR_PARSE);
	next_type = (*head)->next->type;
	if (next_type == TOK_APPEND || next_type == TOK_HEREDOC || \
		next_type == TOK_INPUT_RE || next_type == TOK_OUTPUT_RE || \
		next_type == TOK_PIPE)
		return (ERR_PARSE);
	if ((*head)->type == TOK_INPUT_RE)
	{	
		command->infile = parse_var((*head)->next);
		command->infile = (*head)->next->str;
		if (!command->infile)
			return (ERR_MALLOC);
	}
	else
	{
		command->heredoc = ft_strdup((*head)->next->str);
		if (!command->heredoc)
			return (ERR_MALLOC);
	}
	*head = (*head)->next;
	return (ERR_OK);
}

t_error	add_outfile(t_token **head, t_command *command)
{
	t_token_type	next_type;
	int				fd;

	if (!(*head)->next || !command)
		return (ERR_PARSE);
	next_type = (*head)->next->type;
	if (next_type == TOK_APPEND || next_type == TOK_HEREDOC || \
		next_type == TOK_INPUT_RE || next_type == TOK_OUTPUT_RE || \
		next_type == TOK_PIPE)
		return (ERR_PARSE);
	if ((*head)->type == TOK_APPEND)
		command->append = true;
	command->outfile = parse_var((*head)->next);
	command->outfile = (*head)->next->str;
	fd = open(command->outfile, O_CREAT);
	if (fd < 0)
		return (ERR_FILE_CREAT);
	close(fd);
	*head = (*head)->next;
	return (ERR_OK);
}

char	**append_to_array(char **old_arr, char *to_add)
{
	int		len;
	int		i;
	char	**cpy;
	char	**new_arr;

	len = 0;
	cpy = old_arr;
	if (old_arr)
	{
		while (cpy[len])
			len++;
	}
	new_arr = (char **)ft_calloc(len + 2, sizeof(char *));
	if (!new_arr)
		return (ft_free_strarr(old_arr), NULL);
	i = 0;
	cpy = old_arr;
	while (i < len)
	{		
		new_arr[i] = ft_strdup(cpy[i]);
		if (!new_arr[i])
			return (ft_free_strarr(old_arr), ft_free_strarr(new_arr), NULL);
		i++;
	}
	new_arr[i] = ft_strdup(to_add);
	if (!new_arr[i])
		return (ft_free_strarr(old_arr), ft_free_strarr(new_arr), NULL);
	if (old_arr)
		ft_free_strarr(old_arr);
	return (new_arr);
}

t_error	fill_commands(t_command **commands, t_token *tokens)
{
	t_token		*current;
	t_command	*curr_comm;

	current = tokens;
	curr_comm = *commands;
	while (current)
	{
		if (current->type == TOK_STRING || current->type == TOK_S_QUOTE)
			curr_comm->argv = append_to_array(curr_comm->argv, current->str);
		if (current->type == TOK_VAR)
			curr_comm->argv = append_to_array(curr_comm->argv, parse_var(current));
		if (current->type == TOK_D_QUOTE)
			curr_comm->argv = append_to_array(curr_comm->argv, parse_d_quote(current));
		if (current->type == TOK_INPUT_RE || current->type == TOK_HEREDOC)
			add_infile(&current, curr_comm);
		if (current->type == TOK_OUTPUT_RE || current->type == TOK_APPEND)
			add_outfile(&current, curr_comm);
		if (current->type == TOK_PIPE)
		{
			curr_comm->next = (t_command *)ft_calloc(1, sizeof(t_command));
			if (!curr_comm->next)
				return (ERR_MALLOC);
			curr_comm->next->pipe_data = curr_comm->pipe_data;
			curr_comm = curr_comm->next;
		}
		current = current->next;
	}
	return (ERR_OK);
}

void	print_command(t_command *commands)
{
	while (commands)
	{
		ft_printf("ARGV:\n");
		ft_putstr_arr_fd(commands->argv, '\n', STDIN_FILENO);
		ft_printf("\nInfile: %s", commands->infile);
		ft_printf("\nOutfile: %s", commands->outfile);
		ft_printf("\nHeredoc: %s", commands->heredoc);
		ft_printf("\nAppend: %d\n", commands->append);
		commands = commands->next;
	}
}

void	free_commands(t_command *commands)
{
	t_command 	*current;
	t_command	*prvs;

	current = commands;
	while (current)
	{
		if (current->argv)
			ft_free_strarr(current->argv);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->heredoc)
			free(current->heredoc);
		if (current->pipe_data)
			free(current->pipe_data);
		prvs = current;
		current = current->next;
		free(prvs);
	}
}

t_command	*get_commands(t_usr_input input)
{
	t_command	*commands;
	t_error		error;
	
	commands = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!commands)
		return (NULL);
	commands->pipe_data = (t_pipe_data *)ft_calloc(1, sizeof(t_pipe_data));
	if (!commands->pipe_data)
		return (free(commands), NULL);
	error = fill_commands(&commands, input.token);
	return (commands);
}
