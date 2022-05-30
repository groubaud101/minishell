/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:17:34 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/30 09:17:34 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** mini : master structure
** path : relative or absolute path of where do you want to go
**
** man chdir
** Move the current working directory to 'path'
** Change the PWD and OLDPWD (if exist ?)
** Set env_has_changed to 1
*/

int	ft_cd(t_mini *mini, char *path)
{
	t_env	*env_pwd;
	char	*name;
	char	*value;

	ft_printf("\nENV avant :\n");
	ft_env(mini->env);

	if (chdir(path) == -1)
		return (CHECK_ERR);
	name = ft_strdup("PWD");
	if (name == NULL)
		exit (0); // error malloc
	env_pwd = ft_getenv(name, mini->env);
	value = ft_getcwd();
	if (env_pwd)
		free(env_pwd->value);
	ft_export(mini, name, value);

	ft_printf("\nENV après :\n");
	ft_env(mini->env);
	return (CHECK_OK);
}
