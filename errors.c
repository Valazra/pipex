/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:13:41 by user42            #+#    #+#             */
/*   Updated: 2021/10/13 12:51:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_recup *recup)
{
	close(recup->pipe_fd[0]);
	close(recup->pipe_fd[1]);
	if (recup->fd_file1 != -1)
		close(recup->fd_file1);
	if (recup->fd_file2 != -1)
		close(recup->fd_file2);
}

void	ft_error4(char **global_path, char *tmp)
{
	if (tmp)
		free(tmp);
	if (global_path)
		free_strs(global_path, NULL);
	ft_error("Error\nMalloc failed\n", 0);
}

void	ft_error3(t_recup *recup, char *str, char *cmd)
{
	int	i;

	i = 0;
	if (recup->cmd2)
	{
		while (recup->cmd2[i])
		{
			free(recup->cmd2[i]);
			i++;
		}
		free(recup->cmd2);
		recup->cmd2 = NULL;
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_error2(t_recup *recup, char *str, char *cmd)
{
	int	i;

	i = 0;
	if (recup->cmd1)
	{
		while (recup->cmd1[i])
		{
			free(recup->cmd1[i]);
			i++;
		}
		free(recup->cmd1);
		recup->cmd1 = NULL;
	}
	ft_putstr_fd(str, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}

void	ft_error(char *str, int exit_nbr)
{
	if (errno)
		perror(str);
	else
		ft_putstr_fd(str, 2);
	if (exit_nbr == 0)
		exit(EXIT_FAILURE);
}
