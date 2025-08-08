/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:29 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:14 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	ft_atoi(char *str)
{
	int	nbr;

	nbr = 0;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*str++ - '0');
	if (*str != '\0' || nbr > 2147483647)
		return (-1);
	return (nbr);
}

size_t	get_time(void)
{
	t_timeval	time;
	size_t		time_current;

	gettimeofday(&time, NULL);
	time_current = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (time_current);
}

size_t	time_diff(size_t time_start)
{
	size_t	time_current;

	time_current = get_time();
	return (time_current - time_start);
}

void	print_msg(t_data *data, int id, char *msg, int amounts)
{
	pthread_mutex_lock(&data->control_print);
	if (someone_is_dead(data))
	{
		pthread_mutex_unlock(&data->control_print);
		return ;
	}
	while (amounts--)
		printf("%zu \t %d \t %s \n", time_diff(data->nbr_start), id, msg);
	pthread_mutex_unlock(&data->control_print);
}
