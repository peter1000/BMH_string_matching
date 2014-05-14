#include <stdio.h>
#include <stdlib.h>
#define MAX_ALPHA_CHARS 256 

/**********************************
My implementation and testing of the Boyer-Moore-Horpool algorithm for counting each occurence of a needle (string) in a haystack (string).
Overlapping strings are counted, e.g., 
haystack = "ababababa", needle = "aba" returns 4 occurences. 
**********************************/


/*** utility function to return max of two ints ***/
int max(int a, int b){
    return (a > b) ? a : b;
}


/*** implementation of strlen to return length of str ***/
int myStrLen(char * str){
    int i = 0;
    if(str){
        for(i = 0; str[i]; i++);
    }
    return i;
}


/*** Boyer-Moore-Horspool implementation ***/
int BMH_algo(char * txt, char * needle){
    int i, matches = 0;
    int txtLen = myStrLen(txt);
    int needleLen = myStrLen(needle);

    if((txtLen == 0) || (needleLen == 0)){ 
        fprintf(stderr, "Neither string may be NULL.\n");
        return -1;
    }

    /*** bad char heuristics table (for BMH algo) ***/
    int badCharHtable[MAX_ALPHA_CHARS];


    /*** Initialize badCharHtable values ***/
    for(i = 0; i < MAX_ALPHA_CHARS; i++){
        badCharHtable[i] =  -1;
    }

    /*** Change badCharHtable index for each "needle-char" to its 
    last occurrence of the char within needle ***/
    for(i = 0; i < needleLen; i++){
        badCharHtable[(int) needle[i]] = i;
    }

    int shift = 0;
    
    /*** begin search of txt, until last possible 
    match position is reached***/
    while(shift <= txtLen-needleLen){
        /*** set index to last char in needle ***/
        int nInd = needleLen-1;
    
        /*** While we have a match, move nInd down until a
        mismatch or fully matched neeledLen ***/
        while((nInd >= 0) && 
            (needle[nInd] == txt[shift + nInd])){ 
            nInd--;
        }

        /*** FOUND A MATCH, increment matches ***/
        if(nInd < 0){
            matches++;

            /*** if we still have room in txt for another 
            needle match ***/ 
            if(shift + needleLen < txtLen){ 
                /*** update shift to index where position of last
                occurrence in needle matches next char in txt***/
                shift += needleLen - badCharHtable[txt[shift + needleLen]];
            }
            else{
               shift += 1;
            }
        }
        else{
            /*** NO MATCH, update shift to place where the
            mismatched "badChar" in txt is lined up with 
            the last occurence of it in needle ***/
            shift += max(1, nInd - badCharHtable[txt[shift+nInd]]);
        }
    }   
    return matches;
}


int main(){
    int results = 0, passed_tests = 0, ttl_tests = 9;
    fprintf(stdout, "Testing...\n\n");

    /*** TEST CASE 1, given ***/
    char txt1[] = " my dog really likes to run in the dog park";
    char needle1[] = "dog";
    results = BMH_algo(txt1, needle1);
    fprintf(stdout, "Test Case 1:\n");
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt1, needle1, results);
    if(results == 2){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }

    /*** TEST CASE 2, case sensitivity (code can be modified 
    to be insensitive) ***/
    char txt2[] = "Seriously though, my DOG REALLY likes to run in the dog park";
    char needle2[] = "dog";
    results = BMH_algo(txt2, needle2);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt2, needle2, results);
    if(results == 1){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }

    /*** TEST CASE 3, test occurrence of single char in both
    strings mismatched ***/
    char txt3[] = "dddddd";
    char needle3[] = "kk";
    results = BMH_algo(txt3, needle3);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt3, needle3, results);
    if(results == 0){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }

    /*** TEST CASE 4, test occurrence of single char in both
    strings, matched ***/
    char txt4[] = "dddddd";
    char needle4[] = "ddd";
    results = BMH_algo(txt4, needle4);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt4, needle4, results);
    if(results == 4){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }


    /*** TEST CASE 5, test occurrence of needle is
    empty string***/
    char txt5[] = "abcdefg";
    char needle5[] = "";
    results = BMH_algo(txt5, needle5);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt5, needle5, results);
    if(results == -1){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }

    /*** TEST CASE 6, test occurrence of txt is empty string ***/
    char txt6[] = "";
    char needle6[] = "abc";
    results = BMH_algo(txt6, needle6);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt6, needle6, results);
    if(results == -1){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }


    /*** TEST CASE 7, test occurrence of txt and needle are 
    empty strings***/
    char txt7[] = "";
    char needle7[] = "";
    results = BMH_algo(txt7, needle7);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt7, needle7, results);
    if(results == -1){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }


    /*** TEST CASE 8, test occurrence of repeating string that 
    isn't a repeated char***/
    char txt8[] = "ababababa";
    char needle8[] = "aba";
    results = BMH_algo(txt8, needle8);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt8, needle8, results);
    if(results == 4){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }


    /*** TEST CASE 9, test occurrence of needle with length greater
    than txt length***/
    char txt9[] = "my";
    char needle9[] = "my dog";
    results = BMH_algo(txt9, needle9);
    fprintf(stdout, "HAYSTACK: %s\nNEEDLE: %s\nRESULTS = %d\n", 
        txt9, needle9, results);
    if(results == 0){
        fprintf(stdout, "Passed test.\n\n");
        passed_tests++;
    }
    else{
        fprintf(stdout, "Failed test.\n\n");
    }
 

    /*** Summary of results ***/
    fprintf(stdout, "\n\nPassed %d out of %d tests.\n", 
        passed_tests, ttl_tests);
    return 0;
}
        
           

        
  

