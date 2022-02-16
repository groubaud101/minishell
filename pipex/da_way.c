/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   da_way.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 04:45:37 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 04:45:37 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*where_is_da_way(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0) //fonction systeme
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**what_are_the_paths(char *envp[])
{
	char	*da_way;

	da_way = where_is_da_way(envp);
	if (da_way == NULL)
	{
		printf("Environnement variable PATH not found.\n");
		return (NULL);
	}
	return(ft_split_add_c(da_way, ':', '/'));
}
