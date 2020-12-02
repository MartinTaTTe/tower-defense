#pragma once
#include <SFML/Graphics.hpp>

#include "../enemies/enemy.hpp"
#include "../gui/button.hpp"

class Tower: public Button {
public:
    Tower( int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type, bool tile_type, const std::string& texturePath = "basic.png"); 

    bool                Attack(Enemy& enemy) const;
    
    int                 GetPrice() const;
    float               GetDamage() const;
    const std::pair<int, int> GetCoords() const;
    float               GetSize() const;
    float               GetSpeed() const;
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
    int                 upgrade_max_;
    int                 upgrade_;
    float               range_;
    float               damage_;
    float               speed_;
    int                 upgrade_price_;
    int                 money_from_wave_;
    int                 x_coord_;
    int                 y_coord_;
    sf::Sprite          sprite_; 
    sf::Texture         texture_;
    int                 enemy_type_; //vilken sort av fiender kan den attackera(1 = land, 2 = vatten, 3= båda, 4 = ingen(utility))
    bool                tile_type_; //vilken sort av "underlag" -> true = land, false = hav
 
 
private:
    int                 price_;

    float               size_;
    std::string         texturePath_;
    bool                active_;
    float               prewious_attack_;

    sf::CircleShape     radius_;
    bool                active_;
};









    
