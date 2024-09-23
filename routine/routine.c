/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:41:25 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 18:31:36 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	philo_eat(t_philo *philo, int id, int next_id)
{
	pthread_mutex_lock(&philo->utils->fork[id]);
	print_status("has taken a fork", philo, get_time_in_ms() - philo->utils->start_time);

	pthread_mutex_lock(&philo->utils->fork[next_id]);
	print_status("has taken a fork", philo, get_time_in_ms() - philo->utils->start_time);

	print_status("is eating", philo, get_time_in_ms() - philo->utils->start_time);

	pthread_mutex_lock(&philo->m_eat_count);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->m_eat_count);

	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->m_last_meal);

	ft_usleep(philo->args->time_to_eat, philo);
}

void	philo_sleep(t_philo *philo, int id, int next_id)
{
	pthread_mutex_unlock(&philo->utils->fork[id]);
	pthread_mutex_unlock(&philo->utils->fork[next_id]);
	print_status("is sleeping", philo, get_time_in_ms() - philo->utils->start_time);
	ft_usleep(philo->args->time_to_sleep, philo);
}

void	philo_think(t_philo *philo)
{
	print_status("is thinking", philo, \
		(get_time_in_ms() - philo->utils->start_time));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	int		id;
	int		next_id;
	int		is_dead;

	philo = (t_philo *)arg;
	id = philo->id;
	next_id = (id + 1) % philo->args->philo_count;
	pthread_mutex_lock(&philo->m_last_meal);
	philo->last_meal = get_time_in_ms();
	pthread_mutex_unlock(&philo->m_last_meal);
	if (id % 2 == 0)
		usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&philo->utils->m_is_dead);
		is_dead = philo->utils->is_dead;
		pthread_mutex_unlock(&philo->utils->m_is_dead);
		if (is_dead)
			break;
		philo_eat(philo, id, next_id);
		check_philo_must_eat(philo);
		philo_sleep(philo, id, next_id);
		philo_think(philo);
	}
	pthread_mutex_unlock(&philo->utils->fork[id]);
	pthread_mutex_unlock(&philo->utils->fork[next_id]);
	return (NULL);
}
