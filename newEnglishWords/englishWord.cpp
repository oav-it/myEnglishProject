// englishWord.cpp
// ����������� ������ EnglishWord

#include <iostream>
#include <iomanip>
#include "englishWord.h"

// ������������� ����������� ������
int EnglishWord::wordCount = 0;


// ���������� ����������� �������-�������, ������������
// ����� ������������ ����������� ����.
int EnglishWord::getWordCount() { return wordCount; }

// ����������� �� ���������
EnglishWord::EnglishWord()
{
	original = "";
	translation = "";
	lesson = 0;
	flag = 0;
	++wordCount;		// ��������� ����������� ������� ���������� ����
}

// �����������
EnglishWord::EnglishWord(const string& originalWorld, const string& translationWord, short int lessonNumber, short int answerFlag)
	: original(originalWorld), translation(translationWord), lesson(lessonNumber), flag(answerFlag)
{
	++wordCount;	// ��������� ����������� ������� ���������� ����
}

// ����������
EnglishWord::~EnglishWord()
{
	--wordCount;	// ��������� ����������� ������� ���������� ����
}

// ���������� �����
string EnglishWord::getWord() const
{
	return original;
}

// ���������� �������
string EnglishWord::getTranslation() const
{
	return translation;
}

// ����� �� ������: �����	-	�������
void EnglishWord::print() const
{
	cout << setfill('-') << setw(33) << setiosflags(ios::right) << original << " - "
		<< setw(40) << resetiosflags(ios::right)	// �������� ������������ �� ������ ������� ����
		<< setiosflags(ios::left)					// ��������� ������������ �� ����� ������� ����
		<< translation << endl;
	
}
/* setw(n) ������ ������ ���� (������� �� ������ �������� ���������)*/

// ����� �� ������: �����
void EnglishWord::printWord() const
{
	cout << original << endl;
}

// ����� �� ������: �������
void EnglishWord::printTranslation() const
{
	cout << translation << endl;
}

// ������������� ������� EnglishWord
void EnglishWord::setEnglWord(const string& originalWorld, const string& translationWord, short int lessonNumber, short int answerFlag)
{
	original = originalWorld;
	translation = translationWord;
	lesson = lessonNumber;
	flag = answerFlag;
}

// ���������� ��������� ������������
short int EnglishWord::getFlag() const
{
	return flag;
}

// ���������� �������� ���������� ������������
void EnglishWord::setFlag(const short int answerFlag)
{
	flag = answerFlag;
}

// ���������� ����� �����
short int EnglishWord::getLesson() const
{
	return lesson;
}