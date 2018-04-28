#define DefaultVideoWidth 1920
#define DefaultVideoHeight 1080
#define DefaultHeroXPos -439
#define DefaultHeroYPos 1080
#define DefaultEnemyXPos 2359
#define DefaultEnemyYPos 1080
#define TalkTime 1

class NPC : public sf::Drawable
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Sprite cloudsprite;
    sf::Texture cloudtexture;
    std::vector<Card> Deck;
    int ActNum = 0;
    sf::Vector2f resize_vector;
    float timeDifference = 0;
    sf::Font font;
    sf::Text text;

    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
        target.draw(cloudsprite, states);
        target.draw(text, states);
    }
public:

    NPC(const char *Filename, const sf::Vector2f resize_vector_)
        :resize_vector(resize_vector_)
    {
        texture.loadFromFile(Filename);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setScale(resize_vector);
        sprite.setOrigin(texture.getSize().x, texture.getSize().y);
        sprite.setPosition(DefaultEnemyXPos*resize_vector.x, DefaultEnemyYPos*resize_vector.y);


        cloudtexture.loadFromFile("test/cloud.png");
        cloudtexture.setSmooth(true);
        cloudsprite.setTexture(cloudtexture);
        cloudsprite.setScale( 0, 0 );
        cloudsprite.setPosition( 1500, 400 );
        if (!font.loadFromFile("Summer Love.ttf"))
        {
            // error...
        }
        // select the font
        text.setFont(font); // font is a sf::Font
        // set the string to display
        text.setString("Hello world");
        // set the character size
        text.setCharacterSize(24); // in pixels, not points!
        // set the color
        text.setFillColor(sf::Color::Transparent);
        text.setPosition(1150, 450);

    }

    bool Action(float time)
    {
        switch (ActNum)
        {
        case 0:     //..appear
            if (sprite.getPosition().x < DefaultVideoWidth*resize_vector.x)
            {
                ActNum = 1;
                return true;
            }
            sprite.move(-1000*time, 0);
            return false;
        case 1:     //.. talking
            if (timeDifference == 0)
            {
                cloudsprite.setScale( -1, 1 );
                text.setFillColor(sf::Color::Black);
            }
            timeDifference += time;
            if (timeDifference > TalkTime)
            {
                cloudsprite.setScale( 0, 0 );
                text.setFillColor(sf::Color::Transparent);
                ActNum = 2;
                return true;
            }
            return false;
        case 2:     //..npc disappearing
            if (sprite.getPosition().x > DefaultEnemyXPos*resize_vector.x)
            {
                ActNum = 3;
                return true;
            }
            sprite.move(1000*time, 0);
            return false;
        case 3:
            return true;
        }

        return false;
    }
};
