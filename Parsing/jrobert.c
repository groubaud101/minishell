/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jrobert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:48:31 by jrobert           #+#    #+#             */
/*   Updated: 2022/06/28 12:09:03 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tkn_add_back(t_token **alst, t_token *new)
{
	t_token	*ref;

	if (!alst)
		return ;
	ref = *alst;
	if (*alst)
	{
		while (ref->next)
			ref = ref->next;
		ref->next = new;
	}
	else
		*alst = new;
}

t_token	*new_tkn(char *content, int size, char *type)
{
	t_token	*tmp;

	tmp = malloc(sizeof(t_token));
	if (!tmp)
		return (NULL);
	tmp->content = ft_substr(content, 0, size);
	tmp->size = size;
	tmp->type = type;
	tmp->next = NULL;
	return (tmp);
}

t_spec	find_spec(char *s)
{
	int				i;
	const t_spec	nil = (t_spec){0};
	const t_spec	spec[7] = {{"|", 1, "PIPE"}, {"\n", 1, "NL"},
	{" ", 1, "SPACE"}, {">>", 2, "CHEV_RR"},
	{"<<", 2, "CHEV_LL"}, {">", 1, "CHEV_R"},
	{"<", 1, "CHEV_L"}};

	i = -1;
	while (++i < 7)
	{
		if (!ft_strncmp(spec[i].spec, s, spec[i].size))
			return (spec[i]);
	}
	return (nil);
}

int	valid_quotes(char *input)
{
	while (*input++)
	{
		if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
				input++;
			if (!*input)
				return (0);
		}
		if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
				input++;
			if (!*input)
				return (0);
		}
	}
	return (1);
}

void	handle_quotes(char **input, int *i)
{
	char c;

	c = (*input)[(*i)++];
	while ((*input)[*i] && (*input)[*i] != c)
		++*i;
	++*i;
}

int	is_open_quote(char *str, int len)
{
	char	c;
	int		n;
	int		i;

	c = str[len];
	n = 0;
	i = 0;
	while (str[i] && i < len)
		if (str[i++] == c)
			n++;
	if (n % 2)
		return (0);
	return (1);
}

int		len_wo_quotes(char *str)
{
	int		len;
	int		i;
	char	c;

	len = ft_strlen(str);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] != c)
				i++;
			len -= 2;
		}
	}
	return (len);
}

void	cpy_in_quotes(char *content, int *i, int *j, char *new)
{
	char c;
	
	if (content[*i] == '\'' || content[*i] == '\"')
	{
		c = content[(*i)++];
		while (content[*i] != c)
			new[(*j)++] = content[(*i)++];
	}
	else
		new[(*j)++] = content[*i];
}

int	remove_quotes(t_token **head)
{
	t_token	*tmp;
	int		i;
	int		j;
	char	*new;

	tmp = *head;
	while (tmp)
	{
		new = malloc(sizeof(char) * (len_wo_quotes(tmp->content) + 1));
		if (!new)
			return (0);
		i = -1;
		j = 0;
		while (tmp->content[++i])
			cpy_in_quotes(tmp->content, &i, &j, new);
		new[j] = '\0';
		free(tmp->content);
		tmp->content = new;
		tmp = tmp->next;
	}
	return (1);
}

int	replace_var(t_shell *shell, t_token **head)
{	
	t_token	*tmp;
	int		i;
	int		len;
	//char	*var;

	(void)shell;
	tmp = *head;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '$')
			{
				len = 0;
				while (tmp->content[i] && tmp->content[i] != '$')
				{
					i++;
					len++;
				}
				
				// var = (char *)malloc(sizeof(char) * (len + 1));
				// if (!var)	
				// 	return (0);
				
				// free(tmp->content);
				// tmp->content = var;
				printf("len of var = %d\n", len);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	tokenize(t_shell *shell, char *input, t_token **head)
{
	int		i;
	t_spec	spec;

	if (!valid_quotes(input))
		return (0);
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			handle_quotes(&input, &i);
		spec = find_spec(&input[i]);
		if (spec.spec)
		{
			if (&input[i] != input)
			{
				tkn_add_back(head, new_tkn(input, i, "WORD"));
				input += i;
			}
			tkn_add_back(head, new_tkn(spec.spec, spec.size, spec.type));
			input += spec.size;
			i = -1;
		}
	}
	if (&input[i] != input)
		tkn_add_back(head, new_tkn(input, i, "WORD"));
	if (!remove_quotes(head))
		return (0);
	if (!replace_var(shell, head))
		return (0);
	// /* printer 4 test */
	// i = 0;
	// t_token *tmp;
	// tmp = *head;
	// while (tmp)
	// {
	// 	printf("- ID %-2d =>", i);
	// 	printf("  Type: %-8s |", (tmp)->type);
	// 	printf("  Size: %-2d |", (tmp)->size);
	// 	printf("  Cont: [%s] \n", (tmp)->content);
	// 	tmp = (tmp)->next;
	// 	i++;
	// }
	return (1);
}

