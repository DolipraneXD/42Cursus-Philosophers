/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:56:46 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 14:59:47 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, t_print status)
{
	long	time;

	if (philo->philo_full)
		return ;
	sem_wait(philo->table->write);
	time = get_time() - philo->table->start_time;
	if (status == eat)
		printf("%ld\t%d\tis eating\n", time, philo->id);
	else if (status == sleeping)
		printf("%ld\t%d\tis sleeping\n", time, philo->id);
	else if (status == think)
		printf("%ld\t%d\tis thinking\n", time, philo->id);
	else if (status == left_fork)
		printf("%ld\t%d\thas taken a fork\n", time, philo->id);
	else if (status == right_fork)
		printf("%ld\t%d\thas taken a fork\n", time, philo->id);
	sem_post(philo->table->write);
}

static void	eating(t_philo *philo)
{
	sem_wait(philo->table->forks);
	print_status(philo, right_fork);
	sem_wait(philo->table->forks);
	print_status(philo, left_fork);
	sem_wait(philo->table->last_meal);
	philo->last_meal = get_time() - philo->table->start_time;
	sem_post(philo->table->last_meal);
	print_status(philo, eat);
	philo->count_meals++;
	if (philo->table->nb_meals != -1
		&& (philo->count_meals >= philo->table->nb_meals))
	{
		sem_post(philo->table->full);
		philo->philo_full = true;
	}
	ft_usleep(philo->table->time_to_eat, philo->table);
	sem_post(philo->table->forks);
	sem_post(philo->table->forks);
}

void	*philo_life(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat, philo->table);
	while (1)
	{
		if (philo->philo_full)
			break ;
		eating(philo);
		print_status(philo, sleeping);
		ft_usleep(philo->table->time_to_sleep, philo->table);
		print_status(philo, think);
	}
	return (NULL);
}

void	*monitoring(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->table->nb_philo == 1)
	{
		print_status(philo, left_fork);
		ft_usleep(philo->table->time_to_die, philo->table);
		sem_wait(philo->table->write);
		printf("%ld\t%d\tdied\n", get_time() - philo->table->start_time,
			philo->id);
		sem_post(philo->table->end_dinner);
		return (NULL);
	}
	while (1)
	{
		sem_wait(philo->table->last_meal);
		philo->death_time = get_time() - philo->table->start_time
			- philo->last_meal;
		sem_post(philo->table->last_meal);
		if (philo->death_time >= philo->table->time_to_die)
		{
			sem_wait(philo->table->write);
			printf("%ld\t%d\tdied\n", philo->death_time, philo->id);
			sem_post(philo->table->end_dinner);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
