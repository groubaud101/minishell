/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:59:41 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 15:26:33 by groubaud         ###   ########.fr       */
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
	while(env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}