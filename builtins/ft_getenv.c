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

char	*ft_getenv(char *name, t_env *env)
{
	int		len;
	char	*match;

	len = 0;
	while (env)
	{
		if (len < env->len_name &&
			ft_strncmp(env->name, name, env->len_name) == 0)
		{
			match = env->value;
			len = env->len_name;
		}
		env = env->next;
	}
	if (len == 0)
		return (NULL); // not found
	return (match);
}
