#ifndef __MYGUESSINGSTRATEGY_H__
#define __MYGUESSINGSTRATEGY_H__

#include <vector>
//NOTE: C++11 unordered_set
#include <unordered_set>
//NOTE: C++11 unordered_map
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include "GuessingStrategy.h"
#include "HangmanGame.h"

class MyGuessingStrategy : public GuessingStrategy {
private:
  /**
   * A WordSet is a set of words having the same pattern.
   * A pattern is a string returned by HangmanGame::getGuessedSoFar. It's like
   * "AB-", which matches words like "ABC", "ABD" and "ABX", but not "ABA" or "ABB".
   * A WordSet contains statistical info about letters that are NOT GUESSED yet.
   */
  class WordSet {
  private:

    class LetterStat {
    public:
      //NOTE: C++11 in-class initialization
      char _ch = 0;
      int _count = 0;  //How many times the letter appears in a WordSet
      int _wordCount = 0;  //How many words contains the letter in a WordSet

      LetterStat(char ch) : _ch(ch) {}

      //STL containers like map require a default constructor.
      //NOTE: C++11 "= default" generating the default behavior by compiler.
      LetterStat() = default;

      bool operator<(const LetterStat & rhs) const {
        if (_count > rhs._count)
          return true;
        if (_count == rhs._count)
          return _wordCount - rhs._wordCount < 0;
        return false;
      }
    };

    /**
     * A map of letters to their statistical info.
     */
    unordered_map<char, LetterStat> _stat;

    /**
     * Letters in descendent order on frequency
     */
    vector<LetterStat> _order;

    /**
     * Words in the set.
     */
    vector<string> _words;

    /**
     * Determine if a word matches the pattern and guessed letters.
     */
    bool match(const string & word);

    bool insert(const string & word);

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
      while (first != last) {
        insert(*first);
        ++first;
      }
    }

  public:
    class Iterator {
    public:
      Iterator(const WordSet & wordSet, bool end = false) : _words(wordSet._words) {
        _pos = end ? _words.size() : 0;
      }

      Iterator & operator++() {
        assert(_pos < _words.size());
        ++_pos;
        return *this;
      }

      const string & operator*() {
        assert(_pos < _words.size());
        return _words[_pos];
      }

      bool operator==(const Iterator & rhs) {
        return _pos == rhs._pos && &_words == &rhs._words;
      }

      bool operator!=(const Iterator & rhs) {
        return !operator==(rhs);
      }

    private:
      const vector<string> & _words;
      int _pos;
    };

    string _pattern;

    vector<bool> _guessedLetters;

    template<class InputIterator>
    WordSet(const string & pattern, const vector<bool> & guessedLetters, InputIterator first, InputIterator last) {
      _pattern = pattern;
      _guessedLetters = guessedLetters;
      insert(first, last);
      makeOrder();
      _stat.clear();
    }

    void makeOrder() {
      //NOTE: C++11 auto and for
      for (const auto & elem : _stat) {
        _order.push_back(elem.second);
      }
      sort(_order.begin(), _order.end());
    }

    int size() {
      return _words.size();
    }

    Iterator begin() const {
      return Iterator(*this);
    }

    Iterator end() const {
      return Iterator(*this, true);
    }

    /**
     * Give a suggest of the most probable letter not in the excluded letter set.
     */
    char suggest(const vector<bool> & excluded) {
      //NOTE: C++11 auto and for
      for (const auto & ls : _order) {
        if (!excluded[ls._ch - 'A']) {
          return ls._ch;
        }
      }
      assert(false);
      return '\0';
    }

    string toString() {
      stringstream ss;
      ss << "WordSet[" << size() << "]";
      return ss.str();
    }
  };

  //NOTE: C++11 unique_ptr
  unique_ptr<WordSet> _wordset;

  static int numOfBlanks(const string & pattern) {
    int count = 0;
    for (char ch : pattern) {
      if (ch == HangmanGame::MYSTERY_LETTER)
        count++;
    }
    return count;
  }

  static inline vector<bool> charSetToVec(const unordered_set<char> & set) {
    vector<bool> vec(26);
    for (char ch : set) {
      vec[ch - 'A'] = true;
    }
    return vec;
  }

  //Disable copy and assignment
  //NOTE: C++11 "= delete"
  MyGuessingStrategy(const MyGuessingStrategy &) = delete;

  MyGuessingStrategy & operator=(const MyGuessingStrategy &) = delete;

public:
  template<class InputIterator>
  MyGuessingStrategy(const HangmanGame & game, InputIterator first, InputIterator end) {
    const string & pattern = game.getGuessedSoFar();
    int len = pattern.length();
    vector<string> words;
    for (; first != end; ++first) {
      if (first->length() == len) {
        words.push_back(*first);
      }
    }
    _wordset.reset(new WordSet(pattern, charSetToVec(game.getAllGuessedLetters()), words.begin(), words.end()));
  }

  //NOTE: C++11 shared_ptr and override
  shared_ptr<Guess> nextGuess(const HangmanGame & game) override;

  //NOTE: C++11 override
  string toString() const override {
    stringstream ss;
    ss << "MyGuessingStrategy[" << _wordset->toString() << "]";
    return ss.str();
  }
};

#endif
