/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:21:55 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/12 12:47:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				log_err(char *str, char *strerror)
{
	ft_putstr("\033[0;31m");
	ft_putstr_fd(strerror, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(str, 2);
	ft_putstr("\033[0m");
	return (1);
}

int				log_perr(char *str)
{
	ft_putstr("\033[0;31m");
	perror(str);
	ft_putstr("\033[0m");
	return (1);
}

int				log_guide(void)
{
	ft_putstr("FILLER:\n");
	ft_putstr("usage:\n ./filler\n");
	return (1);
}

void			debug_app(t_app *app)
{
	if (app->board == NULL)
	{
		ft_dprintf(2, "Board is NULL\n");
		return ;
	}
	ft_dprintf(2,
		"Board Width: %d, Board Height %d\n"
		"p1 name: %s, p2 name: %s\n"
		"Token Width: %d, Token Height: %d\n"
		"p1 score: %d, p2 score: %d\n"
		"is_player1: %s\n",
		app->board->width, app->board->height,
		app->player1_name, app->player2_name,
		app->current_piece->width, app->current_piece->height,
		app->player1_score, app->player2_score,
		app->is_player1 ? "TRUE" : "FALSE"
	);
}

void			debug_piece(t_piece *piece)
{
	int		x;
	int		y;

	if (piece == NULL)
	{
		ft_dprintf(2, "Piece is NULL\n");
		return ;
	}
	y = -1;
	while (++y < piece->height)
	{
		ft_dprintf(2, "Debug: ");
		x = -1;
		while (++x < piece->width)
		{
			if (piece->cells[y][x].player_i == UNPLACED)
				ft_dprintf(2, "*");
			else
				ft_dprintf(2, ".");
		}
		ft_dprintf(2, "\n");
	}
}

void			debug_board(t_board *board)
{
	int		x;
	int		y;

	if (board == NULL)
	{
		ft_dprintf(2, "Board is NULL\n");
		return ;
	}
	y = -1;
	while (++y < board->height)
	{
		x = -1;
		ft_dprintf(2, "Debug: ");
		while (++x < board->width)
		{
			if (board->cells[y][x].player_i == PLAYER_1)
				ft_dprintf(2, "O");
			else if (board->cells[y][x].player_i == PLAYER_2)
				ft_dprintf(2, "X");
			else
				ft_dprintf(2, ".");
		}
		ft_dprintf(2, "\n");
	}
}