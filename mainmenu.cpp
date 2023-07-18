#include "stdx.h"
#include "mainmenu.h"

Menu::Menu() {
    window = new sf::RenderWindow();
    winclose = new sf::RectangleShape();
    font = new sf::Font();
    image = new sf::Texture();
    bg = new sf::Sprite();

    set_values();
}

Menu::~Menu() {
    delete window;
    delete winclose;
    delete font;
    delete image;
    delete bg;
}

void Menu::set_values() {
    window->create(sf::VideoMode(1280, 720), "Menu", sf::Style::Titlebar | sf::Style::Close);
    window->setPosition(sf::Vector2i(300, 100));

    pos = 0;
    abpos = 1;
    pressed = theselect = false;
    font->loadFromFile("HelpMe.otf");
    image->loadFromFile("background.jpg");
    bg->setTexture(*image);
    about.setFont(*font);
    about.setFillColor(sf::Color::White);
    about.setString("PTSD is a short\nhorror escape  game");
   // about.setOutlineThickness(1);
    about.setCharacterSize(40);
    about.setPosition(400, 300);
    abouttext = false;

    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };

    options = { "PTSD","Play","About" ,"Quit" };
    texts.resize(4);
    coords = { {590,40},{590,191} ,{590,282} ,{600,370} };
// {623,457} };
    sizes = { 40,32,32,32 }; 
    //24,24 };

    abops = { "PTSD is a short horror escape  game\nPress WSAD to move your character\nUse cursor to interact with puzzle\nEscape the house if you can!", "Back"};
    abtexts.resize(2);
    abcoords = { {200,200},{500,550} };
    absizes = { 40,32 };

    for (std::size_t i{}; i < texts.size(); ++i) {
        texts[i].setFont(*font);
        texts[i].setString(options[i]);
        texts[i].setCharacterSize(sizes[i]);
        texts[i].setOutlineColor(sf::Color::Black);
        texts[i].setPosition(coords[i]);
    }

    texts[1].setOutlineThickness(4);
    pos = 1;

    for (std::size_t i{}; i < abtexts.size(); ++i) {
        abtexts[i].setFont(*font);
        abtexts[i].setString(abops[i]);
        abtexts[i].setCharacterSize(absizes[i]);
        abtexts[i].setOutlineColor(sf::Color::Black);
        abtexts[i].setPosition(abcoords[i]);
    }

    abtexts[1].setOutlineThickness(4);
   // abpos = 1;

}

void Menu::loop_events() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            this->winrun = false;
        }

        pos_mouse = sf::Mouse::getPosition(*window);
        mouse_coord = window->mapPixelToCoords(pos_mouse);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed) {
            if (pos < 3) {
                ++pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos - 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed) {
            if (pos > 1) {
                --pos;
                pressed = true;
                texts[pos].setOutlineThickness(4);
                texts[pos + 1].setOutlineThickness(0);
                pressed = false;
                theselect = false;

            }
        }
   
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            theselect = true;
            if (pos == 1) {
                window->close();
                this->winrun = true;
            }
            else if(pos==3){
                //this->game.window->close();
                window->close();
                this->winrun = false;
            }
            else if (!abouttext && pos == 2 ) {
                abouttext = true;
                //pressed == true;
            }
            else if (abouttext && abpos == 1) {
                abouttext = false;   
            }
            
            
            //std::cout << " "<< options[pos] << '\n';
        }
    
}


void Menu::draw_all() {
    window->clear();
    window->draw(*bg);
    if (!abouttext) {
        for (auto t : texts) {
            window->draw(t);
        }
    }
    else if (abouttext) { 
        //window->draw(about);
        for (auto t : abtexts) {
            window->draw(t);
        }
    }
    window->display();
}

void Menu::run_menu() {
    while (window->isOpen()) {
        loop_events();
        draw_all();
       
    }
}