
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

sf::RenderWindow* Window = nullptr;

template <typename T>
struct Vector
    {
    T x, y;

    Vector() : x (0), y (0) {}

    template <typename U1, typename U2>
    Vector (U1 anX, U2 anY) : x ((T) anX), y ((T) anY) {}

    template <typename U>
    Vector (const Vector <U>& vec) : x ((T) vec.x), y ((T) vec.y) {}

    template <typename U>
    Vector (const sf::Vector2 <U>& vec) : x ((T) vec.x), y ((T) vec.y) {}
    };

using Vec = Vector <float>;

struct Hero
    {
    Vec pos_;
    Vec v_;
    Vec size_;

    float m_;
    float friction_;
    float rotation_;

    sf::Sprite sprite_;

    Hero() :
        pos_      (Vec()),
        v_        (Vec()),
        size_     (Vec()),
        m_        (0),
        friction_ (0),
        rotation_ (0),
        sprite_   (sf::Sprite())
        {
        auto bounds = sprite_.getLocalBounds();
        size_.x = bounds.width;
        size_.y = bounds.height;
        }

    Hero (const Vec& pos, const Vec& v, float m = 0, float friction = 0, float rotation = 0,
          sf::Sprite sprite = sf::Sprite()) :
        pos_      (pos),
        v_        (v),
        size_     (Vec()),
        m_        (m),
        friction_ (friction),
        rotation_ (rotation),
        sprite_   (sprite)
        {
        auto bounds = sprite_.getLocalBounds();
        size_.x = bounds.width;
        size_.y = bounds.height;
        }

    void draw (sf::RenderTarget* screen = Window) const;
    void draw (Vec pos, sf::RenderTarget* screen = Window) const;
    bool doPhysics (Vec sz, float dt);
    void control();
    };

void RunGame();
void DoRender (const Hero& death, const Hero& vader, int lives, const std::vector <Hero>& stars);
int  DoIntersection (Hero* death, const Hero* vader);
void GenStars (Hero stars[], size_t n, const Vector <int>& sz);

void DrawCircle (Vec pos, float radius,
                 sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Transparent,
                 sf::RenderTarget* screen = Window);

inline float sqr (float val) { return val * val; }

int main()
    {
    sf::RenderWindow window (sf::VideoMode (1100, 650), __FILE__, sf::Style::Default & ~sf::Style::Resize);

    window.setVerticalSyncEnabled (true);
    window.setFramerateLimit (25);

    Window = &window;
    
    RunGame();

    return 0;
    }

void RunGame()
    {
    auto sz = Window->getSize();
    
    sf::Texture deathTex;
    if (!deathTex.loadFromFile ("death.png")) return;
    deathTex.setSmooth (true); 
    
    sf::Texture vaderTex;
    if (!vaderTex.loadFromFile ("vader.png")) return;
    vaderTex.setSmooth (true); 

    sf::Music music;
    if (!music.openFromFile    ("vader.wav")) return;
    music.setLoop (true);
    music.play();

    Hero death (Vec (    70,       70), Vec (300, 450), 0.033f, 0.0f, 5, sf::Sprite (deathTex));
    Hero vader (Vec (sz.x/2, sz.y*0.9), Vec (  0,   0), 0.003f, 0.2f, 0, sf::Sprite (vaderTex));
    int lives = 10;

    std::vector <Hero> stars (100);
    GenStars (stars.data(), stars.size(), sz);

    sf::Clock clock;

    for (;;)
        {
        float time = clock.restart().asSeconds();

        sf::Event event;
        while (Window->pollEvent (event)) if (event.type == sf::Event::Closed) break;
            
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)) break;
        
        if (!Window->isOpen()) break;

        DoRender (death, vader, lives, stars);

        if (death.pos_.y + death.size_.y/2.0 >= sz.y) { death.pos_ = death.size_; lives--; }
        if (lives <= 0) break;

        vader.control();

        DoIntersection (&death, &vader);

        death.doPhysics (sz, time);
        vader.doPhysics (sz, time);
        
        vader.pos_.x = (float) ( ((int) vader.pos_.x + sz.x) % sz.x );

        for (auto& star : stars)
            if (star.doPhysics (sz, time))
                GenStars (&star, 1, sz);
        }

    sf::RenderTexture tex;
    tex.create (sz.x, sz.y);
    tex.clear();

    sf::Sprite texSprite (tex.getTexture());
    texSprite.setOrigin (0, (float) sz.y);
    texSprite.setScale (1, -1);
    
    for (size_t n = 0; n < 200; n++)
        {
        sf::Event event;
        while (Window->pollEvent (event)) if (event.type == sf::Event::Closed) break;
            
        if (sf::Keyboard::isKeyPressed (sf::Keyboard::Escape)) break;

        for (int i = 0; i < 10; i++) vader.draw (Vec (rand() % sz.x, rand() % sz.y), &tex);

        Window->clear();
        Window->draw (texSprite);
        Window->display();
        }
        
    Window->close();
    }

