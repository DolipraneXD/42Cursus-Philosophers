/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:32:09 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 15:18:37 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (NULL);
	}
	return (ptr);
}

static int	mutex_error(int status, t_mcode code)
{
	if (status == 0)
		return (0);
	if (EINVAL == status && (code == lock || code == unlock))
		ft_putstr_fd("Error :The value specified by mutex is invalid.\n", 2);
	else if (EINVAL == status && code == init)
		ft_putstr_fd("Error :The value specified by attr is invalid.\n", 2);
	else if (EDEADLK == status)
		ft_putstr_fd("Error :A deadlock would occur if the thread ...\n", 2);
	else if (EPERM == status)
		ft_putstr_fd("Error :The current thread does not hold the ...\n", 2);
	else if (ENOMEM == status)
		ft_putstr_fd("The process cannot allocate enough memory to...\n", 2);
	else if (EBUSY == status)
		ft_putstr_fd("The mutex is already locked.\n", 2);
	return (-1);
}

int	safe_mutex(pthread_mutex_t *mutex, t_mcode code)
{
	if (code == lock)
	{
		if (mutex_error(pthread_mutex_lock(mutex), lock) == -1)
			return (-1);
	}
	else if (code == unlock)
	{
		if (mutex_error(pthread_mutex_unlock(mutex), unlock) == -1)
			return (-1);
	}
	else if (code == init)
	{
		if (mutex_error(pthread_mutex_init(mutex, NULL), init) == -1)
			return (-1);
	}
	else if (code == destroy)
	{
		if (mutex_error(pthread_mutex_destroy(mutex), destroy) == -1)
			return (-1);
	}
	else
		return (ft_putstr_fd("Error: mutex failed\n", 2), -1);
	return (0);
}

static int	thread_error(int status, t_mcode code)
{
	if (status == 0)
		return (0);
	if (EAGAIN == status)
		ft_putstr_fd("Error: No resources to creat more threads\n", 2);
	else if (EPERM == status)
		ft_putstr_fd("Error: you do not have appropriate permission\n", 2);
	else if (EINVAL == status)
		ft_putstr_fd("Error: The value specified by attr is invalid\n", 2);
	else if (EINVAL == status && (join == code || detach == code))
		ft_putstr_fd("Error: The thread is not joinable\n", 2);
	else if (ESRCH == status)
		ft_putstr_fd("Error: No thread could be found corresponding ...\n", 2);
	else if (EDEADLK == status)
		ft_putstr_fd("Error: A deadlock was detected or the value ...\n", 2);
	else
		ft_putstr_fd("Error: thread failed\n", 2);
	return (-1);
}

int	safe_thread(pthread_t *thread, void *(*fanc)(void *), void *data,
		t_mcode code)
{
	if (code == create)
	{
		if (thread_error(pthread_create(thread, NULL, fanc, data), create)
			== -1)
			return (-1);
	}
	else if (code == join)
	{
		if (thread_error(pthread_join(*thread, NULL), join) == -1)
			return (-1);
	}
	else if (code == detach)
	{
		if (thread_error(pthread_detach(*thread), detach) == -1)
			return (-1);
	}
	else
		return (ft_putstr_fd("Error: thread failed\n", 2), -1);
	return (0);
}
