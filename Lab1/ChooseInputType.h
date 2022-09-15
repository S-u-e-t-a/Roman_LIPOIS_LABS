#pragma once
#include "interfaceElement.h"

enum InputTypeVariants
{
	FromKeyboard=1,
	FromFile
};

class ChooseInputType :
	public InterfaceElement
{
public:
	ChooseInputType();
	void Show() override;
private:
	void chooseVariant() override;
};
