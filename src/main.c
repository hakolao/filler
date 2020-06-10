/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/10 15:19:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		hook_app(t_app *app)
{
	mlx_hook(app->window->mlx_wdw, 2, 0, handle_key_press, app);
	mlx_hook(app->window->mlx_wdw, 3, 0, handle_key_release, app);
	mlx_hook(app->window->mlx_wdw, 4, 0, handle_mouse_button_press, app);
	mlx_hook(app->window->mlx_wdw, 5, 0, handle_mouse_button_release, app);
	mlx_hook(app->window->mlx_wdw, 6, 0, handle_mouse_move, app);
	mlx_hook(app->window->mlx_wdw, 17, 0, handle_exit_event, app);
	mlx_loop_hook(app->mlx, handle_loop, app);
	mlx_loop(app->mlx);
}

static t_app	*app_new()
{
	t_app		*app;

	if ((!(app = malloc(sizeof(*app))) ||
		!(app->mlx = mlx_init()) ||
		!(app->window = new_window(app)) ||
		!(app->thread_params = thread_params(app)) ||
		!(app->current_piece = malloc(sizeof(*app->current_piece)))) &&
		log_err("Failed to init app", strerror(5)))
		return (NULL);
	return (app);
}

static t_app	*init_app_data(char *name)
{
	t_app	*app;

	if (!(app = app_new()))
		return (NULL);
	app->board = NULL;
	app->name = name;
	app->window->bg_color = COLOR(50, 50, 50, 0);
	app->show_guide = FALSE;
	app->num_players = 2;
	app->is_finished = FALSE;
	app->is_player1 = FALSE;
	app->player1_score = 0;
	app->player2_score = 0;
	app->player1_name = NULL;
	app->player2_name = NULL;
	app->info_bounds = (t_rect){
			.w = app->window->screen_width * 1 / 4 - 10,
			.h = app->window->screen_height - 20,
			.x = app->window->screen_width * 3 / 4, .y = 10};
	app->grid_bounds = (t_rect){
			.w = app->window->screen_width * 3 / 4 - 10,
			.h = app->window->screen_height * 3 / 4,
			.x = 10, .y = 10};
	return (app);
}

static int		init_filler(char *name)
{
	t_app	*app;

	if (!(app = init_app_data(name)))
		return (FALSE);
	hook_app(app);
	return (TRUE);
}

int				main(int argc, char **argv)
{
	if (argc > 1)
		return (log_guide());
	return (init_filler(argv[0]));
}
