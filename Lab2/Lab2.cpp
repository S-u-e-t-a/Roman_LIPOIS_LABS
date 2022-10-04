#include <iostream>
#include <windows.h>

#include "Math.h"
#include "Matrix.h"
#include "table_printer.h"

int TryGetIntUntilSuccess(std::string inputMessage)
{
	std::cout << inputMessage << std::endl;
    std::string inputtedString;
    getline(std::cin, inputtedString);
    //cin >> inputtedString;
    try
    {
        const int i = std::stoi(inputtedString);
        return i;
    }
    catch (const std::exception&)
    {
        return TryGetIntUntilSuccess(inputMessage);
    }
}

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    const auto numsOftypes = 2;
    auto order = TryGetIntUntilSuccess("Введите максимальный размер матрицы");
    bprinter::TablePrinter tp(&std::cout);

    std::vector<std::vector<double>> norms(4);
    for (int i = 0; i < 4; ++i)
    {
        norms[i] = std::vector<double>(order);
    }
    for (int i = 0; i < order; ++i)
    {
        auto m = MakeGilbertMatrix<double>(i+1);
        auto inv = m.getInverted();
        auto leftResidual = makeLeftResidualMatrix(&m, inv);
        auto rightResidual = makeRightResidualMatrix(&m, inv);
        auto leftNorm = getRowNorm(&leftResidual);
        auto rightNorm = getRowNorm(&rightResidual);
        norms[0][i]=(leftNorm);
        norms[1][i]=(rightNorm);
    }
	for (int i = 0; i < order; ++i)
    {
        auto m = MakeGilbertMatrix<float>(i+1);
        auto inv = m.getInverted();
        auto leftResidual = makeLeftResidualMatrix(&m, inv);
        auto rightResidual = makeRightResidualMatrix(&m, inv);
        auto leftNorm = getRowNorm(&leftResidual);
        auto rightNorm = getRowNorm(&rightResidual);
        norms[2][i] = (leftNorm);
        norms[3][i] = (rightNorm);
    }

    std::vector<std::string> headers{"Порядок", "double left", "double right", "float left", "float right"};
    tp.AddColumn(headers[0], 7);
    for (int i = 1; i < headers.size(); ++i)
    {
        tp.AddColumn(headers[i], 20);
    }
    tp.PrintHeader();
    for (int i = 0; i < order; ++i)
    {
        tp << i+1;
        for (int j = 0; j < headers.size()-1; ++j)
        {
            tp << norms[j][i];
        }
    }
    tp.PrintFooter();
}
