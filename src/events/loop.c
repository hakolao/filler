/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 14:43:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Handle drawing of screen in app loop
*/

int				handle_loop(void *params)
{
	t_app		*app;

	app = (t_app*)params;
	if (app->window->redraw == TRUE)
		draw(app);
	if (!read_filler_input(app) &&
		log_perr("Something went wrong in input reading"))
		handle_exit_event(app);
	ft_dprintf(2, "Hello\n");

	return (0);
}
