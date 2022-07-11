/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:17:03 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/08 16:17:03 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe(t_shell *shell, t_cmd *cmds, int i)
{
	int fd[2];
    int fdp;

    for (i = 0; i < shell->cmds_count; i++) {
        if (i < shell->cmds_count - 1) {
            pipe(fd);
        }
        if (!fork()) {
            if (i > 0)
                dup2(fdp, STDIN_FILENO);
            if (i < shell->cmds_count - 1) {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
            }
            ft_exec(shell, cmds[i]);
        }
        if (i > 0)
            close(fdp);
        if (i < shell->cmds_count - 1) {
            close(fd[1]);
            fdp = fd[0];
        }
    }
	ft_sleep(5000000);
    waitpid(-1, NULL, 0);
	return (0);
}