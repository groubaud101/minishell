/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:18:05 by jrobert           #+#    #+#             */
/*   Updated: 2022/04/11 15:26:35 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	bi_env(t_shell *shell)
{
	int i;

	i = 0;
	while (shell->envp[i])
		ft_putendl_fd(shell->envp[i++], 1);
	return (1);
}
