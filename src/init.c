/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:56:15 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/12 18:34:52 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	check_args(char **ar)
{
	int	i;
	int	j;

	i = 0;
	while (ar[++i])
	{
		if (check_nbr_len(ar[i]) > 9 || check_nbr_len(ar[i]) < 1)
			return (0);
		j = -1;
		while (ar[i][++j])
		{
			if ((!j && (ar[i][j] == '-' || (ar[i][j] != '+' && \
			!(ar[i][j] >= '0' && ar[i][j] <= '9')))) || \
			(j && !(ar[i][j] >= '0' && ar[i][j] <= '9')))
				return (0);
		}
	}
	return (1);
}

bool	init_rules(t_rules *rules, int ac, char **ar)
{
	rules->n_philo = ft_atost(ar[1]);
	rules->tt_die = ft_atost(ar[2]);
	rules->tt_eat = ft_atost(ar[3]);
	rules->tt_sleep = ft_atost(ar[4]);
	if (ac == 6)
		rules->min_meal = ft_atost(ar[5]);
	else
			rules->min_meal = 0;
	rules->must_eat = 0 | (ac == 6);
	rules->run = 0;
	if (!rules->n_philo || rules->n_philo > 200)
		return (0);
	if (pthread_mutex_init(&rules->print, NULL))
		return (0);
	else if (pthread_mutex_init(&rules->status, NULL))
		return (pthread_mutex_destroy(&rules->print), 0);
	else if (pthread_mutex_init(&rules->count, NULL))
		return (pthread_mutex_destroy(&rules->print), \
		pthread_mutex_destroy(&rules->status), 0);
	else if (pthread_mutex_init(&rules->meal, NULL))
		return (pthread_mutex_destroy(&rules->print), \
		pthread_mutex_destroy(&rules->status), \
		pthread_mutex_destroy(&rules->count), 0);
	return (1);
}

void	get_second_fork(t_rules *rules, t_philo **philo)
{
	int	i;

	i = -1;
	while (rules->n_philo != 1 && ++i < (int)rules->n_philo)
	{
		if (i == (int)rules->n_philo - 1)
			(*philo)[i].righ_fork = &(*philo)[0].fork;
		else
			(*philo)[i].righ_fork = &(*philo)[i +1].fork;
	}
}

bool	init_philo(t_rules *rules, t_philo **philo)
{
	int	i;

	*philo = malloc(sizeof(t_philo) * rules->n_philo);
	if (!philo)
		return (destroy(rules, philo), 0);
	i = -1;
	while (++i < (int)rules->n_philo)
	{
		(*philo)[i].id = i;
		(*philo)[i].n_meal = 0;
		(*philo)[i].last_meal = 0;
		if (pthread_mutex_init(&(*philo)[i].fork, NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*philo)[i].fork);
			pthread_mutex_destroy(&rules->print);
			pthread_mutex_destroy(&rules->status);
			pthread_mutex_destroy(&rules->count);
			pthread_mutex_destroy(&rules->meal);
			return (free(*philo), 0);
		}
		(*philo)[i].rules = rules;
	}
	get_second_fork(rules, philo);
	return (1);
}

bool	init_data(t_rules *rules, t_philo **philo, int ac, char **ar)
{
	if (!check_args(ar) || !init_rules(rules, ac, ar) || \
	!init_philo(rules, philo))
		return (0);
	return (1);
}
