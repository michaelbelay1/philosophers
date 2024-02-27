/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:12:09 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/27 22:03:12 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = get_time();
	while (i < data->num_of_philo)
	{
		pthread_create(&data->philo[i].thread_id,
			NULL, &philo_routine, (void *)&data->philo[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	int		philo_dead;

	if (arg_num(ac) || args_all_num(av))
		return (1);
	if (init_struct(&data, av))
	{
		ft_putstr_fd("Invalid argument\n", 2);
		return (1);
	}
	create_threads(&data);
	philo_dead = begin_monitoring(&data);
	if (philo_dead)
	{
		pthread_mutex_lock(&data.mutex_dead);
		printf("\033[0;31m%lu %d died \033[0m\n", get_time()
			- data.philo->data->start_time, philo_dead);
		pthread_mutex_unlock(&data.mutex_dead);
	}
	join_threads(&data);
	free(data.forks_taken);
	free(data.forks);
	free(data.philo);
}
