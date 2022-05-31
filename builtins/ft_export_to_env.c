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

static t_env	*ft_find_the_insert_spot(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = ft_getenv("WSL_DISTRO_NAME", env); // ce sera pas ça
	if (tmp_env)
		return (tmp_env);
	tmp_env = ft_getenv("LANG", env);
	if (tmp_env)
		return (tmp_env);
	tmp_env = ft_getenv("LESSCLOSE", env);
	if (tmp_env)
		return (tmp_env);
	tmp_env = ft_getenv("HOSTTYPE", env);
	if (tmp_env)
		return (tmp_env);
	tmp_env = ft_getenv("LS_COLORS", env);
	if (tmp_env)
		return (tmp_env);
	while (env->next)
		env = env->next;
	return (env);
}

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

	// option 1 on incruste au milieu si possible sinon à la fin
	env = ft_find_the_insert_spot(env);
	env_new->next = env->next;

	// // option 2 on incruste à la fin
	// while (env->next)
	// 	env = env->next;
	
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