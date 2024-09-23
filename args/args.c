/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:33:55 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 18:27:51 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	fill_args(int ac, char **av, t_args *args)
{
	args->philo_count = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->eat_goal = 0;
	if (ac == 6)
		args->eat_goal = ft_atoi(av[5]);
}

int	check_args(int ac, char **av, t_args *args)
{
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd(INVALID_ARGS, 2);
		return (0);
	}
	fill_args(ac, av, args);
	if (args->philo_count < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1
		|| (ac == 6 && args->eat_goal < 1))
	{
		ft_putstr_fd(INVALID_ARGS, 2);
		return (0);
	}
	return (1);
}
