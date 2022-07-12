/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_to_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:00:08 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 19:28:34 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_add_new_elem_env(t_env *env, char *name, char *value)
{
	t_env	*env_new;
	t_env	*start;

	env_new = malloc(sizeof(*env_new));
	if (!env_new)
		return (NULL);
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

int	ft_export_to_env(t_shell *shell, char *name, char *value)
{
	t_env	*env_export;

	env_export = ft_getenv(name, shell->env);
	if (env_export == NULL)
	{
		shell->env = ft_add_new_elem_env(shell->env, name, value);
		if (!shell->env)
		{
			free(name);
			free(value);
			ft_exit(shell);
		}
	}
	else
	{
		free(name);
		if (value)
		{
			free(env_export->value);
			env_export->value = value;
		}
	}
	shell->env_has_changed = 1;
	return (0);
}