void DoRender (const Hero& death, const Hero& vader, int lives, const std::vector <Hero>& stars)
    {
    Window->clear();

    for (const auto& star : stars) star.draw();

    death.draw();
    vader.draw();

    for (int i = 0; i < lives; i++) vader.draw (Vec ((i + 1.0) * vader.size_.x, vader.size_.y/2));
    
    Window->display();
    }

void Hero::draw (sf::RenderTarget* screen) const
    {
    if (sprite_.getTexture())
        screen->draw (sprite_);

    else
        DrawCircle (pos_, 2, sf::Color::White, sf::Color::Transparent, screen);
    }

void Hero::draw (Vec pos, sf::RenderTarget* screen) const
    {
    if (sprite_.getTexture())
        {
        sf::Sprite sprite = sprite_;

        sprite.setOrigin   (size_.x/2, size_.y/2);
        sprite.setPosition (pos.x, pos.y);
        screen->draw (sprite);
        }

    else
        DrawCircle (pos_, 2, sf::Color::White, sf::Color::Transparent, screen);
    }

bool Hero::doPhysics (Vec sz, float dt)
    {
    bool bounce = false;

    if (pos_.x - size_.x/2 <= 0 || pos_.x + size_.x/2 >= sz.x) { v_.x *= -1; bounce = true; }
    if (pos_.y - size_.y/2 <= 0 || pos_.y + size_.y/2 >= sz.y) { v_.y *= -1; bounce = true; }
    
    v_.x *= (1 - friction_);
    v_.y *= (1 - friction_);

    pos_.x += v_.x * dt;
    pos_.y += v_.y * dt;

    sprite_.setOrigin   (size_.x/2, size_.y/2);
    sprite_.setPosition (pos_.x, pos_.y);
    sprite_.rotate      (rotation_);

    return bounce;
    }

void Hero::control()
    {
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))  v_.x -= 1 / m_;
    if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right)) v_.x += 1 / m_;
    }

int DoIntersection (Hero* death, const Hero* vader)
    {
    Vec d (death->pos_.x - vader->pos_.x,
           death->pos_.y - vader->pos_.y);

    if (sqr (d.x) + sqr (d.y) > sqr (vader->size_.y/2 + death->size_.y/2))
        return 0;

    if (d.y > fabs (d.x) * 2)
        {
        if (death->v_.y > 0) death->v_.y *= -1;
        return 'V';
        }

    if (d.x > fabs (d.y) / 2)
        {
        if (death->v_.y > 0) death->v_.y *= -1;
        if (death->v_.x > 0) death->v_.x *= -1;
        return '>';
        }

    if (d.x < fabs (d.y) / 2)
        {
        if (death->v_.y > 0) death->v_.y *= -1;
        if (death->v_.x < 0) death->v_.x *= -1;
        return '<';
        }

    return '?';
    }

void GenStars (Hero stars[], size_t n, const Vector <int>& sz)
    {
    for (size_t i = 0; i < n; i++)
        {
        Vec pos (rand() % sz.x, rand() % (int) sz.y);
        stars[i] = Hero (pos, Vec ((pos.x - sz.x/2.0) / 3, (pos.y - sz.y/2.0) / 3));
        }
    }

void DrawCircle (Vec pos, float radius, sf::Color fillColor, sf::Color outlineColor, sf::RenderTarget* screen)
    {    
    sf::CircleShape circle;

    circle.setRadius (radius);
    circle.setFillColor (fillColor);
    circle.setOutlineColor (outlineColor);
    if (outlineColor != sf::Color::Transparent) circle.setOutlineThickness (3);
    
    circle.setOrigin (radius, radius);
    circle.setPosition (pos.x, pos.y);
    
    screen->draw (circle);
    }

