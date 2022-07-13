/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:04:05 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 20:06:10 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(t_shell *shell)
{
	char	*buff;
	size_t	size;

	size = 128;
	buff = malloc(sizeof(*buff) * (size + 1));
	if (buff == NULL)
		ft_exit_error(shell, errno);
	while (getcwd(buff, size) == NULL && errno == ERANGE)
	{
		free(buff);
		size *= 2;
		if (size >= SIZE_MAX / 2)
			ft_exit_error(shell, errno);
		buff = malloc(sizeof(*buff) * (size + 1));
		if (buff == NULL)
			ft_exit_error(shell, errno);
	}
	return (buff);
}

int	ft_pwd(t_shell *shell)
{
	char	*pwd;

	pwd = ft_getcwd(shell);
	if (pwd == NULL)
		ft_exit_error(shell, errno);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
