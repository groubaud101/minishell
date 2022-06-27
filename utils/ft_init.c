/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:08:55 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 16:08:55 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	tab[1] = NULL;
	tab[2] = NULL;
	if (str[i] == '\0')
		return (tab);
	str = str + i + 1;
	if (str[0] == '\0')
		tab[1] = ft_calloc(sizeof(*tab[1]), 1);
	else
		tab[1] = ft_strdup(str);
	return (tab);
}// a voir pour les fail malloc

/*
** envp : tab[i] of the environment ('name=value') 
**
** Create a node of the list 'env' 
**  'name' is the left part of the '=' (ex : HOME)
**  'len_name' is the len of the name (ex for HOME : 4)
**   (it's used later in ft_getenv)
**  'value' the right part of the '=' (ex : /home/user)
*/

static t_env	*ft_attribute_elem_env(char *envp)
{
	t_env	*lst;
	char	**name_value;

	lst = malloc(sizeof(t_env));
	if (lst == NULL)
		exit (0); // malloc fail
	name_value = ft_split_once(envp, '=');
	if (!name_value)
		exit (0); // malloc fail
	lst->name = name_value[0];
	if (!name_value[0])
		exit (0); // malloc fail ou pas de name ??
	lst->len_name = ft_strlen(lst->name);
	lst->value = name_value[1];
	lst->next = NULL;
	return (lst);
}

/*
** envp : the tab of the environment given by the main
**
** Create the chain list 't_env' of the environment 
*/

static t_env	*ft_init_env(char *envp[])
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
		lst = ft_attribute_elem_env(envp[i]);
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
**  'fd_in' : file descriptor input
**  'fd_out' : file descriptor output
**  'env' : chain list of the environment
**  'env_has_changed' : a bool to know if it's needed to remake envp_tab
**  'envp_tab' : a tab version of 'env' (== envp)
**  'paths' : a tab of every paths in the env variable PATH
*/

void	ft_init_mini(t_shell *shell, char **av, char **envp)
{
	t_env	*env_path;

	shell->binary_name = av[0];
	shell->fd_in = STDIN;
	shell->fd_out = STDOUT;
	shell->env = ft_init_env(envp); //check malloc ?
	//ft_aff_env(shell->env);
	shell->env_has_changed = 1;
	shell->envp_tab = NULL;
	shell->var_bash = NULL;

	env_path = ft_getenv("PATH", shell->env); // a rajouter quand ya update
	if (env_path)
		shell->paths = ft_split(env_path->value, ':');
}
