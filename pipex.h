/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:08:33 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 13:18:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_recup
{
	int		fd_file1;
	int		fd_file2;
	int		pipe_fd[2];
	int		pid1;
	int		pid2;
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}		t_recup;

void	ft_error(char *str, int exit);
void	ft_error2(t_recup *recup, char *str, char *cmd);
void	ft_error3(t_recup *recup, char *str, char *cmd);
void	ft_error4(char **global_path, char *tmp);
void	close_fd(t_recup *recup);
int		check_space(char *str);
void	ft_putstr_fd(char *str, int fd);
int		ft_strlen(char const *str);
void	init_recup(t_recup *recup);
char	**ft_split(char const *s, char c);
void	free_strs(char **big, char *small);
void	free2(char *tmp, char *curr_path);
char	*set_curr_path(char **global_path, char *tmp, char *c_p, char *str);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
