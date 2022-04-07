/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: groubaud <groubaud@student.s19.be >        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 03:24:49 by groubaud          #+#    #+#             */
/*   Updated: 2022/02/11 03:24:49 by groubaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	ft_set_cmd1_cmd2(char ***cmd1, char ***cmd2, char **av)
{
	*cmd1 = ft_split(av[2], ' ');
	if (!(*cmd1))
		return (-1);
	*cmd2 = ft_split(av[3], ' ');
	if (!(*cmd2))
		return (-1);
	return (CHECK_OK);	
}

char **ft_basic_parser(char *str)
{
	return(ft_split(str, '_'));
}

int	ft_count_pipe(char **parser)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (parser[i])
	{
		if (ft_strcmp(parser[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

int		ft_control_tower(t_minishell *mini, char **parser, int i, char *envp[])
{
	pid_t	pid_pipe;
	char	**cmd_args;

	pid_pipe = 0; 
	if (ft_strcmp(parser[i], "<") == 0)
	{
		ft_printf("redir in\n");
		if (i == 0
		&& ft_redir_in(&mini->fd_in, NULL) == CHECK_ERR) //&fd_in sera remplacé par la variable de la structure
			return (1);
		else if (ft_redir_in(&mini->fd_in, parser[i - 1]) == CHECK_ERR) //&fd_in sera remplacé par la variable de la structure
			return (1);
	}
	else if (ft_strcmp(parser[i], ">") == 0)
	{
		ft_printf("redir out : %s %s\n", parser[i], parser[i + 1]);
		if (ft_redir_out(&mini->fd_out, parser[i + 1]) == CHECK_ERR)
			return (1);
	}
	else if (ft_strcmp(parser[i], ">>") == 0)
	{
		ft_printf("double out : %s %s\n", parser[i], parser[i + 1]);
		if (ft_double_redir_out(&mini->fd_out, parser[i + 1]) == CHECK_ERR)
			return (1);
	}
	else if (ft_strcmp(parser[i], "|") == 0)
	{
		ft_printf("pipe : %s %s %s\n", parser[i - 1], parser[i], parser[i + 1]);
		mini->nb_pipe--;
		pid_pipe = ft_pipe(mini);
	}
	if (pid_pipe != 1 && mini->nb_pipe > 0)
	{
		printf("recursive\n");
		mini->nb_pipe--;
		ft_control_tower(mini, parser, i++, envp);
	}
	if (pid_pipe != 1)
	{
		printf("ft_exec\n");
		cmd_args = ft_split(parser[i], ' ');
		ft_exec(mini, cmd_args, envp);
		printf("fin ft_exec\n");
		free(cmd_args);
	}
	
	i++;
	return (1);
}

int main(int ac, char **av, char *envp[])
{
	t_minishell	mini;
	char	**parser;
	char	**cmd_args1;
	char	**cmd_args2;
	int	i;

	if (ac != 2)
		return (printf("Error: %s 'commmand line'\n %i\n", av[0], ac));
	parser = ft_basic_parser(av[1]);

	ft_putstr("parser :\n");
	ft_puttab(parser, " ");
	ft_putstr("\n");
	mini.nb_pipe = ft_count_pipe(parser);
	printf("nb_pipe : %i\n", mini.nb_pipe);

	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.paths = what_are_the_paths(envp);
	if (mini.paths == NULL)
		return (1); // a voir

	ft_control_tower(&mini, parser, 0, envp);

	close(mini.fd_in);
	close(mini.fd_out);
	close(mini.in);
	close(mini.out);

}