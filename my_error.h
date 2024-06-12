/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_error.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sgrootve <sgrootve@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:09:26 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/12 13:09:20 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_ERROR_H
# define MY_ERROR_H

/*
	ERR_EXIT should always be at the bottom as we check 
	if error code is actually between ERR_MALLOC & ERR_EXIT
*/
typedef enum e_error
{
	ERR_OK = 0,
	ERR_MALLOC = 200,
	ERR_NO_INPUT,
	ERR_NO_PIPE,
	ERR_CHILD_CREATION,
	ERR_NO_DIR,
	ERR_INVALID_ENV,
	ERR_ARGS,
	ERR_EOF,
	ERR_SIGNAL,
	ERR_PATH_ENV,
	ERR_INVALID_PERM,
	ERR_INVALID_COMMAND,
	ERR_FAILED_TO_EXEC,
	ERR_FAILED_TO_WRITE,
	ERR_PARSE,
	ERR_FILE_CREAT,
	ERR_EXIT
}	t_error;

extern void	print_error(t_error error);

#endif
