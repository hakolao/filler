/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 12:56:28 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/09 16:37:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int	parse_player(t_app *app, char *line)
{
	static char	*player_1;
	static char	*player_2;
	int			p1_len;
	int			p2_len;

	player_1 = player_1 != NULL ? player_1 : NULL;
	player_2 = player_2 != NULL ? player_2 : NULL;
	if (player_1 == NULL &&
		(player_1 = ft_strstr(line, "$$$ exec p1 : [")))
	{
		p1_len = ft_strchr(player_1, ']') - player_1;
		if (ft_match(player_1, app->name))
			app->is_player1 = TRUE;
	}
	else if (player_2 == NULL &&
		(player_2 = ft_strstr(line, "$$$ exec p2 : [")))
	{
		p2_len = ft_strchr(player_2, ']') - player_2;
		if (ft_match(player_2, app->name))
			app->is_player1 = FALSE;
	}
	if (app->player1_id == NULL)
	{
		if (!(app->player1_id = ft_strnew(p1_len)))
			return (FALSE);
		ft_strncpy(app->player1_id, player_1, p1_len);
	}
	if (app->player2_id == NULL)
	{
		if (!(app->player2_id = ft_strnew(p2_len)))
			return (FALSE);
		ft_strncpy(app->player2_id, player_2, p2_len);
	}
	return (TRUE);
}

static int	init_board(t_app *app, int width, int height)
{
	int			y;
	int			x;

	if (!(app->board = malloc(sizeof(*app->board))))
		return (FALSE);
	app->board->width = width;
	app->board->height = height;
	if (!(app->board->cells = malloc(sizeof(*app->board->cells) * height)))
		return (FALSE);
	y = 0;
	while (y < height)
	{
		if (!(app->board->cells[y] = malloc(sizeof(**app->board->cells) * width)))
			return (FALSE);
		x = 0;
		while (x < width)
		{
			app->board->cells[y][x].color = EMPTY_COLOR;
			app->board->cells[y][x].x = x;
			app->board->cells[y][x].y = y;
			app->board->cells[y][x].player_i = EMPTY;
		}
		y++;
	}
	return (TRUE);
}

static int	init_piece(t_app *app, int width, int height)
{
	int			y;
	int			x;

	if (app->current_piece->cells != NULL)
		free(app->current_piece->cells);
	app->current_piece->width = width;
	app->current_piece->height = height;
	if (!(app->current_piece->cells =
		malloc(sizeof(*app->current_piece->cells) * height)))
		return (FALSE);
	y = 0;
	while (y < height)
	{
		if (!(app->current_piece->cells[y] =
			malloc(sizeof(**app->current_piece->cells) * width)))
			return (FALSE);
		x = 0;
		while (x < width)
		{
			app->current_piece->cells[y][x].color = EMPTY_COLOR;
			app->current_piece->cells[y][x].x = x;
			app->current_piece->cells[y][x].y = y;
			app->current_piece->cells[y][x].player_i = EMPTY;
		}
		y++;
	}
	return (TRUE);
}

static int	read_map_line(t_app *app, char *line)
{
	int	has_width;
	int	width;
	int	height;
	int	x;
	int	y;

	y = 0;
	if (line[0] == 'P')
	{
		has_width = FALSE;
		x = 0;
		while (line[x])
		{
			if (ft_isdigit(line[x]))
			{
				if (!has_width)
				{
					width = ft_atoi(line);
					has_width = TRUE;	
				} else
					height = ft_atoi(line);
			}
			x++;
		}
		if (!init_board(app, width, height))
			return (FALSE);
	} else if (ft_isdigit(line[0]))
	{
		y = ft_atoi(line);
		x = 4;
		while (line[x])
		{
			if (line[x] == '.')
				app->board->cells[y][x].player_i = EMPTY;
			else if (line[x] == 'o' || line[x] == 'O')
			{
				app->board->cells[y][x].player_i = PLAYER_1;
				app->board->cells[y][x].color = PLAYER_1_COLOR;
			}
			else if (line[x] == 'x' || line[x] == 'X')
			{
				app->board->cells[y][x].player_i = PLAYER_2;
				app->board->cells[y][x].color = PLAYER_2_COLOR;
			}
			x++;
		}
	}
	return (TRUE);
}

static int	read_piece_line(t_app *app, char *line)
{
	int	has_width;
	int	width;
	int	height;
	int	x;
	int	y;

	y = 0;
	if (line[0] == 'P')
	{
		has_width = FALSE;
		x = 0;
		while (line[x])
		{
			if (ft_isdigit(line[x]))
			{
				if (!has_width)
				{
					width = ft_atoi(line);
					has_width = TRUE;	
				} else
					height = ft_atoi(line);
			}
			x++;
		}
		if (!init_piece(app, width, height))
			return (FALSE);
	} else
	{
		y = ft_atoi(line);
		x = 0;
		while (line[x])
		{
			if (line[x] == '*')
				app->current_piece->cells[y][x].player_i = UNPLACED;
			x++;
		}
	}
	return (TRUE);
}

static int	read_game_end(t_app *app, char *line)
{
	int		p1_score;
	int		p2_score;

	if (line[3] == '0')
	{
		p1_score = ft_atoi(line + 9);
		if (p1_score != app->player1_score)
			return (log_err("Wrong score calculated", "Error") && FALSE);
	}
	if (line[3] == 'X')
	{
		p2_score = ft_atoi(line + 9);
		if (p2_score != app->player2_score)
			return (log_err("Wrong score calculated", "Error") && FALSE);
		app->is_finished = TRUE;
	}
	return (TRUE);
}

static int	read_stdout(t_app *app)
{
	char		*line;
	int			is_player_parsed;
	int			is_parsing_map;
	int			is_parsing_piece;
	int			is_parsing_end;
	int			ret;

	is_player_parsed = FALSE;
	is_parsing_map = FALSE;
	is_parsing_piece = FALSE;
	is_parsing_end = FALSE;
	while ((ret = get_next_line(1, &line)) == TRUE)
	{
		if (app->player1_id != NULL && app->player2_id != NULL)
			is_player_parsed = TRUE;
		if (ft_match(line, "Plateau"))
			is_parsing_map = TRUE;
		if (ft_match(line, "Piece"))
		{
			is_parsing_map = FALSE;
			is_parsing_piece = TRUE;
		}
		if (ft_match(line, "<got"))
			is_parsing_piece = FALSE;
		if (ft_match(line, "=="))
			is_parsing_end = TRUE;
		//ToDo Read map OR Read Players OR read piece...
		if (!is_player_parsed && !parse_player(app, line))
			return (FALSE);
		if (is_parsing_map && !read_map_line(app, line))
			return (FALSE);
		if (is_parsing_piece && !read_piece_line(app, line))
			return (FALSE);
		if (is_parsing_end && !read_game_end(app, line))
			return (FALSE);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	return (TRUE);
}

int			update_board(t_app *app)
{
	int	p1_score;
	int	p2_score;
	int	y;
	int	x;

	p1_score = 0;
	p2_score = 0;
	if (!(app->board = malloc(sizeof(*app->board))))
		return (FALSE);
	if (!read_stdout(app))
		return (FALSE);
	y = 0;
	while (y < app->board->height)
	{
		x = 0;
		while (x < app->board->width)
		{
			if (app->board->cells[y][x].player_i == PLAYER_1)
				p1_score++;
			else if (app->board->cells[y][x].player_i == PLAYER_2)
				p2_score++;
			x++;
		}
		y++;
	}
	return (TRUE);
}