#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <random>

class Hangman
{
    public:
        Hangman();
        ~Hangman() {};
        void init();
    private:
        std::string filename;
        std::string selectRandomWord();
};

Hangman::Hangman()
{
    this->filename = "words.txt";
}

void Hangman::init()
{
    std::string word = this->selectRandomWord();
    std::cout << word << std::endl;
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
