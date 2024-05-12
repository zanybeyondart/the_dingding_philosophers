/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 11:49:30 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 17:46:46 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_fork_pick(t_philo *philo, t_main *main)
{
	if (not_dead(main, philo))
	{
		pthread_mutex_lock(philo->my_mutex);
		if (not_dead(main, philo))
		{
			pthread_mutex_lock(&main->p_lock);
			printf("%d %d picked up a fork\n", main->current_time, philo->id);
			pthread_mutex_unlock(&main->p_lock);
			philo->my_fork[1] = 1;
		}
	}
}

void	next_fork_pick(t_philo *philo, t_main *main)
{
	if (not_dead(main, philo))
	{
		pthread_mutex_lock(philo->next_mutex);
		if (not_dead(main, philo))
		{
			pthread_mutex_lock(&main->p_lock);
			printf("%d %d picked up a fork\n", main->current_time, philo->id);
			pthread_mutex_unlock(&main->p_lock);
			philo->next_fork[1] = 1;
		}
	}
}

void	eating(t_philo *philo, int start_time, t_main *main)
{
	if (philo->id % 2 != 0 && not_dead(main, philo))
	{
		my_fork_pick(philo, main);
		next_fork_pick(philo, main);
	}
	else if (philo->id % 2 == 0 && not_dead(main, philo))
	{
		usleep(5000);
		next_fork_pick(philo, main);
		my_fork_pick(philo, main);
	}
	if (philo->my_fork[1] == 1 && philo->next_fork[1] == 1
		&& not_dead(main, philo))
	{
		pthread_mutex_lock(&main->p_lock);
		printf("%d %d is eating \n", main->current_time, philo->id);
		philo->eating = 1;
		philo->last_meal = main->current_time;
		pthread_mutex_unlock(&main->p_lock);
		usleep(main->eat_time * 1000);
	}
	philo->eating = 0;
	philo->next_fork[1] = 0;
	philo->my_fork[1] = 0;
	pthread_mutex_unlock(philo->my_mutex);
	pthread_mutex_unlock(philo->next_mutex);
}

void	thinking(t_philo *philo, int start_time, t_main *main)
{
	struct timeval	time;
	struct timeval	dum;

	if (not_dead(main, philo))
	{
		pthread_mutex_lock(&main->p_lock);
		printf("%d %d is thinking\n", main->current_time, philo->id);
		pthread_mutex_unlock(&main->p_lock);
	}
}

void	sleeping(t_philo *philo, int start_time, t_main *main)
{
	if (not_dead(main, philo))
	{
		pthread_mutex_lock(&main->p_lock);
		printf("%d %d is sleeping\n", main->current_time, philo->id);
		usleep(main->sleep_time * 1000);
		pthread_mutex_unlock(&main->p_lock);
	}
	not_dead(main, philo);
}

void	*function(void *ag)
{
	struct timeval	time;
	t_thread		*data;

	data = (t_thread *)ag;
	data->philo->last_meal = data->main->current_time;
	while (not_dead(data->main, data->philo))
	{
		gettimeofday(&time, NULL);
		eating(data->philo, time.tv_usec, data->main);
		sleeping(data->philo, time.tv_usec, data->main);
		thinking(data->philo, time.tv_usec, data->main);
	}
	free(data);
	return (NULL);
}
