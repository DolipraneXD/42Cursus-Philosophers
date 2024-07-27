/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 15:22:09 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 08:42:23 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	table_init(t_table *table, int ac, char **av)
{
	table->nb_philo = ft_atoil(av[1]);
	if (table->nb_philo < 1)
		return (ft_error(table, 4), -1);
	table->time_to_die = ft_atoil(av[2]);
	if (table->time_to_die < 1)
		return (ft_error(table, 4), -1);
	table->time_to_eat = ft_atoil(av[3]);
	if (table->time_to_eat < 1)
		return (ft_error(table, 4), -1);
	table->time_to_sleep = ft_atoil(av[4]);
	if (table->time_to_sleep < 1)
		return (ft_error(table, 4), -1);
	if (ac == 6)
		table->nb_meals = ft_atoil(av[5]);
	else
		table->nb_meals = -1;
	if (ac == 6 && table->nb_meals < 1)
		return (ft_error(table, 4), -1);
	return (0);
}

static void	fork_init(t_philo *philo, t_fork *forks, int i)
{
	int	philo_nb;

	philo_nb = philo->table->nb_philo;
	philo->right_fork = &forks[(i + 1) % philo_nb];
	philo->left_fork = &forks[i];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[i];
		philo->left_fork = &forks[(i + 1) % philo_nb];
	}
}

static int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nb_philo)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->count_meals = 0;
		philo->last_meal = 0;
		philo->table = table;
		philo->philo_full = false;
		philo->philo_dead = false;
		if (safe_mutex(&philo->philo_lock, init) == -1)
			return (-1);
		fork_init(philo, table->forks, i);
	}
	return (0);
}

int	serving_table(t_table *table)
{
	int	i;

	i = -1;
	table->end_time = false;
	table->threads_read = false;
	table->no_error = false;
	if (safe_mutex(&table->table_mutex, init) == -1)
		return (-1);
	if (safe_mutex(&table->write, init) == -1)
		return (-1);
	if (safe_mutex(&table->lock, init) == -1)
		return (-1);
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philo);
	table->forks = safe_malloc(sizeof(t_fork) * table->nb_philo);
	if (!table->philos || !table->forks)
		return (-1);
	while (++i < table->nb_philo)
	{
		if (safe_mutex(&table->forks[i].fork, init) == -1)
			return (-1);
		table->forks[i].fork_id = i;
	}
	if (philo_init(table) == -1)
		return (-1);
	return (0);
}
