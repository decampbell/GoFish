#include "Player.h"

Player::Player()
{
}

int Player::get_numMatches() const
{
	return matchPile.size();
}
int Player::get_rankAt(int index) const
{
	return hand[index].get_rank();
}

void Player::printHand()
{
	for ( unsigned i = 0; i < hand.size(); i++ )
		hand[i].display_card( i * WIDTH + 8 - (i * 9), 3 );
}

unsigned Player::numCards() const
{
	return hand.size();
}


void Player::printMatchPile()
{
	for (unsigned i = 0; i < matchPile.size(); i++)
		matchPile[i][0].display_card(i * WIDTH + 8 - (i*7), 18);
}

bool Player::playerHasCard( Card test ) 
{
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i] == test )
			return true;
	}
	return false;
}

void Player::addCard( Card in )
{
	hand.push_back( in );
}
void Player::addMatches(std::vector<Card> in)
{
	matchPile.push_back(in);
}

std::vector< Card > Player::cardsOfRank( CARD_RANK targetRank )
{
	std::vector< Card > temp;
	for ( unsigned i = 0; i < hand.size(); i++ )
	{
		if ( hand[i].get_rank() == targetRank )
		{
			temp.push_back( hand[i] );
			hand.erase( hand.begin() + i );
			i = -1;
		}
	}
	return temp;
}
int Player::checkHandForMatches()
{	
	int initialNumberOfMatches = matchPile.size();
	for (unsigned i = 0; i < numCards(); i++)
	{
		std::vector< Card> temp = cardsOfRank(static_cast<CARD_RANK>(get_rankAt(i)));
		if (temp.size() == 4)
		{
			addMatches(temp);
			temp.clear();
			i = -1;			
		}
		else
		{
			for (unsigned i = 0; i < temp.size(); i++)
				addCard(temp[i]);
		}
	}
	return matchPile.size() - initialNumberOfMatches;
}