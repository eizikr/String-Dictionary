#include <iostream>
#define _CRT_SECURE_NO_WARNINGS
#ifndef _STRING_H
#define _STRING_H
#define MAX_LENGTH 200 //max letters for a string
#define MAX_WORD_LENGTH 80	//max letters for a word

using namespace std;

class String {
	int length;		//size of string
	char* string;	
	const int getStringSize(char*)const;	//return the size of your string
	const int getStringSize(const char*)const;		//return the size of your string
public:
	//c'tors
	String(char* = NULL);
	String(const char*);
	String(const String&);
	~String();

	//operators
	String& operator=(const String&);
	bool operator==(const String&)const;
	bool operator!=(const String&)const;
	friend ostream& operator<<(ostream&, const String&);
	friend istream& operator>>(istream&, String&);
	String& operator-=(char);
	String& operator+=(char);
	char& operator[](int);
	const char& operator[](int)const;
	const bool operator >(const String&)const;

	//methods
	const void ArrangingData();	////makes the string legal (fix: "spaces" , ":" , "," , ".")
	int getLength() { return length; }
	void setWord();	////make sure the string dont have "spaces"//
};
#endif // !STRING.H