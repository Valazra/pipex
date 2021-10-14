/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:33:04 by user42            #+#    #+#             */
/*   Updated: 2021/10/12 13:18:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (i == ft_strlen(str))
		return (0);
	return (1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

void	free2(char *tmp, char *curr_path)
{
	if (tmp)
		free(tmp);
	if (curr_path)
		free(curr_path);
}

void	free_strs(char **big, char *small)
{
	int	i;

	i = 0;
	if (big)
	{
		while (big[i])
		{
			free(big[i]);
			i++;
		}
		free(big);
	}
	if (small)
		free(small);
}

char	*set_curr_path(char **global_path, char *tmp, char *c_p, char *str)
{
	c_p = ft_strjoin(tmp, str);
	if (c_p == NULL)
		ft_error4(global_path, tmp);
	return (c_p);
}
