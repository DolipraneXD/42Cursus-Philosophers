/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:35:29 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 08:37:42 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_table *table, int flag)
{
	if (flag == 1)
		printf("Error not valid int\n");
	else if (flag == 2)
	{
		printf("Error With mutex\n");
		free(table);
	}
	else if (flag == 5)
	{
		printf("Error with threads\n");
		free(table);
	}
	else if (flag == 3)
		printf("Error not valid arguments\n");
	else if (flag == 4)
		printf("inputs must not be less than 0\n");
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
}

void	clean_up(t_table *table)
{
	if (table)
	{
		free(table->forks);
		free(table->philos);
		free(table);
	}
}
