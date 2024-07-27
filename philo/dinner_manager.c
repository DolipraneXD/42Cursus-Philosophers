/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:57:41 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/17 11:59:15 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating_manager(t_philo *philo)
{
	safe_mutex(&philo->philo_lock, lock);
	philo->last_meal = get_time() - philo->table->start_time;
	if (!the_end(philo->table))
		printf("%ld\t%d\tis eating\n", philo->last_meal, philo->id);
	safe_mutex(&philo->philo_lock, unlock);
}

static void	forks_manager(t_philo *philo, t_print status)
{
	if (status == left_fork && !the_end(philo->table))
	{
		philo->leftforktime = get_time() - philo->table->start_time;
		printf("%ld\t%d\thas taken a fork\n", philo->leftforktime, philo->id);
	}
	else if (status == right_fork && !the_end(philo->table))
	{
		philo->rightforktime = get_time() - philo->table->start_time;
		printf("%ld\t%d\thas taken a fork\n", philo->rightforktime, philo->id);
	}
}

static void	sleep_manager(t_philo *philo)
{
	long	time;

	time = get_time() - philo->table->start_time;
	if (!the_end(philo->table))
		printf("%ld\t%d\tis sleeping\n", time, philo->id);
}

static void	thing_manager(t_philo *philo)
{
	long	time;

	time = get_time() - philo->table->start_time;
	if (!the_end(philo->table))
		printf("%ld\t%d\tis thinking\n", time, philo->id);
}

void	print_status(t_philo *philo, t_print status)
{
	long	time;

	if (philo->philo_full)
		return ;
	time = get_time() - philo->table->start_time;
	safe_mutex(&philo->table->write, lock);
	if (status == eat && !the_end(philo->table))
		eating_manager(philo);
	else if (status == sleeping && !the_end(philo->table))
		sleep_manager(philo);
	else if (status == think && !the_end(philo->table))
		thing_manager(philo);
	else if ((status == left_fork || status == right_fork)
		&& !the_end(philo->table))
		forks_manager(philo, status);
	else if (status == dead)
	{
		printf("%ld\t%d\tdied\n", time, philo->id);
		philo->philo_dead = true;
	}
	safe_mutex(&philo->table->write, unlock);
}
