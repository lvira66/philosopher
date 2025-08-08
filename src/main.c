/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:10 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:31:06 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	create_trhead(t_philos *philo, pthread_t *monitor)
{
	int	i;

	i = -1;
	philo->data->nbr_start = get_time();
	while (++i < philo->data->nbr_philo)
		if (pthread_create(&philo[i].thread, NULL, &dinner_philo, &philo[i]))
			return (EXIT_FAILURE);
	if (pthread_create(monitor, NULL, &monitor_philo, philo))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	join_thread(t_philos *philo, pthread_t *monitor)
{
	int	i;

	i = -1;
	while (++i < philo->data->nbr_philo)
		if (pthread_join(philo[i].thread, NULL))
			return (EXIT_FAILURE);
	if (pthread_join(*monitor, NULL))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_forks(t_data *data)
{
	int	i;

	i = -1;
	data->forks = calloc(data->nbr_philo, sizeof(pthread_mutex_t));
	while (++i < data->nbr_philo)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_philos	*init_philos(t_data *data)
{
	t_philos	*philo;
	int			i;

	i = -1;
	philo = calloc(data->nbr_philo, sizeof(t_philos));
	if (philo == NULL)
		return (NULL);
	if (init_forks(data))
		return (NULL);
	while (++i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].nbr_eat = data->nbr_eat;
		philo[i].forks[R] = &data->forks[philo[i].id - 1];
		philo[i].forks[L] = &data->forks[philo[i].id % data->nbr_philo];
	}
	data->nbr_eat = data->nbr_philo;
	return (philo);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philos	*philo;
	pthread_t	monitor;

	if (init_data(argc, argv, &data))
	{
		printf("INVALID ARGS");
		return (EXIT_FAILURE);
	}
	philo = init_philos(&data);
	if (philo != NULL)
	{
		if (create_trhead(philo, &monitor))
			return (printf("THREAD CRASH"), EXIT_FAILURE);
		if (join_thread(philo, &monitor))
			return (printf("JOIN_THREAD CRASH"), EXIT_FAILURE);
	}
	destroy_all_data(&data);
	free(philo);
	return (EXIT_SUCCESS);
}
