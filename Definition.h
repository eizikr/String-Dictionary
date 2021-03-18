#include "String.h"
#ifndef _DEFINITION_H
#define _DEFINITION_H

class Definition {
	String word;	//the word
	String** interpretations;	//all the interpretatoions of the word
	int interpretations_number;		//interpretatoions number
	const void sortInterpretations()const;	//sort the interpretatoions by the A B C
public:
					//c'tors//
	Definition(String = "Unknoun", int = 0, String** = NULL);//default
	Definition(const Definition&);
	~Definition();
					//operators//
	Definition& operator=(const Definition&);
	const bool operator==(const Definition&)const;
	friend ostream& operator<<(ostream&, const Definition&);
	friend istream& operator>>(istream&, Definition&);
	Definition& operator -=(int);
	Definition& operator += (const String&);
	String& operator [](int);
	const String& operator [](int)const;
	const bool operator> (const Definition&);

					//methods//
	const String getWord()const { return word; }
	const int getInterpretationsNumber()const { return interpretations_number; }
};
#endif // !_DEFINITION_H
