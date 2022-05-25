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

int main(int ac, char **av, char *envp[])
{
	t_mini	mini;

	//ft_puttab(envp, "\n");
	ft_init_mini(&mini, envp);
	ft_convert_env_list_to_tab(&mini);
	ft_aff_env(mini.env);

	ft_printf("env_has_changed : %i\n", mini.env_has_changed);
	ft_printf("envp_tab : %s\n", mini.envp_tab[0]);
	if (ac > 1)
	 	ft_pipe(av + 1, &mini);
}