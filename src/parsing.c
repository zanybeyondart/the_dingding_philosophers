/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zvakil <zvakil@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:02:17 by zvakil            #+#    #+#             */
/*   Updated: 2024/04/30 22:21:11 by zvakil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_arguments(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 4 || ac > 5)
		exit_mes("Invalid Arguments : 3 or 4 Arguments only, Check Subject");
	while (av[i] != NULL)
	{
		if (atoi(av[i++]) == 0)
			exit_mes("Invalid Arguments : Enter number greater than 0");
	}
}
