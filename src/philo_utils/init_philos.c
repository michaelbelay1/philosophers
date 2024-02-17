/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:15:10 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/17 22:30:52 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

unsigned long int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(unsigned long int time, t_philo *philo)
{
	unsigned long int	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(philo->time_to_sleep);
}

int	init_philos(t_data *data)
{
	int	i;

	i = -1;
	data->philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!data->philo)
		return (1);
	while (++i < data->num_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].left_fork = &data->forks[i];
		if (data->philo[i].id == data->num_of_philo)
			data->philo[i].right_fork = &data->forks[0];
		else
			data->philo[i].right_fork = &data->forks[i + 1];
		data->philo[i].last_eat = 0;
		data->philo[i].time_to_die = data->time_to_die;
		data->philo[i].time_to_eat = data->time_to_eat;
		data->philo[i].time_to_sleep = data->time_to_sleep;
		data->philo[i].data = data;
		data->philo[i].is_eating = 0;
		// data->philo[i].num_of_meals = 0;
		data->philo[i].thread_id = 0;
		data->philo[i].num_of_philo = data->num_of_philo;
	}
	return (0);
}

int	mutex(t_data *data)
{
	int	i;

	i = -1;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (1);
	while (++i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->mutex, NULL);
	return (0);
}

int	init_struct(t_data *data, char **av)
{
	data->num_of_philo = ft_atoi_l(av[1]);
	if (data->num_of_philo < 0 || data->num_of_philo > INT_MAX)
		return (1);
	data->time_to_die = ft_atoi_l(av[2]);
	if (data->time_to_die < 0 || data->time_to_die > INT_MAX)
		return (1);
	data->time_to_eat = ft_atoi_l(av[3]);
	if (data->time_to_eat < 0 || data->time_to_eat > INT_MAX)
		return (1);
	data->time_to_sleep = ft_atoi_l(av[4]);
	if (data->time_to_sleep < 0 || data->time_to_sleep > INT_MAX)
		return (1);
	if (av[5])
	{
		data->must_eat_count = ft_atoi_l(av[5]);
		if (data->must_eat_count < 0 || data->must_eat_count > INT_MAX)
			return (1);
	}
	else
		data->must_eat_count = -1;
	data->philo_dead = 0;
	data->start_time = 0;
	data->num_of_meals = 0;
	if (mutex(data) || init_philos(data))
		return (1);
	return (0);
}
