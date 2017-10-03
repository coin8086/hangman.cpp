#ifndef __HANGMANGAME_H__
#define __HANGMANGAME_H__

#include <string>
//NOTE: C++11 unordered_set
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cctype>
#include <cassert>
#include "Util.h"

using namespace std;

class HangmanGame {
public:
  /**
   * A enum for the current state of the game
   */
  //NOTE: C++11 enum class
  enum class Status { GAME_WON, GAME_LOST, KEEP_GUESSING };

  /**
   * A marker for the letters in the secret words that have not been guessed yet.
   */
  static const char MYSTERY_LETTER;

  /**
   * @param secretWord The word that needs to be guessed
   * @param maxWrongGuesses The maximum number of incorrect word/letter guesses that are allowed
   */
  HangmanGame(const string & secretWord, int maxWrongGuesses) {
    _secretWord = toUpper(secretWord);
    _guessedSoFar.resize(secretWord.size(), MYSTERY_LETTER);
    _maxWrongGuesses = maxWrongGuesses;
  }

  /**
   * Guess the specified letter and update the game state accordingly
   * @return The string representation of the current game state
   * (which will contain MYSTERY_LETTER in place of unknown letters)
   */
  const string & guessLetter(char ch);

  /**
   * Guess the specified word and update the game state accordingly
   * @return The string representation of the current game state
   * (which will contain MYSTERY_LETTER in place of unknown letters)
   */
  const string & guessWord(const string & guess);

  /**
   * @return The score for the current game state
   */
  int currentScore() const {
    return gameStatus() == Status::GAME_LOST ? 25 : \
      numWrongGuessesMade() + _correctlyGuessedLetters.size();
  }

  /**
   * @return The current game status
   */
  Status gameStatus() const {
    if (_secretWord == _guessedSoFar) {
      return Status::GAME_WON;
    }
    else if (numWrongGuessesMade() > _maxWrongGuesses) {
      return Status::GAME_LOST;
    }
    else {
      return Status::KEEP_GUESSING;
    }
  }

  /**
   * @return Number of wrong guesses made so far
   */
  int numWrongGuessesMade() const {
    return _incorrectlyGuessedLetters.size() + _incorrectlyGuessedWords.size();
  }

  /**
   * @return Number of wrong guesses still allowed
   */
  int numWrongGuessesRemaining() const {
    return getMaxWrongGuesses() - numWrongGuessesMade();
  }

  /**
   * @return Number of total wrong guesses allowed
   */
  int getMaxWrongGuesses() const {
    return _maxWrongGuesses;
  }

  /**
   * @return The string representation of the current game state
   * (which will contain MYSTERY_LETTER in place of unknown letters)
   */
  const string & getGuessedSoFar() const {
    return _guessedSoFar;
  }

  /**
   * @return Set of all correctly guessed letters so far
   */
  const unordered_set<char> & getCorrectlyGuessedLetters() const {
    return _correctlyGuessedLetters;
  }

  /**
   * @return Set of all incorrectly guessed letters so far
   */
  const unordered_set<char> & getIncorrectlyGuessedLetters() const {
    return _incorrectlyGuessedLetters;
  }

  /**
   * @return Set of all guessed letters so far
   */
  unordered_set<char> getAllGuessedLetters() const {
    unordered_set<char> guessed;
    guessed.insert(_correctlyGuessedLetters.begin(), _correctlyGuessedLetters.end());
    guessed.insert(_incorrectlyGuessedLetters.begin(), _incorrectlyGuessedLetters.end());
    return guessed;
  }

  /**
   * @return Set of all incorrectly guessed words so far
   */
  const unordered_set<string> & getIncorrectlyGuessedWords() const {
    return _incorrectlyGuessedWords;
  }

  /**
   * @return The length of the secret word
   */
  int getSecretWordLength() const {
    return _secretWord.length();
  }

  string toString() const {
    stringstream ss;
    ss << _guessedSoFar << "; score=" << currentScore() << "; status=" << (int)gameStatus();
    return ss.str();
  }

private:
  void assertCanKeepGuessing() const {
    if (gameStatus() != Status::KEEP_GUESSING) {
      stringstream ss;
      ss << "Cannot keep guessing in current game state: " << (int)gameStatus();
      assert(0 && ss.str().c_str());
    }
  }

  /**
   * The word that needs to be guessed
   */
  string _secretWord;

  /**
   * The maximum number of wrong letter/word guesses that are allowed (e.g. 6, and if you exceed 6 then you lose)
   */
  int _maxWrongGuesses;

  /**
   * The letters guessed so far (unknown letters will be marked by the MYSTERY_LETTER constant). For example, 'AB--T'
   */
  string _guessedSoFar;

  /**
   * Set of all correct letter guesses so far
   */
  unordered_set<char> _correctlyGuessedLetters;

  /**
   * Set of all incorrect letter guesses so far
   */
  unordered_set<char> _incorrectlyGuessedLetters;

  /**
   * Set of all incorrect word guesses so far
   */
  unordered_set<string> _incorrectlyGuessedWords;
};

#endif
