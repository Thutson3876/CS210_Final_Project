#include "Trie.h"

void Trie::insert(const std::string& key, double population) {
	TrieNode* node = root;

	for (char c : key) {
		c = tolower(c); // Case-insensitive
		if (node->children.count(c) == 0)
			node->children[c] = new TrieNode();
		node = node->children[c];
	}

	node->population = population;
	node->isEndOfWord = true;
}

City* Trie::search(const std::string& key) {
	TrieNode* node = root;

	for (char c : key) {
		c = tolower(c);
		if (node->children.count(c) == 0)
			return nullptr;
		node = node->children[c];
	}

	std::string countryCode = key.substr(0, 2);
	std::string name = key.substr(2, key.size() - 1);

	return new City(countryCode, name, node->population);
}