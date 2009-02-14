/*
    Awesome Tower Defense
    Copyright (C) 2008-2009  Trygve Vea and contributors (read AUTHORS)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <SDL.h>

#include "render.h"
#include "gfx_charmap.h"
#include "settings.h"
#include "game.h"

static int money = 200;
static int score = 0;
static int lives = 1;
char moneytext[20], scoretext[20], lifetext[20];

int iddqd_enabled = 0;
int idkfa_enabled = 0;

void update_money(int amount) {
    if (! idkfa_enabled) money += amount;
    if ( money < 0 ) money = 0;
    sprintf(moneytext, "money %6d", money);
    updaterect(3,13);
}
void update_score(int amount) {
    score += amount;
    if ( score < 0 ) score = 0;
    sprintf(scoretext, "score %6d", score);
    updaterect(3,13);
}
void update_lives(int amount) {
    if (! iddqd_enabled) lives += amount;
    if ( lives < 0 ) {
        lives = 0;
    }
    if ( lives == 0 ) game_over();
    sprintf(lifetext, "lives %6d", lives);
    updaterect(3,13);
}
int have_money(int amount) {
    if (idkfa_enabled) return 1;
    if ( money >= amount ) return 1;
    return 0;
}
void draw_numbers(void) {
    draw_text(screen,moneytext,3*32,420);
    draw_text(screen,scoretext,3*32,430);
    draw_text(screen,lifetext,3*32,440);
}
SDL_Event go = { SDL_QUIT };
void game_over(void) {
    printf("GAME OVER!!!!\n");
    SDL_PushEvent(&go);
}
void iddqd(void)
{
    iddqd_enabled = 1;
    lives = 999;
    update_lives(0);
}

void idkfa(void)
{
    idkfa_enabled = 1;
    money = 999999;
    update_money(0);
}