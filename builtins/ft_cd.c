/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 09:17:34 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/12 20:05:08 by groubaud         ###   ########.fr       */
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
		ft_exit_error(shell, ENOMEM);
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
** return 0 in case of success, 1 otherwise 
*/

int	ft_cd(t_shell *shell, char *path)
{
	ft_update_pwd_env(shell, "OLDPWD", ft_getcwd(shell));
	if (chdir(path) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "bash: cd: %s: ", path);
		perror(NULL);
		return (1);
	}
	ft_update_pwd_env(shell, "PWD", ft_getcwd(shell));
	if (ft_strcmp(path, ".") != 0)
		shell->env_has_changed = 1;
	return (0);
}
