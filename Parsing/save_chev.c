/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_chev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 18:21:28 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 18:22:35 by jrobert          ###   ########.fr       */
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
	shell->cmds[i].left.target = (*tkn)->content;
	shell->cmds[i].left.oflag = O_RDONLY;
	return (1);
}

int	save_chev_r(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = (*tkn)->content;
	shell->cmds[i].right.oflag = O_CREAT | O_TRUNC | O_RDWR;
	return (1);
}

int	save_chev_rr(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = (*tkn)->content;
	shell->cmds[i].right.oflag = O_CREAT | O_APPEND | O_RDWR;
	return (1);
}
