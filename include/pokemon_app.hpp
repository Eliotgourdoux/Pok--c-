#ifndef POKEMON_APP_HPP
#define POKEMON_APP_HPP

#include "raylib.h"
#include <string>
#include <vector>

class PokemonApp {
  public:
    PokemonApp();
    ~PokemonApp();

    void run();

  private:
    static constexpr int FIXED_WIDTH = 800;
    static constexpr int FIXED_HEIGHT = 600;

    bool isFullscreen;
    Font font;
    Texture2D background;

    struct Button {
        Rectangle rect;
        std::string text;
        Vector2 textPos;
    };

    void init();
    void cleanup();
    void mainMenu();
    void optionsMenu();

    // On modifie la signature de displayScreen pour n’avoir qu’un parametre
    void displayScreen(const char *text);

    // Outils
    void centerText(const char *text, const Rectangle &rect, int fontSize, Vector2 &pos);
    void drawButton(const Button &btn, const Vector2 &mousePos);

    // Nouvelle fonction pour centrer un bloc multi-ligne
    void drawCenteredTextBlock(const char *text, float fontSize, Color color);
};

#endif
