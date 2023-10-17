# Word_Composition-_Problem

<h2>[Approach for this Problem](https://github.com/prahlad2000/Word_Composition-_Problem/blob/main/ImpledgeOA.cpp)</h2>

1. Build a Trie while reading words from the file. For each word, track valid words encountered and push <word, suffix> pairs into a deque.

2. Initialize longest, second_longest, and max_length variables.
3. Process the deque:
    -> While it's not empty, pop <word, suffix> pairs.
    -> Check if the suffix contains valid prefixes from the Trie.
          * If the length of the word > max_length, update longest and max_length.
          * If the length of the word > the length of second_longest, update second_longest.
    -> Find new suffixes based on prefixes and push them back into the deque.
4. Return "longest" as the longest compounded word and "second_longest" as the second-longest.





