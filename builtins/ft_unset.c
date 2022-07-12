/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 11:00:18 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 19:37:30 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_del_first(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	env = env->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	return (CHECK_OK);
}

static int	ft_del_next(t_env *env)
{
	t_env	*tmp;

	tmp = env->next;
	env->next = env->next->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	return (CHECK_OK);
}

static int	ft_unset_one(t_env *env, char *name)
{
	int	len_name;

	len_name = ft_strlen(name);
	if (len_name == env->len_name
		&& ft_strcmp(name, env->name) == 0)
		return (ft_del_first(env));
	while (env->next)
	{
		if (len_name == env->next->len_name
			&& ft_strcmp(name, env->next->name) == 0)
			return (ft_del_next(env));
		env = env->next;
	}
	return (CHECK_ERR);
}

int	ft_unset(t_shell *shell, t_cmd cmd)
{
	int	i;
	int	all_unset;

	i = 1;
	all_unset = 1;
	while (cmd.args[i])
	{
		if (ft_unset_one(shell->env, cmd.args[i]) == CHECK_OK)
			shell->env_has_changed = 1;
		else
			all_unset = 0;
		i++;
	}
	if (all_unset == 1)
		return (0);
	return (0);
}
