#include <iostream>
#include "Math.h"
#include "Matrix.h"
#include "table_printer.h"


int main()
{
    const auto numsOftypes = 2;
    auto order = 50;
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
    auto maxLenOfNumInCol = std::vector<int>(order);
    for (int i = 0; i < numsOftypes*2; ++i)
    {
        int max = 0;
        for (int j = 0; j < order; ++j)
        {
            std::cout << i << " " << j << std::endl;
            auto count = std::to_string(norms[i][j]).size();
            //auto count = countOfSymsBeforeSeparator(norms[i][j]);
            if (count > max)
            {
                max = count;
            }
        }
        maxLenOfNumInCol[i] = max;
    }
    


    std::vector<std::string> headers{"order", "double left", "double right", "float left", "float right"};
    tp.AddColumn(headers[0], 5);
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
