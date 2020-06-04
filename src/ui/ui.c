/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:03:35 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/04 22:36:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				draw_ui(t_app *app)
{
	char	*guidestr;

	if (!app->show_guide)
		return ;
	if (!(guidestr = guide()))
		return ;
	draw_paragraph(app, guidestr, 10, 30);
	ft_strdel(&guidestr);
}
