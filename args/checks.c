/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:37:27 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:03 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	check_philo_must_eat(t_philo *philo)
{
	if (philo->args->eat_goal > 0 && philo->eat_count == philo->args->eat_goal)
	{
		pthread_mutex_lock(&philo->utils->m_fed_philos);
		if (++philo->utils->fed_philos == philo->args->philo_count)
		{
			pthread_mutex_lock(&philo->utils->m_is_dead);
			philo->utils->is_dead = 1;
			pthread_mutex_unlock(&philo->utils->m_is_dead);
		}
		pthread_mutex_unlock(&philo->utils->m_fed_philos);
	}
}

void	check_philo(t_philo *philo)
{
	if ((get_time_in_ms() - get_protected(&philo->last_meal, \
			&philo->m_last_meal)) > philo->args->time_to_die)
	{
		pthread_mutex_lock(&philo->utils->m_print);
		pthread_mutex_lock(&philo->utils->m_is_dead);
		display_msg(RED "died", philo, \
			(get_time_in_ms() - philo->utils->start_time));
		philo->utils->is_dead = 1;
		pthread_mutex_unlock(&philo->utils->m_print);
		pthread_mutex_unlock(&philo->utils->m_is_dead);
	}
}

void	check_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (!get_protected(&philo->utils->is_dead, &philo->utils->m_is_dead))
	{
		usleep(500);
		i = 0;
		while (!get_protected(&philo->utils->is_dead, &philo->utils->m_is_dead)
			&& i < philo->args->philo_count)
		{
			check_philo(&philo[i]);
			i++;
		}
	}
}
