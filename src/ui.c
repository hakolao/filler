/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/10/02 15:48:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				draw_paragraph(t_app *app, char *text, int xpos,
					int ypos)
{
	char	**split_text;
	int		i;

	if (!text || (split_text = ft_strsplit(text, '\n')) == NULL)
		return ;
	i = 0;
	while (split_text[i])
	{
		mlx_string_put(app->mlx, app->window->mlx_wdw, xpos,
			ypos + i * 20, app->window->ui_color, split_text[i]);
		ft_strdel(&split_text[i++]);
	}
	free(split_text);
}

void				draw_finish_text(t_app *app)
{
	if (app->is_finished)
	{
		if (app->i_won)
			draw_paragraph(app, "YOU WON!",
				app->window->screen_width / 2 - 50,
				app->window->screen_height / 2);
		else
			draw_paragraph(app, "YOU LOST!",
				app->window->screen_width / 2 - 50,
				app->window->screen_height / 2);
	}
}
