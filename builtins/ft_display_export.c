/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:58:57 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 00:59:41 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** env : first node of the environment chain list
**
** Return the first (in alphanum sort) element of env
*/

static t_env	*ft_first_env(t_env *env)
{
	t_env	*first;

	first = env;
	while (env)
	{
		if (ft_strcmp("_", env->name) != 0
			&& ft_strcmp(first->name, env->name) > 0)
			first = env;
		env = env->next;
	}
	return (first);
}

/*
** env : first node of the environment chain list
**
** Return the last (in alphanum sort) element of env
*/

static t_env	*ft_last_env(t_env *env)
{
	t_env	*last;

	last = env;
	while (env)
	{
		if (ft_strcmp("_", env->name) != 0
			&& ft_strcmp(last->name, env->name) < 0)
			last = env;
		env = env->next;
	}
	return (last);
}

void	ft_print_export(t_env *your_turn)
{
	if (your_turn->value)
		printf("declare -x %s=\"%s\"\n", your_turn->name, your_turn->value);
	else
		printf("declare -x %s\n", your_turn->name);
}

/*
** env : first node of the environment chain list
**
** Display env view by export (alphanum sort and "value") 
*/

void	ft_display_export(t_env *env)
{
	t_env	*start;
	t_env	*your_turn;
	t_env	*previous;
	t_env	*last;

	start = env;
	last = ft_last_env(env);
	previous = ft_first_env(env);
	your_turn = previous;
	while (your_turn != last)
	{
		ft_print_export(your_turn);
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
	ft_print_export(your_turn);
}
