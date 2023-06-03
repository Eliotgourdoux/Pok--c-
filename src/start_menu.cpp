/*
** EPITECH PROJECT, 2023
** start_menu
** File description:
** start menu
*/

#include "pokemon_cpp.hpp"
#include "SFML/Graphics.hpp"

static void display_rule(window_t *p)
{
    sf::Color grayColor(200, 200, 200);
    sf::Color greenColor(0, 255, 0);
    sf::Color blackColor(0, 0, 0);

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(grayColor);

    sf::Text rulesText;
    rulesText.setFont(p->font);
    rulesText.setString("Regles du jeu:\n\n- Attrapez des Pokemon !\n- Entrainez des Pokemon !\n- Combattez d'autres dresseurs !\n- Explorez le monde de Pokemon !\n- Collectez les Pokemon !");
    rulesText.setCharacterSize(24);
    rulesText.setFillColor(blackColor);
    rulesText.setPosition(50, 50);

    sf::RectangleShape backButton(sf::Vector2f(150, 50));
    backButton.setPosition(325, 450);
    backButton.setFillColor(greenColor);

    sf::Text backText;
    backText.setFont(p->font);
    backText.setString("Retour");
    backText.setCharacterSize(24);
    backText.setFillColor(blackColor);
    centerText(backText, backButton);

    while (p->window.isOpen()) {
        sf::Event event;
        while (p->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                p->window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        return;
                    }
                }
            }
        }

        p->window.clear();
        p->window.draw(background);
        p->window.draw(rulesText);
        p->window.draw(backButton);
        p->window.draw(backText);
        p->window.display();
    }
}

static void display_cred(window_t *p)
{
    sf::Color grayColor(200, 200, 200);
    sf::Color greenColor(0, 255, 0);
    sf::Color blackColor(0, 0, 0);

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(grayColor);

    sf::Text creditsText;
    creditsText.setFont(p->font);
    creditsText.setString("Credits:\n\nEliot Gourdoux\nEnzo Petit");
    creditsText.setCharacterSize(24);
    creditsText.setFillColor(blackColor);
    creditsText.setPosition(300, 250);

    sf::RectangleShape backButton(sf::Vector2f(150, 50));
    backButton.setPosition(325, 450);
    backButton.setFillColor(greenColor);

    sf::Text backText;
    backText.setFont(p->font);
    backText.setString("Retour");
    backText.setCharacterSize(24);
    backText.setFillColor(blackColor);
    centerText(backText, backButton);

    while (p->window.isOpen()) {
        sf::Event event;
        while (p->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                p->window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        p->window.clear();
                        return;
                    }
                }
            }
        }

        p->window.clear();
        p->window.draw(background);
        p->window.draw(creditsText);
        p->window.draw(backButton);
        p->window.draw(backText);
        p->window.display();
    }
}

void start_menu(window_t *p)
{
    // init all ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    p->window.create(sf::VideoMode(800, 600), "Pokemon");
    p->window.setFramerateLimit(60);

    sf::Color grayColor(200, 200, 200);
    sf::Color greenColor(0, 255, 0);
    sf::Color blackColor(0, 0, 0);

    sf::RectangleShape background(sf::Vector2f(800, 600));
    background.setFillColor(grayColor);

    if (!p->font.loadFromFile("assets/Pokemon_Classic.ttf")) {
        return;
    }

    sf::RectangleShape playButton(sf::Vector2f(200, 50));
    playButton.setPosition(300, 160);
    playButton.setFillColor(greenColor);

    sf::Text playText;
    playText.setFont(p->font);
    playText.setString("Jouer");
    playText.setCharacterSize(24);
    playText.setFillColor(blackColor);
    centerText(playText, playButton);

    sf::RectangleShape rulesButton(sf::Vector2f(200, 50));
    rulesButton.setPosition(300, 240);
    rulesButton.setFillColor(greenColor);

    sf::Text rulesText;
    rulesText.setFont(p->font);
    rulesText.setString("Regles");
    rulesText.setCharacterSize(24);
    rulesText.setFillColor(blackColor);
    centerText(rulesText, rulesButton);

    sf::RectangleShape creditsButton(sf::Vector2f(200, 50));
    creditsButton.setPosition(300, 320);
    creditsButton.setFillColor(greenColor);

    sf::Text creditsText;
    creditsText.setFont(p->font);
    creditsText.setString("Credit");
    creditsText.setCharacterSize(24);
    creditsText.setFillColor(blackColor);
    centerText(creditsText, creditsButton);

    sf::RectangleShape quitButton(sf::Vector2f(200, 50));
    quitButton.setPosition(300, 400);
    quitButton.setFillColor(greenColor);

    sf::Text quitText;
    quitText.setFont(p->font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(24);
    quitText.setFillColor(blackColor);
    centerText(quitText, quitButton);

    // boucle du menu ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    while (p->window.isOpen()) {
        sf::Event event;
        while (p->window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                p->window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                    if (playButton.getGlobalBounds().contains(mousePos)) {
                    }
                    else if (rulesButton.getGlobalBounds().contains(mousePos)) {
                        display_rule(p);
                    }
                    else if (creditsButton.getGlobalBounds().contains(mousePos)) {
                        display_cred(p);
                    }
                    else if (quitButton.getGlobalBounds().contains(mousePos)) {
                        p->window.close();
                    }
                }
            }
        }

        p->window.clear();
        p->window.draw(background);
        p->window.draw(playButton);
        p->window.draw(playText);
        p->window.draw(rulesButton);
        p->window.draw(rulesText);
        p->window.draw(creditsButton);
        p->window.draw(creditsText);
        p->window.draw(quitButton);
        p->window.draw(quitText);
        p->window.display();
    }
}
