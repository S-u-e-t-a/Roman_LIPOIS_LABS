#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab1/StringWorker.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab1Tests2
{
	TEST_CLASS(Lab1Tests2)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			std::string text = "������ ���! 123456? ��.";
			const auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
			Assert::AreEqual(static_cast<int>(firstWords.size()), 3);
		  /*EXPECT_EQ(firstWords.size(), 3);
		  EXPECT_EQ(firstWords[0], "������");
		  EXPECT_EQ(firstWords[1], "123456");
		  EXPECT_EQ(firstWords[2], "��");*/
		}
	};
}
