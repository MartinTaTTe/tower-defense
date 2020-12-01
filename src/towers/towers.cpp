#include "towers.hpp"
#include "../game/texture_manager.hpp"

    Tower::Tower( int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texturePath):
    price_(price), 
    damage_(damage), 
    x_coord_(x_coord), 
    y_coord_(y_coord), 
    size_(size),
    speed_(speed),
    range_(range),
    texturePath_(texturePath),
    prewious_attack_(0),
    upgrade_(1),
    money_from_wave_(0){
        texture_ = GetTexture(texturePath_);
        texture_.setSmooth(true);
        sprite_ = sf::Sprite(texture_);
       
        radius_.setRadius(range);
        radius_.setFillColor(sf::Color::Transparent);
        radius_.setOutlineThickness(10);
        radius_.setOutlineColor(sf::Color::Red);
    }

    bool Tower::Attack(Enemy& enemy) const{
        enemy.SetHp(enemy.GetHp - damage_);
    }
    
    int Tower::GetPrice() const{
        return price_;
    }
    float Tower::GetDamage() const{
        return damage_;
    }
    const std::pair<int, int> Tower::GetCoords() const{
        return {x_coord_, y_coord_};
    }
    float Tower::GetSize() const{
        return size_;
    }
    float Tower::GetSpeed() const{
        return speed_;
    }
  
    int Tower::GetUpgrade() const{
        return upgrade_;
    }
    int Tower::GetUpgradePrice() const{
        return upgrade_price_;
    }
    sf::Sprite* Tower::GetSprite(){
        return &sprite_;
    }
    float Tower::GetRange(){
        return range_;
    }
    int Tower:: MoneyFromWave() const{
        return money_from_wave_;
    }
    void Tower::SetPosition(float xCoord, float yCoord){
        sprite_.setPosition(xCoord, yCoord);
    }
    void Tower::SetScale(float size){
        sprite_.setScale(size / texture_.getSize().x_coord_, size / texture_.getSize().y_coord_)
    } //Från tile -> räcker bara det här?


    void Tower::SetActive(){
        active_ = true;
    }
    void Tower::SetNotActive(){
        active_ = false;
    }

    bool Tower::IsActive() const{
        return active_;
    }
    bool Tower::CanBeUpgraded() const{
        return upgrade_ < upgrade_max_;
    }
//Tower::Draw?????