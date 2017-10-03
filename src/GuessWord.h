#ifndef __GUESSWORD_H__
#define __GUESSWORD_H__

#include <sstream>
#include "Guess.h"

/**
 * A Guess that represents guessing a word for the current Hangman game
 */
class GuessWord : public Guess {
public:
  GuessWord(const string & guess) {
    _guess = guess;
  }

  void makeGuess(HangmanGame & game) {
    game.guessWord(_guess);
  }

  string toString() const {
    stringstream ss;
    ss <<  "GuessWord[" << _guess << "]";
    return ss.str();
  }

private:
  string _guess;

};

#endif
