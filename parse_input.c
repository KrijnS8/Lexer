/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sgrootve <sgrootve@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/08 13:30:40 by kschelvi      #+#    #+#                 */
/*   Updated: 2024/06/06 14:31:43 by kschelvi      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "my_error.h"
#include "libft/libft.h"

#define QUOTES "'\""
#define SEPCHARS "'\"|><"

void	free_args(t_arg **args)
{
	t_arg	*current;
	t_arg	*next;

	current = *args;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

static int	quoted_arg(t_arg *arg, char *str, int index)
{
	char	quote;
	int		i;

	i = index;
	quote = str[i];
	arg->quote = quote;
	i++;
	arg->start = i;
	while (str[i] != quote && str[i])
		i++;
	if (!str[i])
		return (-1);
	arg->end = i - 1;
	return (i - index + 1);
}

static int	non_quoted_arg(t_arg *arg, t_error *error, char *str, int index)
{
	int	i;

	i = index;
	arg->start = i;
	arg->quote = '\0';
	if (ft_strncmp(&(str[i]), ">>", 2) == 0 || ft_strncmp(&(str[i]), "<<", 2) == 0)
	{
		if (ft_strncmp(&str[i], ">>>", 3) == 0 || ft_strncmp(&(str[i]), "<<<", 3) == 0)
		{
			*error = ERR_EOF;
			return (1);
		}
		i += 1;
		arg->end = i;
		return (2);
	}
	while (!ft_isspace(str[i]) && !ft_strchr(SEPCHARS, str[i]) && str[i])
		i++;
	if (i == index)
	{
		arg->end = i;
		return (1);
	}
	arg->end = i - 1;
	if (ft_isspace(str[i]))
		i++;
	return (i - index);
}

static t_error	get_args(t_arg **output, char *str)
{
	t_arg	**current;
	int		i;
	int		len;
	t_error	error;

	current = output;
	i = 0;
	error = ERR_OK;
	while (str[i])
	{
		if (i == 20)
			break ;
		*current = (t_arg *)malloc(sizeof(t_arg));
		if (!*current)
			return (ERR_MALLOC);
		while (ft_isspace(str[i]))
			i++;
		if (ft_strchr(QUOTES, str[i]))
		{
			if (!str[i])
				break ;
			len = quoted_arg(*current, str, i);
			if (len < 0)
			{
				free(*current);
				*current = NULL;
				return (ERR_EOF);
			}
			i += len;
		}
		else
			i += non_quoted_arg(*current, &error, str, i);
		current = &(*current)->next;
	}
	*current = NULL;
	return (error);
}

void	print_args(char *str, t_arg *args)
{
	t_arg	*current;
	char	*tmp;

	current = args;
	while (current)
	{
		tmp = ft_substr(str, current->start, current->end - current->start + 1);
		ft_printf("%s\n", tmp);
		free(tmp);
		current = current->next;
	}
}

t_error	parse_input(t_arg **output, char *str)
{
	t_arg	*args;
	t_error	error;

	args = NULL;
	error = get_args(&args, str);
	if (error)
		return (free_args(&args), error);
	*output = args;
	return (ERR_OK);
}
