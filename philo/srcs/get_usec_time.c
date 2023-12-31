/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_usec_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamiyaza <mamiyaza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 22:54:47 by mamiyaza          #+#    #+#             */
/*   Updated: 2023/12/19 00:46:00 by mamiyaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

time_t	get_usec_time(t_data *d)
{
	struct timeval	s_timeval;
	time_t			usec_time;

	if (gettimeofday(&s_timeval, NULL))
	{
		handle_errors(d, GETTIMEOFDAY_ERROR, __func__, __LINE__);
		return (0);
	}
	usec_time = s_timeval.tv_sec * 1000000 + s_timeval.tv_usec;
	return (usec_time);
}

t_funcstat	wait_precise_time(t_data *d, time_t target_time)
{
	time_t	cur_time;

	cur_time = 0;
	while (1)
	{
		cur_time = get_usec_time(d);
		if (d->errstat)
			return (1);
		if (cur_time >= target_time)
		{
			__DEBUG__(d);
			return (0);
		}
		if (usleep((target_time - cur_time) / 2))
		{
			handle_errors(d, USLEEP_ERROR, __func__, __LINE__);
			return (1);
		}
	}
	return (0);
}
