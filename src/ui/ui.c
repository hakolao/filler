/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/15 17:23:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void			draw_scores(t_app *app)
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
	draw_paragraph(app, temp,
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_1_cell_y + app->cell_size / 2);
	ft_strdel(&temp);
	if (!(temp = ft_strjoin(p2, p2_score)))
		return ;
	draw_paragraph(app, temp,
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y + app->cell_size / 2);
	ft_strdel(&temp);
	ft_strdel(&p1);
	ft_strdel(&p2);
	ft_strdel(&p1_score);
	ft_strdel(&p2_score);
}

void				draw_texts(t_app *app)
{
	char	*guidestr;

	if (app->board != NULL)
		draw_scores(app);
	if (app->is_finished)
		draw_paragraph(app, "GAME OVER!",
		app->info_bounds.x + 10 + app->cell_size + 10,
		app->player_2_cell_y + 2 * app->cell_size);
	if (!app->show_guide)
		return ;
	if (!(guidestr = guide()))
		return ;
	draw_paragraph(app, guidestr, 10, 30);
	ft_strdel(&guidestr);
}
