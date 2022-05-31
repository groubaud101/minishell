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
** Set env_has_changed to 1 if 'path' is diff than '.' 
*/

int	ft_cd(t_mini *mini, char *path)
{
	char	*name;
	char	*value;

	if (chdir(path) == -1)
		return (CHECK_ERR);
	if (ft_strcmp(path, ".") != 0)
		mini->env_has_changed = 1;
	name = ft_strdup("PWD");
	if (name == NULL)
		exit (0); // error malloc
	value = ft_getcwd();
	ft_export_to_env(mini, name, value);
	return (CHECK_OK);
}
