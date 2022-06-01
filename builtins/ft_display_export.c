/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:58:57 by groubaud          #+#    #+#             */
/*   Updated: 2022/06/01 17:58:57 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display_export(t_env *env)
{
	t_env	*start;
	t_env	*your_turn;
	t_env	*previous;
	t_env	*last;

	start = env;
	previous = env;
	while (env)
	{
		if (ft_strcmp("_", env->name) != 0
			&& ft_strcmp(previous->name, env->name) > 0)
			previous = env;
		env = env->next;
	}

	env = start;
	last = env;
	while (env)
	{
		if (ft_strcmp("_", env->name) != 0
			&& ft_strcmp(last->name, env->name) < 0)
			last = env;
		env = env->next;
	}

	your_turn = previous;
	while (your_turn != last)
	{
		printf("declare -x %s=\"%s\"\n", your_turn->name, your_turn->value);
		your_turn = last;
		env = start;
		while (env)
		{
			if (ft_strcmp("_", env->name) != 0
				&& ft_strcmp(your_turn->name, env->name) >= 0
				&& ft_strcmp(env->name, previous->name) > 0)
				your_turn = env;
			env = env->next;
		}
		previous = your_turn;
	}
	printf("declare -x %s=\"%s\"\n", your_turn->name, your_turn->value);	
}
