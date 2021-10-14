/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:07:47 by user42            #+#    #+#             */
/*   Updated: 2021/10/14 15:42:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*set_tmp(char **global_path, char *tmp, int i)
{
	tmp = ft_strjoin(global_path[i], "/");
	if (tmp == NULL)
		ft_error4(global_path, tmp);
	return (tmp);
}

char	*find_path(char *str, char **env, int i)
{
	char	**global_path;
	char	*tmp;
	char	*curr_path;

	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			global_path = ft_split(&env[0][5], ':');
		env++;
	}
	while (global_path && global_path[i])
	{
		tmp = set_tmp(global_path, tmp, i);
		curr_path = set_curr_path(global_path, tmp, curr_path, str);
		if (access(curr_path, X_OK) != -1)
		{
			free_strs(global_path, tmp);
			return (curr_path);
		}
		i++;
		free2(tmp, curr_path);
	}
	free_strs(global_path, NULL);
	return (NULL);
}

void	run_cmd1(t_recup *recup, char **av, char **env)
{
	if (check_space(av[2]))
		recup->cmd1 = ft_split(av[2], ' ');
	else
		recup->cmd1 = ft_split(av[2], '\0');
	recup->path1 = find_path(recup->cmd1[0], env, 0);
	if (recup->path1 == NULL)
		ft_error2(recup, "command not found: ", av[2]);
	dup2(recup->fd_file1, STDIN_FILENO);
	dup2(recup->pipe_fd[1], STDOUT_FILENO);
	close_fd(recup);
	if (execve(recup->path1, recup->cmd1, env) < 0)
	{
		if (recup->path1)
			free(recup->path1);
	}
	exit(0);
}

void	run_cmd2(t_recup *recup, char **av, char **env)
{
	if (check_space(av[3]))
		recup->cmd2 = ft_split(av[3], ' ');
	else
		recup->cmd2 = ft_split(av[3], '\0');
	recup->path2 = find_path(recup->cmd2[0], env, 0);
	if (recup->path2 == NULL)
		ft_error3(recup, "command not found: ", av[3]);
	dup2(recup->pipe_fd[0], STDIN_FILENO);
	dup2(recup->fd_file2, STDOUT_FILENO);
	close_fd(recup);
	if (execve(recup->path2, recup->cmd2, env) < 0)
	{
		if (recup->path2)
			free(recup->path2);
	}
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	t_recup	recup;

	if (ac != 5)
		ft_error("Error\nBad Model (not 4 args)\n", 0);
	init_recup(&recup);
	recup.fd_file1 = open(av[1], O_RDONLY);
	if (recup.fd_file1 == -1)
		ft_error(av[1], 1);
	recup.fd_file2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (recup.fd_file2 == -1)
		ft_error(av[4], 0);
	if (pipe(recup.pipe_fd) == -1)
		ft_error("Error\nInitialization of pipe's fd failed\n", 0);
	if (recup.fd_file1 != -1)
		recup.pid1 = fork();
	if (recup.pid1 == 0 && recup.fd_file1 != -1)
		run_cmd1(&recup, av, env);
	recup.pid2 = fork();
	if (recup.pid2 == 0)
		run_cmd2(&recup, av, env);
	close_fd(&recup);
	if (recup.fd_file1 != -1)
		waitpid(recup.pid1, NULL, 0);
	waitpid(recup.pid2, NULL, 0);
	return (0);
}
