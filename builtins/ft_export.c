/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:48:27 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/30 13:48:27 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_add_new_elem_env(t_env *env, char *name, char *value)
{
	t_env	*env_new;
	t_env	*start;

	env_new = malloc(sizeof(*env_new));
	env_new->name = name;
	env_new->len_name = ft_strlen(name);
	env_new->value = value;
	env_new->next = NULL;
	start = env;
	if (env)
		while (env->next)
			env = env->next;
	env->next = env_new;
	return (start);
}

int		ft_export(t_mini *mini, char *name, char *value) 
{
	t_env	*env_export;

	env_export = ft_getenv(name, mini->env);
	if (env_export == NULL)
		mini->env = ft_add_new_elem_env(mini->env, name, value);
	else
	{
		free(env_export->value);
		env_export->value = value;
	}
	return (CHECK_OK);
}