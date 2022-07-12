/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:49:33 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 18:04:33 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse(t_shell *shell, char *input)
{
	t_token	*tkn;

	tkn = NULL;
	if (!tokenize(shell, input, &tkn))
		return (free_all(&tkn) && fail("Error - Syntax"));
	if (!init_parser(shell, tkn))
		return (free_all(&tkn) && fail("Error - Init Parser"));
	if (!save_cmds(shell, tkn))
		return (free_all(&tkn) && fail("Error - Save Cmds"));
	return (1);
}
