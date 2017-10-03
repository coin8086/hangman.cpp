#include "MyGuessingStrategy.h"
#include "GuessLetter.h"
#include "GuessWord.h"

bool MyGuessingStrategy::WordSet::match(const string & word) {
  int size = _pattern.length();
  assert(size == word.length());

  bool ret = true;
  for (int i = 0; i < size; i++) {
    if (_pattern[i] != HangmanGame::MYSTERY_LETTER) {
      if (_pattern[i] != word[i]) {
        ret = false;
        break;
      }
    }
    else {
      if (_guessedLetters.count(word[i]) > 0) {
        ret = false;
        break;
      }
    }
  }
  return ret;
}

bool MyGuessingStrategy::WordSet::insert(const string & word) {
  if (!match(word)) {
    return false;
  }

  unordered_set<char> parsed;
  for (char ch : word) {
    if (!_guessedLetters.count(ch)) {
      LetterStat & stat = _stat[ch];
      stat._ch = ch;
      stat._count++;
      if (parsed.insert(ch).second) {
        stat._wordCount++;
      }
    }
  }
  _words.push_back(word);
  return true;
}

shared_ptr<Guess> MyGuessingStrategy::nextGuess(const HangmanGame & game) {
  const string & pattern = game.getGuessedSoFar();
  const unordered_set<char> & guessedLetters = game.getAllGuessedLetters();
  unordered_set<char> guessed(guessedLetters);
  const unordered_set<string> & wrongWords = game.getIncorrectlyGuessedWords();
  //NOTE: The strategy will make a word guess either when there's only one
  //word in the wordset, or when there's only one blank left.
  //When a word guess failed, the incorrectly guessed letter in the word should be
  //counted.
  if (!wrongWords.empty()) {
    int idx = pattern.find(HangmanGame::MYSTERY_LETTER);
    for (const auto & wd : wrongWords) {
      guessed.insert(wd[idx]);
    }
  }

  //TODO: Is it OK to use "==" for C++ sets?
  //Update the wordset when the game status(pattern and guessed) doesn't match.
  if (!(pattern == _wordset->_pattern && guessed == _wordset->_guessedLetters)) {
    //Update wordset on a previous guess result, be it successful or not.
    _wordset.reset(new WordSet(pattern, guessed, _wordset->begin(), _wordset->end()));
  }

  if (_wordset->size() == 1) {
    return shared_ptr<Guess>(new GuessWord(*_wordset->begin()));
  }

  if (numOfBlanks(pattern) > 1) {
    if (!game.numWrongGuessesRemaining()) {
      //Simply return the first word in the word set for the last chance.
      return shared_ptr<Guess>(new GuessWord(*_wordset->begin()));
    }
    else {
      return shared_ptr<Guess>(new GuessLetter((_wordset->suggest(guessedLetters))));
    }
  }
  else {
    //TODO: Any "replace" algorithm?
    //When there's only one blank letter, try to guess the word to save one
    //score on a successfull guess.
    char ch = _wordset->suggest(guessed);
    int idx = pattern.find(HangmanGame::MYSTERY_LETTER);
    string word = pattern;
    word[idx] = ch;
    //TODO: Move operation for Guess and its subclasses since NRVO not applicable
    //for so many returns?
    return shared_ptr<Guess>(new GuessWord(word));
  }
}

