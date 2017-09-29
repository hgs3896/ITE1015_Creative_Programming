#include "minimal_fighter.h"
MinimalFighter::MinimalFighter() : mHp(0), mPower(0), mStatus(FighterStatus::Invailid) {}
MinimalFighter::MinimalFighter(int _hp, int _power) : mHp(_hp), mPower(_power){
	mStatus = _hp <= 0 ? FighterStatus::Dead : FighterStatus::Alive;
}
int MinimalFighter::hp() const{
	return mHp;
}
int MinimalFighter::power() const{
	return mPower;
}
FighterStatus MinimalFighter::status() const {
	return mStatus;
}
void MinimalFighter::setHP(int _hp) {
	mHp = _hp;
	mStatus = _hp <= 0 ? FighterStatus::Dead : FighterStatus::Alive;
}
void MinimalFighter::attack(MinimalFighter *_enemy) {
	if (mStatus == FighterStatus::Alive) {
		_enemy->setHP(_enemy->hp() - this->power());
		this->mPower = 0;
	}
}
void MinimalFighter::hit(MinimalFighter *_enemy) {
	if (this->status() == FighterStatus::Alive && _enemy->status() == FighterStatus::Alive) {
		_enemy->setHP(_enemy->hp() - this->power());
		this->setHP(this->hp() - _enemy->power());
	}
}
void MinimalFighter::fight(MinimalFighter *_enemy) {
	while (this->status() == FighterStatus::Alive && _enemy->status() == FighterStatus::Alive) {
		_enemy->setHP(_enemy->hp() - this->power());
		this->setHP(this->hp() - _enemy->power());
	}
		
}