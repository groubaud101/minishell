/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 05:20:19 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/07 05:20:19 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_mini(t_mini *mini, char **envp)
{
	mini->fd_in = STDIN;
	mini->fd_out = STDOUT;
	mini->envp = envp;
	mini->paths = ft_split(getenv("PATH"), ':'); // voir de la liste chainée, on verra après
}

int main(int ac, char **av, char *envp[])
{
	t_mini	mini;

	ft_init_mini(&mini, envp);
	if (ac > 1)
		ft_pipe(av + 1, &mini);
}