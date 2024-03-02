/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaile <mhaile@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 21:07:40 by mhaile            #+#    #+#             */
/*   Updated: 2024/03/02 12:59:31 by mhaile           ###   ########.fr       */
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

typedef struct s_philo
{
	int						id;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	long					last_eat;
	int						num_of_philo;
	unsigned long int		time_to_die;
	unsigned long int		time_to_eat;
	unsigned long int		time_to_sleep;
	int						*forks_taken_left;
	int						*forks_taken_right;
	pthread_t				thread_id;
	struct s_data			*data;
}				t_philo;

typedef struct s_data
{
	int						num_of_philo;
	unsigned long int		time_to_die;
	unsigned long int		time_to_eat;
	unsigned long int		time_to_sleep;
	int						must_eat_count;
	int						num_of_meals;
	int						philo_dead;
	unsigned long int		start_time;
	int						*forks_taken;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mutex_dead;
	pthread_mutex_t			mutex_print;
	pthread_mutex_t			mutex_meals;
	t_philo					*philo;
}				t_data;

//************************ Libft ************************//
long long int		ft_atoi_l(const char *str);
void				ft_putstr_fd(char *s, int fd);
int					ft_isdigit(int c);

//************************ Parsing ************************//
int					args_all_num(char **av);
int					arg_num(int ac);

//************************ Philosophers ************************//
int					init_struct(t_data *data, char **av);
void				create_threads(t_data *data);
int					begin_monitoring(void *arg);
int					philo_takes_forks(t_philo *philo);
void				philo_is_eating(t_philo *philo);
void				philo_is_sleeping(t_philo *philo);
void				philo_is_thinking(t_philo *philo);
void				print_message(char *str, t_philo *philo);
void				*philo_routine(void *arguments);
void				join_threads(t_data *data);
unsigned long int	get_time(void);
int					philo_is_dead(t_philo *philo);
void				is_max_eat(t_philo *philo);
void				ft_sleep(unsigned long int time, t_philo *philo);
int					check_last_meal(t_philo *philo);
void				one_philo_case(t_philo *philo);
int					check_if_one_is_dead(t_data *data);
void				clean_up(t_data *data);

#endif
