/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 10:06:07 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 10:17:01 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error(t_table *table, int flag)
{
	if (table)
		cleanup_table(table);
	if (flag == 1)
		printf("Error: Invalid number of arguments\n");
	else if (flag == 2)
		printf("Error: Invalid arguments\n");
	else if (flag == 3)
		printf("Error: Malloc failed\n");
	else if (flag == 4)
		printf("Error: Invalid arguments Must be a positive number\n");
	else if (flag == 5)
		printf("Error: Number of argument need to be 4 or 5\n");
	else if (flag == 6)
		printf("Error: Semaphore creation failure\n");
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (fd < 0)
		return ;
	if (s == NULL)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
	if (fd == 2)
		exit (EXIT_FAILURE);
}
