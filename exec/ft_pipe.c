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

int	ft_pipe(t_cmd *cmds, t_shell *shell)
{
	ft_execve(cmds[0].args, shell->paths, shell->envp_tab);
	return (0);
}