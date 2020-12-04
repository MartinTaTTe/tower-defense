#pragma once

#include "../enemies/enemy.hpp"
#include "../gui/button.hpp"
#include <vector>

class Tower: public Button {
public:
    Tower(const Vector4f& vector,int x, int y, int price, float damage, float speed, float range, int enemy_type, bool tile_type, const std::string& texturePath = T_DEFAULT_TOWER); 

    
    int                 GetPrice() const;
    float               GetSize() const;
    float               GetSpeed() const;
    int                 GetUpgrade() const;
    float               GetRange();
    int                 MoneyFromWave() const;
    bool                CanBeUpgraded() const;
    virtual void        Update(std::vector<Enemy*>& enemies);
    virtual void        Upgrade() = 0;
    virtual             ~Tower(){};
protected:
    int                 x_;
    int                 y_;
    void                Attack(Enemy* target) const;
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









    
