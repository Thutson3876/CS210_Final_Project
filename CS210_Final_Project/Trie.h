#pragma once
#include <iostream>
#include <unordered_map>
#include <string>
#include "City.h"

struct TrieNode {
	bool isEndOfWord;
	double population = 0;
	std::unordered_map<char, TrieNode*> children;

	TrieNode() : isEndOfWord(false) {}
};

class Trie {

private:

	TrieNode* root;

public:

	Trie() {
		root = new TrieNode();
	}

	void insert(const std::string& key, double population);

	City* search(const std::string& key);
};

