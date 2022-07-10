/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:26:50 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/10 17:26:50 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cmd : tab of the command + args (ex : 'cd', '/home/user')
** paths : tab of the paths in the env variable PATH
** envp : tab of the environment
**
** Execute the command if possible
**  first, try if absolute or relative path
**  then, try concat every paths[i] with '/' with cmd[0]
**   (ex : '/usr/bin', '/', 'cd' -> /usr/bin/cd)
*/

int	ft_execve(char **cmd, char **paths, char *envp[])
{
	int		i;
	char	*tmp_path;

	i = 0;
	tmp_path = NULL;
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, envp);
	while (paths[i])
	{
		tmp_path = ft_strjoin(paths[i], "/");
		tmp_path = ft_strjoin_gnl(tmp_path, cmd[0]);
		if (access(tmp_path, X_OK) == 0)
			execve(tmp_path, cmd, envp);
		free(tmp_path);
		tmp_path = NULL;
		i++;
	}
	return (CHECK_ERR);
}

int	ft_exec(t_shell *shell, t_cmd cmd)
{
	int	ret;

	ret = ft_exec_builtin(shell, cmd);
	if (ret == -1)
		ret = ft_execve(cmd.args, shell->paths, shell->envp_tab);
	return (ret);
}
