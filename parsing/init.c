/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:06:11 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/13 18:22:18 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_token *tkn)
{
	int		n;
	t_token	*head;

	n = 0;
	head = tkn;
	while (tkn)
	{
		if (tkn == head)
			n += 1;
		if (!ft_strncmp(tkn->type, "PIPE", 4))
			n++;
		tkn = tkn->next;
	}
	return (n);
}

int	count_args(t_token *tkn)
{
	int		n;

	n = 0;
	while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
	{
		if (!ft_strncmp(tkn->type, "WORD", 4))
			n++;
		else if (!ft_strncmp(tkn->type, "CHEV_L", 6)
			|| !ft_strncmp(tkn->type, "CHEV_LL", 7)
			|| !ft_strncmp(tkn->type, "CHEV_R", 6)
			|| !ft_strncmp(tkn->type, "CHEV_RR", 7))
			while (tkn && ft_strncmp(tkn->type, "WORD", 4))
				tkn = tkn->next;
		tkn = tkn->next;
	}
	return (n);
}

void	init_cmd(t_shell *shell, int i, int n)
{
	shell->cmds[i].argc = n;
	shell->cmds[i].left.oflag = -1;
	shell->cmds[i].right.oflag = -1;
}

int	init_parser(t_shell *shell, t_token *tkn)
{
	int	i;
	int	n;

	shell->cmds_count = count_cmds(tkn);
	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (shell->cmds == NULL)
		ft_exit_error(shell, errno);
	i = -1;
	while (++i < shell->cmds_count)
	{
		n = count_args(tkn);
		init_cmd(shell, i, n);
		shell->cmds[i].args = (char **)malloc(sizeof(char *) * (n + 1));
		if (shell->cmds[i].args == NULL)
			ft_exit_error(shell, errno);
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
			tkn = tkn->next;
		if (tkn)
			tkn = tkn->next;
	}
	return (1);
}
