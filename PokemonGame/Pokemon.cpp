using namespace std;
#include <algorithm>
#include <iostream>

#include "Pokemon.h"
#include "allAbilities.h"

Pokemon::Pokemon()
{
	mName = "Minum";
	mDescription = "Promotes blood circulation and relieves muscular tension.";
	mType = PokeType::Electric;
	mLevel = 1;
	mLife = 60;
	mMaxLife = mLife;
	mIsInCombat = false;
	mAbilities = { Thunder, Aeroblast };
}

Pokemon::Pokemon(string name, string description, PokeType type, int life, vector<Ability> abilitie)
{
	mName = name;
	mDescription = description;
	mType = type;
	mLevel = 1;
	mLife = life;
	mMaxLife = mLife;
	mIsInCombat = false;
	mAbilities = abilitie;
}

const vector<Ability>& Pokemon::GetAbilities()
{
	return mAbilities;
}

string Pokemon::GetPokemonName()
{
	return mName;
}

float Pokemon::GetPokemonLife()
{
	return mLife;
}

float Pokemon::GetPokemonMaxLife()
{
	return mMaxLife;
}

float Pokemon::GetPokemonDamage()
{
	return mDamageResistance;
}

void Pokemon::ChangePokemonLife(int newLife)
{
	mLife = newLife;
}

bool Pokemon::AttackOtherPokemon(Pokemon& pokemon)
{
	bool canUseSkill = false;

	for (int i = 0; i < mAbilities.size(); i++)
	{

		if (mAbilities[i].GetTurnUse() > 0)
		{
			canUseSkill = true;
			break;
		}
	}

	if (canUseSkill)
	{
		int skill;
		cout << "\nYou have all this abilities : " << endl;

		for (int i = 1; i < mAbilities.size() + 1; i++)
		{
			//add type ?
			cout << i << ". " << mAbilities[i - 1].GetName() << endl;
		}

		cout << "Which ability do you want to use ? (write the corresponding number) : " << endl;
		cin >> skill;

		Ability* abilityBeingUsed = &mAbilities[skill - 1];

		if (abilityBeingUsed->GetTurnUse() > 0)
		{
			pokemon.TakeDamage(abilityBeingUsed->GetDamage(), *abilityBeingUsed);

			abilityBeingUsed->UseAbility();

			cout << "\nYour Pokemon (" << mName << ") used " << abilityBeingUsed->GetName() << ", it did " << pokemon.mDamageResistance;

			return true;
		}

		cout << "You don't have enough turn point to use that ability" << "\nPlease use an other one : " << endl;
		return AttackOtherPokemon(pokemon);
	}

	cout << "\nYour pokemon can't use any more skill, please change it " << endl;
	return false;
}

void Pokemon::TakeDamage(int damage, Ability abilityAttack)
{
	float matrix[18][18] = { 
		/* NORMAL   */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0 },
		/* FIRE     */ { 1.0, 0.5, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0 },
		/* WATER    */ { 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
		/* GRASS    */ { 1.0, 0.5, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* ELECTRIC */ { 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 },
		/* ICE      */ { 1.0, 0.5, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* FIGHTING */ { 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5 },
		/* POISON   */ { 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.5, 1.0, 0.5, 1.0, 1.0, 0.0, 2.0 },
		/* GROUND   */ { 1.0, 2.0, 1.0, 0.5, 2.0, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0 },
		/* FLYING   */ { 1.0, 1.0, 1.0, 2.0, 0.5, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* PSYCHIC  */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0 },
		/* BUG      */ { 1.0, 0.5, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5 },
		/* ROCK     */ { 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 2.0, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 },
		/* GHOST    */ { 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 1.0 },
		/* DRAGON   */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0 },
		/* DARK     */ { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5 },
		/* STEEL    */ { 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 2.0 },
		/* FAIRY    */ { 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 2.0, 2.0, 2.0, 1.0 } };

	int indexAbilityType = (int) abilityAttack.GetPoketype();
	int indexPokemonType = (int) mType;
	float resistance = matrix[indexAbilityType][indexPokemonType];
	float allDamage = damage * resistance;
	mDamageResistance = allDamage;

	mLife -= allDamage;
}

void Pokemon::Rest()
{

	mLife = mMaxLife;

	for (int i = 0; i < mAbilities.size(); i++)
	{
		mAbilities[i].ResetAbilityUse();
	}
}

bool Pokemon::CheckIfInCombat()
{
	return mIsInCombat;
}

void Pokemon::LearnNewAbilities()
{

	bool haveAbility = false;
	int skill;

	if (mAbilities.size() >= 4)
	{
		return;
	}

	cout << "\nHere are all the abilities : " << endl;
	for (int i = 1; i < allAbility.size() + 1; i++)
	{
		//add type ?
		cout << i << ". " << allAbility[i - 1].GetName() << endl;
	}

	cout << "Which ability do you want to choose ? (write the corresponding number) : " << endl;
	cin >> skill;

	string wantedAbilityName = allAbility[skill - 1].GetName();

	for (Ability abilities : mAbilities)
	{
		if (abilities.GetName() == wantedAbilityName)
		{
			cout << "You already have this ability, please choose an other one : " << endl;
			haveAbility = true;
			LearnNewAbilities();
			break;
		}
	}

	if (!haveAbility)
	{
		mAbilities.push_back(allAbility[skill - 1]);

		cout << mName << " has learned " << allAbility[skill - 1].GetName() << endl;
	}
}


void Pokemon::GetDescription()
{
	cout << "\n" << mName << mDescription << " and has " << mLife << " pv " <<
		"\nHis abilities are " << endl;

	for (int i = 0; i < mAbilities.size(); i++)
	{
		cout << mAbilities[i].GetName() << endl;
	}
}
