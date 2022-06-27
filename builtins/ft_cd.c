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
** shell : master structure
** name : PWD or OLDPWD non memory allocated
** absolute_path : allocated absolute path get by ft_getcwd
**
** Create OLDPWD and PWD if doesn't exist
** Then change them
*/

static int	ft_update_pwd_env(t_shell *shell, char *name, char *absolute_path)
{
	char	*tmp_pwd;
	t_env	*tmp_env;

	tmp_env = ft_getenv(name, shell->env);
	if (tmp_env)
		tmp_pwd = tmp_env->name;
	else
		tmp_pwd = ft_strdup(name);
	if (tmp_pwd == NULL)
		exit (0); // error malloc
	ft_export_to_env(shell, tmp_pwd, absolute_path);
	return (CHECK_OK);
}

/*
** shell : master structure
** path : relative or absolute path of where do you want to go
**
** man chdir
** Move the current working directory to 'path'
** Set env_has_changed to 1 if 'path' is diff than '.' 
*/

int	ft_cd(t_shell *shell, char *path)
{
	ft_update_pwd_env(shell, "OLDPWD", ft_getcwd());
	if (chdir(path) == -1)
		return (CHECK_ERR);
	ft_update_pwd_env(shell, "PWD", ft_getcwd());
	if (ft_strcmp(path, ".") != 0)
		shell->env_has_changed = 1;
	return (CHECK_OK);
}
