/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:35:10 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:03 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	display_msg(char *str, t_philo *philo, unsigned int time)
{
	if (philo->utils->is_dead == 0)
	{
		printf(GRN "%7u" YEL " %4d" CYN " %s\n" CRESET, \
			time, philo->id + 1, str);
	}
}

void	print_status(char *str, t_philo *philo, unsigned int time)
{
	pthread_mutex_lock(&philo->utils->m_is_dead);
	pthread_mutex_lock(&philo->utils->m_print);
	display_msg(str, philo, time);
	pthread_mutex_unlock(&philo->utils->m_print);
	pthread_mutex_unlock(&philo->utils->m_is_dead);
}
