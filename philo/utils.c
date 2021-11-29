/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbronwyn <sbronwyn@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:35:02 by sbronwyn          #+#    #+#             */
/*   Updated: 2021/11/29 23:09:11 by sbronwyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_philosopher	*create_philosophers_data(t_args *args)
{
	t_philosopher	*philo_data;
	pthread_mutex_t	*forks;
	int				i;

	philo_data = malloc(args->n_philosophers * sizeof(*philo_data));
	forks = malloc(args->n_philosophers * sizeof(*forks));
	if (philo_data == 0 || forks == 0)
		return (0);
	i = -1;
	while (++i < args->n_philosophers)
	{
		philo_data[i].num = i + 1;
		gettimeofday(&philo_data[i].time, 0);
		philo_data[i].args = args;
		if (pthread_mutex_init(forks + i, 0) != 0)
			return (0);
		philo_data[i].left_fork = forks + i;
	}
	i = 0;
	while (++i < args->n_philosophers)
		philo_data[i - 1].right_fork = forks + i;
	philo_data[args->n_philosophers - 1].right_fork = forks;
	return (philo_data);
}

void	free_philo_data(t_philosopher *philo_data, t_args *args)
{
	int	i;

	i = -1;
	while (++i < args->n_philosophers)
		pthread_mutex_destroy(philo_data[i].left_fork);
	free(philo_data);
}
