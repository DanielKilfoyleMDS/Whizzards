#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class cControlMenu {
public:
    cControlMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    std::vector<int> scores;
    sf::Font font;
    sf::Text title;
    sf::Text player1Controls;
    sf::Text player2Controls;
    sf::RectangleShape controlSquare;
    sf::Text menu[1]; // Single "Back" option to return to the main menu
    sf::Text scoreTexts[5]; // Display top 5 scores
    int selectedItemIndex;

    static const int MAX_SCORES = 5;

    sf::Texture backgroundTexture;  // Background texture
    sf::Sprite backgroundSprite;    // Background sprite
};