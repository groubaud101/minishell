/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:49:33 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/29 12:07:58 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_shell *shell, char *input)
{
	t_token	*tkn;

	tkn = NULL;
	if (!tokenize(shell, input, &tkn))
	{
		shell->ret_value = 258;
		free_all(&tkn);
		return (fail("syntax error"));
	}
	if (!init_parser(shell, tkn))
	{
		free_all(&tkn);
		return (fail("Error - Init Parser"));
	}
	if (!save_cmds(shell, tkn))
	{
		free_all(&tkn);
		return (fail("Error - Save commands"));
	}
	free_all(&tkn);
	return (0);
}
