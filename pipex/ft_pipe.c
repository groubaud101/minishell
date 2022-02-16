/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:30:01 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 11:30:01 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_minishell mini, char **cmd1, char **cmd2, char *envp[])
{
	int   	end[2];
	pid_t	child1;
	pid_t	child2;
	int		status;
		
	if (pipe(end) == -1)
		return (perror("pipe: "));
	child1 = ft_child1(mini, end, cmd1, envp);
	child2 = ft_child2(mini, end, cmd2, envp);	
	close(end[0]);
	close(end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}
