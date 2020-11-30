#include "tower.hpp"
#include "../game/texture_manager.hpp"

    Tower::Tower( int price, float damage, int x_coord, int y_coord, float size, float speed, float range, const std::string& texture):
    _price(price), 
    _damage(damage), 
    _x_coord(x_coord), 
    _y_coord(y_coord), 
    _size(size),
    _texture(texture),
    _prewious_attack(0){
        _sprite = sf::Sprite(GetTexture());
        _sprite.setScale(size / (float)(*_sprite.getTexture()).getSize().x_coord, size / (float)(*_sprite.getTexture()).getSize().y_coord));
        _radius.setRadius(range);
        // setFillColor till _radius när vi har bestämt!
    }

    bool Tower::Attack(Enemy& enemy) const{
        enemy.SetHp(enemy.GetHp - _damage);
    }
    
    int Tower::GetPrice() const{
        return _price;
    }
    float Tower::GetDamage() const{
        return _damage;
    }
    const std::pair<int, int> GetCoords() const{
        return (_x_coord, _y_coord);
    }
    float Tower::GetSize() const{
        return _size;
    }
    float Tower::GetSpeed() const{
        return _speed;
    }
    sf::Texture& Tower::GetTexture() const{
        return _texture;
    }
    int Tower::GetUpgrade() const{
        return _upgrade;
    }
    int Tower::GetUpgradePrice() const{
        return _upgrade_price;
    }
    sf::Sprite* Tower::GetSprite(){
        return _sprite;
    }
    float Tower::GetRange(){
        return _range;
    }
    int Tower:: MoneyFromWave() const{
        return _money_from_wave;
    }
    void Tower::SetPosition(float xCoord, float yCoord){
        _sprite.setPosition(xCoord, yCoord);
    }
    void Tower::SetScale(float size){
        _sprite.setScale(size / _texture.getSize().x, size / _texture.getSize().y)
    } //Från tile -> räcker bara det här?
    void Tower::SetActive(){
        _active = true;
    }
    void Tower::SetNotActive(){
        _active = false;
    }

    bool Tower::IsActive() const{
        return _active;
    }
    bool Tower::CanBeUpgraded() const{
        return _upgrade < _upgrade_max;
    }
//Tower::Draw?????