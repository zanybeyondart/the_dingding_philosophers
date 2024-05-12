/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:51:14 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 17:37:54 by zvakil           ###   ########.fr       */
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
		pthread_mutex_lock(&main->p_lock);
		main->current_time = (time.tv_sec * 1000)
			+ (time.tv_usec / 1000) - start;
		pthread_mutex_unlock(&main->p_lock);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_main	*main;

	check_arguments(ac, av);
	main = smart_malloc(sizeof(t_main));
	main->philos = init_thread(atoi(av[1]));
	main->eat_time = atoi(av[3]);
	main->current_time = 0;
	main->sleep_time = atoi(av[4]);
	main->dead_time = atoi(av[2]);
	main->philo_dead = 0;
	pthread_mutex_init(&main->p_lock, NULL);
	assign_forks(main->philos, NULL, NULL);
	pthread_create(&main->thread, NULL, monitor, main);
	create_threads(main);
	join_threads(main->philos);
	pthread_join(main->thread, NULL);
	free_program(main->philos);
	free(main);
}
