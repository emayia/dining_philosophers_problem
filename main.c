/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:57:51 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 21:40:48 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_protected(long *var, pthread_mutex_t *mtx)
{
	long	tmp;

	pthread_mutex_lock(mtx);
	tmp = *var;
	pthread_mutex_unlock(mtx);
	return (tmp);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_utils	utils;
	t_philo	*philo;

	if (!check_args(ac, av, &args))
		return (-1);
	utils = init_utils(&args);
	philo = init_philo(&args, &utils);
	init_threads(philo);
	
	kill_philos(philo);
	free_philos(philo);
	return (0);
}
