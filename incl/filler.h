/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:07:11 by ohakola           #+#    #+#             */
/*   Updated: 2020/06/22 14:52:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "mlx.h"
# include <stdio.h>
# include <pthread.h>
# include "libft.h"

/*
** Key codes for event listening
*/
# define KEY_ESC 53
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_P 35
# define KEY_1 18
# define KEY_2 19
# define KEY_NUM_4 86
# define KEY_NUM_6 88
# define KEY_NUM_8 91
# define KEY_NUM_2 84
# define SCROLL_UP 5
# define SCROLL_DOWN 4
# define MOUSE_BUTTON_RIGHT 2
# define MOUSE_BUTTON_LEFT 1
# define MOUSE_BUTTON_MIDDLE 3
# define KEY_R 15
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_G 5
# define KEY_C 8
# define KEY_B 11
# define KEY_TAB 48
# define KEY_SHIFT 257
# define KEY_O 31

/*
** Color helpers
*/
# define CLAMP_0_255(color) (color > 255 ? 255 : color < 0 ? 0 : color)
# define ALPHA(a) ((a >> 24) & 255)
# define RED(r) ((r >> 16) & 255)
# define GREEN(g) ((g >> 8) & 255)
# define BLUE(b) (b & 255)
# define R(r) (CLAMP_0_255(r) & 255) << 16
# define G(g) (CLAMP_0_255(g) & 255) << 8
# define B(b) CLAMP_0_255(b) & 255
# define A(a) (CLAMP_0_255(a) & 255) << 24
# define COLOR(r, g, b, a) A(a) | R(r) | G(g) | B(b)
# define UI_COLOR COLOR(0, 0, 0, 0)
# define BACKGROUND_COLOR COLOR(0, 0, 0, 0)

# define WIDTH 1200
# define HEIGHT 1000
# define THREADS 8

# define EMPTY '.'
# define PLAYER_1 'O'
# define PLAYER_2 'X'
# define UNPLACED '*'

# define PLAYER_1_COLOR COLOR(255, 0, 0, 0)
# define PLAYER_2_COLOR COLOR(0, 255, 0, 0)
# define EMPTY_COLOR COLOR(100, 100, 100, 0)

typedef struct		s_thread_params
{
	int					thread_i;
}					t_thread_params;

enum				e_alignment
{
	left,
	right,
	top,
	down
};

/*
** Scene contains all data the application needs inside its loop
*/

typedef struct		s_window
{
	int				id;
	void			*mlx_wdw;
	void			*frame;
	char			*frame_buf;
	int				screen_width;
	int				screen_height;
	int				pixel_bits;
	int				line_bytes;
	int				pixel_endian;
	int				ui_color;
	int				bg_color;
}					t_window;

typedef struct		s_cell
{
	int				x;
	int				y;
	int				color;
	char			id;
}					t_cell;

typedef struct		s_piece
{
	int				width;
	int				height;
	t_cell			**cells;
}					t_piece;

typedef struct		s_board
{
	int				width;
	int				height;
	t_cell			**cells;
}					t_board;

typedef struct		s_rect
{
	int				w;
	int				h;
	int				x;
	int				y;
}					t_rect;

typedef struct		s_app
{
	char			*name;
	t_window		*window;
	void			*mlx;
	int				cell_size;
	int				player_1_cell_y;
	int				player_2_cell_y;
	int				player1_count;
	int				player1_score;
	int				player2_count;
	int				player2_score;
	int				player1_color;
	int				player2_color;
	char			*player1_name;
	char			*player2_name;
	int				is_player1;
	int				is_finished;
	int				i_won;
	t_piece			*current_piece;
	t_board			*board;
	t_rect			grid_bounds;
	t_rect			info_bounds;
}					t_app;

typedef struct		s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct		s_triangle
{
	t_point			a;
	t_point			b;
	t_point			c;
}					t_triangle;

/*
**	Window
*/

t_window			*new_window(t_app *app);

/*
** Pixel numbers
*/
void				number_0(int letters[10][9][6]);
void				number_1(int letters[10][9][6]);
void				number_2(int letters[10][9][6]);
void				number_3(int letters[10][9][6]);
void				number_4(int letters[10][9][6]);
void				number_5(int letters[10][9][6]);
void				number_6(int letters[10][9][6]);
void				number_7(int letters[10][9][6]);
void				number_8(int letters[10][9][6]);
void				number_9(int letters[10][9][6]);
void				assign_ints(int ints[6], int *arr);

/*
** Input & Output
*/

int					update_map(t_app *app);
int					place_piece(t_app *app);
int					init_new_piece(t_app *app, char *line);
int					init_new_board(t_app *app, char *line);
int					parse_board(t_app *app);
int					parse_piece(t_app *app);
int					parse_dimensions(int *height, int *width,
					int i, char *line);
void				init_new_cell(t_cell *cell, int x, int y);
int					w_extra(t_piece *piece, enum e_alignment alignment);
int					h_extra(t_piece *piece, enum e_alignment alignment);
int					distance(int *pos, int *target);
int					is_closer(int *pos, int *other, int *target);
int					*enemy_center_of_mass(t_app *app, int *com);

/*
** UI
*/

void				draw_paragraph(t_app *app, char *text, int xpos,
					int ypos);
void				draw_finish_text(t_app *app);

/*
** Draw
*/

int					draw(t_app *app);
void				draw_rectangle(t_app *app, t_rect *rect, int color);
void				draw_triangle(t_app *app, t_triangle *rect, int color);
void				draw_pyramid_shape(t_app *app, t_rect *rect, int color);
void				draw_game(t_app *app);
void				draw_scores(t_app *app);

/*
** Events
*/

int					handle_key_press(int key, void *param);
int					handle_key_release(int key, void *param);
int					handle_mouse_button_press(int key, int x, int y,
					void *param);
int					handle_mouse_button_release(int key, int x, int y,
					void *param);
int					handle_mouse_move(int x, int y, void *param);
int					handle_loop(void *params);
int					handle_exit_event(void *params);

/*
** Logging
*/

int					log_err(char *str, char *strerror);

/*
** Score
*/
void				calculate_score(t_app *app);

#endif
