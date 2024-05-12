/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:51:14 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 12:35:33 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	threader(t_philo *current_philo, t_main *main)
{
	t_thread	*data;

	data = smart_malloc(sizeof(t_thread));
	data->philo = current_philo;
	data->main = main;
	pthread_mutex_init(data->philo->my_mutex, NULL);
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

void	*monitor(void *ag)
{
	struct timeval	time;
	int				start;
	t_main			*main;

	main = (t_main *)ag;
	gettimeofday(&time, NULL);
	start = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	while (main->philo_dead != 1)
	{
		gettimeofday(&time, NULL);
		main->current_time = (time.tv_sec * 1000)
			+ (time.tv_usec / 1000) - start;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	*main;

	check_arguments(ac, av);
	main = smart_malloc(sizeof(t_main));
	main->eat_time = atoi(av[3]);
	main->philos = init_thread(atoi(av[1]));
	main->sleep_time = atoi(av[4]);
	main->dead_time = atoi(av[2]);
	main->think_time = main->dead_time - (main->eat_time + main->sleep_time) - 1000;
	main->philo_dead = 0;
	assign_forks(main->philos, NULL, NULL);
	pthread_create(&main->thread, NULL, monitor, main);
	create_threads(main);
	join_threads(main->philos);
	pthread_join(main->thread, NULL);
	free_program(main->philos);
	free(main);
}
