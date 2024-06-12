/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 15:03:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/12 14:47:07 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "my_error.h"
#include "lexer.h"
#include <stdlib.h>

int main(void)
{
	t_command	*commands;

	commands = NULL;
	lexer(&commands, "<< test.txt test.txt cat");
	print_command(commands);
	free_commands(commands);
}
