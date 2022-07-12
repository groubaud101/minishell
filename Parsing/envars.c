/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envars.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:57:39 by jrobert           #+#    #+#             */
/*   Updated: 2022/07/12 20:11:45 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_shell *shell, char **str, char **bef, int *i)
{
	char	*tmp;
	char	*nbr;
	t_env	*env;
	char	c;

	if ((*str[*i]) == '?')
	{
		++*str;
		nbr = ft_itoa(shell->ret_value);
		tmp = ft_strjoin_free(*bef, nbr);
		free(nbr);
	}
	else
	{
		while (ft_isalnum((*str)[*i]) || (*str)[*i] == '_')
			++*i;
		c = (*str)[*i];
		(*str)[*i] = '\0';
		env = ft_getenv(*str, shell->env);
		if (env == NULL)
			tmp = *bef;
		else
			tmp = ft_strjoin_free(*bef, env->value);
	}
	return (tmp);
}

char	**init_vars(char *str, char **bef, int *i)
{
	char	**vars;

	*bef = NULL;
	vars = ft_split(str, '$');
	if (str[0] && str[0] == '$' && !str[1])
		*bef = ft_strdup("$");
	else if (str[0] && str[0] == '$')
		*bef = ft_strdup("");
	else
	{
		*bef = ft_strdup(vars[0]);
		++*i;
	}
	return (vars);
}

int	replace_var(t_shell *shell, char *str, char **bef)
{
	int		i;
	char	*tmp;

	i = 0;
	printf("STR = %s\n", str);
	tmp = get_var(shell, &str, bef, &i);
	printf("tmp = %s\n", tmp);
	*bef = ft_strjoin(tmp, str + i);
	printf("bef = %s\n", *bef);
	free(tmp);
	if (str[ft_strlen(str) - 1] == '$')
		*bef = ft_strjoin_free(*bef, "$");
	return (1);
}

int	replace(t_shell *shell, char **vars, int i, char **bef)
{
	char	*tmp;

	printf("vars i = %s\n", vars[i]);
	if (odd_quote_bef(vars, i, '\'') && odd_quote_aft(vars, i, '\''))
	{
		tmp = ft_strjoin("$", vars[i]);
		*bef = ft_strjoin_free(*bef, tmp);
		free(tmp);
	}
	else if (odd_quote_bef(vars, i, '\"') && odd_quote_aft(vars, i, '\"'))
	{
		vars[i][ft_strlen(vars[i]) - 1] = '\0';
		printf("vars i INSIDE = %s\n", vars[i]);
		replace_var(shell, vars[i], bef);
	}
	else
		replace_var(shell, vars[i], bef);
	return (1);
}

int	replace_env_var(t_shell *shell, t_token **head)
{	
	t_token	*tmp;
	char	*cpy;
	char	*bef;
	char	**vars;
	int		i;

	tmp = *head;
	while (tmp)
	{
		i = 0;
		if (tmp->content)
		vars = init_vars(tmp->content, &bef, &i);
		while (vars[i])
		{
			replace(shell, vars, i, &bef);
			i++;
		}
		cpy = tmp->content;
		tmp->content = bef;
		free(cpy);
		tmp = tmp->next;
	}
	return (1);
}
