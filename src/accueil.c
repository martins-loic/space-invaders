/*
 * accueil.c
 *
 *  Created on: 22 janv. 2020
 *      Author: loic
 */
#include "serial.h"
#include "vt100.h"
#include "accueil.h"

static uint8_t x[11] =
{ 10, 30, 50, 70, 20, 40, 60, 10, 30, 50, 70 };
static uint8_t y[11] =
{ 3, 3, 3, 3, 6, 6, 6, 9, 9, 9, 9 };
static uint8_t x1 = 38;
static uint8_t compteur = 0;
static uint8_t xt;

void fenetre_horizontal(unsigned char character)
{
	unsigned char i;
	for (i = 1; i < 81; i++)
	{
		vt100_move(i, 1);
		serial_putchar(character);
		vt100_move(i, 25);
		serial_putchar(character);
	}
}

void fenetre_vertical(unsigned char character)
{
	unsigned char i;
	for (i = 1; i < 25; i++)
	{
		vt100_move(1, i);
		serial_putchar(character);
		vt100_move(81, i);
		serial_putchar(character);
	}
}

void titre_vertical(unsigned char character)
{
	unsigned char i;
	for (i = 35; i < 46; i++)
	{
		vt100_move(i, 3);
		serial_putchar(character);
		vt100_move(i, 7);
		serial_putchar(character);
	}
}


void titre_horizontal(unsigned char character)
{
	unsigned char i;
	for (i = 4; i < 8; i++)
	{
		vt100_move(34, i);
		serial_putchar(character);
		vt100_move(46, i);
		serial_putchar(character);
	}
}

void titre_texte1(void)
{
	vt100_move(38, 4);
	serial_puts("space");

	vt100_move(37, 6);
	serial_puts("invader");

	vt100_move(32, 22);
	serial_puts("press to R for rules");

	vt100_move(30, 15);
	serial_puts("press to space for play");
}
void apregle(signed char touche)
{
	if (touche == 'r')
	{
		vt100_clear_screen();
		fenetre_horizontal('#');
		fenetre_vertical('#');

		vt100_move(33, 4);
		serial_puts("rules of the game");

		vt100_move(10, 6);
		serial_puts(
				"the object of the game is to kill all enemies by shooting them");

		vt100_move(29, 8);
		serial_puts("press  q  for move left");

		vt100_move(28, 10);
		serial_puts("press  d  for move right");

		vt100_move(30, 12);
		serial_puts("press  z  for shoot");

		vt100_move(26, 14);
		serial_puts("take shelter behind ███████ ");

		vt100_move(30, 16);
		serial_puts("press to space for play");

	}
}
char play2(signed char touche)
{
	uint8_t i;
	if (touche == ' ')
	{
		vt100_clear_screen();
		fenetre_horizontal('#');
		fenetre_vertical('#');

		vt100_move(11, 18);
		serial_puts("███████");

		vt100_move(38, 18);
		serial_puts("███████");

		vt100_move(66, 18);
		serial_puts("███████");

		for (i = 0; i < 11; i++)
		{
			if (i < 4)
			{
				vt100_move(x[i], y[i]);
				serial_puts("<->");
			}
			else if (i < 7)
			{

				vt100_move(x[i], y[i]);
				serial_puts("]-[");
			}
			else
			{
				vt100_move(x[i], y[i]);
				serial_puts("\\!/");
			}
		}
		return 1;
	}
	return 0;
}
void personnage(signed char touche)
{
	vt100_move(x1, 22);
	serial_puts("({^})");

	if (touche == 'q' && x1 > 3)
	{
		vt100_move(x1, 22);
		serial_puts("     ");
		x1--;
		vt100_move(x1, 22);
		serial_puts("({^})");
	}
	else if (touche == 'd' && x1 < 74)
	{
		vt100_move(x1, 22);
		serial_puts("     ");
		x1++;
		vt100_move(x1, 22);
		serial_puts("({^})");
	}


}
void deplacement(void)
{
	uint8_t i;
	for (i = 0; i < 11; i++)
	{
		if (x[i] != 250)
		{
			vt100_move(x[i], y[i]);
			serial_puts("   ");
		}
	}
	for (i = 0; i < 11; i++)
	{
		if (x[i] != 250)
		{
			if (x[i] == 77)
			{
				compteur = 1;
			}
			else if (x[i] == 2)

			{
				compteur = 0;
			}
			if (compteur == 0)
			{


				x[i]++;
				if (i < 4)
				{
					vt100_move(x[i], y[i]);
					serial_puts("<->");
				}
				else if (i < 7)
				{

					vt100_move(x[i], y[i]);
					serial_puts("]-[");
				}
				else
				{
					vt100_move(x[i], y[i]);
					serial_puts("\\!/");
				}

			}
			else if (compteur == 1)
			{


				x[i]--;
				if (i < 4)
				{
					vt100_move(x[i], y[i]);
					serial_puts("<->");
				}
				else if (i < 7)
				{

					vt100_move(x[i], y[i]);
					serial_puts("]-[");
				}
				else
				{
					vt100_move(x[i], y[i]);
					serial_puts("\\!/");
				}


			}


		}
	}
}
void tire(signed char touche)
{
	uint8_t yt1 = 21;
	if (touche == 'z')
	{
		xt = x1 + 2;
		vt100_move(xt, yt1);
		serial_puts("°");
		while (yt1 >= 3)
		{
			vt100_move(xt, yt1);
			serial_puts(" ");

			yt1--;

			vt100_move(xt, yt1);
			serial_puts("°");

		}
		vt100_move(xt, yt1);
		serial_puts(" ");
	}

}
void sup(void)
{
	uint8_t i;
	for (i = 0; i < 11; i++)
	{
		if (x[i] > (xt - 1) && x[i] < (xt + 1))
		{
			vt100_move(x[i], y[i]);
			serial_puts("   ");

			x[i] = 250;
			y[i] = 250;

			xt = 0;

			break;
		}
	}
}










