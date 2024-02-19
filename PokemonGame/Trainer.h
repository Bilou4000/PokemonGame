#pragma once

#include <iostream>
#include <vector>

#include "Pokemon.h"

using namespace std;


class Trainer
{
private:
	string mFirstName;
	string mLastName;
	string mCatchPhrase;
	int mMoney;
	int mLifePoints = 100;
	vector<Pokemon> mPokemonTeam;
	int mPokeballs = 10;
	int mCurrentPokemonIndex = 0;


public:
	Trainer();
	Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam);

	void Introduction();
	void ChallengeTrainer(Trainer& thePlayer, Trainer& otherTrainer);
	void ChallengePokemon(Trainer& thePlayer);
	void CapturePokemon(Pokemon& pokemon);
	Pokemon& SendOrChangePokemon();
	void WinFight();
	bool CheckIfTeamDead();
	void ChangeCurrentMainPokemon(int newMainPokemonIndex);
	vector<Pokemon>& GetPokemonTeam();
};

