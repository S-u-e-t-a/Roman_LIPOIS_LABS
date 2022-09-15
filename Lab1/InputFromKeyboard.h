#pragma once
#include "interfaceElement.h"

class InputFromKeyboard :
	public InterfaceElement
{
public:
	InputFromKeyboard();
	void Show() override;
private:
	void chooseVariant() override;
};
