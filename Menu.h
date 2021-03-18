#include "Dictionary.h"
#ifndef _MENU_H
#define _MENU_H

class Menu {
	Dictionary* dictionary;
	void createAndInsertDictionary();		//option 1
	void createNewDefinition();				//option 2
	void addInterpretationToDefinition();	//option 3
	void searchForDefinition();				//option 4
	void showShareDefinitions();			//option 5
	void endMenu();							//option 6
public:
	Menu();
	Menu(const Menu&);
	~Menu();

	void MainMenu();
};

#endif // !_MENU_H
