/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:38:21 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/16 11:38:21 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve(char **cmd, char **paths, char *envp[])
{
	int		i;
	char	*tmp_path;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
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
	else
		waitpid(pid, NULL, 0);
	return (CHECK_ERR);
}

int		ft_kind_of_pipe(void)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	//dprintf(2, "pid : %i\n", pid);
	if (pid == 0) // fils
	{
		close(pipefd[1]); // close la sortie
		dup2(pipefd[0], STDIN); // redirige l'entrée std sur l'entrée du tuyau
		return (pid);
	}
	else // père
	{
		close(pipefd[0]); // close l'entrée
		dup2(pipefd[1], STDOUT); // redirige la sortie std sur la sortie du tuyau
		return (pid);
	}
}

int	ft_exec_process(char *expression, t_mini *mini, bool to_exit)
{
	char	**cmd;
	int		ret_value;

	ft_convert_env_list_to_tab(mini);
	cmd = ft_split(expression, ' ');
	ret_value = ft_execve(cmd, mini->paths, mini->envp_tab);
	ft_free_tab(cmd);
	if (to_exit == TO_EXIT)
		exit (1); // faudra changer cette valeur
	return (ret_value);
}

int ft_pipe(char **cmds, t_mini *mini)
{
	int		i;
	int		pid;

	i = 0;
	if (mini->paths == NULL || cmds == NULL || cmds[i] == NULL)
		return (CHECK_ERR);
	while (cmds[i + 1] != NULL)
	{
		pid = ft_kind_of_pipe();
		if (pid != 0) // process père
			ft_exec_process(cmds[i], mini, TO_EXIT);
		else
			waitpid(pid, NULL, 0);
		i++;
	}
	ft_exec_process(cmds[i], mini, NO_EXIT);

	return (CHECK_OK);
}