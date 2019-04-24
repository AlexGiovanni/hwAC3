//Alexis Santiago 10/13/18 20241845
#include "autocompleter.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


	// Creates a new Autocompleter with an empty dictionary.
	//
	// Must run in O(1) time.
Autocompleter::Autocompleter() {
	root = new Node();
}

	// Adds a string x to the dictionary.
	// If x is already in the dictionary, does nothing.
	//
	// Must run in O(1) time.
void Autocompleter::insert(string x, int freq) {
	int i = 0;
	Node * c = root;

	while (i < x.length())
	{
		
		
		if (c->top.size() == 0) {//if nothing is in top
			Entry en;	en.freq = freq; en.s = x;//create entry
			c->top.push_back(en);//insert into top
		}
		else {//check if it belongs in top, insert end remove greater than 3
			int insertIndex = -1;
			for (unsigned y = 0; y < c->top.size(); y++) {
				if (freq > c->top[y].freq) {
					insertIndex = y;
					break;
				}
			}
			if (insertIndex != -1) {//insert
			Entry en; en.freq = freq; en.s = x;
			c->top.insert(c->top.begin() + insertIndex, en);
			}
			else if (insertIndex == -1) {//insert at the end if greater than 3 it will be removed
				Entry en; en.freq = freq; en.s = x;
				c->top.push_back(en);
			}
			//remove the completions greater than 3
			while (c->top.size() > 3) {
			  c->top.pop_back();
			}
		}

		
		//create node if path not already in Trie
		if (c->children[x[i]] == nullptr) {//if the letter is not in the array
			c->children[x[i]] = new Node();
		}

		//move pointer down proper path
		c = c->children[x[i]];
		i++;
	}
	
	if (c->top.size() == 0) {//if nothing is in top
		Entry en;	en.freq = freq; en.s = x;//create entry
		c->top.push_back(en);//insert into top
	}
	else {//check if it belongs in top, insert end remove greater than 3
		int insertIndex = -1;
		for (unsigned y = 0; y < c->top.size(); y++) {
			if (freq > c->top[y].freq) {
				insertIndex = y;
				break;
			}
		}
		if (insertIndex != -1) {//insert
			Entry en; en.freq = freq; en.s = x;
			c->top.insert(c->top.begin() + insertIndex, en);
		}
		else if (insertIndex == -1) {//insert at the end if greater than 3 it will be removed
			Entry en; en.freq = freq; en.s = x;
			c->top.push_back(en);
		}
		//remove the completions greater than 3
		while (c->top.size() > 3) {
			c->top.pop_back();
		}
	}



	//set marked to true to add s to Trie
	if (c->marked == false)
		c->marked = true;
	
}//end insert

	// Returns the number of strings in the dictionary.
	// 
	// Must run in O(1) time.
int Autocompleter::size() {
	return size_recurse(root);
}//end size

	// Fills the vector T with the three most-frequent completions of x.
	// If x has less than three completions, then 
	// T is filled with all completions of x.
	// The completions appear in T from most to least frequent.
	// 
	// Must run in O(1) time.
void Autocompleter::completions(string x, vector<string> &T) {
	Node * c = root;
	while (T.size() != 0) { T.pop_back(); }//delete whats inside of T
	//step 1: travel down trie,
	//according to letters of x
	for (int i = 0; i < x.length(); i++){
		c = c->children[x[i]];
		if (c == nullptr) {
			return;
		}
			
	}

	//step 2: set T to whatever is in top
	for (int i = 0; i < c->top.size(); i++) {
	T.push_back(c->top[i].s);
	}
	

}//end completions


//helper size function
int Autocompleter::size_recurse(Node * r) {
	if (r == nullptr){	return 0; }
	else {
		int total = 0;

		//count node P if it's marked
		if (r->marked)
			total++;

		//add in words for all subtrees
		for (int i = 0; i < 256; i++){
			total += size_recurse(r->children[i]);
		}

		return total;
	}
}
