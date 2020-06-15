/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:18 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:53:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				handle_key_press(int key, void *param)
{
	t_app		*app;

	app = (t_app*)param;
	if (key == KEY_ESC)
		handle_exit_event(app);
	return (0);
}

int				handle_key_release(int key, void *param)
{
	t_app		*app;

	app = (t_app*)param;
	(void)key;
	return (0);
}
