#include <SFML/Graphics.hpp>

class cMenu {
public:
    cMenu(float width, float height);

    void draw(sf::RenderWindow& window);

    void MoveUp();
    void MoveDown();

    int GetPressedItem();

private:
    int selectedItemIndex;
    sf::Font font;
    sf::Text menu[2];

    static const int MAX_NUMBER_OF_ITEMS = 2;
};