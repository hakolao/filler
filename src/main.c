/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:41:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		hook_app_to_loop(t_app *app)
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

static t_app	*app_new(int is_visual)
{
	t_app		*app;

	if ((!(app = malloc(sizeof(*app))) ||
		(is_visual && !(app->mlx = mlx_init())) ||
		(is_visual && !(app->window = new_window(app)))) &&
		log_err("Failed to init app", strerror(5)))
		return (NULL);
	return (app);
}

static t_app	*init_app_data(char **argv, int is_visual)
{
	t_app	*app;

	if (!(app = app_new(is_visual)))
		return (NULL);
	app->board = NULL;
	app->name = argv[0];
	app->window->bg_color = COLOR(50, 50, 50, 0);
	app->player1_color = PLAYER_1_COLOR;
	app->player2_color = PLAYER_2_COLOR;
	app->show_guide = FALSE;
	app->is_finished = FALSE;
	app->is_player1 = FALSE;
	app->player1_score = 0;
	app->player2_score = 0;
	app->player1_name = NULL;
	app->player2_name = NULL;
	app->strategy = find_first;
	app->current_piece = NULL;
	if (is_visual)
	{
	app->info_bounds = (t_rect){
		.w = app->window->screen_width * 1 / 4 - 10,
		.h = app->window->screen_height - 20,
		.x = app->window->screen_width * 3 / 4, .y = 10};
	app->grid_bounds = (t_rect){
		.w = app->window->screen_width * 3 / 4 - 10,
		.h = app->window->screen_height * 3 / 4,
		.x = 10, .y = 10};
	}
	return (app);
}

static int		init_filler(char **argv, int is_visual)
{
	t_app		*app;
	static int	ret;

	if (!(app = init_app_data(argv, is_visual)))
		return (FALSE);
	if (is_visual)
		hook_app_to_loop(app);
	else
	{
		ret = FALSE;
		while (update_map(app))
			;
	}
	return (TRUE);
}

int				main(int argc, char **argv)
{
	int		is_visual;

	if (argc > 2)
		return (0);
	is_visual = FALSE;
	if (argc == 2)
	{
		is_visual = ft_strequ(argv[1], "visual");
		if (!is_visual)
			return (log_err("Argument must be empty or 'visual'", strerror(5)));
	}
	return (init_filler(argv, is_visual));
}
