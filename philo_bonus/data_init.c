/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 10:53:01 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 10:07:19 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	table_init(t_table *table, int ac, char **av)
{
	if (ac < 5)
		ft_error(table, 5);
	table->nb_philo = ft_atoil(av[1]);
	if (table->nb_philo < 1)
		ft_error(table, 4);
	table->time_to_die = ft_atoil(av[2]);
	if (table->time_to_die < 1)
		ft_error(table, 4);
	table->time_to_eat = ft_atoil(av[3]);
	if (table->time_to_eat < 1)
		ft_error(table, 4);
	table->time_to_sleep = ft_atoil(av[4]);
	if (table->time_to_sleep < 1)
		ft_error(table, 4);
	if (ac == 6)
	{
		table->nb_meals = ft_atoil(av[5]);
		if (table->nb_meals < 1)
			ft_error(table, 4);
	}
	else
		table->nb_meals = -1;
	table->start_time = 0;
}

static void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->nb_philo)
	{
		table->philos[i].id = i + 1;
		table->philos[i].count_meals = 0;
		table->philos[i].last_meal = get_time();
		table->philos[i].death_time = table->philos[i].last_meal
			+ table->time_to_die;
		table->philos[i].philo_full = false;
		table->philos[i].philo_dead = false;
		table->philos[i].table = table;
		table->philos[i].thread_id = 0;
	}
}

static void	serving_table(t_table *table)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("end_dinner");
	sem_unlink("full");
	sem_unlink("last_meal");
	table->forks = sem_open("forks", O_CREAT, 0644, table->nb_philo);
	table->write = sem_open("write", O_CREAT, 0644, 1);
	table->full = sem_open("full", O_CREAT, 0644, 0);
	table->end_dinner = sem_open("end_dinner", O_CREAT, 0644, 0);
	table->last_meal = sem_open("last_meal", O_CREAT, 0644, 1);
	if (table->forks == SEM_FAILED || table->write == SEM_FAILED
		|| table->last_meal == SEM_FAILED || table->end_dinner == SEM_FAILED
		||table->full == SEM_FAILED)
		ft_error(table, 6);
	table->pid = safe_malloc(sizeof(int) * table->nb_philo);
	table->philos = safe_malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->pid || !table->philos)
		ft_error(table, 3);
	table->start_time = get_time();
	init_philo(table);
}

t_table	*initialize_simulation(int ac, char **av)
{
	t_table	*table;

	table = safe_malloc(sizeof(t_table));
	if (!table)
		ft_error(NULL, 3);
	table_init(table, ac, av);
	serving_table(table);
	return (table);
}

void	cleanup_table(t_table *table)
{
	free(table->pid);
	free(table->philos);
	sem_close(table->forks);
	sem_close(table->write);
	sem_close(table->last_meal);
	sem_close(table->end_dinner);
	sem_post(table->full);
	sem_close(table->full);
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("last_meal");
	sem_unlink("end_dinner");
	sem_unlink("full");
	free(table);
}
