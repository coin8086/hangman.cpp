#include "HangmanGame.h"

const char HangmanGame::MYSTERY_LETTER = '-';

const string & HangmanGame::guessLetter(char ch) {
  assertCanKeepGuessing();
  ch = toupper(ch);

  // update the _guessedSoFar buffer with the new character
  bool goodGuess = false;
  for (int i = 0; i < _secretWord.size(); i++) {
    if (_secretWord[i] == ch) {
      _guessedSoFar[i] = ch;
      goodGuess = true;
    }
  }

  // update the proper set of guessed letters
  if (goodGuess) {
    _correctlyGuessedLetters.insert(ch);
  }
  else {
    _incorrectlyGuessedLetters.insert(ch);
  }

  return getGuessedSoFar();
}

const string & HangmanGame::guessWord(const string & word) {
  assertCanKeepGuessing();
  string guess = toUpper(word);

  if (guess == _secretWord) {
    // if the guess is correct, then set _guessedSoFar to the secret word
    _guessedSoFar = _secretWord;
  }
  else {
    _incorrectlyGuessedWords.insert(guess);
  }

  return getGuessedSoFar();
}

