/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:59:41 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 22:59:41 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_aff_env(t_env *env)
{
	while(env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}