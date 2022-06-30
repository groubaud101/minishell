/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 08:56:29 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/30 08:56:29 by groubaud         ###   ########.fr       */
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
}

void	ft_exit(t_shell *shell, int ret_value)
{
	ft_free_t_cmd(shell->cmds, shell->cmds_count); // a check
	ft_free_t_env(shell->env);
	ft_free_tab(shell->paths);
	ft_free_tab(shell->envp_tab);
	exit(ret_value);
}