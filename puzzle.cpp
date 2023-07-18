#include "stdx.h"
#include"puzzle.h"

puzzle::puzzle() {

}

puzzle::~puzzle() {

}

bool puzzle::npuzzle(bool win)
{
    srand(static_cast<unsigned>(time(0)));
    bool win2 = false;

    //15 puzzle win bg
    if(win==true){
    sf::Texture bgtext;
    bgtext.loadFromFile("images/map.png");
    sf::Sprite bg;
    bg.setTexture(bgtext);

    sf::Texture swordText;
    if (!swordText.loadFromFile("keyy.png"))
    {
        std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD sword" << "\n";
    }
    sf::Sprite sword;
    sword.setTexture(swordText);
    sword.setPosition(600, 350);
    sword.setScale(0.7f, 0.7f);

    //15puzzle window
    sf::RenderWindow app(sf::VideoMode(1280, 720), "Puzzle!");
    app.setPosition(sf::Vector2i(300, 100));
    app.setFramerateLimit(60);

    sf::Texture t;
    t.loadFromFile("Textures/15.png");

    //15 puzzle win text
    sf::Font font;
    sf::Text guiText;
    sf::Text endGameText;

    if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
    {
        std::cout << " ! ERROR::GAME::INITFONTS::COULD NOT LOAD PixellettersFull.ttf" << "\n";
    }
    guiText.setFont(font);
    guiText.setFillColor(sf::Color::White);
    guiText.setCharacterSize(25);
    guiText.setStyle(sf::Text::Bold);
    guiText.setOutlineThickness(1);
    guiText.setString(" CONGRATULATIONS!\n YOU HAVE OBTAINED THE KEY!\nYOU CAN USE THIS TO ESCAPE THE HOUSE!\n TO CONTINUE,\n PRESS ESC!\n");
    guiText.setPosition(300.f, 100.f);
    guiText.setScale(1.5f, 1.5f);

    //15 puzzle code
    int w = 64;
    int grid[6][6] = { 0 };
    sf::Sprite sprite[20];

    sf::Color color = sf::Color(sf::Color::Black);

    int n = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
            n++;
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(sf::IntRect(i * w, j * w, w, w));
            grid[i + 1][j + 1] = n;
        }
    int g1 = grid[2][3], g2 = grid[3][3], g3 = grid[2][4];

    grid[2][4] = g2;
    grid[3][3] = g1;
    grid[2][3] = g3;
    while (app.isOpen())
    {
        sf::Event e;
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed) 
            {
                app.close();
                return win2 = false;
            }
            if (sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::Escape)
                    app.close();
            }
            if (e.type == sf::Event::MouseButtonPressed)
                if (e.key.code == sf::Mouse::Left && !win2)
                {
                    sf::Vector2i pos = sf::Mouse::getPosition(app);
                    int x = pos.x / w + 1;
                    int y = pos.y / w + 1;

                    int dx = 0;
                    int dy = 0;

                    if (grid[x + 1][y] == 16) { dx = 1; dy = 0; };
                    if (grid[x][y + 1] == 16) { dx = 0; dy = 1; };
                    if (grid[x][y - 1] == 16) { dx = 0; dy = -1; };
                    if (grid[x - 1][y] == 16) { dx = -1; dy = 0; };

                    int n = grid[x][y];
                    grid[x][y] = 16;
                    grid[x + dx][y + dy] = n;

                    //animation
                    sprite[16].move(-dx * w, -dy * w);
                    float speed = 3;

                    for (int i = 0; i < w; i += speed)
                    {
                        sprite[n].move(speed * dx, speed * dy);
                        app.draw(sprite[16]);
                        app.draw(sprite[n]);
                        app.display();
                    }
                }
            int cnt = 0;
            int nn = 1;
            for (int i = 1; i <= 4; i++)
            {
                for (int j = 1; j <= 4; j++)
                {
                    if (grid[i][j] == nn) cnt++;
                    nn++;
                }
                if (cnt == 16)
                {
                    win2 = true;
                    //app.close();
                    break;

                }
            }
            //if (win) break;
        }


        //15 puzzle win bg render
        app.clear(color);
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
            {
                int n = grid[i + 1][j + 1];
                sprite[n].setPosition((i * w), (j * w));
                app.draw(sprite[n]);
            }

        if (win2)
        {
            app.setPosition(sf::Vector2i(300.f, 100.f));
            app.setSize(sf::Vector2u(1280, 720));
            app.clear(color);
            app.draw(bg);
            app.draw(sword);
            app.draw(guiText);
          
        }
        app.display();
    }
}

    return win2;
}

