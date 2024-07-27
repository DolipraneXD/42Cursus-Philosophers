/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 12:20:45 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 10:59:42 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	create_philo(t_philo *philo)
{
	safe_thread(&philo->thread_id, &monitoring, philo, create);
	philo_life(philo);
	exit(EXIT_SUCCESS);
}

static void	*check_if_philos_full(void *data)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)data;
	while (i < table->nb_philo)
	{
		sem_wait(table->full);
		i++;
	}
	sem_post(table->end_dinner);
	return (NULL);
}

static void	kill_them_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
		kill(table->pid[i], SIGKILL);
}

void	start_dinner(t_table *table)
{
	int			i;
	pthread_t	checker;

	i = -1;
	if (table->nb_meals == 0)
		return ;
	else
	{
		while (++i < table->nb_philo)
		{
			table->pid[i] = fork();
			if (table->pid[i] == 0)
				create_philo(&table->philos[i]);
		}
		safe_thread(&checker, check_if_philos_full, table, create);
		pthread_detach(checker);
		sem_wait(table->end_dinner);
		kill_them_all(table);
		cleanup_table(table);
	}
}
