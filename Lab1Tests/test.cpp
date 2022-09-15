#include "pch.h"
#include <list>
#include <regex>
#include <string>
#include <vector>
#include "../Lab1/StringWorker.cpp"
#include "../Lab1/StringWorker.h"
TEST(GetFirstWordsOfSentences, defaultCase)
{
	std::string text = "Привет мир! 123456? Да.";
	auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
  EXPECT_EQ(firstWords.size(), 3);
  EXPECT_EQ(firstWords[0], "Привет");
  EXPECT_EQ(firstWords[1], "123456");
  EXPECT_EQ(firstWords[2], "Да");
}
TEST(GetFirstWordsOfSentences, noSpaceBetweenSentence) {
	std::string text = "Привет мир!123456?Да.";
	auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	EXPECT_EQ(firstWords.size(), 3);
	EXPECT_EQ(firstWords[0], "Привет");
	EXPECT_EQ(firstWords[1], "123456");
	EXPECT_EQ(firstWords[2], "Да");
}
TEST(GetFirstWordsOfSentences, loremipsumCase) {
	std::string text =
		"Lorem ipsum dolor sit amet, consectetur adipiscing elit."
	" Pellentesque lobortis, leo in mattis auctor, arcu ante suscipit lacus, ac aliquet diam ipsum a quam."
	" Duis euismod purus at magna lacinia, eget semper felis iaculis."
	" Cras et mollis arcu?"
	" Proin vehicula ullamcorper nulla vel vulputate."
	" Pellentesque vel accumsan felis, a placerat nisl."
	" Donec nisi urna, volutpat eu blandit at, posuere eget nunc."
	" Morbi consequat lectus a justo fermentum pretium."
	" Nam rutrum lorem ipsum, eu facilisis mi sodales finibus."
	" Nunc ac tellus ut lacus tempus pharetra.";
	auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	EXPECT_EQ(firstWords.size(), 10);
	EXPECT_EQ(firstWords[0], "Lorem");
	EXPECT_EQ(firstWords[9], "Nunc");
}
TEST(GetFirstWordsOfSentences, oneWord) {
	std::string text = "Привет.";
	auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	EXPECT_EQ(firstWords.size(), 1);
	EXPECT_EQ(firstWords[0], "Привет");
}
TEST(GetFirstWordsOfSentences, nothing) {
	std::string text = "";
	auto firstWords = StringWorker::GetFirstWordsOfSentences(text);
	EXPECT_EQ(firstWords.size(), 0);
	
}