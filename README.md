BMH_string_matching
===================

My implementation in C of the Boyer-Moore-Horspool algorithm for string matching, including test cases.

Run-time Analysis
=================

The BMH algorithm compares the tail end of the needle string, and skips over multiple characters when possible before the next comparison (as opposed to brute force).

n = length of txt string (haystack string)
m = length of needle string

In the best case, this algorithm runs in O(n/m), if the needle does not appear in the haystack (all jumps of size m).  In the worst case, the haystack and needle have the same repeating character, e.g., "ddddddddddd" for haystack and "dddd" for needle, resulting in runtime O(nm).  

A brute force search (moving up one char at a time in the haystack) would result in worst case O(nm), and best case O(n) (if the first char of the needle doesn't appear in the haystack).  

The BMH algorithm is best suited when the domain is similar to the 26-letter English alphabet, and the longer the needle, the better the performance because we can skip over more characters.  If this were a binary string, one may as well use a naive brute force approach and eliminate the overhead of the more complex BMH algorithm.   
