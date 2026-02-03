/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:26:35 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/08 14:06:12 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_run(t_rules *rules)
{
	pthread_mutex_lock(&rules->status);
	rules->run = 0;
	pthread_mutex_unlock(&rules->status);
}

void	print_death(t_rules *rules, size_t i)
{
	end_run(rules);
	pthread_mutex_lock(&rules->print);
	printf(DEATH, get_time(rules->start), i + 1);
	pthread_mutex_unlock(&rules->print);
}

size_t	check_meals(t_philo *philo, t_rules *rules)
{
	size_t	n;

	pthread_mutex_lock(&rules->count);
	n = 0 | (philo->n_meal >= rules->min_meal);
	pthread_mutex_unlock(&rules->count);
	return (n);
}

void	check(t_philo *philo, t_rules *rules)
{
	size_t	i;
	size_t	m;

	i = 0;
	m = 0;
	while (i < rules->n_philo)
	{
		if (!ft_run(rules))
			return ;
		pthread_mutex_lock(&rules->meal);
		if (get_time(philo[i].last_meal + rules->start) >= (rules->tt_die))
			print_death(rules, i);
		pthread_mutex_unlock(&rules->meal);
		if (rules->must_eat)
			m += check_meals(&philo[i], rules);
		i++;
		if (rules->must_eat && i == rules->n_philo && m == i)
			end_run(rules);
		else if (rules->must_eat && i == rules->n_philo)
			m = 0;
		if (i == rules->n_philo)
			usleep(1000);
		i %= rules->n_philo;
	}
}
