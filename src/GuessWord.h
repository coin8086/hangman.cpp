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

  //NOTE: C++11 override
  void makeGuess(HangmanGame & game) override {
    game.guessWord(_guess);
  }

  //NOTE: C++11 override
  string toString() const override {
    stringstream ss;
    ss <<  "GuessWord[" << _guess << "]";
    return ss.str();
  }

private:
  string _guess;

};

#endif
