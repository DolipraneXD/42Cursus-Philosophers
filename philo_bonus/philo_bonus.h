/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:40:20 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/24 15:48:12 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdatomic.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>
# include <semaphore.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	long			start_time;
	int				*pid;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*end_dinner;
	sem_t			*full;
	sem_t			*last_meal;
	t_philo			*philos;
}					t_table;

struct s_philo
{
	int				id;
	long			count_meals;
	long			last_meal;
	long			death_time;
	bool			philo_full;
	bool			philo_dead;
	pthread_t		thread_id;
	t_table			*table;
	sem_t			philo_lock;
};

typedef enum e_mcode
{
	lock,
	unlock,
	init,
	create,
	destroy,
	join,
	detach,
}	t_mcode;

typedef enum e_print
{
	eat,
	sleeping,
	think,
	forks,
	left_fork,
	right_fork,
	dead,
}	t_print;

//***********************************Main***********************************//
t_table		*initialize_simulation(int ac, char **av);
void		cleanup_table(t_table *table);
void		*philo_life(void *data);
void		print_status(t_philo *philo, t_print status);
void		*monitoring(void *data);
void		start_dinner(t_table *table);
//*********************************UTILS************************************//
bool		check_input(int ac, char **av);
void		cleanup_table(t_table *table);
void		ft_error(t_table *table, int flag);
long		get_time(void);
void		ft_usleep(long time, t_table *table);
long int	ft_atoil(char *str);
void		ft_putstr_fd(char *s, int fd);
bool		check_input(int ac, char **av);
//*******************************safe functions****************************//
void		safe_thread(pthread_t *thread, void *(*fanc)(void *),
				void *data, t_mcode code);
void		*safe_malloc(size_t size);
#endif