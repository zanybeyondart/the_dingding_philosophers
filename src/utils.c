/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:52:56 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/12 12:35:09 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_program(t_philo *philo)
{
	if (philo->next != NULL)
		free_program(philo->next);
	free(philo->my_fork);
	free(philo->my_mutex);
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
	return (sec * 1000 + usec / 1000);
}

void	add_to_list(t_philo *philo, int index)
{
	t_philo		*temp;

	temp = smart_malloc(sizeof(t_philo));
	temp->my_fork = smart_malloc(sizeof(int));
	temp->my_mutex = smart_malloc(sizeof(pthread_mutex_t));
	temp->next_mutex = NULL;
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

	i = 1;
	philo = smart_malloc(sizeof(t_philo));
	philo->my_fork = smart_malloc(sizeof(int));
	philo->my_mutex = smart_malloc(sizeof(pthread_mutex_t));
	philo->next_mutex = NULL;
	philo->my_fork[0] = 1;
	philo->next_fork = NULL;
	philo->next = NULL;
	philo->id = i++;
	while (i <= philos)
	{
		add_to_list(philo, i);
		i++;
	}
	return (philo);
}
