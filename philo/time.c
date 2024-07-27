/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:40:09 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 09:15:37 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		ft_putstr_fd("Error: gettimeofday\n", 2);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(long time, t_table *table)
{
	long	start;

	start = get_time();
	while (get_time() - start < time && !the_end(table))
		usleep(300);
}
