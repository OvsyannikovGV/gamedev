#define DefaultVideoWidth 1920
#define DefaultVideoHeight 1080
#define DefaultHeroXPos -439
#define DefaultHeroYPos 1080
#define DefaultEnemyXPos 2359
#define DefaultEnemyYPos 1080
#define TalkTime 1

class Hero : public sf::Drawable
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite cloudsprite;
    sf::Texture cloudtexture;
    std::vector<Card> Deck;
    float velocity;
    int ActNum = 0;
    float timeDifference = 0;
    sf::Font font;
    sf::Text text;
//    sf::VertexArray lines;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
        target.draw(cloudsprite, states);
        target.draw(text, states);
    }

public:

    Hero(const char *Filename, const sf::Vector2f resize_vector)
//        : lines(sf::TriangleStrip, 7)
    {
        texture.loadFromFile(Filename);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setScale(resize_vector);
        sprite.setOrigin(0, texture.getSize().y);
        sprite.setPosition(DefaultHeroXPos*resize_vector.x, DefaultHeroYPos*resize_vector.y);


        cloudtexture.loadFromFile("test/cloud.png");
        cloudtexture.setSmooth(true);
        cloudsprite.setTexture(cloudtexture);
        cloudsprite.setScale( 0, 0 );
        cloudsprite.setPosition( 400, 400 );
        if (!font.loadFromFile("Summer Love.ttf"))
        {
            // error...
        }
        // select the font
        text.setFont(font); // font is a sf::Font
        // set the string to display
        text.setString("I will fight\n\nthe honour");
        // set the character size
        text.setCharacterSize(24); // in pixels, not points!
        // set the color
        text.setFillColor(sf::Color::Transparent);
        text.setPosition(450, 450);
        // set the text style
//        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }

    bool Action(float time)
    {
        switch (ActNum)
        {
        case 0:     //..appearing
            if (sprite.getPosition().x > 0)
            {
                ActNum = 1;
                return true;
            }
            sprite.move(1000*time, 0);
            return false;
        case 1:     //..waiting for npc appearing
            return true;
        case 2:     //..talking
            timeDifference += time;
            if (timeDifference > TalkTime)
            {
                cloudsprite.setScale( 0, 0 );
                text.setFillColor(sf::Color::Transparent);
                ActNum = 3;
                return true;
            }
            return false;
        case 3:     //..waiting for npc talk
            return true;
        case 4:     //..disappearing
            if (sprite.getPosition().x < DefaultHeroXPos)
            {
                ActNum = 5;
                return true;
            }
            sprite.move(-1000*time, 0);
            return false;
        case 5:     //..waiting for npc disappearing
            return true;
        }


        return false;
    }

    bool ChangeAction()
    {
        ActNum++;
        if (ActNum == 2)
        {
            cloudsprite.setScale( 1, 1 );
            text.setFillColor(sf::Color::Black);
        }
        if (ActNum > 5)
            return true;
        return false;
    }
};
