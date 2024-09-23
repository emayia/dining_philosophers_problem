/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:36:13 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 21:36:34 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time, t_philo *philo)
{
	long	start;

	start = get_time_in_ms();
	while (start + time > get_time_in_ms())
	{
		pthread_mutex_lock(&philo->utils->m_is_dead);
		if (philo->utils->is_dead == 1)
		{
			pthread_mutex_unlock(&philo->utils->m_is_dead);
			break ;
		}
		pthread_mutex_unlock(&philo->utils->m_is_dead);
		usleep(100);
	}
}
