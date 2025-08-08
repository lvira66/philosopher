/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:21 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:17 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	set_data_nbr_eat(t_data *data)
{
	pthread_mutex_lock(&data->control);
	data->nbr_eat--;
	pthread_mutex_unlock(&data->control);
}

void	set_nbr_eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->control);
	philo->nbr_eat--;
	pthread_mutex_unlock(&philo->data->control);
}

void	set_someone_dead(t_data *data)
{
	pthread_mutex_lock(&data->control);
	data->someone_dead = TRUE;
	pthread_mutex_unlock(&data->control);
}

void	set_last_eat_time(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->control);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->control);
}
