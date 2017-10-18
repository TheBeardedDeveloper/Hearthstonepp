/*************************************************************************
> File Name: Console.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Console version of Hearthstone++ game.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Agents/GameAgent.h>
#include <Commons/Constants.h>
#include <Enums/EnumsToString.h>
#include <Loaders/CardLoader.h>
#include <Models/Card.h>
#include <Models/Cards.h>
#include <Programs/Console.h>

#include <iostream>

namespace Hearthstonepp
{
	template<std::size_t SIZE>
	void Console::ShowMenu(std::array<std::string, SIZE>& menus)
	{
		std::cout << "========================================\n";
		for (auto& menu : menus)
		{
			std::cout << menu.c_str() << '\n';
		}
		std::cout << "========================================\n";
	}

	size_t Console::InputMenuNum(std::string questionStr, const int menuSize)
	{
		while (true)
		{
			std::cout << questionStr;
			size_t num;
			std::cin >> num;

			if (num < 1 || num > menuSize)
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				return num;
			}
		}
	}

	bool Console::InputYesNo(std::string sentence) const
	{
		std::cout << sentence;
		std::cout << "(Please input \"y/yes\" or \"n/no\" (insensitive))\n";
		std::cout << "Input: ";

		std::string str;
		std::cin >> str;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		return (str == "y" || str == "yes") ? true : (str == "n" || str == "no") ? false : InputYesNo(sentence);
	}

	//Function to search for a card based on card flavor (IE lifesteal, golden, rarity, etc)
	void Console::SearchCard()
	{
		std::string str;	//String variable used in searching for a specific card flavor
		std::boolean isWild;	//Boolean to determine if it's Standard or wild cards only
		std::Card Card[];	//Object array to hold all the cards we have found with our loop
		
		std::cout << "Enter your card search query:\n";
		cin >> str;
		
		//Loop through and find any matching results to your query
		if (isWild) //Standard or wild?
		{	
		while (true)
			{
			//if the card has any matching query to str add that card to an array to return
			//logic is as follows: 
			//if (card.attribute.equals(str)) add it to the array
			//append it to the array and increase index counter
			
			//if reachedEnd/null
			//break;
			}
		}
		else
		{
			//Loop through specific indexes for only standard cards
		}
		
		//Should this function return an array full of cards that match the description or null if none are found?
		
	}

	void Console::MakeDeck()
	{
		std::cout << "========================================\n";
		std::cout << "               Make Deck!               \n";
		std::cout << "========================================\n";

		ShowMenu(m_playerClassStr);
		const size_t selectedClassNum = InputMenuNum("What's your player class? ", PLAYER_CLASS_SIZE);
		const CardClass playerClass = static_cast<CardClass>(selectedClassNum + 1);

		std::cout << "What's your deck name? ";
		std::string name;
		std::cin >> name;

		Deck deck(playerClass, name);

		std::cout << "Input Card ID to add or delete to your deck.\n";
		std::cout << "If you do not want to add or delete more, please input \"STOP\"\n";

		while (true)
		{
			std::cout << "The number of cards in the current deck = " << deck.GetNumOfCards() << " / " << MAXIMUM_NUM_CARDS_IN_DECK << "\n";
			std::cout << "Card ID: ";
			std::string selectedCardID;
			std::cin >> selectedCardID;

			if (selectedCardID == "STOP")
			{
				break;
			}

			const Card* card = Cards::GetInstance()->FindCardByID(selectedCardID);
			if (card == nullptr)
			{
				std::cout << selectedCardID << " doesn't exist. Try again.\n";
				continue;
			}
			if (card->GetCardClass() != CardClass::NEUTRAL && card->GetCardClass() != playerClass)
			{
				std::cout << "The class of " << selectedCardID << " is " << ConverterFromCardClassToString.at(card->GetCardClass()).c_str() << '\n';
				std::cout << "It is neither a NETURAL nor a " << ConverterFromCardClassToString.at(playerClass).c_str() << '\n';
				continue;
			}

			card->ShowInfo();

			const bool isYes = InputYesNo("Is it correct? ");
			if (isYes == false)
			{
				continue;
			}

			ShowMenu(m_makeDeckOperationStr);
			const size_t selectedOperation = InputMenuNum("What do you want to do? ", 2);
			m_makeDeckOperationFuncs[selectedOperation - 1](*this, deck, card, selectedCardID);
		} 
	}

	void Console::AddCardInDeck(Deck& deck, const Card* card, std::string& selectedCardID)
	{
		if (deck.GetNumOfCards() >= MAXIMUM_NUM_CARDS_IN_DECK)
		{
			std::cout << "The deck " << deck.GetName() << " is full of cards.\n";
			return;
		}

		while (true)
		{
			unsigned int numCardToAddAvailable = card->GetMaxAllowedInDeck() - deck.GetNumCardInDeck(selectedCardID);
			if (deck.GetNumOfCards() + numCardToAddAvailable > MAXIMUM_NUM_CARDS_IN_DECK)
			{
				numCardToAddAvailable = deck.GetNumOfCards() + numCardToAddAvailable - MAXIMUM_NUM_CARDS_IN_DECK;
			}

			std::cout << "How many cards to add (0 - " << numCardToAddAvailable << ") ? ";
			unsigned int numCardToAdd;
			std::cin >> numCardToAdd;

			if (numCardToAdd < 0 || numCardToAdd > numCardToAddAvailable)
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck.AddCard(card, numCardToAdd);
				break;
			}
		}
	}

	void Console::DeleteCardInDeck(Deck& deck, const Card* card, std::string& selectedCardID)
	{
		if (deck.GetNumCardInDeck(selectedCardID) == 0)
		{
			std::cout << selectedCardID << " doesn't exist.\n";
			return;
		}

		while (true)
		{
			std::cout << "How many cards to delete (0 - " << deck.GetNumCardInDeck(selectedCardID) << ") ? ";
			unsigned int numCardToDelete;
			std::cin >> numCardToDelete;

			if (numCardToDelete < 0 || numCardToDelete > deck.GetNumCardInDeck(selectedCardID))
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck.DeleteCard(card, numCardToDelete);
				break;
			}
		}
	}

	void Console::LoadDeck()
	{

	}

	void Console::StoreDeck()
	{
		
	}

	void Console::SimulateGame()
	{
		//CardLoader loader;
		//std::vector<Card*> cards;

		//loader.Load(cards);

		//Deck deck1; // temporal deck
		//Deck deck2;

		//deck1.reserve(30);
		//deck2.reserve(30);

		//deck1.assign(cards.begin(), cards.begin() + 30); 
		//deck2.assign(cards.begin() + 30, cards.begin() + 60);

		//User user1(0, new Hero(), new HeroPower(), deck1); // define new user
		//User user2(1, new Hero(), new HeroPower(), deck2);

		//GameAgent agent(&user1, &user2);
		//GameResult result;

		//std::thread *at = agent.StartAgent(result);

		//for (int i = 0; i < 2; ++i)
		//{
		//	Card *list[3] = { 0, };
		//	int result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get card data

		//	for (auto card : list)
		//	{
		//		std::cout << "[" << card->name << "] ";
		//	}
		//	std::cout << std::endl;

		//	BYTE mulligan[] = { 0, 2 }; // index of the card to be mulligan
		//	result = agent.WriteBuffer(mulligan, 2); // send index to agent

		//	result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get new card data

		//	for (auto card : list)
		//	{
		//		std::cout << "[" << card->name << "] ";
		//	}
		//	std::cout << std::endl;
		//}

		//at->join(); // join agent thread
	}

	int Console::Play()
	{
		std::cout << "    Welcome to Hearthstone++ Ver " << VERSION << '\n';

		ShowMenu(m_menuStr);
		const size_t selectedNum = InputMenuNum("Select: ", MENU_SIZE);
		bool isFinish = false;

		if (selectedNum != MENU_SIZE)
		{
			m_menuFuncs[selectedNum - 1](*this);
		}
		else
		{
			isFinish = true;
		}

		return isFinish ? 0 : Play();
	}
}
