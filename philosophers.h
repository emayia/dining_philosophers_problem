/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayyildi <mayyildi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:57:48 by mayyildi          #+#    #+#             */
/*   Updated: 2023/03/01 20:41:03 by mayyildi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define GRN "\e[0;32m"
# define YEL "\e[0;33m"
# define BLU "\e[0;34m"
# define MAG "\e[0;35m"
# define CYN "\e[0;36m"
# define WHT "\e[0;37m"
# define CRESET "\e[0m"

# define INVALID_ARGS	"\e[0;31mInvalid arguments\e[0m\n"

/*	-----	Prompt args	-----	*/
typedef struct s_args
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_goal;
}			t_args;

typedef struct s_utils
{
	pthread_mutex_t	m_print;
	long			is_dead;
	pthread_mutex_t	m_is_dead;
	pthread_mutex_t	*fork;
	unsigned int	start_time;
	int				fed_philos;
	pthread_mutex_t	m_fed_philos;
}				t_utils;

/*	-----	Philosophers	-----	*/
typedef struct s_philo
{
	int				id;
	pthread_t		th;
	t_args			*args;
	t_utils			*utils;
	int				eat_count;
	pthread_mutex_t	m_eat_count;
	long			last_meal;
	pthread_mutex_t	m_last_meal;
}				t_philo;

/*	-----	Minilib	-----	*/
int		ft_isdigit(int c);
int		ft_isspace(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(char *str);

/*	-----	Args	-----	*/
/*	args.c	*/
int		check_args(int ac, char **av, t_args *args);
void	fill_args(int ac, char **av, t_args *args);
/*	checks.c	*/
void	check_philo_must_eat(t_philo *philo);
void	check_philo(t_philo *philo);
void	check_death(t_philo *philo);
/*	init.c	*/
void	init_threads(t_philo *philo);
t_philo	*init_philo(t_args *args, t_utils *utils);
t_utils	init_utils(t_args *args);

/*	-----	Routine	-----	*/
/*	routine.c	*/
void	*philo_routine(void *arg);

/*	-----	Utils	-----	*/
/*	print.c	*/
void	print_status(char *str, t_philo *philo, unsigned int time);
void	display_msg(char *str, t_philo *philo, unsigned int time);
/*	terminate.c	*/
void	free_philos(t_philo *philo);
void	kill_philos(t_philo *philo);
/*	time.c	*/
void	ft_usleep(long time, t_philo *philo);
time_t	get_time_in_ms(void);

/*	main.c	*/
long	get_protected(long *var, pthread_mutex_t *mtx);

#endif
