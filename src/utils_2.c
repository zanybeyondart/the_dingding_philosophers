/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 15:11:54 by zvakil            #+#    #+#             */
/*   Updated: 2024/05/11 18:15:13 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*smart_malloc(size_t size)
{
	void	*temp;

	temp = NULL;
	temp = malloc(size);
	if (temp == NULL)
		exit_mes("Program Failed : Memory Allocatin");
	return (temp);
}

void	assign_forks(t_philo *philo, int *first_fork)
{
	static int	i;

	if (philo->next && i == 0)
	{
		i++;
		philo->next_fork = philo->next->my_fork;
		assign_forks(philo->next, philo->my_fork);
	}
	else if (philo->next)
	{
		philo->next_fork = philo->next->my_fork;
		assign_forks(philo->next, first_fork);
	}
	else if (philo->id > 0)
		philo->next_fork = first_fork;
}