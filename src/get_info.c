/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:16 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:02 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	get_nbr_eat(t_philos *philo)
{
	int	yes_or_not;

	pthread_mutex_lock(&philo->data->control);
	yes_or_not = philo->nbr_eat;
	pthread_mutex_unlock(&philo->data->control);
	return (yes_or_not);
}

size_t	get_last_eat_time(t_philos *philo)
{
	size_t	yes_or_not;

	pthread_mutex_lock(&philo->data->control);
	yes_or_not = philo->last_eat_time;
	pthread_mutex_unlock(&philo->data->control);
	return (yes_or_not);
}

int	get_data_nbr_eat(t_data *data)
{
	int	yes_or_not;

	pthread_mutex_lock(&data->control);
	yes_or_not = data->nbr_eat;
	pthread_mutex_unlock(&data->control);
	return (yes_or_not);
}

t_bool	someone_is_dead(t_data *data)
{
	t_bool	yes_or_not;

	pthread_mutex_lock(&data->control);
	yes_or_not = data->someone_dead;
	pthread_mutex_unlock(&data->control);
	return (yes_or_not);
}
