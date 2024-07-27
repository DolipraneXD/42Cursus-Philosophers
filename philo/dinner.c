/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:49:19 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 09:10:51 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	check_death(t_philo *philo)
{
	long	time;

	safe_mutex(&philo->philo_lock, lock);
	time = get_time() - philo->table->start_time - philo->last_meal;
	safe_mutex(&philo->philo_lock, unlock);
	if (time > philo->table->time_to_die)
		return (true);
	return (false);
}

static void	monitoring(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->nb_philo)
		{
			if (check_death(&table->philos[i]) == true)
			{
				if (safe_mutex(&table->write, lock) == -1)
					return ;
				set_bool(&table->table_mutex, &table->end_time, true);
				table->philos->death_time = get_time() - table->start_time;
				if (table->philos[i].philo_full != true)
					printf("%ld\t%d\tdied\n", table->philos->death_time,
						table->philos[i].id);
				if (safe_mutex(&table->write, unlock) == -1)
					return ;
				if (table->nb_philo == 1)
					safe_mutex(&table->philos->right_fork->fork, unlock);
				return ;
			}
		}
	}
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		safe_mutex(&table->philos[i].philo_lock, destroy);
		safe_mutex(&table->forks[i].fork, destroy);
	}
	safe_mutex(&table->write, destroy);
	safe_mutex(&table->lock, destroy);
	safe_mutex(&table->table_mutex, destroy);
}

static int	join_all(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		if (safe_thread(&table->philos[i].thread_id, NULL, NULL, join) == -1)
			return (-1);
	}
	return (0);
}

int	start_dinner(t_table *table)
{
	int	i;

	i = -1;
	if (table->nb_meals == 0)
		return (0);
	else
	{
		while (++i < table->nb_philo)
		{
			if (safe_thread(&table->philos[i].thread_id,
					&philo_life, &table->philos[i], create) == -1)
			{
				set_bool(&table->table_mutex, &table->no_error, true);
				return (-1);
			}
		}
	}
	table->start_time = get_time();
	set_bool(&table->table_mutex, &table->threads_read, true);
	monitoring(table);
	join_all(table);
	destroy_mutex(table);
	return (0);
}
