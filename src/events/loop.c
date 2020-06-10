/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 18:23:34 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 15:58:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			debug_app(t_app *app)
{
	if (app->board == NULL)
	{
		ft_printf("Board is NULL\n");
		return ;
	}
	ft_printf(
		"Board Width: %d, Board Height %d\n"
		"p1 name: %s, p2 name: %s\n"
		"Token Width: %d, Token Height: %d"
		"p1 score: %d, p2 score: %d\n",
		app->board->width, app->board->height,
		app->player1_name, app->player2_name,
		app->current_piece->width, app->current_piece->height,
		app->player1_score, app->player2_score
	);
}

int				handle_loop(void *params)
{
	t_app		*app;

	app = (t_app*)params;
	if (!read_filler_input(app) &&
		log_perr("Something went wrong in input reading"))
		handle_exit_event(app);
	if (app->window->redraw == TRUE)
		draw(app);
	debug_app(app);
	return (0);
}