int	count_cmds(t_token *tkn)
{
	int		n;
	t_token	*head;

	n = 0;
	head = tkn;
	while (tkn)
	{
		if (tkn == head)
			n += 1;
		if (!ft_strncmp(tkn->type, "PIPE", 4))
			n++;
		tkn = tkn->next;
	}
	return (n);
}

int	count_args(t_token *tkn)
{
	int		n;

	n = 0;
	while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
	{
		if (!ft_strncmp(tkn->type, "WORD", 4))
			n++;
		else if (!ft_strncmp(tkn->type, "CHEV_L", 6)
			|| !ft_strncmp(tkn->type, "CHEV_LL", 7)
			|| !ft_strncmp(tkn->type, "CHEV_R", 6)
			|| !ft_strncmp(tkn->type, "CHEV_RR", 7))
			while (tkn && ft_strncmp(tkn->type, "WORD", 4))
				tkn = tkn->next;
		tkn = tkn->next;
	}
	// printf("ARGS = %d\n", n);
	return (n);
}

// int	free_mallocs(t_shell *shell, int i)
// {
// 	while (i--)
// 		free(shell->cmds[i].args);
// 	free(shell->cmds);
// 	return (0);
// }

int	init_parser(t_shell *shell, t_token *tkn)
{
	int	i;
	int n;

	shell->cmds_count = count_cmds(tkn);
	// printf("CMD CNT = %d\n", shell->cmds_count);
	shell->cmds = (t_cmd *)malloc(sizeof(t_cmd) * shell->cmds_count);
	if (shell->cmds == NULL)
		return (0);
	n = 0;
	i = -1;
	while (++i < shell->cmds_count)
	{
		n = count_args(tkn);
		shell->cmds[i].argc = n;
		shell->cmds[i].args = (char **)malloc(sizeof(char *) * (n + 1));
		if (shell->cmds[i].args == NULL)
		{
			ft_free_t_cmd(shell->cmds, shell->cmds_count);
			return (0);
		}
		// return (free_mallocs(shell, i));
		// printf("ARGC of CMD %d = %d\n", i, shell->cmds[i].argc);
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
			tkn = tkn->next;
		if (tkn)
			tkn = tkn->next;
	}
	return (1);
}

int	trim_tkn(t_token **tkn)
{
	if (*tkn)
		*tkn = (*tkn)->next;
	while (*tkn && !ft_strncmp((*tkn)->type, "SPACE", 4))
		*tkn = (*tkn)->next;
	return (1);
}

int	parse_chev_l(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].left.target = (*tkn)->content;
	shell->cmds[i].left.oflag = O_RDONLY;
	return (1);
}

int	parse_chev_r(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = (*tkn)->content;
	shell->cmds[i].right.oflag = O_CREAT | O_TRUNC | O_RDWR;
	return (1);
}

int	parse_chev_rr(t_shell *shell, t_token **tkn, int i)
{
	trim_tkn(tkn);
	shell->cmds[i].right.target = (*tkn)->content;
	shell->cmds[i].right.oflag = O_CREAT | O_APPEND | O_RDWR;
	return (1);
}

