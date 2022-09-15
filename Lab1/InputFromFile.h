#pragma once
#include "interfaceElement.h"

class InputFromFile :
	public InterfaceElement
{
public:
	InputFromFile();
	void Show() override;
private:
	void chooseVariant() override;
};
