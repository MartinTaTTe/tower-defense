#pragma once
#include <SFML/Graphics.hpp>

#include "../enemies/enemy.hpp"

class Tower {
public:
    Tower( int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texture = "basic.png"); 

    bool                Attack(Enemy& enemy) const;
    
    int                 GetPrice() const;
    float               GetDamage() const;
    const std::pair<int, int> GetCoords() const;
    float               GetSize() const;
    float               GetSpeed() const;
    sf::Texture&        GetTexture() const;
    int                 GetUpgrade() const;
    int                 GetUpgradePrice() const;
    sf::Sprite*         GetSprite();
    float               GetRange();

    int                 MoneyFromWave() const;

    void                SetPosition(float xCoord, float yCoord);
    void                SetScale(float size); //Från tile
    void                SetActive();
    void                SetNotActive();

    bool                IsActive() const;
    bool                CanBeUpgraded() const;

    virtual void        Upgrade() = 0;
    virtual             ~Tower(){};
    void                Draw(sf::RenderWindow& window);
protected:
    int                 _upgrade_max;
    int                 _upgrade;
    float               _range;
    float               _damage;
    float               _speed;
    int                 _upgrade_price;
    int                 _money_from_wave;
 
private:
    int                 _price;
    float               _damage;
    int                 _x_coord;
    int                 _y_coord;
    float               _size;
    float               _speed;
    std::string         _texture;
    bool                _active;
    float               _prewious_attack;
    sf::Sprite           _sprite; 
    sf::CircleShape     _radius;
    bool                _active;
};









    
