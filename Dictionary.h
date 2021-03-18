#include "Definition.h"
#ifndef _DICTIONARY_H
#define _DICTIONARY_H

class Dictionary {
	int definitions_number;
	Definition** definition;
public:
			//c'tors//
	Dictionary(int = 0, Definition** = NULL);
	Dictionary(const Dictionary&);
	~Dictionary();

			//operators//
	Dictionary& operator=(const Dictionary&);
	const bool operator==(const Dictionary&)const;
	friend ostream& operator<<(ostream&, const Dictionary&);
	friend istream& operator>>(istream&, Dictionary&);
	Dictionary& operator-=(int);
	Dictionary& operator+=(const Definition&);
	Definition& operator[](int);
	const Definition& operator[](int)const;

				//methods//
	const int checkIfWordExist(const String&)const;	//check if the definition is already exist in the dictionary
	void sortDefinitions();//sort the definitions names by the A B C

	const int getDefinitionsNumber()const { return definitions_number; } 
};
#endif // !_DICTIONARY_H
