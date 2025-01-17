/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:52:56 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/11 20:43:49 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_program(t_philo *philo)
{
	if (philo->next != NULL)
		free_program(philo->next);
	free(philo->my_fork);
	free(philo);
}

void	exit_mes(char *mes)
{
	printf("%s\n", mes);
	exit (0);
}

int	magic_time(struct timeval time_main)
{
	struct timeval	time;
	long			sec;
	int				usec;

	gettimeofday(&time, NULL);
	sec = time.tv_sec - time_main.tv_sec;
	usec = time.tv_usec - time_main.tv_usec;
	return (sec * 1000000 + usec);
}

void	eating(t_philo *philo, int start_time, t_main *main)
{
	struct timeval	time;
	struct timeval	dum;

	pthread_mutex_lock(&philo->mutex);
	printf("\n%d Philo, takes %d and %d\n", philo->id, philo->my_fork[0], philo->next_fork[0]);
	gettimeofday(&time, NULL);
	while (magic_time(time) < main->eat_time)
	{
		gettimeofday(&dum, NULL);
	}
	pthread_mutex_unlock(&philo->mutex);
}

void	*function(void *ag)
{
	struct timeval	time;
	t_thread		*data;

	data = (t_thread *)ag;
	gettimeofday(&time, NULL);
	eating(data->philo, time.tv_usec, data->main);
	free(data);
	return (NULL);
}

void	add_to_list(t_philo *philo, int index)
{
	t_philo		*temp;

	temp = smart_malloc(sizeof(t_philo));
	temp->my_fork = smart_malloc(sizeof(int));
	temp->my_fork[0] = index;
	temp->next_fork = NULL;
	temp->next = NULL;
	temp->id = index;
	while (philo->next != NULL)
		philo = philo->next;
	philo->next = temp;
	return ;
}


t_philo	*init_thread(int philos)
{
	t_philo			*philo;
	int				i;

	i = 0;
	philo = smart_malloc(sizeof(t_philo));
	philo->my_fork = smart_malloc(sizeof(int));
	philo->my_fork[0] = 0;
	philo->next_fork = NULL;
	philo->next = NULL;
	philo->id = i++;
	while (i < philos)
	{
		add_to_list(philo, i);
		i++;
	}
	return (philo);
}
