/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:32:09 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 23:32:09 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_envp_tab(char **envp_tab)
{
	int	i;

	i = 0;
	if (envp_tab == NULL)
		return ;
	while (envp_tab[i])
		free(envp_tab[i++]);
	free(envp_tab);
}