/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lviravon <marvin@d42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 22:55:24 by lviravon          #+#    #+#             */
/*   Updated: 2025/08/08 03:30:57 by lviravon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	*verify_args(int argc, char **argv)
{
	int	i;
	int	*args;

	i = 1;
	if (argc < 5 || argc > 6)
		return (NULL);
	args = malloc(sizeof(int) * (argc - 1));
	if (args == NULL)
		return (NULL);
	while (i < argc)
	{
		args[i - 1] = ft_atoi(argv[i]);
		if (args[i - 1] < 1)
		{
			free(args);
			return (NULL);
		}
		i++;
	}
	return (args);
}

int	init_data(int argc, char **argv, t_data *data)
{
	int	*args;

	args = verify_args(argc, argv);
	if (!args)
		return (EXIT_FAILURE);
	data->times[TIME_SLEEP] = args[3] * 1000;
	data->times[TIME_EAT] = args[2] * 1000;
	data->times[TIME_DIE] = args[1];
	data->nbr_philo = args[0];
	data->nbr_eat = -1;
	data->someone_dead = FALSE;
	if (argc == 6)
		data->nbr_eat = args[4];
	pthread_mutex_init(&data->control, NULL);
	pthread_mutex_init(&data->control_print, NULL);
	free(args);
	return (EXIT_SUCCESS);
}

void	destroy_all_data(t_data *data)
{
	int	i;

	i = 0;
	while (++i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->control_print);
	free(data->forks);
}
