/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_to_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:08 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:09 by groubaud         ###   ########.fr       */
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
	if (env == NULL)
		return (env_new);
	start = env;

	while (env->next)
		env = env->next;
	
	env->next = env_new;
	return (start);
}

int		ft_export_to_env(t_mini *mini, char *name, char *value) 
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