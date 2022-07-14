/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_the_exec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 16:15:50 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 12:01:24 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_choose_the_exec(t_shell *shell)
{
	ft_attribute_signal(SIG_IGN, SIG_IGN);
	ft_convert_env_list_to_tab(shell);
	if (shell->cmds_count == 1)
	{
		if (ft_redir(shell, shell->cmds[0]) == 0)
		{
			shell->ret_value = ft_exec_builtin(shell, shell->cmds[0]);
			ft_back_to_std(shell, shell->cmds[0]);
		}
	}
	if (shell->ret_value == -19 || shell->cmds_count > 1)
		shell->ret_value = ft_pipe(shell, 0);
	if (shell->ret_value == 11)
		ft_printf_fd(STDERR_FILENO, "Segmentation fault: 11\n");
	else if (shell->ret_value == 10)
		ft_printf_fd(STDERR_FILENO, "Bus error: 10\n");
	return (1);
}
