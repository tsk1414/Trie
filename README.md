# Trie

Implement a trie (prefix tree) and use it to autocomplete words.
In C++, the trie node and class definitions might look like:

struct TrieNode {

bool isLeaf;

vector<TrieNode*> letters;

};

class Trie {

TrieNode* root;

};


You will need to implement the following operations:

- lookup(string) which returns a boolean indicating whether given word was found.
- insert(string) which inserts the given word into the trie.
- remove(string) which removes the given word from the trie (really removes it, not just
changing the flag).
- info() which prints out the number of nodes and number of words in the trie.
- alphabetical() which prints out the words in the trie in alphabetical order.
- autocomplete(prefix, k) which prints alphabetically all possible words that can be
formed by the given prefix and k additional characters.

Input

- The first line of the input will be an integer n indicating how many commands follow
it.
- The next n lines will consist of one of 6 commands (”insert”, ”remove”, ”lookup”,
”info”, ”alphabetical”, and ”autocomplete”).
- The commands ”insert”, ”remove”, and ”lookup” will be followed by a space, then a
string representing the word to perform the command on.
- The commands ”info” and ”alphabetical” have nothing following it.
- The command ”autocomplete” will be followed by a space, then a string to perform
the command on, then a space, then finally an integer representing the number of
additional characters to consider. The integer may be a special value of ”-1” which
means consider all words without a length limitation.
At the end of the input there will be a blank line. Your program should initialize an
empty trie and perform the commands given by the input, in sequence, on it.

Output
- For the ”insert” and ”remove” commands, print nothing.
- For the ”lookup” command, print the line ”0” if the string is not found and the line
”1” if it is found.
- For the ”info” command, print a line containing two space separated integers. The
first integer is the number of nodes in the trie, the second is the number of words.
- For the ”alphabetical” command, print all the words contained in the trie in alphabetical order. One word per line.
- For the ”autocomplete” command, print the possible autocompleted words on a single
space-separated line in alphabetical order (the line will end in a space).

