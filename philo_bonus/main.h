/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:03:41 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/06 18:00:59 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <signal.h>
# include <sys/time.h>
# include <semaphore.h>

# define EXIT_STATUS_EATEN 10
# define EXIT_STATUS_DIED 11

typedef struct s_args
{
	int	n_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	n_times_to_eat;
}	t_args;

typedef struct s_philosopher
{
	int				id;
	pid_t			pid;
	struct timeval	start_time;
	struct timeval	last_meal_time;
	t_args			*args;
	sem_t			*forks;
	sem_t			*display;
}	t_philosopher;

void			parse_args(t_args *args, int size, char **arr);

int				create_death_mutex(t_philosopher *philo_data, t_args *args);
t_philosopher	*create_philosophers_data(t_args *args);
void			free_philo_data(t_philosopher *philo_data, t_args *args);
int				is_died(t_philosopher *data);

void			print_status(t_philosopher *data, char *str, int save_time);
void			take_forks(t_philosopher *data);
void			release_forks(t_philosopher *data);

#endif