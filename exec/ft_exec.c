/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:26:50 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 09:59:33 by groubaud         ###   ########.fr       */
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
	if (paths != NULL)
	{
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
	}
	ft_printf_fd(STDERR_FILENO, "bash: %s: command not found\n", cmd[0]);
	return (1);
}

int	ft_exec(t_shell *shell, t_cmd cmd)
{
	int	ret;

	ft_attribute_signal(SIG_DFL, SIG_DFL);
	ret = 1;
	if (ft_redir(shell, cmd) == 0)
		ret = ft_execve(cmd.args, shell->paths, shell->envp_tab);
	if (ret == 1)
		ft_exit_error(shell, ret);
	return (ret);
}
