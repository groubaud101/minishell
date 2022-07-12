/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:10:48 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 18:22:47 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_arg(t_shell *shell, t_token **tkn, int i, int *j)
{
	shell->cmds[i].args[++*j] = (*tkn)->content;
	if (!shell->cmds[i].cmd)
		shell->cmds[i].cmd = (*tkn)->content;
	return (1);
}

int	end_save(t_shell *shell, t_token **tkn, int i, int j)
{
	shell->cmds[i].args[++j] = NULL;
	if (*tkn)
		*tkn = (*tkn)->next;
	return (1);
}

int	save_cmds(t_shell *shell, t_token *tkn)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->cmds_count)
	{
		shell->cmds[i].cmd = NULL;
		j = -1;
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
		{
			if (!ft_strncmp(tkn->type, "CHEV_LL", 7))
				shell->cmds[i].left.target = "EOF";
			else if (!ft_strncmp(tkn->type, "CHEV_L", 6))
				save_chev_l(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "CHEV_RR", 7))
				save_chev_rr(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "CHEV_R", 6))
				save_chev_r(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "WORD", 4))
				save_arg(shell, &tkn, i, &j);
			tkn = tkn->next;
		}
		end_save(shell, &tkn, i, j);
	}
	return (1);
}
