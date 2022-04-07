/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:43:04 by groubaud          #+#    #+#             */
/*   Updated: 2022/03/29 18:43:04 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_libft/include/libft.h"
#include "my_libft/include/get_next_line.h"

void	ft_puttab_temp(char **tab)
{
	for (int i = 0; tab[i]; i++)
	{
		printf("%s\n", tab[i]);
	}
	printf("\n");
}

int	ft_execve(char **cmd, char **paths, char *envp[])
{
	int		i;
	char	*tmp_path = NULL;
	pid_t	pid;

	i = 0;
	pid = fork();
	if (pid == 0)
	{
		while (paths[i])
		{
			tmp_path = ft_strjoin(paths[i], "/");
			tmp_path = ft_strjoin_gnl(tmp_path, cmd[0]);
			//ft_putendl(tmp_path);
			if (access(tmp_path, X_OK) == 0)
				execve(tmp_path, cmd, envp);
			free(tmp_path);
			tmp_path = NULL;
			i++;
		}
	}
	waitpid(pid, NULL, 0);
	return (-1);
}

int main(int ac, char **av, char *envp[])
{
	char	**cmd;
	char	**paths;
	int		i;

	i = 1;
	paths = ft_split(getenv("PATH"), ':');
	//ft_puttab_temp(paths);
	while (i < ac)
	{
		cmd = ft_split(av[i], ' ');
		ft_execve(cmd, paths, envp);
		i++;
	} 
	return (0);
}