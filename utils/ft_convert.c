/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 23:05:41 by groubaud          #+#    #+#             */
/*   Updated: 2022/05/25 23:05:41 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** t_env *env : the first element of the list
**
** Count the number of element in the list
*/

static int	ft_list_len(t_env *env)
{
	int	len;

	len = 0;
	while (env)
	{
		len++;
		env = env->next;
	}
	return (len);
}

static char	*ft_group_name_value(t_shell *shell, t_env *env)
{
	char	*str;

	str = ft_strjoin_gnl(NULL, env->name);
	str = ft_strjoin_gnl(str, "=");
	str = ft_strjoin_gnl(str, env->value);
	if (!str)
		ft_exit(shell, 1);
	return (str);
}

/*
** t_shell *shell : the general structure with everything
**
** Convert the environnement list into a char ** to be like envp
**  it's needed for excve
** It will be stocked in shell as 'envp_tab'
** If it hasn't changed, it won't be reconvert
**  else the previous is freed and envp_tab is (re)made
*/

char	**ft_convert_env_list_to_tab(t_shell *shell)
{
	t_env	*env;
	char	**envp_tab;
	int		i;

	if (shell->env_has_changed == 0)
		return (shell->envp_tab);
	ft_free_tab(shell->envp_tab);
	env = shell->env;
	envp_tab = malloc(sizeof(*envp_tab) * (ft_list_len(env) + 1));
	i = 0;
	while (env)
	{
		envp_tab[i] = ft_group_name_value(shell, env);
		// envp_tab[i] = ft_strjoin_gnl(NULL, env->name);
		// envp_tab[i] = ft_strjoin_gnl(envp_tab[i], "=");
		// envp_tab[i] = ft_strjoin_gnl(envp_tab[i], env->value);
		i++;
		env = env->next;
	}
	envp_tab[i] = NULL;
	shell->envp_tab = envp_tab;
	shell->env_has_changed = 0;
	return (NULL);
}