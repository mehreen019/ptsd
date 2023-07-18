#pragma once


class Menu {
    int pos;
    int abpos;
    bool pressed, theselect;

    sf::RenderWindow* window;
    sf::RectangleShape* winclose;
    
    sf::Texture* image;
    sf::Sprite* bg;

    sf::Vector2i pos_mouse;
    sf::Vector2f mouse_coord;

    std::vector<const char*> options;
    std::vector<sf::Vector2f> coords;
    std::vector<sf::Text> texts;
    std::vector<std::size_t> sizes;

    std::vector<const char*> abops;
    std::vector<sf::Vector2f> abcoords;
    std::vector<sf::Text> abtexts;
    std::vector<std::size_t> absizes;

protected:
    void set_values();
    void loop_events();
    void draw_all();

public:
    sf::Font* font;
    sf::Text about;
    bool abouttext;

    bool winrun;
    Menu();
    ~Menu();
    void run_menu();
};