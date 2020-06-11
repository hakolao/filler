/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/11 17:15:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				handle_loop(void *params)
{
	t_app		*app;

	app = (t_app*)params;
	if (!update_map(app) &&
		log_perr("Something went wrong in input reading"))
		handle_exit_event(app);
	if (app->window->redraw == TRUE)
		draw(app);
	return (0);
}
