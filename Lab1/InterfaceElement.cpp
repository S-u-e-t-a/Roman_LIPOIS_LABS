//
// Created by aspir on 9/7/2022.
//

#include "interfaceElement.h"
#include "interfacePrinter.h"
#include <iostream>
using namespace std;


string InterfaceElement::GetText()
{
	return text;
}

void InterfaceElement::ClearScreenAndPrintNew(const std::shared_ptr<InterfaceElement> interfaceElement)
{
	system("cls");
	interfaceElement->Show();
}

void InterfaceElement::Show()
{
	cout << text << std::endl;
}
