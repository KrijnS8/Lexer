/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   my_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sgrootve <sgrootve@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/04 13:10:28 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/12 13:51:39 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "libft/libft.h"
#include "my_error.h"

const char	*g_error_map[] = {
[ERR_OK] = "",
[ERR_MALLOC] = "Malloc failure",
[ERR_NO_INPUT] = "No input given",
[ERR_NO_PIPE] = "Failed to create pipe",
[ERR_CHILD_CREATION] = "Failed to create child process",
[ERR_NO_DIR] = "Failed to open directory",
[ERR_ARGS] = "Invalid arguments",
[ERR_EOF] = "Unexpected end of file",
[ERR_INVALID_ENV] = "Encountered invalid enviroment variable",
[ERR_SIGNAL] = "Failed to create Signal",
[ERR_PATH_ENV] = "PATH environment variable not found.",
[ERR_INVALID_PERM] = "Invalid Permissions",
[ERR_INVALID_COMMAND] = "Command not found",
[ERR_FAILED_TO_EXEC] = "Failed to execute command",
[ERR_FAILED_TO_WRITE] = "Failed to write data",
[ERR_PARSE] = "Parse error",
[ERR_FILE_CREAT] = "Failed to create file"
};

void	print_error(t_error error)
{
	char	*error_msg;

	if (!(error > ERR_MALLOC && error <= ERR_EXIT))
		return ;
	error_msg = (char *)g_error_map[error];
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
