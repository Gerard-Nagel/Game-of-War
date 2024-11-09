/**
 * The Game of War by Gerard Nagel
 */

#include <iostream>
#include <algorithm>    
#include <vector>
#include <random>
#include <chrono>
#include <stack>
#include <queue>

using namespace std;

class GetRandom {
  
public:
    GetRandom(int size) {
        random_device rd; // declares a random_device object that need to generate a random number.
        mt19937 gen(rd()); 
        uniform_int_distribution<int> intdist(1, size); // create a uniform distribution object to turn the pseudorandom result into a random digit between 1 and size.
        self_rand_int_ = intdist(gen); // generates the random number.
    }
    int roll() {
        return self_rand_int_;
    }
private:
    int self_rand_int_;
}; 

class Game_of_War {
    /**
    Allows the user to play the card game War with the computer.
    */
public:
    Game_of_War() {
        // FIXME

        // This code makes the 5 decks of cards that are in order
        newdecks.reserve(125);
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                newdecks.push_back(j);
            }
        }
        // time-based seed for randomness
        unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());

       
        shuffle(newdecks.begin(), newdecks.end(), std::default_random_engine(seed));

        for (int i = 0; i < 50; i++) {
            dealing_pile.push(newdecks[i]);
        }
        game_over = false;
    }

    void Deal() {
        // this function deals the cards to the player and the computer, all 50 cards will
        // be dealt one by one from the top of the dealing pile, which also the newdecks vector to the top of each playing pile, alternating between playing piles.

        for (int i = 0; i < 50; i++) {
            if (i % 2 == 0) {
                player_deck.push(dealing_pile.top());
                dealing_pile.pop();
            }
            else {
                computer_deck.push(dealing_pile.top());
                dealing_pile.pop();
            }

        }
        cout << player_deck.size() << endl;

    }
    bool make_move() {
        // initiates a round of play and communicates play-by-play during the round
        // returns true when the game is still in play
        // returns false when the game is over
        if (player_deck.size() + player_storage.size() == 50) {
            cout << "You win!" << endl;
            return false;
        }
        else if (computer_deck.size() + computer_storage.size() == 50) {
            cout << "You lose!" << endl;
            return false;
        }
        else {
            return true;
        }
    }

    int remove_player_card() {
        // removes the top card from the player's playing pile and returns it
        if (!player_deck.empty()) {
            playercard = player_deck.top();
            player_deck.pop();
        }
        else if (!player_storage.empty()) {
            for (int i = 0; i < player_storage.size(); i++) {
                player_deck.push(player_storage.front());
                player_storage.pop();
            }
            playercard = player_deck.top();
            player_deck.pop();
        }
        else {
            make_move();
        }
        return playercard;
    }

    int remove_computer_card() {
        // removes the top card from the computer's playing pile and returns it
        if (!computer_deck.empty()) {
            computercard = computer_deck.top();
            computer_deck.pop();
        }
        else if (!computer_storage.empty()) {
            for (int i = 0; i < computer_storage.size(); i++) {
                computer_deck.push(computer_storage.front());
                computer_storage.pop();
            }
            computercard = computer_deck.top();
            computer_deck.pop();
        }
        else {
            make_move();
        }
        return computercard;
    }

    void show_cards(int compcard, int playcard) {
        // displays the cards that were drawn by the player and the computer
        cout << "You drew a " << playcard << " and the computer drew a " << compcard << endl;
    }

    void compare_cards() {
        // compares the cards that were drawn by the player and the computer
        if (computercard > playercard) {
            loot_pile.push(playercard);
            loot_pile.push(computercard);
            cout << "The computer wins this round!" << endl;
            while (!loot_pile.empty()) {
                computer_storage.push(loot_pile.front());
                loot_pile.pop();
            }
            
        }
        else if (computercard < playercard) {
            loot_pile.push(playercard);
            loot_pile.push(computercard);
            cout << "The player wins this round!" << endl;
            while (!loot_pile.empty()) {
                player_storage.push(loot_pile.front());
                loot_pile.pop();
            }
           
        }
        else if (computercard == playercard) {
            cout << "War has been declared!" << endl;
            loot_pile.push(playercard);
            loot_pile.push(computercard);
            remove_player_card();
            remove_computer_card();
            loot_pile.push(playercard);
            loot_pile.push(computercard);
            remove_player_card();
            remove_computer_card();
            
        }
    }

    void play() {
        // plays the game of war
        Deal();
        while (make_move()) {
            show_cards(remove_computer_card(), remove_player_card());
            compare_cards();
        }
    }


private:
    vector<int> newdecks; 
    stack<int> player_deck;
    stack<int> computer_deck;
    queue<int> player_storage;
    queue<int> computer_storage;
    queue<int> loot_pile;
    stack<int> dealing_pile;
    bool game_over;
    int playercard;
    int computercard;
};

//---------------------------------------------------------------------


int main() {
    char stopme;

    Game_of_War game;
    game.play();

    cin >> stopme; 

    return 0;
}
