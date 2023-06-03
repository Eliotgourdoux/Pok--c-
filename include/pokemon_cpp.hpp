/*
** EPITECH PROJECT, 2023
** pokemon_cpp
** File description:
** header file
*/

#ifndef POKEMON_CPP
    #define POKEMON_CPP
    #include <SFML/Graphics.hpp>
    #include <iostream>

    typedef struct {
        sf::Font font;
        sf::RenderWindow window;
    } window_t;

    typedef struct {
    } pokemon_t;

    typedef struct {
    } invent_t;

    typedef struct {
    } jeu_t;

void start_menu(window_t *p);
void centerText(sf::Text& text, const sf::RectangleShape& button);

#endif /* !POKEMON_CPP */
