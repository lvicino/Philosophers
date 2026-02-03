/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvicino <lvicino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:38:56 by lvicino           #+#    #+#             */
/*   Updated: 2024/08/22 13:34:00 by lvicino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_atost(const char *nptr)
{
	size_t	i;
	size_t	nb;

	nb = 0;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = (nb * 10) + (nptr[i] - 48);
		i++;
	}
	return (nb);
}

int	check_nbr_len(char *s)
{
	int	ln;
	int	i;

	ln = 0;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		i++;
		ln++;
	}
	if (!ln && i && s[i - 1] == '0')
		ln++;
	return (ln);
}

void	ft_print(size_t time, size_t id, char *state, t_rules *rules)
{
	if (!ft_run(rules))
		return ;
	sem_wait(rules->print);
	printf("\x1b[1;32m%zu\x1b[0m \x1b[1;38;5;220m%zu\x1b[0m %s\n", \
	time, id, state);
	sem_post(rules->print);
}

size_t	get_time(size_t ms)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - ms);
}

void	destroy(t_rules *rules, t_philo *philo)
{
	free(rules->pid_tab);
	sem_close(rules->print);
	sem_close(rules->status);
	sem_close(rules->count);
	sem_close(rules->meal);
	sem_close(philo->fork);
}
