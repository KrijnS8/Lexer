/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/11 12:16:04 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/11 12:33:29 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "my_error.h"
#include "lexer.h"
#include "libft.h"

#include <stdbool.h>


t_command	*get_commands(t_usr_input input)
{
	t_command	*commands;

	commands = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!commands)
		return (NULL);
	commands->pipe_data = (t_pipe_data *)ft_calloc(1, sizeof(t_pipe_data));
	if (!commands->pipe_data)
		return (free(commands), NULL);
}
