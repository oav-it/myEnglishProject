// englishWord.h
// Определение класса EnglishWord
#ifndef ENGLISHWORD_H
#define ENGLISHWORD_H

#include <iostream>
using namespace std;

class EnglishWord {
public:
	EnglishWord();																	// конструктор по умолчанию 
	EnglishWord(const string&, const string&, short int = 0, short int = 0);		// конструктор
	~EnglishWord();																	// деструктор
	string getWord() const;															// возвратить слово
	string getTranslation() const;													// возвратить перевод
	short int getFlag() const;														// возвратить индикатор правильности
	void print() const;																// вывод на печать: слово	-	перевод
	void printWord() const;															// вывод на печать: слово
	void printTranslation() const;													// вывод на печать: перевод
	void setEnglWord(const string&, const string&, short int = 0, short int = 0);	// инициализация объекта
	void setFlag(const short int);													// установить значения индикатора правильности
	short int getLesson() const;													// возвратить номер урока
	
	// статическая функция-элемент
	static int getWordCount();														// возвратить число слов
private:
	string original;		// слово на английском
	string translation;		// перевод
	short int lesson;		// номер урока
	short int flag;			// флаг для отслеживания правильности ввода во время тестирования

	static int wordCount;	// число слов в словаре
};

#endif // !ENGLISHWORD_H

/*
1) вывести список всех слов по алфавиту
*/