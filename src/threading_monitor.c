/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_monitor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:54:51 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:08 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	print_dead(t_data *data, int id)
{
	pthread_mutex_lock(&data->control_print);
	printf("%zu \t %d \t died\n", time_diff(data->nbr_start), id);
	pthread_mutex_unlock(&data->control_print);
}

static size_t	aux_monitor(t_philos *philo)
{
	size_t	diff;
	int		nbr_eat;

	diff = get_time() - get_last_eat_time(philo);
	nbr_eat = get_nbr_eat(philo);
	return (diff > philo->data->times[TIME_DIE] && nbr_eat);
}

void	*monitor_philo(void *arg)
{
	int			i;
	t_philos	*philo;

	i = 0;
	philo = (t_philos *)arg;
	while (get_data_nbr_eat(philo->data))
	{
		if (aux_monitor(&philo[i]))
		{
			set_someone_dead(philo->data);
			print_dead(philo->data, philo[i].id);
			return (NULL);
		}
		i++;
		if (i == philo->data->nbr_philo)
			i = 0;
		usleep(100);
	}
	return (NULL);
}
