#include "Definition.h"

Definition::Definition(String _word, int number, String** _definitions) :word(_word)
{
	if (_definitions != NULL && number != 0)//check if there is no interpretatoions
	{
		interpretations_number = number;
		interpretations = new String*[interpretations_number];		//allocate memory and set strings
		for (int i = 0; i < interpretations_number; i++)
		{
			interpretations[i] = new String;
			interpretations[i] = _definitions[i];
		}
	}
	else//default interpretatoions
	{
		interpretations = NULL;
		interpretations_number = 0;
	}
}

Definition::Definition(const Definition& obj) : word(obj.word)
{
	if (obj.interpretations != NULL) 
	{
		interpretations_number = obj.interpretations_number;
		interpretations = new String*[interpretations_number];	//allocate memory and set strings
		for (int i = 0; i < interpretations_number; i++)
			interpretations[i] = new String(*(obj.interpretations[i]));
	}
	else
	{
		interpretations = NULL;
		interpretations_number = 0;
	}
}

Definition::~Definition()
{
	for (int i = 0; i < interpretations_number; i++)	//free all interpretations
		delete interpretations[i];
	delete[] interpretations;
}

Definition& Definition::operator=(const Definition& obj)
{
	if (this != &obj) //check self assigment
	{
		word = obj.word;
		if (obj.interpretations == NULL)	//if we copy null string delete our string
		{
			for (int i = 0; i < interpretations_number; i++)
				delete interpretations[i];
			delete[] interpretations;
			interpretations_number = 0;
		}
		else {
			for (int i = 0; i < interpretations_number; i++)	//delete interpretations
				delete interpretations[i];
			delete[] interpretations;
			interpretations_number = obj.interpretations_number;	
			interpretations = new String*[interpretations_number];	//allocate memory and set values
			for (int i = 0; i < interpretations_number; i++)
				interpretations[i] = new String(*(obj.interpretations[i]));
		}
	}
	else
		cout << "Self assigment!\n";
	return *this;
}

const bool Definition::operator==(const Definition& obj) const
{
	return word == obj.word;
}

ostream& operator<<(ostream& output, const Definition& obj)
{
	output << endl;
	output << obj.word << ":\n";
	if (obj.interpretations != NULL)	//check if there is interpretations
		for (int i = 0; i < obj.interpretations_number; i++)
			cout << "Interpretation " << i + 1 << ": " << obj[i] << endl;
	else
		cout << "No interpretations\n";
	return output;
}

istream& operator>>(istream& input, Definition& obj)
{
	int size;
	String temp;	//temp string to get values

	if (obj.interpretations != NULL)	//check if there is interpretations to delete
	{
		for (int i = 0; i < obj.interpretations_number; i++)
			delete obj.interpretations[i];
		delete[] obj.interpretations;
	}
	cout << "\nEnter a word:";
	input >> obj.word;
	obj.word.setWord();		//make sure word is ligal
	cout << "How many interpretations do you want to enter:";
	cin >> size;
	////	make sure he enter number bigger then 0	  ////
	while (size <= 0)
	{
		cout << "Every definition must have at least 1 interpretation!\n";
		cout << "How many interpretations do you want to set:";
		cin >> size;
	}
	////	set first interpretation	////
	obj.interpretations_number = 1;
	obj.interpretations = new String*[1];
	cout << "Interpretation " << 1 << ":";
	getchar();
	input >> temp;
	obj.interpretations[0] = new String(temp);

	////	set rest of them	////
	for (int i = 1; i < size; i++)
	{
		cout << "Interpretation " << i + 1 << ":";
		input >> temp;
		obj += temp;
	}
		obj.sortInterpretations();//sort by A B C
	return input;
}

Definition& Definition::operator-=(int index)
{
	if (index > interpretations_number || index <= 0)	//check if index is exist
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	else {
		String **temp = interpretations;	//copy pointers
		if (temp != NULL)//check if there is strings to check
		{
			interpretations = new String*[--interpretations_number];	//interpretations - 1 is new memory

			for (int i = 0, u = 0; i < interpretations_number + 1; i++)//check who is the string and free his memory
				if (i != index - 1)
					interpretations[u++] = temp[i];
			delete temp[index - 1];
		}
		else
			cout << "No interpretations\n";
		delete[] temp;
		sortInterpretations();//sort by A B C
		return *this;
	}
}

Definition& Definition::operator+=(const String& new_commentaries)	//add a definition
{
	for (int i = 0; i < interpretations_number; i++)	//check if already inside
		if (*interpretations[i] == new_commentaries)
		{
			cout << "~ This interpretation already exist in the word definition, Cant let him in ~\n";
			return *this;
		}
	String** temp = interpretations;
	if (temp != NULL) 
	{	// 	 allocate new memory and 	//
		interpretations = new String*[++interpretations_number];
		for (int i = 0; i < interpretations_number - 1; i++)
			interpretations[i] = temp[i];
		interpretations[interpretations_number - 1] = new String(new_commentaries);
	}
	delete[] temp;
	return *this;
}

String& Definition::operator[](int index) 
{//return interpretation by index
	if (index < 0 || index >= interpretations_number)
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return *interpretations[index];
}

const String& Definition::operator[](int index)const
{//return interpretation by index
	if (index < 0 || index >= interpretations_number)
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return *(interpretations[index]);
}

const bool Definition::operator>(const Definition& obj)
{//compare word by A B C and length
	if (this->word > obj.word)
		return true;
	return false;
}

const void Definition::sortInterpretations() const
{//sort all the Interpretations of this definition 
	String temp;
	int flag;
	do {	//"bubble sort"//
		flag = 0;
		for (int i = 0; i < interpretations_number - 1; i++)
		{
			if (*interpretations[i] > *interpretations[i + 1])//cmp definitions
			{//switch theme
				temp = *interpretations[i];
				*interpretations[i] = *interpretations[i + 1];
				*interpretations[i + 1] = temp;
				flag = 1;
			}
		}
	} while (flag == 1);
}

