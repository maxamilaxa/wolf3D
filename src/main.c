/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/24 20:31:05 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 20:49:57 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		sdl_initial(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		get_error(FAIL_SDL);
	if (!(sdl->win_ptr = SDL_CreateWindow("Wolf3d", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_ALLOW_HIGHDPI)))
		get_error(FAIL_SDL);
	if (!(sdl->srf_ptr = SDL_GetWindowSurface(sdl->win_ptr)))
		get_error(FAIL_SDL);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		get_error(FAIL_SDL);
	if (!(sdl->audio = Mix_LoadMUS("./music/adrift.mp3")))
		get_error(FAIL_SDL);
}

static int		check_argv(char **str)
{
	int			l;

	if (ft_strcmp("./wolf3d", str[0]) != 0)
		return (0);
	l = ft_strlen(str[1]);
	if (l < 6)
		return (0);
	if (ft_strcmp(".maze", &str[1][l - 5]) != 0)
		return (0);
	return (1);
}

static void		default_value(t_maze *m, t_sign *sgn)
{
	m->sym_pl = '@';
	m->sym_fr = '.';
	m->sym_wl = '#';
	m->is_area = 0;
	m->is_play = 0;
	m->dirc_pl = (t_point_d){.x = -1, .y = 0};
	m->proj_pl = (t_point_d){.x = 0, .y = 0.60};
	m->pos_pl = (t_point_d){.x = 1.5, .y = 1.5};
	sgn->up = 0;
	sgn->down = 0;
	sgn->w = 0;
	sgn->s = 0;
	sgn->a = 0;
	sgn->d = 0;
	sgn->rgt = 0;
	sgn->lft = 0;
	sgn->sh = 1;
	m->sgn_t = 0;
}

static void		image_initial(t_sdl *sdl)
{
	int			i;

	i = 0;
	if (!(sdl->image = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 8)))
		get_error(FAIL_MALLOC);
	sdl->image[0] = IMG_Load("./txtr/a.gif");
	sdl->image[1] = IMG_Load("./txtr/b.gif");
	sdl->image[2] = IMG_Load("./txtr/c.gif");
	sdl->image[3] = IMG_Load("./txtr/d.gif");
	sdl->image[4] = IMG_Load("./txtr/aa.gif");
	sdl->image[5] = IMG_Load("./txtr/bb.gif");
	sdl->image[6] = IMG_Load("./txtr/cc.gif");
	sdl->image[7] = IMG_Load("./txtr/dd.gif");
	while (i < 8)
	{
		if (!(sdl->image[i]))
			get_error(FAIL_SDL);
		i++;
	}
}

int				main(int argc, char **argv)
{
	t_data		*data;
	int			fd;

	if (argc != 2)
		get_error(FAIL_ARGC);
	if ((check_argv(argv)) == 0)
		get_error(FAIL_NAME);
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		get_error(FAIL_MALLOC);
	default_value(&data->maze, &data->sgn);
	fd = open(argv[1], O_RDONLY);
	maze_validation(fd, data);
	close(fd);
	sdl_initial(&data->sdl);
	image_initial(&data->sdl);
	game_loop(data);
	return (0);
}
