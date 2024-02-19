#pragma once
#include <iostream>
#include <vector>

#include "PokeType.h"
#include "Ability.h"

using namespace std;

class Pokemon
{
private:
	string mName;
	string mDescription;
	PokeType mType;
	int mLevel;
	int mLife;
	int mMaxLife;
	bool mIsInCombat;
	vector<Ability> mAbilities;


public:
	Pokemon();
	Pokemon(string name, string description, PokeType type, int life, vector<Ability> abilitie);

	const vector<Ability>& GetAbilities();
	string GetPokemonName();
	int GetPokemonLife();
	int GetPokemonMaxLife();
	void ChangePokemonLife(int newLife);
	bool AttackOtherPokemon(Pokemon& pokemon);
	void TakeDamage(int damage);
	void LearnNewAbilities();
	void Rest();
	bool CheckIfInCombat();

	void GetDescription();
};