bool puzzle::wordpuzzle() {
    //3rd

    bool win = false;
    bool next = false;
    //text game window
    {
        
        sf::RenderWindow window(sf::VideoMode(1280, 720), "Riddle Game");
        window.setPosition(sf::Vector2i(300, 100));

        //text game q&a font
        sf::Font font;
        if (!font.loadFromFile("Fonts/PixellettersFull.ttf")) {
            std::cout << "Font loading failed!" << std::endl;
        }

        sf::Text question;
        question.setFont(font);
        question.setCharacterSize(50);
        question.setOutlineThickness(0.5f);
        question.setStyle(sf::Text::Bold);
        question.setOutlineColor(sf::Color::Black);
        question.setPosition(100, 100);
        question.setFillColor(sf::Color::White);

        sf::Text answer;
        //sf::Color color = sf::Color(110.f, 18.f, 18.f, 1.f);
        answer.setFont(font);
        answer.setCharacterSize(50);
        answer.setPosition(100, 300);
        answer.setFillColor(sf::Color::White);
        sf::Texture texture;
        if (!texture.loadFromFile("images/map.png"))
        {
            throw("error");
        }
        sf::Sprite sprite;
        sprite.setTexture(texture);
        // sprite.setTextureRect(sf::IntRect(0, 0, 800, 800));

        std::string currentAnswer;
        std::string currentQuestion;

        // Game loop
        question.setString("Are you ready for the riddles??\nSolve these to proceed\n(Click anywhere to continue)");
        bool wonWordPuzzle = false;
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return win = false;
                }
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                        return win = false;
                    }
                    if (event.key.code == sf::Keyboard::F && next) {
                        window.close();
                        return win = true;
                    }
                }
               else if (event.type == sf::Event::MouseButtonPressed && wonWordPuzzle ==  false)
                {
                    answer.setString("I am taken from a mine, and shut up in a wooden case,\nfrom which I am never released.\n Yet, I am used by almost every person. What am I?");
                    wonWordPuzzle = true;
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                        currentAnswer += static_cast<char>(event.text.unicode);
                        std::transform(currentAnswer.begin(), currentAnswer.end(), currentAnswer.begin(), ::tolower);
                        answer.setString(currentAnswer);
                    }
                    else if (event.text.unicode == 8 && currentAnswer.size() > 0) {
                        currentAnswer.pop_back();
                        answer.setString(currentAnswer);
                    }
                    else if (event.text.unicode == 13) {  // Enter key
                        // Check if the answer is correct

                        if (currentAnswer == "pencil lead") {
                            currentQuestion = "I am an odd number. Take away one letter,\nand I become even. What number am I?";
                            currentAnswer = "";
                        }
                        else if (currentAnswer == "seven") {
                            currentQuestion = "I am a word of letters three;\nadd two, and fewer there will be. What word am I?";
                            currentAnswer = "";
                        }
                        else if (currentAnswer == "few") {
                            currentQuestion = "Congratulations! You solved all the riddles!\nPress F to continue!";
                            currentAnswer = "";
                             next = true;
                             wonWordPuzzle = true;
                        } 
                        else {
                            currentQuestion = "Wrong answer! Try again.";
                            currentAnswer = "";
                        }

                        question.setString(currentQuestion);
                    }
                }

            }

            window.clear();
            window.draw(sprite);
            window.draw(question);
            window.draw(answer);
            window.display();
        }
        window.close();


    }

}

