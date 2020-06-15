/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 18:36:09 by ohakola          ###   ########.fr       */
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

void				draw_scores(t_app *app)
{
	char	*p1;
	char	*p1_score;
	char	*p2;
	char	*p2_score;
	char	*temp;

	if (!(p1_score = ft_itoa(app->player1_score)) ||
		!(p2_score = ft_itoa(app->player2_score)) ||
		!(p1 = ft_strdup("P1: ")) ||
		!(p2 = ft_strdup("P2: ")))
		return ;
	if (!(temp = ft_strjoin(p1, p1_score)))
		return ;
	draw_paragraph(app, temp, app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_1_cell_y + app->cell_size / 2);
	ft_strdel(&temp);
	if (!(temp = ft_strjoin(p2, p2_score)))
		return ;
	draw_paragraph(app, temp, app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y + app->cell_size / 2);
	ft_strdel(&temp);
	ft_strdel(&p1);
	ft_strdel(&p2);
	ft_strdel(&p1_score);
	ft_strdel(&p2_score);
}

void				draw_texts(t_app *app)
{
	if (app->board != NULL)
		draw_scores(app);
	if (app->is_finished)
		draw_paragraph(app, "GAME OVER!",
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y + 2 * app->cell_size);
}
