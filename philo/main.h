/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:03:41 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/12/02 06:00:20 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

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
	struct timeval	start_time;
	struct timeval	last_meal_time;
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philosopher;

void			parse_args(t_args *args, int size, char **arr);

t_philosopher	*create_philosophers_data(t_args *args);
void			free_philo_data(t_philosopher *philo_data, t_args *args);

void			print_status(t_philosopher *data, char *str, int save_time);
void			take_forks(t_philosopher *data);
void			release_forks(t_philosopher *data);

#endif