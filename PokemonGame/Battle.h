#pragma once

#include "Trainer.h"
#include "Pokemon.h"
#include "Ability.h"

class Battle
{
private:
	Trainer* mThePlayer;
	Trainer* mOpponentTrainer;
	Ability mOpponentPokemonAbility;
	Pokemon mUsedOpponentPokemon;
	Pokemon mDeadPlayerPokemon;
	int mMaxAbilityCost;
	int mNuberOfTimeAbiityWasUsed = 0;

public:
	Battle(Trainer& thePlayer);
	Battle(Trainer& thePlayer, Trainer& opponentTrainer);

	void BattleAgainstTrainer(bool firstTime);
	void BattleAgainstPokemon(bool firstTime);
};

