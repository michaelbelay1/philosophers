/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:12:09 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/14 22:35:55 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (arg_num(ac) || args_all_num(av))
		return (1);
	if (init_struct(&data, av))
	{
		printf("Invalid argument\n");
		return (1);
	}
	create_threads(&data);
	begin_monitoring(&data);
	join_threads(&data);
	free(data.philo);
	free(data.forks);
}
