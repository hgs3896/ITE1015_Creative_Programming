#pragma once
#ifndef INC_MINIMAL_FIGHTER
#define INC_MINIMAL_FIGHTER
enum FighterStatus { Invailid, Alive, Dead };
class MinimalFighter {
private:
	int mHp;
	int mPower;
	FighterStatus mStatus;
public:	
	MinimalFighter();
	MinimalFighter(int _hp, int _power);
	int hp() const;
	int power() const;
	FighterStatus status() const;
	void setHP(int _hp);
	void hit(MinimalFighter *_enemy);
	void attack(MinimalFighter *_enemy);
	void fight(MinimalFighter *_enemy);
};
#endif