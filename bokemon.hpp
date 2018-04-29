#define DefaultVideoWidth 1920
#define DefaultVideoHeight 1080

class Card
{
private:
    int hp;

public:
//    const int attack[5][2];
//    const int defense;

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
