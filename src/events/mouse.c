/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:22:48 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 22:25:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				handle_mouse_button_press(int button, int x, int y, void *param)
{
	t_app	*app;

	(void)x;
	(void)y;
	(void)button;
	app = (t_app*)param;
	return (1);
}

int				handle_mouse_button_release(int button, int x, int y,
				void *param)
{
	t_app	*app;

	(void)x;
	(void)y;
	(void)button;
	app = (t_app*)param;
	return (1);
}

int				handle_mouse_move(int x, int y, void *param)
{
	t_app	*app;

	(void)x;
	(void)y;
	app = (t_app*)param;
	return (1);
}
