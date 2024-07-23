// englishWord.cpp
// ќпределение класса EnglishWord

#include <iostream>
#include <iomanip>
#include "englishWord.h"

// инициализаци€ статических данных
int EnglishWord::wordCount = 0;


// ќпределить статическую функцию-элемент, возвращающую
// число существующих иностранных слов.
int EnglishWord::getWordCount() { return wordCount; }

//  онструктор по умолчанию
EnglishWord::EnglishWord()
{
	original = "";
	translation = "";
	lesson = 0;
	flag = 0;
	++wordCount;		// увеличить статический счетчик количества слов
}

//  онструктор
EnglishWord::EnglishWord(const string& originalWorld, const string& translationWord, short int lessonNumber, short int answerFlag)
	: original(originalWorld), translation(translationWord), lesson(lessonNumber), flag(answerFlag)
{
	++wordCount;	// увеличить статический счетчик количества слов
}

// ƒеструктор
EnglishWord::~EnglishWord()
{
	--wordCount;	// уменьшить статический счетчик количества слов
}

// ¬озвратить слово
string EnglishWord::getWord() const
{
	return original;
}

// ¬озвратить перевод
string EnglishWord::getTranslation() const
{
	return translation;
}

// вывод на печать: слово	-	перевод
void EnglishWord::print() const
{
	cout << setfill('-') << setw(33) << setiosflags(ios::right) << original << " - "
		<< setw(40) << resetiosflags(ios::right)	// отменили выравнивание по правой стороне пол€
		<< setiosflags(ios::left)					// назначили выравнивание по левой стороне пол€
		<< translation << endl;
	
}
/* setw(n) задает ширину пол€ (выбрали по самому длинному выражению)*/

// вывод на печать: слово
void EnglishWord::printWord() const
{
	cout << original << endl;
}

// вывод на печать: перевод
void EnglishWord::printTranslation() const
{
	cout << translation << endl;
}

// инициализаци€ объекта EnglishWord
void EnglishWord::setEnglWord(const string& originalWorld, const string& translationWord, short int lessonNumber, short int answerFlag)
{
	original = originalWorld;
	translation = translationWord;
	lesson = lessonNumber;
	flag = answerFlag;
}

// возвратить индикатор правильности
short int EnglishWord::getFlag() const
{
	return flag;
}

// установить значение индикатора правильности
void EnglishWord::setFlag(const short int answerFlag)
{
	flag = answerFlag;
}

// возвратить номер урока
short int EnglishWord::getLesson() const
{
	return lesson;
}