/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaguyon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 19:40:00 by glaguyon          #+#    #+#             */
/*   Updated: 2024/03/26 13:53:29 by glaguyon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dec_sems(t_pdata *pdata, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		sem_wait(pdata->run_n[i]);
		i++;
	}
}

void	dec_sems_except(t_pdata *pdata, int n)
{
	int	i;

	i = 0;
	while (i < 2 * (int)pdata->data.nphilo)
	{
		sem_post(pdata->run_n[n]);
		i++;
	}
	i = 0;
	while (i < pdata->data.nphilo)
	{
		if (i != n)
			sem_wait(pdata->run_n[i]);
		i++;
	}
}

void	clean_exit(t_pdata *pdata, int n)
{
	free_philo(pdata);
	exit(n);
}
