/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:17:44 by jrobert           #+#    #+#             */
/*   Updated: 2022/04/28 08:08:25 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_echo(t_shell *shell, int i)
{
	int j;

	j = 0;
	while (++j < shell->cmds[i].argc)
	{
		ft_putstr_fd(shell->cmds[i].args[j], 1);
		if (j < shell->cmds[i].argc)
			write(1, " ", 1);
	}
	write(1, "\n", 1);
	return (1);
}