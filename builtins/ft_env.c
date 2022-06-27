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

/*
** env : the environment chain list
**
** Display the environment
*/

void	ft_env(t_env *env)
{
	printf("ft_env\n");
	while(env)
	{
		ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}