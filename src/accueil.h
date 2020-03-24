/*
 * accueil.h
 *
 *  Created on: 22 janv. 2020
 *      Author: loic
 */

#ifndef ACCUEIL_H_
#define ACCUEIL_H_

void fenetre_horizontal(unsigned char character);
void fenetre_vertical(unsigned char character);
void titre_vertical(unsigned char character);
void titre_horizontal(unsigned char character);
void titre_texte1(void);
void apregle(signed char touche);
char play2(signed char touche);
void personnage(signed char touche);
void deplacement(void);
void tire(signed char touche);
void sup(void);
#endif /* ACCUEIL_H_ */
