#include "String.h"

String::String(char* _string)//c'tor
{
	if (_string != NULL)
	{
		length = getStringSize(_string);		//set length
		string = new char[length + 1];			//allocate memory
		for (int i = 0; i < length + 1; i++)	//and fill string
			string[i] = _string[i];				//with values
		ArrangingData();
	}
	else	////default////
	{
		string = NULL;
		length = 0;
	}
}

String::String(const char* _string)// const c'tor
{
	if (_string != NULL)
	{
		length = getStringSize(_string);		//set length
		string = new char[length + 1];			//allocate memory
		for (int i = 0; i < length + 1; i++)	//and fill string
			string[i] = _string[i];				//with values
		ArrangingData();	
	}
	else	////default////
	{
		string = NULL;
		length = 0;
	}
}

String::String(const String& obj)//cpy c'tor
{
	if (obj.string != NULL && obj.length != 0)
	{
		length = obj.length;					//set length
		string = new char[length + 1];			//allocate memory
		for (int i = 0; i < length + 1; i++)	//and fill string
			string[i] = obj.string[i];			//with values
	}
	else	////default////
	{
		string = NULL;
		length = 0;
	}
}

String::~String()
{
////free allocated memory from string////
	delete[] string;	
}

String& String::operator=(const String& obj)
{
	if (this != &obj)//check self assigment
	{
		length = obj.length;
		delete[] string;//free allocated memory
		if (obj.string != NULL) {//check obj string is not emptey and set values
			string = new char[length + 1];
			for (int i = 0; i < length + 1; i++)
				string[i] = obj.string[i];
		}
		else
			length = 0;//if obj string is emptey length is 0
	}
	else
		cout << "Self assigment" << endl;
	return *this;
}
 
bool String::operator==(const String& obj) const
{
	if (length == obj.length)//check length is same
	{
		for (int i = 0; i < length; i++) 
		{
			if (string[i] != obj.string[i])//check every letter 
				return false;
		}
		return true;
	}
	return false;
}

bool String::operator!=(const String& obj) const { return !(obj == *this); }

ostream& operator<<(ostream& output, const String& obj)
{
	if (obj.string != NULL)//check if obj string is emptey 
	{
		for (int i = 0; i < obj.length; i++)//print every letter
			output << obj.string[i];
	}
	else
		output << "String is empty\n";
	return output;
}

istream& operator>>(istream& input, String& obj)
{
	int i = 0;
	//get temp string from user
	char temp[MAX_LENGTH];
	cin.getline(temp, MAX_LENGTH);

	obj.length = obj.getStringSize(temp);	//get the string size
	delete[] obj.string;	//free old string
	
	if (obj.length != 0)	//if size is not 0, set the values
	{
		obj.string = new char[obj.length + 1];
		while (temp[i] != '\0') 
		{
			obj.string[i] = temp[i++];
		}
		obj.string[obj.length] = '\0';
		obj.ArrangingData(); //fix sentence
	}
	else 
		obj.string = NULL;
	return input;
}

String& String::operator-=(char _char)
{
	int count = 0;
	char temp[MAX_LENGTH];

	for (int j=0, i = 0; i < length+1; i++)	/////////////////////////
	{										////count how many   ////
		if (string[i] == _char)				////times this char  ////
			count++;						////is apearing		 ////
		else								////and if not, enter////
			temp[j++] = string[i];			////the value to temp////
	}										/////////////////////////

	////fix capital first char////
	if (temp[0] <= 'z' && temp[0] >= 'a')
		temp[0] -= 32;

	////allocate a new memory for sentence////
	length -= count;
	delete[] string;
	string = new char[length + 1];

	////fill string with new values////
	for (int i = 0; i < length + 1; i++)
	{
		string[i] = temp[i];
	}
	
	return *this;
}

String& String::operator+=(char _char)
{
	//create a temp string
	char temp[MAX_LENGTH];
	for (int i = 0; i < length + 1; i++)
		temp[i] = string[i];

	//allocate new memory
	delete[] string;
	string = new char[++length + 1];

	//set temp values in string
	for (int i = 0; i < length; i++)
		string[i] = temp[i];

	//set the last value
	string[length-1] = _char;
	string[length] = '\0';
	return *this;
}

char& String::operator[](int index)
{
	if (index<0 || index>length - 1)	//check index
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return string[index];
}

const char& String::operator[](int index) const
{
	if (index<0 || index>length - 1)	//check index
	{
		cout << "Error! ~ index isn't exist ~ ";
		exit(1);
	}
	return string[index];
}

const bool String::operator>(const String& obj) const
{
	int shorter;	//check who is the shorter string
	if (length < obj.length)
		shorter = length;
	else
		shorter = obj.length;
		for (int i = 0; i < shorter; i++)	//run shorter times and compare every letter
		{
			if (string[i] > obj.string[i])	
				return true;
			else if (string[i] < obj.string[i])
				return false;
		}
	if (length > obj.length)	//if they are the same compare there lengths
		return true;
	return false;
}

const void String::ArrangingData()
{
	int i = 0, index = 0;
	char temp[MAX_LENGTH];
	if (string != NULL) {

		//go forword untill value is not space
		while (string[index] == ' ')
			index++;

		while (index < length) 
		{
			////	fix double space	////
			while (string[index] == ' ' && string[index + 1] == ' ')		
				index++;
			////	no space before "." or "," or ":"  ////
			if (string[index] == ' ' && (string[index + 1] == '.' || string[index + 1] == ':' || string[index + 1] == ','))
				index++;
			////	no space after "," or ":"  ////
			if (string[index+1] == ' ' && (string[index] == '.' || string[index] == ':' || string[index] == ','))
			{
				temp[i++] = string[index++];	
				while (string[index] == ' ')	
					index++;		
			}
			////	one space after "." and capital after it   ////
			if (temp[i - 1] == '.')
			{
				temp[i++] = ' ';
					////	make sure next is capital	////
				if (string[index] >= 'a' && string[index] <= 'z')
					string[index] -= 32;
			}
			////	enter next value to temp string and make it a small letter	 ////
			temp[i++] = string[index++];
			if (string[index] >= 'A' && string[index] <= 'Z')
				string[index] += 32;
		}
		////	end of string    ////
		if (temp[i] == ' ')
			i--;
			temp[i] = '\0';
		////	turn first char to capital 	 ////
		if (temp[0] <= 'z' && temp[0] >= 'a')
			temp[0] -= 32;
		////	allocate new memory    ////
		delete[] string;				
		length = i;						
		string = new char[length + 1];
		////	fill string with new values    ////
		for (i = 0; temp[i] != '\0'; i++)	
			string[i] = temp[i];			
		string[length] = '\0';
	}
}

void String::setWord()	////make sure the string dont have "spaces"//
{
	if (string != NULL)
	{
	int count = 0;
		for (int i = 0; i < length && count < MAX_WORD_LENGTH; i++)
		{
			if (string[i] != ' ')//if the letter is not a "space" let him in
				string[count++] = string[i];
		}
		string[count] = '\0';
		length = count;//fix length
	}
}

const int String::getStringSize(char* _string)const//return the size of your string
{
	int count = 0, i = 0;
	while (_string[i] != '\0')//count size
	{
		count++;
		i++;
	}
	return count;
}

const int String::getStringSize(const char* _string)const//return the size of your string
{
	int count = 0, i = 0;
	while (_string[i] != '\0')//count size
	{
		count++;
		i++;
	}
	return count;
}