/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/02 15:48:23 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
** Main visual loop, update map reads stdin data from filler_vm
** Calls draw every loop
*/

int				handle_loop(void *params)
{
	t_app		*app;
	static int	ret;

	app = (t_app*)params;
	ret = false;
	ret = app->is_finished ? ret : update_map(app);
	if (ret == false)
		app->is_finished = true;
	draw(app);
	return (0);
}
