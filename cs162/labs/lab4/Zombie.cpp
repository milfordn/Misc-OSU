/******************************************
** Author:	Nick Milford
** Date:	10/18/16
** Description: Zombie class implementation
******************************************/

#include <cstdio>
#include "Zombie.hpp"

int Zombie::numZombies = 0;

Zombie::Zombie()
{
	numZombies++;
}

Zombie::~Zombie()
{
	numZombies--;
}

void Zombie::speak()
{
	printf("Braaaaaaaaiiinnnnsss!");
}
