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
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
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
	}
	else
		waitpid(pid, NULL, 0);
	return (CHECK_ERR); // exit ?
}

/*
** Create the parent/child process and link fd_in and fd_out
*/
// TODO add t_mini *mini
int		ft_kind_of_pipe(t_mini *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	dprintf(2, "pid : %i\n", pid);
	if (pid == 0) // fils
	{
		close(pipefd[1]); // close la sortie
		dup2(pipefd[0], mini->fd_in); // redirige l'entrée std sur l'entrée du tuyau
		return (pid);
	}
	else // père
	{
		close(pipefd[0]); // close l'entrée
		dup2(pipefd[1], mini->fd_out); // redirige la sortie std sur la sortie du tuyau
		return (pid);
	}
}

/*
** expression : command + args in a string (ex : "echo 'coucou'")
** mini : the master structure
** to_exit : a booleen to know if we need ti add an exit (for pipe)
**
** Prepare and execute the command given by 'expression'
*/
// TODO add the call to BUILTIN check before ft_exec_process
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
	return (ret_value); // ca aussi
}

/*
** cmds : a tab of the strings between pipe or just one if there is no pipe
** mini : the master structure
**
** Call the previous function to make the magic pipe happens.
*/

int ft_pipe(char **cmds, t_mini *mini)
{
	int		i;
	int		pid;

	i = 0;
	if (mini->paths == NULL || cmds == NULL || cmds[i] == NULL)
		return (CHECK_ERR);
	while (cmds[i + 1] != NULL)
	{
		pid = ft_kind_of_pipe(mini);
		if (pid != 0) // process père
			ft_exec_process(cmds[i], mini, TO_EXIT);
		else
			waitpid(pid, NULL, 0);
		i++;
	}
	ft_exec_process(cmds[i], mini, NO_EXIT);

	return (CHECK_OK);
}