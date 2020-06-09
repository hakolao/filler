/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/09 13:14:11 by ohakola          ###   ########.fr       */
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
	return (0);
}
