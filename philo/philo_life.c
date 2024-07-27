/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:19:59 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 09:05:48 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	wait_for_all(t_philo *philo)
{
	while (!get_bool(&philo->table->table_mutex, &philo->table->threads_read)
		&& !get_bool(&philo->table->table_mutex, &philo->table->no_error))
		;
	if (get_bool(&philo->table->table_mutex, &philo->table->no_error) == true)
	{
		return (-1);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	return (0);
}

void	thinking(t_philo *philo)
{
	print_status(philo, think);
}

int	eating(t_philo *philo)
{
	if (safe_mutex(&philo->right_fork->fork, lock) == -1)
		return (-1);
	print_status(philo, right_fork);
	if (safe_mutex(&philo->left_fork->fork, lock) == -1)
		return (-1);
	print_status(philo, left_fork);
	set_long(&philo->philo_lock, &philo->last_meal, get_time());
	print_status(philo, eat);
	philo->count_meals++;
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->nb_meals != -1
		&& (philo->count_meals > philo->table->nb_meals))
		set_bool(&philo->philo_lock, &philo->philo_full, true);
	if (safe_mutex(&philo->right_fork->fork, unlock) == -1)
		return (-1);
	if (safe_mutex(&philo->left_fork->fork, unlock) == -1)
		return (-1);
	return (0);
}

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (wait_for_all(philo) == -1)
		return (NULL);
	while (!the_end(philo->table))
	{
		if (philo->philo_full)
			break ;
		if (eating(philo) == -1)
			return (NULL);
		print_status(philo, sleeping);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		thinking(philo);
	}
	return (NULL);
}
