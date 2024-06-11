/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kschelvi <kschelvi@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/03 15:03:27 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/11 12:30:32 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "my_error.h"
#include "lexer.h"
#include <stdlib.h>

int main(void)
{
	lexer(NULL, "cat test.txt | wc -l");
}
