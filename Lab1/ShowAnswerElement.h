#pragma once
#include "interfaceElement.h"

enum SaveDataVariants
{
	SaveOnlyInitial=1,
	SaveOnlyResult,
	SaveInitialAndResultToOneFile,
	SaveInitialAndResultSeparately,
	SaveNothing
};

class AnswerElement :
	public InterfaceElement
{
public:
	AnswerElement(std::string initial, std::string answer);
	void Show() override;
private:
	void chooseVariant() override;
	std::string initial;
	std::string answer;
};
