/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/07/14 11:57:05 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_split_norm(char **tab)
{
	ft_free_tab(tab);
	return (NULL);
}

/*
** str :  the string to split
** c : the caracter of separation ('=' here)
**
** ft_split but just once.
** For the environment, to get the name and the value in two string
**  the value could have several '=' in it
*/

char	**ft_split_once(char *str, char c)
{
	int		i;
	char	**tab;

	i = 0;
	tab = (char **)malloc(sizeof(*tab) * 3);
	if (!tab)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	tab[0] = ft_strndup(str, i);
	if (!tab[0])
		return (ft_split_norm(tab));
	tab[1] = NULL;
	tab[2] = NULL;
	if (str[i] == '\0')
		return (tab);
	str = str + i + 1;
	if (str[0] == '\0')
		tab[1] = ft_calloc(sizeof(*tab[1]), 1);
	else
		tab[1] = ft_strdup(str);
	if (!tab[1])
		return (ft_split_norm(tab));
	return (tab);
}

/*
** envp : tab[i] of the environment ('name=value') 
**
** Create a node of the list 'env' 
**  'name' is the left part of the '=' (ex : HOME)
**  'len_name' is the len of the name (ex for HOME : 4)
**   (it's used later in ft_getenv)
**  'value' the right part of the '=' (ex : /home/user)
*/

static t_env	*ft_attribute_elem_env(t_shell *shell, char *envp)
{
	t_env	*lst;
	char	**name_value;

	lst = malloc(sizeof(t_env));
	if (lst == NULL)
		ft_exit_error(shell, errno);
	name_value = ft_split_once(envp, '=');
	if (!name_value)
		ft_exit_error(shell, errno);
	lst->name = ft_strdup(name_value[0]);
	lst->len_name = ft_strlen(lst->name);
	lst->value = ft_strdup(name_value[1]);
	lst->next = NULL;
	ft_free_tab(name_value);
	return (lst);
}

/*
** envp : the tab of the environment given by the main
**
** Create the chain list 't_env' of the environment 
*/

static t_env	*ft_init_env(t_shell *shell, char *envp[])
{
	t_env	*start;
	t_env	*lst;
	int		i;

	i = 0;
	start = NULL;
	while (envp[i])
		i++;
	i--;
	while (i >= 0)
	{
		lst = ft_attribute_elem_env(shell, envp[i]);
		lst->next = start;
		start = lst;
		i--;
	}
	return (start);
}

/*
** shell : adress of shell given by the main
** envp : the tab of the environment given by the main
**
** Create the master structure 'shell'
**  'cmds_count' : nb of cmd in the expression, ex : 'ls | cat' -> 2 cmds
**  'cmds' : tab of structure where the commands are set up
**  'env' : chain list of the environment
**  'env_has_changed' : a bool to know if it's needed to remake envp_tab
**  'envp_tab' : a tab version of 'env' (== envp)
**  'paths' : a tab of every paths in the env variable PATH
**  'fd_in' : file descriptor input
**  'fd_out' : file descriptor output
**  'ret_value' : value for $?
*/

void	ft_init_mini(t_shell *shell, char **envp)
{
	t_env	*env_path;

	shell->cmds_count = 0;
	shell->cmds = NULL;
	shell->env = ft_init_env(shell, envp);
	if (!shell->env)
		ft_exit_error(shell, errno);
	shell->env_has_changed = 1;
	shell->envp_tab = NULL;
	shell->paths = NULL;
	env_path = ft_getenv("PATH", shell->env);
	if (env_path)
	{
		shell->paths = ft_split(env_path->value, ':');
		if (!shell->paths)
			ft_exit_error(shell, errno);
	}
	shell->fd_in = STDIN_FILENO;
	shell->fd_out = STDOUT_FILENO;
	shell->ret_value = 0;
}
