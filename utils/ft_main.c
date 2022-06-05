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

/*
** ac/av/envp : number of arg / tab of arg / tab of the environnement
**
** Initialize the master structure mini
*/

int main(int ac, char **av, char *envp[])
{
	t_mini	mini;

	ft_init_mini(&mini, av, envp);
	ft_display_export(mini.env);
	ft_printf("\nnew env :\n");
	if (ac > 1)
		// ft_pipe(av + 1, &mini);
		ft_cd(&mini, av[1]);
	ft_display_export(mini.env);
	// ft_printf("\n\nThis is the end, hold your breath and count to ten\n");
}