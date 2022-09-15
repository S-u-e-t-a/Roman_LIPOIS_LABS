#pragma once
#include "interfaceElement.h"

enum MainMenuVariants { ShowWorkWithStringsMenu=1, About, Exit };

class MainMenu : public InterfaceElement
{
public:
	MainMenu();
	void Show() override;
private:
	void chooseVariant() override;
};
