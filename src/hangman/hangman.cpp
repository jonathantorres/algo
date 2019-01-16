#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>
#include <cstdio>

class Hangman
{
    public:
        Hangman();
        ~Hangman() {};
        void init();
    private:
        std::string filename;
        std::string word_to_guess;
        std::vector<char> guessed_letters;
        int max_attempts;
        int attempts;
        int letters_to_guess;
        std::string selectRandomWord();
        bool letterIsGuessed(char letter);
        void printWord();
        bool checkGuess(char letter);
};

Hangman::Hangman()
{
    this->max_attempts = 10;
    this->attempts = 0;
    this->letters_to_guess = 0;
    this->filename = "words.txt";
}

bool Hangman::letterIsGuessed(char letter)
{
    bool letter_found = false;

    for (unsigned long i = 0; i < this->guessed_letters.size(); i++) {
        if (this->guessed_letters.at(i) == letter) {
            letter_found = true;
        }
    }

    return letter_found;
}

void Hangman::printWord()
{
    for (unsigned long i = 0; i < this->word_to_guess.size(); i++) {
        if (this->letterIsGuessed(this->word_to_guess[i])) {
            std::cout << this->word_to_guess[i];
        } else {
            std::cout << '_';
        }
    }
    std::cout << std::endl;
}

bool Hangman::checkGuess(char letter)
{
    bool correct_guess = false;

    for (unsigned long i = 0; i < this->word_to_guess.size(); i++) {
        if (letter == this->word_to_guess[i]) {
            correct_guess = true;
            this->guessed_letters.push_back(letter);
        }
    }

    return correct_guess;
}

void Hangman::init()
{
    bool user_won = false;
    this->word_to_guess = this->selectRandomWord();
    this->letters_to_guess = this->word_to_guess.size();
    this->printWord();

    while (this->attempts <= this->max_attempts) {
        char guess;
        std::cout << "Pick a guess: ";
        std::cin >> guess;
        this->attempts++;
        if (this->checkGuess(guess)) {
            this->printWord();
            if (this->letters_to_guess == (int)this->guessed_letters.size()) {
                std::cout << "You won!" << std::endl;
                user_won = true;
                break;
            }
        } else {
            std::cout << "Wrong guess" << std::endl;
            this->printWord();
        }
    }

    if (!user_won) {
        std::cout << "You lost sucka!!!" << std::endl;
    }
}

std::string Hangman::selectRandomWord()
{
    std::fstream file(this->filename, std::ios_base::in);
    std::vector<std::string> words;

    if (!file.is_open()) {
        std::cerr << "The file could not be found." << std::endl;
        std::exit(EXIT_FAILURE);
    }
    std::string str;
    while (std::getline(file, str)) {
        words.push_back(str);
    }

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, words.size());
    int index = distr(generator);
    std::string word_to_guess = words.at(index);
    file.close();

    return word_to_guess;
}

int main()
{
    Hangman hangman_game;
    hangman_game.init();
    return 0;
}
