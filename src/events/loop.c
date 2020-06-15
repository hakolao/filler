/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:33:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				handle_loop(void *params)
{
	t_app		*app;
	static int	ret;

	app = (t_app*)params;
	ret = FALSE;
	ret = app->is_finished ? ret : update_map(app);
	if (ret == FALSE)
		app->is_finished = TRUE;
	else
		app->window->redraw = TRUE;
	if (app->window->redraw == TRUE)
		draw(app);
	return (0);
}
