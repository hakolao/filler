/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/17 15:41:17 by ohakola          ###   ########.fr       */
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
	ret = FALSE;
	ret = app->is_finished ? ret : update_map(app);
	if (ret == FALSE)
		app->is_finished = TRUE;
	draw(app);
	return (0);
}
