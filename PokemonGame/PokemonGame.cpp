using namespace std; 
#include <iostream>

#include "allPokemons.h"
#include "Trainer.h"


int main()
{

    vector<Pokemon> firstTeam = { Minun, Pansage, Vanillite };
    vector<Pokemon> secondTeam = { Magikarp, Snorlax };

    Trainer firstTrainer = Trainer("Claire", "Benes", "As the wind continues to blow, so too shall I continue to fight !", firstTeam);
    Trainer secondTrainer = Trainer("Jean", "Louis", "OHOHOHOHOHOH !!!", secondTeam);

    //ask if want to combat or stroll around
    //if stroll around --> find wild pokemon --> combat
    //if combat --> combat against other trainer

    //firstTrainer.ChallengePokemon(firstTrainer);
    firstTrainer.ChallengeTrainer(firstTrainer, secondTrainer);
    //firstTrainer.ChallengeTrainer(firstTrainer, secondTrainer);


    //newTrainer.Introduction();

    //newTrainer.SendOrChangePokemon()
    //Snorlax.LearnNewAbilities();
    //Snorlax.AttackOtherPokemon(Darumaka);

    Darumaka.GetDescription();
}
