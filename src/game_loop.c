/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkopiika <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 20:33:40 by mkopiika          #+#    #+#             */
/*   Updated: 2019/07/28 21:09:46 by mkopiika         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		game_over(t_sdl *sdl)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (sdl->image[i])
			SDL_FreeSurface(sdl->image[i]);
		i++;
	}
	if (sdl->srf_ptr)
		SDL_FreeSurface(sdl->srf_ptr);
	if (sdl->win_ptr)
		SDL_DestroyWindow(sdl->win_ptr);
	if (sdl->audio)
		Mix_CloseAudio();
	SDL_Quit();
}

static void		render_calculate(t_render *tick)
{
	tick->past = tick->now;
	tick->now = SDL_GetTicks();
	tick->render = (tick->now - tick->past) / 1000.0;
	tick->rottn = tick->render * 2.0;
}

static void		check_sign(int key_code, t_sign *sgn, SDL_Event e, t_maze *m)
{
	if ((e.type != SDL_KEYDOWN) && (e.type != SDL_KEYUP))
		return ;
	if (key_code == SDLK_UP)
		sgn->up = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_DOWN)
		sgn->down = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_w)
		sgn->w = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_s)
		sgn->s = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_a)
		sgn->a = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_d)
		sgn->d = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_LEFT)
		sgn->lft = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_RIGHT)
		sgn->rgt = e.type == SDL_KEYDOWN;
	if (key_code == SDLK_LSHIFT)
		sgn->sh = (e.type == SDL_KEYDOWN) ? 2 : 1;
	if (key_code == SDLK_TAB && e.type == SDL_KEYDOWN)
		m->sgn_t = (m->sgn_t == 0) ? 4 : 0;
}

void			game_loop(t_data *data)
{
	t_render	tick;
	int			game_loop;
	int			key_code;
	SDL_Event	event;

	game_loop = 42;
	if (Mix_PlayMusic(data->sdl.audio, 1) == -1)
		get_error(FAIL_SDL);
	while (game_loop == 42)
	{
		render_calculate(&tick);
		while (SDL_PollEvent(&event))
		{
			key_code = event.key.keysym.sym;
			if ((event.type == SDL_KEYDOWN && key_code == SDLK_ESCAPE)
			|| (event.type == SDL_QUIT))
				game_loop = 0;
			check_sign(key_code, &data->sgn, event, &data->maze);
		}
		key_events(data->sgn, &data->maze, &tick);
		raycast_alg(data);
		SDL_UpdateWindowSurface(data->sdl.win_ptr);
	}
	game_over(&data->sdl);
}
