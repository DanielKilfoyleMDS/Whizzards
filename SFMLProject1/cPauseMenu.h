#include <SFML/Graphics.hpp>

class cPauseMenu {
public:
    cPauseMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    sf::Font font;
    sf::Text menu[2];
    sf::Text title; 
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    int selectedItemIndex;
    const int MAX_NUMBER_OF_ITEMS = 2;
};