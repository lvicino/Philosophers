/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 19:26:35 by lvicino           #+#    #+#             */
/*   Updated: 2024/07/22 11:58:24 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	ft_run(t_rules *rules)
{
	bool	r;

	sem_wait(rules->status);
	r = rules->run;
	sem_post(rules->status);
	return (r);
}

void	end_run(t_rules *rules)
{
	sem_wait(rules->status);
	rules->run = 0;
	sem_post(rules->status);
}

void	check_meals(t_philo *philo, t_rules *rules)
{
	sem_wait(rules->count);
	if (rules->min_meal == philo->n_meal)
	{
		rules->r = 1;
		end_run(rules);
	}
	sem_post(rules->count);
}

void	check(t_philo *philo, t_rules *rules)
{
	while (ft_run(rules))
	{
		if (!ft_run(rules))
			return ;
		sem_wait(rules->print);
		sem_wait(rules->meal);
		if (ft_run(rules) && \
		get_time(philo->last_meal + rules->start) >= (rules->tt_die))
		{
			sem_post(rules->meal);
			end_run(rules);
			printf(DEATH, get_time(rules->start), philo->id);
			rules->r = 0;
		}
		else
		{
			sem_post(rules->meal);
			sem_post(rules->print);
		}
		if (rules->must_eat && ft_run(rules))
			check_meals(philo, rules);
		usleep(1000);
	}
}
