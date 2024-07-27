/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-fat <moel-fat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:14:13 by moel-fat          #+#    #+#             */
/*   Updated: 2024/07/25 08:41:56 by moel-fat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <limits.h>
# include <pthread.h>
# include <errno.h>

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	fork;
	int				fork_id;
}					t_fork;

typedef struct s_table
{
	long			nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			nb_meals;
	long			start_time;
	bool			end_time;
	bool			start_threads;
	bool			threads_read;
	bool			no_error;
	pthread_mutex_t	write;
	pthread_mutex_t	lock;
	pthread_mutex_t	table_mutex;
	t_fork			*forks;
	t_philo			*philos;
}					t_table;

struct s_philo
{
	int				id;
	long			count_meals;
	long			last_meal;
	long			last_sleep;
	long			death_time;
	bool			philo_full;
	bool			philo_dead;
	t_fork			*right_fork;
	long			rightforktime;
	t_fork			*left_fork;
	long			leftforktime;
	pthread_t		thread_id;
	t_table			*table;
	pthread_mutex_t	philo_lock;
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

//** main**//
int			serving_table(t_table *table);
int			table_init(t_table *table, int ac, char **av);
void		clean_up(t_table *table);
int			start_dinner(t_table *table);
void		*philo_life(void *data);
void		destroy_mutex(t_table *table);
//**safe	 functions**//
void		*safe_malloc(size_t size);
int			safe_mutex(pthread_mutex_t *mutex, t_mcode code);
int			safe_thread(pthread_t *thread, void *(*fanc)(void *), void *data,
				t_mcode code);
bool		get_bool(pthread_mutex_t *mutex, bool *var);
void		set_bool(pthread_mutex_t *mutex, bool *var, bool value);
long		get_long(pthread_mutex_t *mutex, long *var);
void		set_long(pthread_mutex_t *mutex, long *var, long value);
bool		the_end(t_table *table);
void		print_status(t_philo *philo, t_print status);
//** utils.c **//
long int	ft_atoil(char *str);
void		ft_usleep(long time, t_table *table);
bool		check_input(int ac, char **av);
void		ft_putstr_fd(char *s, int fd);
long		get_time(void);
//** error manager **//
void		ft_error(t_table *table, int flag);

#endif