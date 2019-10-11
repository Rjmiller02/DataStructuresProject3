#include <iostream>
#include "list.h"
#include "queue.h"
#include <cstring>
#include <fstream>

using namespace std;

struct Word {
    string
        word;

    int
        reference = -1;

    LinearList<int>
        hammingWords;
};

Word
    WordList[5757];

int sequentialSearch(Word L[], int, string);
void genLadder(int, int, Word L[]);
void outputFunction(int &s);
int hamming(string w1,string w2)
{
    int counter = 0;

    for (int i = 0; i < 5; i++ )
    {
        if (w1[i] != w2[i])
        {
            counter++;
        }
    }

    return counter;
}



int main() {
    int
        w1,
        w2;

    string
        word1,
        word2;


    string
        fileName = "sgb-words.txt";

    ifstream
        fin;

    fin.open(fileName.c_str());
    if (fin.fail())
    {
        cout << "Unable to open the file: " << fileName << endl;
        exit(1);
    }

    for (int i = 0; i < 5757; i++)
    {
        fin >> WordList[i].word;

        for (int j = 0;j < i;j++)
            if (hamming(WordList[i].word,WordList[j].word) == 1) {
                WordList[i].hammingWords.insert(0, j);
                WordList[j].hammingWords.insert(0, i);
            }
    }

    fin.close();

    cout << "Enter two 5-letter words." << endl;
    cin >> word1;
    cin >> word2;

    w1 = sequentialSearch(WordList, 5757, word1);
    w2 = sequentialSearch(WordList, 5757, word2);

    if ( w1 == -1 )
    {
        cout << "There is no word ladder for Word 1." << endl;
        return 0;
    }
    else if ( w2 == -1 )
    {
        cout << "There is no word ladder for Word 2." << endl;
        return 0;
    }
    else
    {
        genLadder(w1, w2, WordList);
    }

    return 0;

}

int sequentialSearch(Word L[], int n , string k)
{
//procedure SequentialSearch(L,n,k)
//  i <- 0
    int i = 0;

//  while i < n and L[i] != k do
//      i <- i + 1
//  end while
    while ( i < n && L[i].word != k)
    {
        i = i + 1;
    }

// if i < n then
//      return success
//  else
//      return failure
//  end if
    if ( i < n )
    {
        return i;
    }
    else
    {
        return -1;
    }
//end procedure
}

void genLadder(int w1, int w2, Word L[])
{
//procedure GenLadder(w[1], w[2])
    LinearList<int>
        s;

    Queue<int>
        q;

    int
        w,
        v;

//  Clear S
    s.clear();

//  Add w[2] to a queue Q
    q.enqueue(w1);

//  while Q is not empty do
//      Dequeue Q into w

//      for each word v in w.list do
//          if v.ptr = NULL and v != w[2] then
//              v.ptr <- w
//              Enqueue v in Q
//          end if
//      end for
//  end while
    while ( !q.isEmpty() )
    {
        w = q.dequeue();

        for ( int i = 0; i < L[w].hammingWords.size(); i++ )
        {
            v = L[w].hammingWords[i];
            if ( L[v].reference == -1 && v != w1 )
            {
                L[v].reference = w;
                q.enqueue(v);
            }
        }
    }

//  if w[1].ptr != NULL then
//      Append w[1] to S
//      w <- w[1].ptr

//      while w != NULL do
//          Append w to S
//          w <- w.ptr
//      end while
//  end if
    if (L[w2].reference != -1)
    {
        s.insert(0, w2);
        w = L[w2].reference;

        while (w != -1)
        {
            s.insert(0, w);
            w = L[w].reference;
        }
    }

    s.traverse(outputFunction);

    if (WordList[w2].reference == -1)
    {
        cout << "No word ladder exists." << endl;
    }

//end procedure
}

void outputFunction(int &s)
{
    cout << WordList[s].word << endl;
}