/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:21:28 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/13 18:10:33 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_tkn(t_token **tkn)
{
	if (*tkn)
		*tkn = (*tkn)->next;
	while (*tkn && !ft_strncmp((*tkn)->type, "SPACE", 4))
		*tkn = (*tkn)->next;
	return (1);
}

int	save_chev_l(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].left.target = ft_strdup((*tkn)->content);
	if (!shell->cmds[i].left.target)
	{
		free_all(tkn);
		ft_exit_error(shell, errno);
	}
	shell->cmds[i].left.oflag = O_RDONLY;
	return (1);
}

int	save_chev_r(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = ft_strdup((*tkn)->content);
	if (!shell->cmds[i].right.target)
	{
		free_all(tkn);
		ft_exit_error(shell, errno);
	}
	shell->cmds[i].right.oflag = O_CREAT | O_TRUNC | O_RDWR;
	return (1);
}

int	save_chev_rr(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = ft_strdup((*tkn)->content);
	if (!shell->cmds[i].right.target)
	{
		free_all(tkn);
		ft_exit_error(shell, errno);
	}
	shell->cmds[i].right.oflag = O_CREAT | O_APPEND | O_RDWR;
	return (1);
}
