/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:04:05 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/30 13:04:05 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(void)
{
	char	*buff;
	size_t	size;

	size = 128;
	buff = malloc(sizeof(*buff) * (size + 1));
	if (buff == NULL)
		return (NULL); // erreur malloc
	while (getcwd(buff, size) == NULL && errno == ERANGE)
	{
		free(buff);
		size *= 2;
		if (size >= SIZE_MAX / 2)
			exit (1); // attention overflow
		buff = malloc(sizeof(*buff) * (size + 1));
		if (buff == NULL)
			return (NULL); // erreur malloc
	}
	return (buff);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = ft_getcwd();
	if (pwd == NULL)
		return (CHECK_ERR); // voir errno
	printf("%s\n", pwd);
	return (CHECK_OK);
}