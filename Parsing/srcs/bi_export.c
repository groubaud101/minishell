/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:15:26 by jrobert           #+#    #+#             */
/*   Updated: 2022/04/11 15:26:58 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	env_len(char **envp)
{
	int len;

	len = 0;
	while (envp[len])
		len++;
	return (len);
}

int	bi_export(t_shell *shell, int i)
{
	char	**tmp;
	int		j;

	tmp = (char **)malloc(sizeof(char *) * (env_len(shell->envp) + 1));
	if (!tmp)
		return (0);
	j = -1;
	while (shell->envp[++j])
		tmp[j] = ft_strdup(shell->envp[j]);
	tmp[j] = shell->cmds[i].args[1];
	tmp[++j] = NULL;
	free(shell->envp);
	shell->envp = tmp;
	return (1);
}
