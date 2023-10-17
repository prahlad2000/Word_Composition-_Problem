#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
using namespace std;

// this program calculate the longest and the second longest compounded  words in a file
// And calculated time taken to process the input file

class Node
{
public:
    char character;
    unordered_map<char, Node *> children;
    bool islastnode;

    Node(char ch = '\0', bool lastnode = false) : character(ch), islastnode(lastnode) {}
};

class Trie
{
public:
    Node *root;

    Trie()
    {
        root = new Node();
    }

    void insert(const string &word)
    {

        /* This method is used to insert the word into the trie.*/

        Node *curr = root;
        for (char ch : word)
        {
            /*if the current character word is not in the children list of the node pointed by curr add the character as a child to the current node
            and set the curr child of itself pointed by the current character*/

            if (curr->children.find(ch) == curr->children.end())
            {
                curr->children[ch] = new Node(ch);
            }
            curr = curr->children[ch];
        }

        /*After reading the entire word , set the final charachter to which curr is now
        pointing as the lastnode character*/
        curr->islastnode = true;
    }

    bool contains(const string &word)
    {
        // This method helps to check if the trie contains a certain word as
        //   a valid word (i.e ->  The word ends with a lastnode Character node)

        Node *curr = root;
        for (char ch : word)
        {
            //   Whenever even one character of the word is not found, False is returned.
            //  If the entire word has been traversed and the final character is found to be
            //  a lastnode character , True is returned. Else False is returned.
            if (curr->children.find(ch) == curr->children.end())
            {
                return false;
            }
            curr = curr->children[ch];
        }
        return curr->islastnode;
    }

    vector<string> getPrefixes(const string &word)
    {
        /* This method returns all the possible prefixes of a word already existing in
         the trie*/
        string prefix;
        vector<string> prefixes;
        Node *curr = root;
        for (char ch : word)
        {
            /*        Whenever the currently read character is not found within the children of
                      the current trie, the prefixes list is returned, else we traverse all the
                      characters in the word and keep appending prefix with the current character
                      untill we reach a lastnode node, where we append the prefixes list with the
                      prefix
            */

            if (curr->children.find(ch) == curr->children.end())
            {
                return prefixes;
            }
            curr = curr->children[ch];
            prefix += ch;
            if (curr->islastnode)
            {
                prefixes.push_back(prefix);
            }
        }
        return prefixes;
    }
};

class Solution
{
public:
    Trie trie;
    deque<pair<string, string>> queue;

    void buildTrie(const string &filePath)
    {
        try
        {
            ifstream file(filePath);
            string line;
            while (getline(file, line))
            {
                /*
                    If prefixes are found, simply divide the word into its respective
                    suffix and enter the word ,suffix into the deque.
                    Finally Insert the word into the trie.*/
                string word = line;
                vector<string> prefixes = trie.getPrefixes(word);
                for (const string &prefix : prefixes)
                {
                    queue.push_back(make_pair(word, word.substr(prefix.length())));
                }
                trie.insert(word);
            }
        }
        catch (...)
        {
            cerr << "Error found in the file!" << endl;
            exit(0);
        }
    }

    pair<string, string> findLongestCompoundWords()
    {
        /* Finds the longest and second longest compound words within the trie
        and returns them as a pair (longest, secondLongest)*/
        string longestWord = "";
        int longestLength = 0;
        string secondLongest = "";

        while (!queue.empty())
        {
            pair<string, string> entry = queue.front();
            queue.pop_front();
            string word = entry.first;
            string suffix = entry.second;
            /* if the suffix is found in trie  and valid  check the length of the word if greater than previous longest length
             change the second longest and record the new longest */

            if (trie.contains(suffix) && word.length() > longestLength)
            {
                secondLongest = longestWord;
                longestWord = word;
                longestLength = static_cast<int>(word.length());
            }
            else
            {
                /*  Else get the possible prefixes for the suffix of the word.
                If prefixes are found, simply divide the word into its respective
                suffix and enter the word ,suffix into the deque.*/
                vector<string> prefixes = trie.getPrefixes(suffix);
                for (const string &prefix : prefixes)
                {
                    queue.push_back(make_pair(word, suffix.substr(prefix.length())));
                }
            }
        }

        return make_pair(longestWord, secondLongest);
    }
};

int main()
{
    auto start = chrono::high_resolution_clock::now();
    Solution sol;
    sol.buildTrie("Input_01.txt");
    pair<string, string> result = sol.findLongestCompoundWords();

    cout << "Longest Compound Word: " << result.first << endl;
    cout << "Second Longest Compound Word: " << result.second << endl;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken to process the first input file: " << elapsed.count() << " seconds" << endl;
    return 0;
}
