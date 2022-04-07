/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:21 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 11:38:21 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	ft_pipe(t_minishell *mini)
{
	pid_t	pid;
	int		end[2];

	pipe(end);
	pid = fork();
	if (pid == 0)
	{
		close(end[1]);
		dup2(end[0], STDIN);
		mini->end0 = end[0];
		return (1);
	}
	else
	{
		close(end[0]);
		dup2(end[1], STDOUT);
		mini->end1 = end[1];
		return (2);
	}
	return (pid);
}
