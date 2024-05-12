/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:49:30 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 12:20:13 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, int start_time, t_main *main)
{
	struct timeval	time;
	struct timeval	dum;

	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(philo->my_mutex);
		printf("%d %d picked up a fork\n", main->current_time, philo->id);
		pthread_mutex_lock(philo->next_mutex);
		printf("%d %d picked up a fork\n", main->current_time, philo->id);
		printf("%d %d is eating \n", main->current_time, philo->id);
	}
	else if (philo->id % 2 == 0)
	{
		usleep(100);
		pthread_mutex_lock(philo->next_mutex);
		printf("%d %d picked up a fork\n", main->current_time, philo->id);
		pthread_mutex_lock(philo->my_mutex);
		printf("%d %d picked up a fork\n", main->current_time, philo->id);
		printf("%d %d is eating \n", main->current_time, philo->id);
	}
	gettimeofday(&time, NULL);
	while (magic_time(time) < main->eat_time && not_dead(main, philo))
		gettimeofday(&dum, NULL);
	philo->last_meal = main->current_time;
	pthread_mutex_unlock(philo->my_mutex);
	pthread_mutex_unlock(philo->next_mutex);
}

void	thinking(t_philo *philo, int start_time, t_main *main)
{
	struct timeval	time;
	struct timeval	dum;

	printf("%d %d is thinking\n", main->current_time, philo->id);
	gettimeofday(&time, NULL);
	while (magic_time(time) < main->think_time && not_dead(main, philo))
		gettimeofday(&dum, NULL);
}

void	sleeping(t_philo *philo, int start_time, t_main *main)
{
	struct timeval	time;
	struct timeval	dum;

	printf("%d %d is sleeping\n", main->current_time, philo->id);
	gettimeofday(&time, NULL);
	while (magic_time(time) < main->sleep_time && not_dead(main, philo))
		gettimeofday(&dum, NULL);
}

void	*function(void *ag)
{
	struct timeval	time;
	t_thread		*data;

	data = (t_thread *)ag;
	data->philo->last_meal = 0;
	while (data->main->philo_dead != 1)
	{
		gettimeofday(&time, NULL);
		eating(data->philo, time.tv_usec, data->main);
		thinking(data->philo, time.tv_usec, data->main);
		sleeping(data->philo, time.tv_usec, data->main);
	}
	free(data);
	return (NULL);
}
