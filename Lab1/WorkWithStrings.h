#pragma once
#include "interfaceElement.h"

enum WorkWithStringsVariants { PrintAllFirstWordsOfSentence = 1, BackToMenu };

class WorkWithStrings : public InterfaceElement
{
public:
	WorkWithStrings();
	void Show() override;
private:
	void chooseVariant() override;
};
