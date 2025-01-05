#include "pokemon_app.hpp"
#include <iostream>
#include <sstream> // Pour separer le texte en lignes
#include <vector>

// Couleurs pour les boutons
static const Color BUTTON_NORMAL = {255, 255, 255, 200}; // Blanc semi-transparent
static const Color BUTTON_HOVER = {220, 220, 220, 200};  // Gris clair semi-transparent

// Couleurs du texte
static const Color TEXT_COLOR = WHITE;
static const Color TEXT_SHADOW_COLOR = {0, 0, 0, 170};

//
// --- Constructeur & Destructeur ---
//
PokemonApp::PokemonApp() : isFullscreen(false) {}

PokemonApp::~PokemonApp() {}

//
// --- Methode principale : run() ---
//
void PokemonApp::run() {
    init();
    mainMenu();
    cleanup();
}

//
// --- Initialisation & Nettoyage ---
//
void PokemonApp::init() {
    InitWindow(FIXED_WIDTH, FIXED_HEIGHT, "Pokemon Rot");
    SetTargetFPS(60);

    font = LoadFont("assets/Pokemon_Classic.ttf");
    background = LoadTexture("assets/background.png");
}

void PokemonApp::cleanup() {
    UnloadTexture(background);
    UnloadFont(font);
    CloseWindow();
}

//
// --- Centrer le texte dans un rectangle ---
void PokemonApp::centerText(const char *text, const Rectangle &rect, int fontSize, Vector2 &pos) {
    Vector2 size = MeasureTextEx(font, text, (float)fontSize, 1.0f);
    pos.x = rect.x + (rect.width - size.x) / 2.0f;
    pos.y = rect.y + (rect.height - size.y) / 2.0f;
}

//
// --- Dessiner un bouton avec effet hover ---
void PokemonApp::drawButton(const Button &btn, const Vector2 &mousePos) {
    bool hovered = CheckCollisionPointRec(mousePos, btn.rect);
    Color colorToUse = hovered ? BUTTON_HOVER : BUTTON_NORMAL;

    // Boîte semi-transparente derriere le bouton
    Color boxColor = {50, 50, 50, 150};
    DrawRectangleRec(btn.rect, boxColor);

    // Rectangle du bouton + bordure
    DrawRectangleRec(btn.rect, colorToUse);
    DrawRectangleLinesEx(btn.rect, 2, BLACK);

    // Ombre du texte
    Vector2 shadowPos = {btn.textPos.x + 1, btn.textPos.y + 1};
    DrawTextEx(font, btn.text.c_str(), shadowPos, 24, 1, TEXT_SHADOW_COLOR);

    // Texte principal
    DrawTextEx(font, btn.text.c_str(), btn.textPos, 24, 1, TEXT_COLOR);
}

//
// --- Fonction utilitaire pour centrer un bloc de texte ligne par ligne ---
void PokemonApp::drawCenteredTextBlock(const char *text, float fontSize, Color color) {
    // 1) Separer le texte en lignes
    std::istringstream iss(text);
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(iss, line, '\n')) {
        lines.push_back(line);
    }

    // 2) Calculer la hauteur totale du bloc
    float spacing = 8.0f; // espace entre lignes
    float totalHeight = 0.0f;

    for (auto &l : lines) {
        Vector2 size = MeasureTextEx(font, l.c_str(), fontSize, 1.0f);
        totalHeight += size.y + spacing;
    }
    totalHeight -= spacing; // retirer le spacing apres la derniere ligne

    // 3) Point de depart Y pour être au centre vertical
    float startY = (FIXED_HEIGHT - totalHeight) / 2.0f;

    // 4) Dessiner chaque ligne au centre horizontal
    float currentY = startY;

    for (auto &l : lines) {
        Vector2 size = MeasureTextEx(font, l.c_str(), fontSize, 1.0f);
        float x = (FIXED_WIDTH - size.x) / 2.0f;
        float y = currentY;

        // Ombre legere
        DrawTextEx(font, l.c_str(), {x + 1, y + 1}, fontSize, 1, TEXT_SHADOW_COLOR);
        // Texte
        DrawTextEx(font, l.c_str(), {x, y}, fontSize, 1, color);

        currentY += size.y + spacing;
    }
}

