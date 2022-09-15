#pragma once
#include <memory>
#include <string>
#include "InputTools.h"

class InterfaceElement
{
public:
	std::string GetText();
	void ClearScreenAndPrintNew(const std::shared_ptr<InterfaceElement> interfaceElement);
	virtual void Show();
protected:
	std::string text;
	virtual void chooseVariant() = 0;
};
