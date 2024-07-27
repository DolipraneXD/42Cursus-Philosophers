/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:22:31 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 14:37:25 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *mutex, bool *var, bool value)
{
	if (safe_mutex(mutex, lock) == -1)
		return ;
	*var = value;
	if (safe_mutex(mutex, unlock) == -1)
		return ;
}

bool	get_bool(pthread_mutex_t *mutex, bool *var)
{
	bool	value;

	if (safe_mutex(mutex, lock) == -1)
		return (false);
	value = *var;
	if (safe_mutex(mutex, unlock) == -1)
		return (false);
	return (value);
}

void	set_long(pthread_mutex_t *mutex, long *var, long value)
{
	if (safe_mutex(mutex, lock) == -1)
		return ;
	*var = value;
	if (safe_mutex(mutex, unlock) == -1)
		return ;
}

long	get_long(pthread_mutex_t *mutex, long *var)
{
	long	value;

	if (safe_mutex(mutex, lock) == -1)
		return (-1);
	value = *var;
	if (safe_mutex(mutex, unlock) == -1)
		return (-1);
	return (value);
}

bool	the_end(t_table *table)
{
	return (get_bool(&table->table_mutex, &table->end_time));
}
