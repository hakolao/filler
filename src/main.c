/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:59:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 23:01:31 by ohakola          ###   ########.fr       */
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
	mlx_loop_hook(app->window->mlx, handle_loop, app);
	mlx_loop(app->window->mlx);
}

static int		init_filler()
{
	t_app		*app;
	void*		*mlx;

	if ((!(app = malloc(sizeof(*app))) ||
		!(mlx = mlx_init()) ||
		!(app->window = new_window(mlx)) ||
		!(app->thread_params = thread_params(app))) &&
		log_err("Failed to init app", strerror(5)))
		return (0);
	app->window->bg_color = COLOR(255, 255, 255, 0);
	hook_app(app);
	return (1);
}

int				main(int argc, char **argv)
{
	(void)argv;
	if (argc < 2)
	{
		return (log_guide() && init_filler());
	}
	return (1);
}
