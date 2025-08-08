/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:06 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:11 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	philo_sleeping_thinking(t_philos *philo)
{
	print_msg(philo->data, philo->id, SLEEP, 1);
	usleep(philo->data->times[TIME_SLEEP]);
	print_msg(philo->data, philo->id, THINK, 1);
}

static void	philo_eating(t_philos *philo)
{
	print_msg(philo->data, philo->id, EAT, 1);
	set_last_eat_time(philo);
	set_nbr_eat(philo);
	usleep(philo->data->times[TIME_EAT]);
	pthread_mutex_unlock(philo->forks[L]);
	pthread_mutex_unlock(philo->forks[R]);
}

static void	philo_get_forks(t_philos *philo)
{
	pthread_mutex_lock(philo->forks[philo->id % 2 == 0]);
	pthread_mutex_lock(philo->forks[philo->id % 2 != 0]);
	print_msg(philo->data, philo->id, FORK, 2);
}

void	*dinner_philo(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	set_last_eat_time(philo);
	if (philo->data->nbr_philo == 1)
	{
		print_msg(philo->data, philo->id, FORK, 1);
		return (NULL);
	}
	while (philo->nbr_eat && !someone_is_dead(philo->data))
	{
		philo_get_forks(philo);
		philo_eating(philo);
		if (philo->nbr_eat == 0)
		{
			set_data_nbr_eat(philo->data);
			break ;
		}
		philo_sleeping_thinking(philo);
		usleep(100);
	}
	return (NULL);
}
