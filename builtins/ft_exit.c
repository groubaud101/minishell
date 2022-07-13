/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:56:29 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/13 17:29:58 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_t_cmd(t_cmd *cmds, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds)
	{
		ft_free_tab(cmds->args);
		i++;
	}
	free(cmds);
	cmds = NULL;
}

void	ft_free_t_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	env = NULL;
}

void	ft_exit(t_shell *shell)
{
	if (shell->cmds)
		ft_free_t_cmd(shell->cmds, shell->cmds_count);
	if (shell->env)
		ft_free_t_env(shell->env);
	ft_free_tab(shell->paths);
	shell->paths = NULL;
	ft_free_tab(shell->envp_tab);
	shell->envp_tab = NULL;
	clear_history();
	exit(shell->ret_value);
}
