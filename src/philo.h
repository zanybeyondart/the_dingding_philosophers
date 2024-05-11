/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 11:53:25 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/11 20:33:39 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					p_fork;
	int					*my_fork;
	int					*next_fork;
	long				start_time;
	pthread_mutex_t		mutex;
	struct s_philo		*next;
}	t_philo;

typedef struct s_main
{
	t_philo			*philos;
	int				eat_time;
}	t_main;

typedef struct s_thread
{
	t_philo	*philo;
	t_main	*main;
	struct s_thread		*next;
}	t_thread;

void		check_arguments(int ac, char **av);
void		exit_mes(char *mes);
void		check_if_invalid(char *av);
void		*smart_malloc(size_t size);
void		free_program(t_philo *philo);
void		thread_create(t_philo *philos);
void		*function(void *ag);
void		add_to_list(t_philo *philo, int index);
void		assign_forks(t_philo *philo, int *first_fork);
t_philo		*init_thread(int philos);

#endif