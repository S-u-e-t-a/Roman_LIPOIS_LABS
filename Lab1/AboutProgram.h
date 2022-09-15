#pragma once
#include <memory>

#include "InterfaceElement.h"
#include "mainMenu.h"

class AboutProgram :
    public InterfaceElement
{
public:
    AboutProgram();
    void Show() override;
private:
	void chooseVariant() override;
};

