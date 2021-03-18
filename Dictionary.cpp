#include "Dictionary.h"

Dictionary::Dictionary(int number, Definition** _definitions)
{
	if (_definitions != NULL && number != 0)
	{	//allocate memory and set values
		definitions_number = number;
		definition = new Definition*[definitions_number];
		for (int i = 0; i < definitions_number; i++)
		{
			definition[i] = new Definition;
			definition[i] = _definitions[i];
		}
	}
	else
	{	//default dictionary is emptey
		definition = NULL;
		definitions_number = 0;
	}
}

Dictionary::Dictionary(const Dictionary& obj):definitions_number(obj.definitions_number)
{
	if (obj.definition != NULL)
	{//allocate memory and set values
		definition = new Definition*[definitions_number];
		for (int i = 0; i < definitions_number; i++)
		{
			definition[i] = new Definition(*(obj.definition[i]));
		}
	}
	else
		definition = NULL;
}

Dictionary::~Dictionary()
{//free alocated definitions memory
	for (int i = 0; i < definitions_number; i++)
		delete definition[i];
	delete[] definition;
}

Dictionary& Dictionary::operator=(const Dictionary& obj)
{
	if (this != &obj)
	{//check self assigment
		if (obj.definition == NULL)
		{//check if we need just to free old memory and no more
			for (int i = 0; i < definitions_number; i++)
				delete definition[i];
			delete definition;
			definitions_number = 0;
		}
		else
		{//allocate new memory and fill with values
			for (int i = 0; i < definitions_number; i++)
				delete definition[i];
			delete definition;
			definitions_number = obj.definitions_number;
			definition = new Definition*[definitions_number];
			for (int i = 0; i < definitions_number; i++)
				definition[i] = new Definition(*(obj.definition[i]));
		}
	}
	else
		cout << "Self assigment!\n";
	return *this;
}

const bool Dictionary::operator==(const Dictionary& obj) const
{
	if (definitions_number == obj.definitions_number)//check length
	{
		for (int i = 0; i < definitions_number; i++)
			if (!(*(definition[i]) == *(obj.definition[i])))//check every definition in the dictionary
				return false;
		return true;
	}
	return false;
}

ostream& operator<<(ostream& output, const Dictionary& obj)
{
	if (obj.definition != NULL)
	{//print all definitions
		for (int i = 0; i < obj.definitions_number; i++)
			cout << *obj.definition[i] << endl;
	}
	else
		cout << "Dictionary is emptey\n";
	return output;
}

istream& operator>>(istream& input, Dictionary& obj)
{
	int size;
	Definition temp;
	//free old memory
	for (int i = 0; i < obj.definitions_number; i++)
		delete obj.definition[i];
	delete[] obj.definition;
	
	//get definitions number from user and if size < 0 --> definitions number = 0
	cout << "How many definitions would you like to set:";
	input >> size;
	if (size <= 0)
	{
		obj.definitions_number = 0;
	}
	else
	{//set first value
		obj.definitions_number = 1;
		obj.definition = new Definition*[1];
		getchar();
		input >> temp;
		obj.definition[0] = new Definition(temp);
		//set rest of them and check if there is equals definitions!
		for (int i = 1; i < size; i++)
		{
			input >> temp;
			obj += temp;
		}
	}
	return input;
}

Dictionary& Dictionary::operator-=(int index)
{
	if (index > definitions_number || index <= 0)
	{//check if index exist
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	Definition** temp = definition;//temp pointer on all definitions
	if (temp != NULL)
	{
		definition = new Definition*[--definitions_number];//allocate memory -1

		for (int i = 0, u = 0; i < definitions_number + 1; i++)
			if (i != index - 1)//if not index set him
				definition[u++] = temp[i];
		delete temp[index - 1];//free index memory
	}
	else
		cout << "No definitions\n";
	delete[] temp;
	return *this;
}

Dictionary & Dictionary::operator+=(const Definition& new_definition)
{	//check if the definition is already exist
	for (int i = 0; i < definitions_number; i++)
		if (*definition[i] == new_definition)
		{
			cout << "\n~ You enterd a Definition that already exist in the dictionary, Cant let him in ~\n";
			return *this;
		}
	Definition** temp = definition;//temp pointer on all definitions
	if (temp != NULL)
	{
		definition = new Definition*[++definitions_number];//allocate +1 memory
		for (int i = 0; i < definitions_number - 1; i++)
			definition[i] = temp[i];//set old values
		definition[definitions_number - 1] = new Definition(new_definition);//add the new definition
	}
	delete[] temp;
	return *this;
}

Definition& Dictionary::operator[](int index)
{	//get definition by index
	if (index < 0 || index >= definitions_number)
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return *definition[index];
}

const Definition & Dictionary::operator[](int index) const
{	//get definition by index
	if (index < 0 || index >= definitions_number)
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return *definition[index];
}

const int Dictionary::checkIfWordExist(const String& word) const
{	//check every word and if exist return index
	for (int i = 0; i < definitions_number; i++)
	{
		if (definition[i]->getWord() == word)
			return i;
	}
	return -1; //-1 is a sign for word is not exist
}

void Dictionary::sortDefinitions()
{	//	sort the definitions by A B C
	Definition temp;
	int flag;
	do {//	bubble sort
		flag = 0;
		for (int i = 0; i < definitions_number - 1; i++)
		{
			if (*definition[i] > *definition[i + 1])
			{
				temp = *definition[i];
				*definition[i] = *definition[i + 1];
				*definition[i + 1] = temp;
				flag = 1;
			}
		}
	} while (flag == 1);
}
