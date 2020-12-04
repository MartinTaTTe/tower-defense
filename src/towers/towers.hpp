#pragma once

#include "../enemies/enemy.hpp"
#include "../gui/button.hpp"

class Tower: public Button {
public:
    Tower( int price, float damage, int x_coord, int y_coord, float size, float speed, float range, int enemy_type, bool tile_type, const std::string& texturePath = T_DEFAULT_TOWER); 

    bool                Attack(Enemy& enemy) const;
    
    int                 GetPrice() const;
    float               GetDamage() const;
    const std::pair<int, int> GetCoords() const;
    float               GetSize() const;
    float               GetSpeed() const;
    int                 GetUpgrade() const;
    int                 GetUpgradePrice() const;
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
protected:
    bool                CanStillAttack();
    int                 upgrade_max_;
    int                 upgrade_;
    float               range_;
    float               damage_;
    float               speed_;
    int                 upgrade_price_;
    int                 money_from_wave_;
    int                 enemy_type_; //vilken sort av fiender kan den attackera(1 = land, 2 = vatten, 3= båda, 4 = ingen(utility))
    bool                tile_type_; //vilken sort av "underlag" -> true = land, false = hav
    Enemy*              target_;
 
 
private:
    int                 price_;
    bool                active_;
    sf::CircleShape     radius_;
};









    
