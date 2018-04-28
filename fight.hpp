#define DefaultVideoWidth 1920
#define DefaultVideoHeight 1080
#define DefaultHeroXPos -439
#define DefaultHeroYPos 1080
#define DefaultEnemyXPos 2359
#define DefaultEnemyYPos 1080
#define TalkTime 1

class Card
{
private:
    int hp;

public:
    const char *txtrFilename;
    const int attack[5][2];
    const int defense;

    sf::Sprite sprite;
    sf::Texture texture;

    void defaultAttack();
    void the1stAttack();
    void the2ndAttack();
    void the3rdAttack();
    void the4thAttack();
    bool recieve_dmg(int damage);
    bool IsAlive();

};

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

class Background : public sf::Drawable
{
private:
    sf::Sprite sprite;
    sf::Texture texture;
    
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(sprite, states);
    }

public:
    Background(const char *Filename, const sf::Vector2f resize_vector)
    {
        texture.loadFromFile(Filename);
        texture.setSmooth(true);
//        texture.setRepeated(true);
        sprite.setTexture(texture);
        sprite.setScale(resize_vector);
    }
};

class FightScene : public sf::Drawable
{
public:
    sf::Vector2f resize_vector;

    FightScene(sf::VideoMode &VM)
    {
        resize_vector = sf::Vector2f((float)VM.width/DefaultVideoWidth, 
                (float)VM.height/DefaultVideoHeight);
    }

    FightScene(sf::VideoMode &VM, Background *bckgnd)
        :background(bckgnd)
    {
        resize_vector = sf::Vector2f((float)VM.width/DefaultVideoWidth, 
                (float)VM.height/DefaultVideoHeight);
    }

//    void setHero(char *TxtrFilename/*, std::vector<Card> &deck*/)
//    {
//        m_Hero.texture.loadFromFile(TxtrFilename);
//        m_Hero.texture.setSmooth(true);
//        m_Hero.sprite.setTexture(m_Hero.texture);
//        m_Hero.sprite.setScale(resize_vector);
//        m_Hero.sprite.setOrigin(m_Hero.texture.getSize().x, m_Hero.texture.getSize().y);
//        m_Hero.sprite.setPosition(m_VideoMode.width, m_VideoMode.height);
//    }
//
//    void setBackground(const char *Filename)
//    {
//        background.texture.loadFromFile(Filename);
//        background.texture.setSmooth(true);
//        texture.setRepeated(true);
//        background.sprite.setTexture(background.texture);
//        background.sprite.setScale(resize_vector);
//    }

//private:
//    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
//    {
        // You can draw other high-level objects
//        target.draw(background.sprite, states);
//        target.draw(m_Hero.sprite, states);
        // ... or use the low-level API
//        states.texture = &background.texture;
//        target.draw(m_vertices, states);
//    }

    Background *background;
//    Hero &m_Hero;
//    NPC &Enemy;// enemy may be single Bokemon or npc-player
//    Bokemon &my_Bokemon;
//    Bokemon &enemy_Bokemon;
//    Menu menu;
//    sf::VideoMode m_VideoMode;
    
//    sf::VertexArray m_vertices;

};