int	parse_arg(t_shell *shell, t_token **tkn, int i, int *j)
{
	shell->cmds[i].args[++*j] = (*tkn)->content;
	if (!shell->cmds[i].cmd)
		shell->cmds[i].cmd = (*tkn)->content;
	return (1);
}

int	end_parse(t_shell *shell, t_token **tkn, int i, int j)
{
	shell->cmds[i].args[++j] = NULL;
	if (*tkn)
		*tkn = (*tkn)->next;
	return (1);
}

int	parse_cmds(t_shell *shell, t_token *tkn)
{
	int	i;
	int j;

	i = -1;
	while (++i < shell->cmds_count)
	{
		shell->cmds[i].cmd = NULL;
		j = -1;
		while (tkn && ft_strncmp(tkn->type, "PIPE", 4))
		{
			if (!ft_strncmp(tkn->type, "CHEV_LL", 7))
				shell->cmds[i].left.target = "EOF";
			else if (!ft_strncmp(tkn->type, "CHEV_L", 6))
				parse_chev_l(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "CHEV_RR", 7))
				parse_chev_rr(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "CHEV_R", 6))
				parse_chev_r(shell, &tkn, i);
			else if (!ft_strncmp(tkn->type, "WORD", 4))
				parse_arg(shell, &tkn, i, &j);
			tkn = tkn->next;
		}
		end_parse(shell, &tkn, i, j);
	}
	
	/* printer for tests */ //
	// i = -1;
	// while (++i < shell->cmds_count)
	// {
	// 	j = -1;
		
	// 	printf("---------------\n# LEFT TARGET = %s\n", shell->cmds[i].left.target);
	// 	printf("# LEFT oflag = %d\n", shell->cmds[i].left.oflag);
	// 	printf("# LEFT HEREDOC = %s\n", shell->cmds[i].left.heredoc);
	// 	printf("# RIGHT TARGET = %s\n", shell->cmds[i].right.target);
	// 	printf("# RIGHT oflag = %d\n", shell->cmds[i].right.oflag);
	// 	printf("# RIGHT HEREDOC = %s\n---------------\n", shell->cmds[i].right.heredoc);
		
	// 	while (++j < shell->cmds[i].argc)
	// 		printf("%d:%d = %s\n", i, j, shell->cmds[i].args[j]);
	// 	printf("---------------\n");
	// }
	
	return (1);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (ECHO);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (CD);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (PWD);
	else if (!ft_strncmp(cmd, "export", 6))
		return (EXPORT);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (UNSET);
	else if (!ft_strncmp(cmd, "env", 3))
		return (ENV);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (EXIT);
	else
		return (0);
}

char	*get_path(char *cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		ret;

	paths = ft_split(getenv("PATH"), ':');
	ret = -1;
	while (ret == -1 && *paths++)
	{
		tmp = ft_strjoin(*paths, "/");
		path = ft_strjoin(tmp, cmd);
		ret = access(path, R_OK);
		// printf("RET = %d - ", ret);
		// printf("PATH = %s\n", path);
		free(tmp);
		if (ret == -1)
			free(path);
		else
			return (path);
	}
	return (NULL);
}

int	parse(t_shell *shell, char *input)
{
	t_token	*tkn;

	tkn = NULL;
	if (!tokenize(shell, input, &tkn))
		return (free_all(&tkn) && fail("Error - Syntax"));
	if (!init_parser(shell, tkn))
		return (free_all(&tkn) && fail("Error - Init Parser"));
	if (!parse_cmds(shell, tkn))
		return (free_all(&tkn) && fail("Error - Parse Cmds"));
	return (1);
}

// int	copy_envp(t_shell *shell, char **envp_tab)
// {
// 	char **my_envp;
// 	int	i;

// 	i = 0;
// 	while (envp_tab[i])
// 		i++;
// 	my_envp = (char **)malloc(sizeof(char *) * (i + 1));
// 	if (!my_envp)
// 		return (0);
// 	i = 0;
// 	while (envp_tab[i])
// 	{
// 		my_envp[i] = ft_strdup(envp_tab[i]);
// 		i++;
// 	}
// 	my_envp[i] = NULL;
// 	shell->envp_tab = my_envp;
// 	return (1);
// }
