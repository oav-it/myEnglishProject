// englishWord.h
// ����������� ������ EnglishWord
#ifndef ENGLISHWORD_H
#define ENGLISHWORD_H

#include <iostream>
using namespace std;

class EnglishWord {
public:
	EnglishWord();																	// ����������� �� ��������� 
	EnglishWord(const string&, const string&, short int = 0, short int = 0);		// �����������
	~EnglishWord();																	// ����������
	string getWord() const;															// ���������� �����
	string getTranslation() const;													// ���������� �������
	short int getFlag() const;														// ���������� ��������� ������������
	void print() const;																// ����� �� ������: �����	-	�������
	void printWord() const;															// ����� �� ������: �����
	void printTranslation() const;													// ����� �� ������: �������
	void setEnglWord(const string&, const string&, short int = 0, short int = 0);	// ������������� �������
	void setFlag(const short int);													// ���������� �������� ���������� ������������
	short int getLesson() const;													// ���������� ����� �����
	
	// ����������� �������-�������
	static int getWordCount();														// ���������� ����� ����
private:
	string original;		// ����� �� ����������
	string translation;		// �������
	short int lesson;		// ����� �����
	short int flag;			// ���� ��� ������������ ������������ ����� �� ����� ������������

	static int wordCount;	// ����� ���� � �������
};

#endif // !ENGLISHWORD_H

/*
1) ������� ������ ���� ���� �� ��������
*/