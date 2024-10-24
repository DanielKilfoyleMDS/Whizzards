#include <SFML/Graphics.hpp>

class cPauseMenu {
public:
    cPauseMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[2];  // Resume and Quit buttons

    static const int MAX_NUMBER_OF_ITEMS = 2;
};