/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:02:45 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 23:02:45 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** name : the name of the env variable you are looking for (ex : HOME)
** env : environment chain list
**
** Search throught the env chain list and return the node of the 'name'
** Return NULL if not found
*/

t_env	*ft_getenv(char *name, t_env *env)
{
	int	len_name;

	len_name = ft_strlen(name);
	while (env)
	{
		if (len_name == env->len_name
			&& ft_strcmp(env->name, name) == 0)
			return(env);
		env = env->next;
	}
	return (NULL); // not found
}
