/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:39:21 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 18:29:27 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

t_utils	init_utils(t_args *args)
{
	t_utils	utils;

	utils.is_dead = 0;
	utils.start_time = get_time_in_ms();
	utils.fed_philos = 0;
	pthread_mutex_init(&utils.m_print, NULL);
	pthread_mutex_init(&utils.m_is_dead, NULL);
	pthread_mutex_init(&utils.m_fed_philos, NULL);
	utils.fork = malloc(sizeof(pthread_mutex_t) * args->philo_count);
	return (utils);
}

t_philo	*init_philo(t_args *args, t_utils *utils)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * args->philo_count);
	i = 0;
	while (i < args->philo_count)
	{
		philo[i].args = args;
		philo[i].utils = utils;
		philo[i].eat_count = 0;
		pthread_mutex_init(&philo[i].utils->fork[i], NULL);
		pthread_mutex_init(&philo[i].m_eat_count, NULL);
		pthread_mutex_init(&philo[i].m_last_meal, NULL);
		i++;
	}
	return (philo);
}

void	init_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->args->philo_count)
	{
		philo[i].id = i;
		pthread_create(&philo[i].th, NULL, &philo_routine, &philo[i]);
		i++;
	}
	check_death(philo);
	i = 0;
	while (i < philo->args->philo_count)
	{
		pthread_join(philo[i].th, NULL);
		i++;
	}
}
