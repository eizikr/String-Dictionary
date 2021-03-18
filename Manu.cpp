#include "Menu.h"

Menu::Menu() :dictionary(NULL){}//start NULL
	
Menu::Menu(const Menu& obj)
{	//start NULL
	if (obj.dictionary == NULL)
		dictionary = NULL;
	else
		*dictionary = *obj.dictionary;
}

Menu::~Menu()
{	//free dictionary
	delete dictionary;
}

void Menu::MainMenu()
{
	int choice;
	bool Dictionary_was_created = false;
	do {//print the menu untill choice is 6
		cout << "Manu:\n(1) Create a dictionary";
		if(Dictionary_was_created)
			cout << " - (Cant use this option anymore)";
		cout << "\n(2) Enter a new definition\n(3) Add a new commentary to the definition\n(4) Search definition\n(5) Show definitions that have the same interpretation\n(6) Exit\n";
		cout << "Enter your choice:";
		cin >> choice;
		cin.ignore();
		switch (choice) 
		{//by the choice call functions
		case 1:
			if (!Dictionary_was_created)
			{//have to use it first or exit
				createAndInsertDictionary();
				Dictionary_was_created = true;
			}
			else
			{//cant use it more then once
				cout << "\n~ You already created a dictionary! ~\n" << endl;
			}
			break;
		case 2:
			if (Dictionary_was_created)
				createNewDefinition();
			else
				cout << "\n~ You need to create a dictionary before you can use this option ~\n" << endl;
			break;
		case 3:
			if (Dictionary_was_created)
				addInterpretationToDefinition();
			else
				cout << "\n~ You need to create a dictionary before you can use this option ~\n" << endl;
			break;
		case 4:
			if (Dictionary_was_created)
				searchForDefinition();
			else
				cout << "\n~ You need to create a dictionary before you can use this option ~\n" << endl;
			break;
		case 5:
			if(Dictionary_was_created)
				showShareDefinitions();
			else
				cout << "\n~ You need to create a dictionary before you can use this option ~\n" << endl;
			break;
		case 6:
				endMenu();
			break;
		default:
			if (Dictionary_was_created)
				cout << "\n~ You have to choose only 2-6 options! ~\n" << endl;
			else
				cout << "\n~ You have to choose only 1-6 options! ~\n" << endl;
			break;
		}
	} while (choice != 6);
}

void Menu::createAndInsertDictionary()
{
	dictionary = new Dictionary;
	cin >> *dictionary;
	dictionary->sortDefinitions();
}

void Menu::createNewDefinition()
{
	Definition new_definition;
	cin >> new_definition;
	(*dictionary) += new_definition;
	dictionary->sortDefinitions();
}

void Menu::addInterpretationToDefinition()
{
	String temp_definition, temp_interpretation;
	cout << "\nEnter a definition name: ";
	cin >> temp_definition;
	int index = dictionary->checkIfWordExist(temp_definition);
	if (index < 0) // index = -1 if word isnt exist
		cout << "\n~ Definition dosn't exist in the dictionary ~\n" << endl;
	else
	{
		cout << "\nEnter your new interpretation: ";
		cin >> temp_interpretation;
		(*dictionary)[index] += temp_interpretation;
		dictionary->sortDefinitions();
	}
}

void Menu::searchForDefinition()
{
	String temp;
	cout << "\nEnter a definition name: ";
	//getchar();
	cin >> temp;
	int index = dictionary->checkIfWordExist(temp);
	if (index < 0) // index = -1 if word isnt exist
		cout << "\n~ Definition dosn't exist in the dictionary ~\n" << endl;
	else
		cout << (*dictionary)[index] << endl;
}

void Menu::showShareDefinitions()
{
	int flag = false;
	for (int i = 0; i < dictionary->getDefinitionsNumber(); i++)
	{
		for (int j = i + 1; j < dictionary->getDefinitionsNumber(); j++)
		{
				for (int u = 0; u < (*dictionary)[i].getInterpretationsNumber(); u++)
			{
					for (int k = 0; k < (*dictionary)[j].getInterpretationsNumber(); k++)
				{
					if (((*dictionary)[i])[u] == ((*dictionary)[j])[k])
					{
						if (!flag)
						{
							cout << "\nShared definitions are:\n";
							flag = true;
						}
						cout << (*dictionary)[i] << endl;
						cout << (*dictionary)[j] << endl;
						cout << "----------------------------------\n";
					}
				}
			}
		}
	}
	if (!flag)
		cout << "\n ~No shared definitions ~\n" << endl;
}

void Menu::endMenu()
{
	cout << "\nTank you for using the program, see you on the next mission!!" << endl;
}