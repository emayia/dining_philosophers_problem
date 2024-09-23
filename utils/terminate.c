/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:38:35 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 18:33:01 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	kill_philos(t_philo *philo)
{
	int	i;

	pthread_mutex_destroy(&philo->utils->m_is_dead);
	i = 0;
	while (i < philo->args->philo_count)
	{
		pthread_mutex_destroy(&philo[i].utils->fork[i]);
		pthread_mutex_destroy(&philo[i].m_eat_count);
		pthread_mutex_destroy(&philo[i].m_last_meal);
		i++;
	}
	pthread_mutex_destroy(&philo->utils->m_fed_philos);
}

void	free_philos(t_philo *philo)
{
	free(philo->utils->fork);
	free(philo);
}
