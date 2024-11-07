#include <SFML/Graphics.hpp>

class cMenu {
public:
    cMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    static const int MAX_NUMBER_OF_ITEMS = 3;  // Updated for "Scores" option
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    sf::Text title;
    sf::Texture backgroundTexture;  // Background texture
    sf::Sprite backgroundSprite;    // Background sprite
};