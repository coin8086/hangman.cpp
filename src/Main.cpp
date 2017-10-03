//NOTE: C++11 unordered_set
#include <unordered_set>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "MyGuessingStrategy.h"
#include "Util.h"

using namespace std;

//Read in dictionary file
unordered_set<string> loadDictionary(const char * file) {
  ifstream fin(file);
  if (!fin) {
    cerr << "Error when reading dictionary file '" << file << "'!" << endl;
    exit(-1);
  }
  unordered_set<string> dict;
  string word;
  while (fin >> word) {
    dict.insert(toUpper(word));
  }
  fin.close();
  return dict;
}

//Run game
int run(HangmanGame & game, GuessingStrategy & strategy, bool debug) {
  //TODO: scoped enum...
  while(game.gameStatus() == HangmanGame::Status::KEEP_GUESSING) {
    if (debug) {
      cerr << game.toString() << endl;
    }
    shared_ptr<Guess> guess = strategy.nextGuess(game);
    if (debug) {
      cerr << guess->toString() << endl;
      cerr << strategy.toString() << endl;
    }
    guess->makeGuess(game);
  }
  if (debug) {
    cerr << game.toString() << endl;
  }
  return game.currentScore();
}

int main(int argc, char ** argv) {
  const char * file = getenv("hangman_dict");
  if (!file)
    file = "words.txt";

  int guesses = 5;
  const char * sguesses = getenv("hangman_guesses");
  if (sguesses) {
    guesses = atoi(sguesses);
    if (guesses < 1)
      guesses = 5;
  }

  //NOTE: C++11 nullptr
  bool debug = getenv("hangman_debug") != nullptr;

  unordered_set<string> dict = loadDictionary(file);

  int totalScore = 0;
  int total = 0;
  string word;

  while (1) {
    cerr << "Enter a word:" << endl;
    if (cin >> word) {
      word = toUpper(word);
      if (!dict.count(word)) {
        cerr << "Word '" << word << "' is not in dictionary!" << endl;
        continue;
      }

      if (debug) {
        cerr << "New Game [" << word << "]" << endl;
      }

      HangmanGame game(word, guesses);
      MyGuessingStrategy strategy(game, dict.begin(), dict.end());
      int score = run(game, strategy, debug);
      totalScore += score;
      total++;
      cout << word << " = " << score << endl;
    }
    else {
      break;
    }
  }

  if (total > 0) {
    cout << "-----------------------------" << endl
      << "AVG: " << totalScore * 1.0 / total << endl
      << "NUM: " << total << endl
      << "TOTAL: " << totalScore << endl;
  }
}
