#pragma once
#include <iostream>
#include "Trainer.h"
#include "allPokemons.h"
#include "Battle.h"

Trainer::Trainer()
{
	mFirstName = "Arthur";
	mLastName = "Cathelain";
	mCatchPhrase = "Nothing in life is equivalent to the beauty of splines";
	mPokemonTeam = { Diglett };
}

Trainer::Trainer(string firstName, string lastName, string CatchPhrase, vector<Pokemon> PokemonTeam)
{
	mFirstName = firstName;
	mLastName = lastName;
	mCatchPhrase = CatchPhrase;
	mPokemonTeam = PokemonTeam;
}

void Trainer::Introduction()
{
	string firstName = mFirstName;
	string lastName = mLastName;
	string catchPhrase = mCatchPhrase;

	cout << "\n" << firstName << " " << lastName << " said : " << mCatchPhrase << endl;
}

void Trainer::ChallengeTrainer(Trainer& thePlayer, Trainer& otherTrainer)
{
	cout << "\nI challenge you " << otherTrainer.mFirstName << " " << otherTrainer.mLastName << " !!" << endl;
	Battle theBattle = Battle(thePlayer, otherTrainer);
	theBattle.BattleAgainstTrainer(true);
}

void Trainer::ChallengePokemon(Trainer& thePlayer)
{
	cout << "\nYou just found a wild pokemon !!" << endl;
	Battle theBattle = Battle(thePlayer);
	theBattle.BattleAgainstPokemon(true);
}

void Trainer::CapturePokemon(Pokemon& pokemon)
{
	if (mPokemonTeam.size() < 6 && mPokeballs > 0)
	{
		cout << "\nYou are trying to capture " << pokemon.GetPokemonName() << endl;
		float captureRate = (((1.0f + (((pokemon.GetPokemonMaxLife() * 3.0f) - (pokemon.GetPokemonLife() * 2.0f)) * 256.0f)) / (pokemon.GetPokemonMaxLife() * 3.0f)) / 334.0f) * 100.0f;

		//float captureRate = ((1.0f + (((60.0f * 3.0f) - (60.0f * 2.0f)) * 256.0f)) / (60.0f * 3.0f)) / 334.0f;

		cout << captureRate << endl;

		//((1+(MaxHP*3-CurrentHP*2)*256)/(MaxHP*3))/334


		if (captureRate <= 50) 
		{
			cout << "You have failed to capture the pokemon" << endl;
			return;
		}
		
		cout << "You have managed to capture " << pokemon.GetPokemonName() << " !!!!" << endl;

		mPokemonTeam.push_back(pokemon);
		mPokeballs -= 1;
		return;
	}
	else if (mPokeballs <= 0)
	{
		cout << "\nYou don't have enough Pokeballs, try an other time." << endl;

		return;
	}
	cout << "\nYou already have 6 pokemon and can't capture one anymore" << endl;
	return;
}

bool Trainer::CheckIfTeamDead()
{
	for (int i = 0; i < mPokemonTeam.size(); i++)
	{
		if (mPokemonTeam[i].GetPokemonLife() > 0) {
			return false;
		}
	}

	cout << "\nAll your Pokemon are dead, you have lost the fight " << endl;
	mMoney -= 10;
	cout << "You have lost 10 gold, you now have " << mMoney << " gold" << endl;
	return true;
}

Pokemon& Trainer::SendOrChangePokemon()
{
	int pokemonIndex;
	int answer;

	cout << "\nYou have this Pokemon team, please choose one to use" << endl;
	for (int i = 1; i < mPokemonTeam.size() + 1; i++)
	{
		//add type ?
		cout << i << ". " << mPokemonTeam[i - 1].GetPokemonName() << endl;
	}

	cout << "Which Pokemon do you want to use ? (write the corresponding number) : " << endl;
	cin >> pokemonIndex;

	Pokemon& pokemonWantingToBeUse = mPokemonTeam[pokemonIndex - 1];

	if (pokemonWantingToBeUse.CheckIfInCombat() == true)
	{
		cout << "Your pokemon is already in combat, are you sure you don't want to change ?" << endl;
		cout << "1. Yes, I am sure \n" << "2. No, I want to change again" << endl;
		cin >> answer;

		if (answer == 1)
		{
			return pokemonWantingToBeUse;
		}
		else if (answer == 2)
		{
			return SendOrChangePokemon();
		}
	}

	mCurrentPokemonIndex = pokemonIndex - 1;
	return pokemonWantingToBeUse;
}

void Trainer::WinFight()
{
	cout << "You have won the Battle !!!!! " << endl;
	int random = rand() % 101;
	if (random <= 50)
	{
		mMoney += 10;
		cout << "You won 10 gold, you now have " << mMoney << " gold" << endl;
		return;
	}
	else if (random > 50)
	{
		mPokeballs += 2;
		cout << "You won 2 new Pokeballs, you now have " << mPokeballs << " Pokeballs" << endl;
		return;
	}
}


void Trainer::ChangeCurrentMainPokemon(int newMainPokemonIndex)
{
	mCurrentPokemonIndex = newMainPokemonIndex;
}

vector<Pokemon>& Trainer::GetPokemonTeam()
{
	return mPokemonTeam;
}
