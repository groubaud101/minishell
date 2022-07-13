/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:27:25 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 01:23:03 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax(t_shell *shell)
{
	int	ct;
	int	i;

	i = 0;
	ct = 0;
	while (i < shell->cmds_count)
	{
		if (shell->cmds[i].args[0])
			ct++;
		i++;
	}
	if (ct == i)
		return (CHECK_OK);
	ft_printf_fd(STDERR, "bash: syntax error near unexpected token `|'\n");
	shell->ret_value = 258;
	return (CHECK_ERR);
}
