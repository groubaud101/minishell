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
**  check every node to get the most accurate
**  ex : > export va=hi
**       > export var=hello
**       > echo $variable
**       > helloiable
** Return NULL if not found
*/

t_env	*ft_getenv(char *name, t_env *env)
{
	int		len;
	t_env	*match;

	len = 0;
	while (env)
	{
		if (len < env->len_name &&
			ft_strncmp(env->name, name, env->len_name) == 0)
		{
			match = env;
			len = env->len_name;
		}
		env = env->next;
	}
	if (len == 0)
		return (NULL); // not found
	return (match);
}
