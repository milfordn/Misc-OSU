/***********************************
** Author:	Nick Milford
** Date: 	10/18/16
** Description: Main class for Lab4 Zombies
***********************************/

#include <vector>
#include <cstdio>
#include "Zombie.hpp"

using std::vector;

int main(int argc, char** argv)
{

	vector<Zombie*> zombies;
	
	int choice = -1;
	
	printf("Possible actions are:\n");
	printf("1\tAdd a new Zombie\n");
	printf("2\tDestroy a Zombie\n");
	printf("3\tShow number of Zombies\n");
	printf("4\tMake all zombies speak\n");
	printf("5\tQuit");
	
	while(choice != 5)
	{
		printf("\nAction: ");
		scanf("%d", &choice);
		
		if(choice == 1)
		{
			Zombie *newZ = new Zombie();
			zombies.push_back(newZ);
			printf("\nNew Zombie created");
		}
		else if(choice == 2)
		{
			if(Zombie::numZombies == 0)
				printf("\nThis is where I would kill the zombie.... IF THERE WERE ANY!");
			else
			{
				Zombie *toDestroy = zombies.back();
				delete toDestroy;
				zombies.pop_back();
				printf("\nZombie destroyed");
			}
		}
		else if(choice == 3)
		{
			printf("\n%d Zombies", Zombie::numZombies);
		}
		else if(choice == 4)
		{
			for(int i = 0; i < Zombie::numZombies; i++)
			{
				printf("\n");
				zombies[i]->speak();
			}
		}
	}
	return 0;
}
			
