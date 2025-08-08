/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:56:52 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 01:56:52 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

# define FORK "has taken a fork 𐂐"
# define EAT "is eating 😋"
# define SLEEP "is sleeping 😴"
# define THINK "is thinking 🤔"
# define DIED "died 💀"

enum
{
	TIME_DIE,
	TIME_EAT,
	TIME_SLEEP
};

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

enum
{
	L,
	R
};

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int					nbr_eat;
	t_bool				someone_dead;
	int					nbr_philo;
	size_t				nbr_start;
	pthread_mutex_t		control_print;
	pthread_mutex_t		control;
	size_t				times[3];
	pthread_mutex_t		*forks;
}						t_data;

typedef struct s_philos
{
	int					nbr_eat;
	size_t				last_eat_time;
	pthread_t			thread;
	pthread_mutex_t		*forks[2];
	t_data				*data;
	int					id;
}						t_philos;

int						init_data(int argc, char **argv, t_data *data);
void					destroy_all_data(t_data *data);
int						create_trheads(t_philos *philo, pthread_t *monitor);
int						joinning_threads(t_philos *philo, pthread_t *monitor);
size_t					get_time(void);
void					*dinner_philo(void *arg);
void					set_data_nbr_eat(t_data *data);
int						get_data_nbr_eat(t_data *data);
t_bool					someone_is_dead(t_data *data);
size_t					get_last_eat_time(t_philos *philo);
void					print_msg(t_data *data, int id, char *msg,
							int amounts);
void					set_last_eat_time(t_philos *philo);
void					set_nbr_eat(t_philos *philo);
void					set_someone_dead(t_data *data);
int						get_nbr_eat(t_philos *philo);
void					*monitor_philo(void *arg);
int						ft_atoi(char *str);
size_t					time_diff(size_t time_start);

#endif
