#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../include/deck.hpp"
#include <string>
#include <thread>
#include <iomanip>
#include <string.h>
#include <boost/format.hpp>

#ifdef __unix__
#include <unistd.h>
#define clear() system("clear")
#endif
#ifdef _WIN32
#include <windows.h>
#define clear() system("cls")
#endif

void loading(int times);
void performRound(Deck& d, bool& t);
void printResults(int rounds, Deck& de);
void printHelp();

int main(int argc, char* argv[])
{
        if(argc > 1 && (!strcmp(argv[1],"-h") || !strcmp(argv[1],"--help")))
        {
                printHelp();
                return EXIT_SUCCESS;
        }
        Deck standard_deck;
        bool isPlayersTurn = true;
        std::string loadingMessage;
        if(argc == 1)
        {
                loadingMessage = "Randomizing the Deck";
                standard_deck.randomize();
        }
        else if(!strcmp(argv[1],"-w") || !strcmp(argv[1],"--warmode")) {
                loadingMessage = "Running the game in WARMODE";
                
        }
        else {
                std::cerr << "Unknown option: \'" << argv[1] << "\'\n";
                return EXIT_FAILURE;
        }
        clear();
        std::cout << "************************************************" << std::endl;
        std::cout << boost::format("%=48s\n") % "WELCOME TO THE WAR CARD GAME";
        std::cout << "************************************************" << std::endl;
        std::cout << loadingMessage;
        loading(2);
        performRound(standard_deck, isPlayersTurn);
        return 0;
}

void loading(int times)
{
        for(int j = 0; j < times; j++)
        {
                for (int i = 0; i < 3; i++) {
                        std::cout << ".";
                        std::cout.flush();
                        std::chrono::milliseconds timespan(500);
                        std::this_thread::sleep_for(timespan);
                }
                std::cout << "\b\b\b   \b\b\b";
        }
        std::cout << std::endl;
}
void performRound(Deck &d, bool& t)
{
        static int rounds = 1;
        static short cardsLeft = 52;
        static bool isWar = false;
        static short war_level = 0;
        while (cardsLeft >= 2) {
                if(!isWar)
                {
                        clear();
                        std::cout << "ROUND " << rounds << std::endl;
                }
                t = true;
                std::cout << "Cards left in the deck: " << cardsLeft << std::endl;
                std::cout << "It's your turn. Press Enter to pick up a card from the deck: ";
                std::cin.ignore();
                std::cout << "Your card is " << d.getTop(t) << std::endl;
                cardsLeft--;
                t = false;
                std::cout << "AI is picking up its card";
                loading(2);
                std::cout << "AI's card is " << d.getTop(t) << std::endl;
                cardsLeft--;
                if(d.getPlayerVal() < d.getAIVal())
                {
                        std::cout << "AI wins this round" << std::endl;
                        if (isWar) 
                        {
                                isWar = false;
                                d.changeAIsCards(2 + 2 * war_level);
                        }
                        else d.changeAIsCards(2);
                }
                else if (d.getPlayerVal() > d.getAIVal())
                {
                        std::cout << "You win this round" << std::endl;
                        if (isWar) 
                        {
                                isWar = false;
                                d.changePlayersCards(2 + 2 * war_level);
                        }
                        else d.changePlayersCards(2);
                }
                else
                {
                        std::cout << "This means WAR" << std::endl; 
                        while (d.getPlayerVal() == d.getAIVal()) {
                                isWar = true;
                                war_level++;
                                performRound(d, t); 
                        }
                };
                if (!isWar) {
                        printResults(rounds,d);
                        rounds++;
                }
        }
        clear();
        if(d.getPlayersCards() > d.getAIsCards())
                std::cout << "CONGRATULATIONS! YOU'VE WON AFTER " << rounds << " ROUNDS WITH " << d.getPlayersCards() << " CARDS" << std::endl;
        else
                std::cout << "YOU'VE LOST AFTER " << rounds << " ROUNDS WITH " << d.getPlayersCards() << " CARDS" << std::endl;

}
void printResults(int rounds, Deck& de)
{
        std::cout << "********************************************" << std::endl;
        std::string resultString = "RESULTS OF ROUND " + std::to_string(rounds);
        std::cout << boost::format("%=44s\n") % resultString; 
        resultString = "AI " + std::to_string(de.getAIsCards()) + "                " + "YOU " + std::to_string(de.getPlayersCards());
        std::cout << boost::format("%=44s\n") % resultString; 
        std::cout << "********************************************" << std::endl;
        std::cout << "Press Enter to continue... ";
        std::cin.ignore();
}
void printHelp()
{
        std::cout << "Usage: war [OPTIONS]" << std::endl;
        std::cout << "Available Options: " << std::endl;
        std::cout << "-h | --help - prints this help menu and exits" << std::endl;
        std::cout << "-w | --warmode  - enables Warmode where deck is not randomized at the beginning" << std::endl;
}