//
// --- Afficher un ecran de texte + bouton Retour ---
void PokemonApp::displayScreen(const char *text) {
    float btnWidth = FIXED_WIDTH * 0.20f;
    float btnHeight = FIXED_HEIGHT * 0.08f;
    Rectangle backBtn = {(FIXED_WIDTH - btnWidth) / 2.0f,
                         FIXED_HEIGHT * 0.80f, // on descend un peu pour ne pas chevaucher le texte
                         btnWidth,
                         btnHeight};

    const char *backText = "Retour";
    Vector2 backTextPos;
    centerText(backText, backBtn, 24, backTextPos);

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePos, backBtn)) {
                return; // On revient au menu precedent
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(background, Rectangle{0, 0, (float)background.width, (float)background.height}, Rectangle{0, 0, (float)FIXED_WIDTH, (float)FIXED_HEIGHT}, Vector2{0, 0}, 0.0f, WHITE);

        // On dessine le texte (centre ligne par ligne)
        drawCenteredTextBlock(text, 24.0f, TEXT_COLOR);

        // Dessin du bouton Retour
        Button backButton{backBtn, backText, backTextPos};
        drawButton(backButton, mousePos);

        EndDrawing();
    }
}

//
// --- Sous-menu Options ---
void PokemonApp::optionsMenu() {
    float btnWidth = FIXED_WIDTH * 0.25f;
    float btnHeight = FIXED_HEIGHT * 0.08f;
    float centerX = FIXED_WIDTH / 2.0f;
    float startY = FIXED_HEIGHT * 0.3f;
    float gap = FIXED_HEIGHT * 0.15f;

    std::vector<Button> options = {{{0, 0, 0, 0}, "Plein ecran", {}}, {{0, 0, 0, 0}, "Retour", {}}};

    for (int i = 0; i < (int)options.size(); i++) {
        options[i].rect = {centerX - btnWidth / 2.0f, startY + i * gap, btnWidth, btnHeight};
    }

    for (auto &op : options) {
        centerText(op.text.c_str(), op.rect, 24, op.textPos);
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < (int)options.size(); i++) {
                if (CheckCollisionPointRec(mousePos, options[i].rect)) {
                    if (i == 0) {
                        ToggleFullscreen();
                        isFullscreen = !isFullscreen;
                    } else if (i == 1) {
                        return;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(background, Rectangle{0, 0, (float)background.width, (float)background.height}, Rectangle{0, 0, (float)FIXED_WIDTH, (float)FIXED_HEIGHT}, Vector2{0, 0}, 0.0f, WHITE);

        for (auto &op : options) {
            drawButton(op, mousePos);
        }
        EndDrawing();
    }
}

//
// --- Menu principal ---
void PokemonApp::mainMenu() {
    float buttonWidth = FIXED_WIDTH * 0.25f;
    float buttonHeight = FIXED_HEIGHT * 0.08f;
    float centerX = FIXED_WIDTH / 2.0f;
    float startY = FIXED_HEIGHT * 0.30f;
    float gap = FIXED_HEIGHT * 0.10f;

    Button buttons[] = {{{0, 0, 0, 0}, "Jouer", {}}, {{0, 0, 0, 0}, "Options", {}}, {{0, 0, 0, 0}, "Regles", {}}, {{0, 0, 0, 0}, "Credit", {}}, {{0, 0, 0, 0}, "Quitter", {}}};

    for (int i = 0; i < 5; i++) {
        buttons[i].rect = {centerX - buttonWidth / 2.0f, startY + i * gap, buttonWidth, buttonHeight};
    }

    for (auto &b : buttons) {
        centerText(b.text.c_str(), b.rect, 24, b.textPos);
    }

    while (!WindowShouldClose()) {
        Vector2 mousePos = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < 5; i++) {
                if (CheckCollisionPointRec(mousePos, buttons[i].rect)) {
                    if (i == 0) {
                        std::cout << "[INFO] Jouer.\n";
                    } else if (i == 1) {
                        optionsMenu();
                    } else if (i == 2) {
                        // Regles
                        displayScreen("Regles du jeu:\n\n- Attrapez des Pokemon !\n- Entrainez-les !\n- Combattez !");
                    } else if (i == 3) {
                        // Credits
                        displayScreen("Credits:\n\nEliot Gourdoux\n\nMerci d'avoir joue !");
                    } else if (i == 4) {
                        return;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(background, Rectangle{0, 0, (float)background.width, (float)background.height}, Rectangle{0, 0, (float)FIXED_WIDTH, (float)FIXED_HEIGHT}, Vector2{0, 0}, 0.0f, WHITE);

        for (auto &b : buttons) {
            drawButton(b, mousePos);
        }
        EndDrawing();
    }
}
