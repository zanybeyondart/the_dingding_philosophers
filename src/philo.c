/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:51:14 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/11 20:33:51 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threader(t_philo *current_philo, t_main *main)
{
	t_thread	*data;

	data = smart_malloc(sizeof(t_thread));
	data->philo = current_philo;
	data->main = main;
	pthread_mutex_init(&data->philo->mutex, NULL);
	pthread_create(&current_philo->thread, NULL, function, (void *)data);
}

void	create_threads(t_main *main)
{
	t_philo	*current_philo;

	current_philo = main->philos;
	while (current_philo)
	{
		threader(current_philo, main);
		current_philo = current_philo->next;
	}
}

void	join_threads(t_philo *philos)
{
	while (philos)
	{
		pthread_join(philos->thread, NULL);
		philos = philos->next;
	}
}

int	main(int ac, char **av)
{
	t_main	*main;

	check_arguments(ac, av);
	main = smart_malloc(sizeof(t_main));
	main->eat_time = atoi(av[2]) * 1000;
	main->philos = init_thread(atoi(av[1]));
	assign_forks(main->philos, NULL);
	create_threads(main);
	join_threads(main->philos);
	free_program(main->philos);
	free(main);
}
