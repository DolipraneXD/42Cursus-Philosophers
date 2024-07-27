/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:32:09 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 10:15:31 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		ft_putstr_fd("Error: malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

static void	thread_error(int status, t_mcode code)
{
	if (status == 0)
		return ;
	if (EAGAIN == status)
		ft_putstr_fd("Error: No resources to creat more threads", 2);
	else if (EPERM == status)
		ft_putstr_fd("Error: you do not have appropriate permission\n", 2);
	else if (EINVAL == status)
		ft_putstr_fd("Error: The value specified by attr is invalid\n", 2);
	else if (EINVAL == status && (join == code || detach == code))
		ft_putstr_fd("Error: The thread is not joinable\n", 2);
	else if (ESRCH == status)
		ft_putstr_fd("Error: No thread could be found corresponding \n", 2);
	else if (EDEADLK == status)
		ft_putstr_fd("Error: A deadlock was detected or the value\n", 2);
	else
	{
		ft_putstr_fd("Error: thread failed\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	safe_thread(pthread_t *thread, void *(*fanc)(void *),
	void *data, t_mcode code)
{
	if (code == create)
		thread_error(pthread_create(thread, NULL, fanc, data), create);
	else if (code == join)
		thread_error(pthread_join(*thread, NULL), join);
	else if (code == detach)
		thread_error(pthread_detach(*thread), detach);
	else
	{
		ft_putstr_fd("Error: thread failed\n", 2);
		exit(EXIT_FAILURE);
	}
}
