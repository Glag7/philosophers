/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:21:44 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/15 18:16:29 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "thread/philo.h"

void	*routine(void *philo_)
{
	t_philo	*philo = philo_;

	printp(23000, philo->num, FORK);
	printp(23000, philo->num, EAT);
	printp(23000, philo->num, SLEEP);
	printp(23000, philo->num, THINK);
	printp(23000, philo->num, DIE);
	return (philo);
}
