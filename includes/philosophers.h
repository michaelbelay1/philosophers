/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:07:40 by mhaile            #+#    #+#             */
/*   Updated: 2024/02/09 22:32:28 by mhaile           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

int	g;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	long			last_eat;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_eating;
	int				num_of_meals;
	pthread_mutex_t	mutex_test;
	pthread_t		thread_id;
	struct s_data	*data;
}				t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex;
	t_philo			*philo;
}				t_data;

//libft
long long int	ft_atoi_l(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			*ft_calloc(size_t count, size_t size);
void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);

//philo
int				arg_num(int ac);
int				args_all_num(char **av);
int				init_struct(t_data *data, char **av);
void			create_threads(t_data *data);
int				get_time(void);
int				philo_takes_forks(t_philo *philo);
int				philo_is_dead(t_philo *philo);
void			*philo_routine(void *arguments);
void			ft_sleep(int time, t_philo *philo);

#endif
