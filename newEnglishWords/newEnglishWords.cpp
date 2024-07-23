#include "englishWord.h"
#include <string>
#include <iomanip>
using namespace std;

#define DICTIONARY_SIZE 1016								// на 1 больше, чем элементов массива слов
#define DICTIONARY_DIFF_SIZE 158							// на 1 больше, чем элементов массива сложных слов

void initMerfiDictionary(EnglishWord*);						// инициализация словаря
int CheckKnowledgesMerfiDictionary(EnglishWord*, int);		// функция выборки случайных слов из словаря
void mistakesMerfiDictionary(EnglishWord*, int);			// вывод ошибок посел тестирования
void initDifficultMerfiDictionary(EnglishWord*);			// инициализация словаря сложных слов
void flagsMerfiDictionary(EnglishWord*);					// вывод флагов после тестирования
void CheckKnowledgesMerfiDictionaryUnit(EnglishWord*, int);	// проверка лексикона одного урока
void searchWordInTheMerfiDictionary(EnglishWord*, string);	// поиск подстроки в словаре
int CheckKnowledgesIntervalMerfiDictionary(EnglishWord*,
					const int, const int, const int = 0);	// функция выборки случайных слов из словаря в интервале

int CheckKnowledgesDifficultMerfiDictionary(EnglishWord*, int);	// функция выборки случайных сложных слов из словаря

int main()
{
	// Функция setlocate задает локаль для программы
	setlocale(LC_ALL, "rus");								// для корректного отображения русских символов
	srand((unsigned int)time(NULL));						// рандомизация семени
	int errors;

	/* Инициализации словаря новыми словами  */
	EnglishWord MerfiDictionary[DICTIONARY_SIZE];
	initMerfiDictionary(MerfiDictionary);							// инициализация словаря
	//errors = CheckKnowledgesMerfiDictionary(MerfiDictionary, 906);	// проверка знаний (основная функция)

	//errors = CheckKnowledgesIntervalMerfiDictionary(MerfiDictionary, 67, 67);	// проверка знаний диапазона
	//mistakesMerfiDictionary(MerfiDictionary, errors);				// вывод списка ошибок, после проверки знаний
	//flagsMerfiDictionary(MerfiDictionary);							// вывод диаграммы флагов словаря

	//CheckKnowledgesMerfiDictionaryUnit(MerfiDictionary, 88);
	searchWordInTheMerfiDictionary(MerfiDictionary, "in tim");			// поиск подстроки в словаре

	/********************************** Проверка сложных слов ***************************************************/
	/* Инициализации словаря сложными словами  */
	//EnglishWord difficultMerfiDictionary[DICTIONARY_DIFF_SIZE];
	//initDifficultMerfiDictionary(difficultMerfiDictionary);					// инициализация словаря
	//errors = CheckKnowledgesDifficultMerfiDictionary(difficultMerfiDictionary, 157);	// проверка знаний (основная функция)

	//mistakesMerfiDictionary(difficultMerfiDictionary, errors);				// вывод списка ошибок, после проверки знаний
	//flagsMerfiDictionary(difficultMerfiDictionary);							// вывод диаграммы флагов словаря
	/**************************** Конец секции проыерки сложных слов ********************************************/

	/* Сделать тест по таймеру 
	
	2) Когда нет слов в уроке CheckKnowledgesIntervalMerfiDictionary работает некорректно*/

	/*
	Важно: убрать бесконечную отсрочку.
	- унаследовать от массива слов массив + поле для старого индекса.
	- скопировать в него массив слов
	- перетасовать слова
	- сделать любое тестирование
	- изменить флаги в первом массиве (за один проход второго массива по всем элементам флаг, через старый индекс)
	

	3) Переписать функцию CheckKnowledgesMerfiDictionary чтобы можно было задать размер массива
	*/
	

	return 0;
}

// Функция случайным образом выбирает numberOfWords слов из словаря:
// Для каждого слова выводит перевод и ждет, пока пользователь не введет число.
// Затем выводится оригинал выражения и пользователь может свериться.
int CheckKnowledgesMerfiDictionary(EnglishWord* MerfiDictionary, int numberOfWords)
{
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = rand() % DICTIONARY_SIZE;

		// Исключаем повторы слов в тестировании
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ищем новое слово
			wordNumber = rand() % DICTIONARY_SIZE;			

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// Подсчет правильных ответов для ваставления оценки
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ответы совпали
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// отметили, что вопрос был в тесте
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// отметили ошибку 
		}

		// Отслеживание % выполненного теста и текущего результата (выводим только для больших тестов)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\nВы выполнили " << count * 100 / numberOfWords << " % теста."
				<< " С текущим результатом " << rightAnswer * 100 / count << " %.\n" << endl;
		}
		
	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;
	
	return numberOfWords - rightAnswer;		// количество ошибок
}

// Функция выводит неправильные ответы после тестирования из словаря (массива numberOfWords)
void mistakesMerfiDictionary(EnglishWord* MerfiDictionary, int errorCount)
{
	if (errorCount == 0)
		cout << "Congratulations! There are no any mistakes!\n";
	else 
	{
		cout << "List of mistakes is:" << endl;
		for (int count = 1; count < EnglishWord::getWordCount(); count++)
			if (MerfiDictionary[count].getFlag() == 2)	// ошибка при тестировании
			{
				cout << "Lesson №" << setfill(' ') << setw(3) << setiosflags(ios::right) << MerfiDictionary[count].getLesson() << ": ";
				MerfiDictionary[count].print();
			}
	}
}

// Функция выводит все флаги слов из словаря (массива numberOfWords) (диаграмма запоминания по урокам)
void flagsMerfiDictionary(EnglishWord* MerfiDictionary)
{
	cout << "\nList of flags:\n 0 - слово не было в тестировании;\n"
		<< " 1 - верный ответ;\n 2 - ошибка;";
	for (int count = 0; count < EnglishWord::getWordCount(); count++)
	{
		if (count % 86 == 0)	cout << endl;

		cout << MerfiDictionary[count].getFlag();
	}
	cout << "\n";
}

// Функция проверки знаний одного конкретного урока из numberOfWords слов из словаря:
// Для каждого слова выводит перевод и ждет, пока пользователь не введет ответ.
// Затем выводится оригинал выражения в случае ошибки.
void CheckKnowledgesMerfiDictionaryUnit(EnglishWord* MerfiDictionary, int unitNumber)
{
	string temp;			// временная переменная для сравнения правильности ответа
	int rightAnswer = 0;	// количество правильных ответов
	int numberOfWords = 0;	// количество слов в уроке	
	cout << "Let's check a lexicon of the lesson №" << unitNumber << ':' << endl;

	for (int count = 0; count < DICTIONARY_SIZE; count++)		// пробегаем по всем словам
	{
		if (MerfiDictionary[count].getLesson() == unitNumber)	// слова нужного урока
		{
			numberOfWords++;
			MerfiDictionary[count].printTranslation();

			cout << "Enter your answer: ";
			getline(cin, temp);

			// Подсчет правильных ответов для выставления оценки
			if (MerfiDictionary[count].getWord() == temp)	// ответы совпали
			{
				rightAnswer++;
				cout << "***************You are right***********************" << endl;
			}
			else {
				cout << "***************You are wrong***********************" << endl;
				MerfiDictionary[count].printWord();
			}
		}
		//else
			// если номер урока больше нужного прекращаем цикл
			//if ((MerfiDictionary[count].getLesson() > unitNumber) && (MerfiDictionary[count].getLesson() != 125))	
			//{
			//	break;
			//}		
	}

	if (numberOfWords == 0)					// урок пустой
		cout << "There are no any words in unit №" << unitNumber << '.' << endl;
	else
	{
		cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " quastions.";
		cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;
	}
}

// Функция поиска слов в словаре
// Описание: функция находит вхождение строки substring в массиве numberOfWords,
// Как на русском (перевод слова), так и на английском (оригигал слова) и
// вывводит список всех совпадений. 
// Удобно для поиска повторов или правок словаря.
void searchWordInTheMerfiDictionary(EnglishWord* MerfiDictionary, string substring)
{
	int flag = 0;												// для отслеживания совпадений
	for (int count = 0; count < DICTIONARY_SIZE; count++)		// пробегаем по всем словам
	{
		/*
		Функция find() возвращает индекс первого вхождения подстроки или отдельного символа в строке в
		виде значения типа size_t.
		Если строка или символ не найдены, то возвращается специальная константа std::string::npos.
		Пример:		
			string text {"My friend loves apples"};
			cout << text.find("apple") << std::endl;      // 16
		*/
		// нашли совпадение
		if ((MerfiDictionary[count].getWord().find(substring) != std::string::npos) ||		// в оригинале,
			(MerfiDictionary[count].getTranslation().find(substring) != std::string::npos))	// или в переводе
		{
			cout << "Lesson №" << setfill(' ') << setw(3) << setiosflags(ios::right)
				<< MerfiDictionary[count].getLesson() << ": ";
			MerfiDictionary[count].print();
			flag++;
		}
	}
	if (flag == 0)											// совпадений не было
		cout << "There is no substring '" << substring << "' in the dictionary.";
}

// Функция, которая тестирует знания между двумя заданными уроками. 
// Функция случайным образом выбирает все слова из словаря между заданными уроками.
// Для каждого слова выводит перевод и ждет, пока пользователь не введет число.
// Затем выводится оригинал выражения и пользователь может свериться.
// ***************************************************************************************
// Параметры:
// - MerfiDictionary - словарь (массив объектов EnglishWord)
// - leftUnit - номер меньшего урокв в интервале
// - rightUnit - номер большего урока в интервале
// - umberOfWords = 0 - количество тестируемых слов, по умолчанию 0 (0: тестируем все слова интервала)
// ***************************************************************************************
// Примечание: полагаем, что массив заполняется последовательно.
// ВАЖНО: секция POPULAR WORDS мешает выборке (если между уроками идет)
// ***************************************************************************************
// Краткое описание алгоритма:
// 1) Находим номер первого слова заданного интервала (первое слово урока с номером leftUnit): minIndex
// 2) Находим номер последнего слова заданного интервала (последнее слово урока с номером rightUnit): maxUndex
// 3) Алгоритм основной функции (за исключением диапазона)
int CheckKnowledgesIntervalMerfiDictionary(EnglishWord* MerfiDictionary, const int leftUnit, 
											const int rightUnit, int numberOfWords)
{
	int minIndex = -1;		// индекс первого слова заданного интервала
	int maxIndex = -1;		// индекс последнего слова заданного интервала
	
	// первое слово в интервале
	for (int count = 0; count < DICTIONARY_SIZE; count++)
		if (MerfiDictionary[count].getLesson() == leftUnit)
		{
			minIndex = count;
			break;	// при первом совпадении выходим из цикла
		}
	
	// последнее слово в интервале (начинаем поиск с minIndex)
	// Замечание: так как № popular_words = 500 и идет не по порядку, приходится проверять весь словарь
	for (int count = minIndex; count < DICTIONARY_SIZE; count++)
		if (MerfiDictionary[count].getLesson() == rightUnit)
			maxIndex = count;

	cout << "first index: " << minIndex << endl;
	cout << "last index: " << maxIndex << endl;
	cout << "Number of test-words: " << maxIndex - minIndex + 1 << endl;

	if (numberOfWords == 0 || (numberOfWords > maxIndex - minIndex + 1))	// параметр по умолчанию
		numberOfWords = maxIndex - minIndex + 1;	// тестируем все слова

	// алгоритм основной функции, за исключением диапазона
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = minIndex + rand() % (maxIndex - minIndex + 1);

		// Исключаем повторы слов в тестировании
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ищем новое слово
			wordNumber = minIndex + rand() % (maxIndex - minIndex + 1);

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// Подсчет правильных ответов для ваставления оценки
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ответы совпали
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// отметили, что вопрос был в тесте
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// отметили ошибку 
		}

		// Отслеживание % выполненного теста и текущего результата (выводим только для больших тестов)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\nВы выполнили " << count * 100 / numberOfWords << " % теста."
					<< " С текущим результатом " << rightAnswer * 100 / count << " %.\n" << endl;
		}

	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;

	return numberOfWords - rightAnswer;		// количество ошибок
}

// Функция заполнения словаря (массива EnglishWord) значениями
// - оригинал слова
// - перевод
// - номер урока (по умолчанию 0)
// - флаг правильности ответа на тестировании (по умолчанию true)
void initMerfiDictionary(EnglishWord* MerfiDictionary)
{
	/****************** Lesson 1: *************************************************************************/
	MerfiDictionary[1].setEnglWord("hospital", "больница", 1);
	MerfiDictionary[2].setEnglWord("shop assistant", "продавец", 1);
	MerfiDictionary[3].setEnglWord("Tokyo", "Токио", 1);
	MerfiDictionary[4].setEnglWord("designer", "дизайнер", 1);										// дизайне
	MerfiDictionary[5].setEnglWord("be interested in", "интересоваться чем-то", 1);
	MerfiDictionary[6].setEnglWord("be thirsty", "хотеть пить", 1);
	MerfiDictionary[7].setEnglWord("be afraid of", "бояться чего-то (пр)", 1);
	MerfiDictionary[8].setEnglWord("feel depressed", "чувствовать себя расстроенным, быть в депрессии", 1);	// дипрест
	MerfiDictionary[9].setEnglWord("get ill", "заболеть", 1);
	MerfiDictionary[10].setEnglWord("for over", "более(о времени)", 1);
	MerfiDictionary[11].setEnglWord("take medicine", "принимать лекарства", 1);								// медсн
	MerfiDictionary[12].setEnglWord("sharp", "острый", 1);													// Урок 63
	/*************** End of init Lesson 1 ****************************************************************/

	/****************** Lesson 2: *************************************************************************/
	MerfiDictionary[13].setEnglWord("a little", "немного", 2);
	MerfiDictionary[14].setEnglWord("a snack", "закуски (арт.)", 2);
	MerfiDictionary[15].setEnglWord("on the internet", "по интернету", 2);
	MerfiDictionary[16].setEnglWord("discussion", "обсуждение", 2);
	MerfiDictionary[17].setEnglWord("by the next week", "к следующей неделе", 2);
	/*************** End of init Lesson 2 ****************************************************************/

	/****************** Lesson 3: *************************************************************************/
	MerfiDictionary[18].setEnglWord("take a shower", "принимать душ", 3);
	MerfiDictionary[19].setEnglWord("right now", "прямо сейчас, в данный момент", 3);
	MerfiDictionary[20].setEnglWord("at the moment", "в данный момент, прямо сейчас", 3);
	MerfiDictionary[21].setEnglWord("listen to", "слушать", 3);
	MerfiDictionary[22].setEnglWord("quiet", "тихий", 3);
	MerfiDictionary[23].setEnglWord("improve", "улучшать", 3);
	MerfiDictionary[24].setEnglWord("come late", "опаздывать", 3);
	MerfiDictionary[25].setEnglWord("argue", "спорить", 3);
	MerfiDictionary[26].setEnglWord("complain", "жаловаться", 3);
	MerfiDictionary[27].setEnglWord("currently", "сейчас, в текущий момент", 3);
	MerfiDictionary[28].setEnglWord("belong to", "принадлежать (пр)", 3);
	MerfiDictionary[29].setEnglWord("at least", "по крайней мере, как минимум", 3);
	MerfiDictionary[30].setEnglWord("wrong", "ошибочно, ошибочный", 3);
	MerfiDictionary[31].setEnglWord("think of", "думать о…", 3);
	/*************** End of init Lesson 3 ****************************************************************/

	/****************** Lesson 4: *************************************************************************/
	MerfiDictionary[32].setEnglWord("look at", "смотреть на (что-то)", 4);
	MerfiDictionary[33].setEnglWord("shout at", "кричать на (кого-то)", 4);
	MerfiDictionary[34].setEnglWord("look after", "следить, присматривать за (кем-то)", 4);
	MerfiDictionary[35].setEnglWord("critisize", "критиковать", 4);
	MerfiDictionary[36].setEnglWord("answer the phone", "ответить на зонок", 4);
	/*************** End of init Lesson 4 ****************************************************************/

	/****************** Lesson 5: *************************************************************************/
	MerfiDictionary[37].setEnglWord("violin", "скрипка", 5);
	MerfiDictionary[38].setEnglWord("purse", "сумочка, кошелек, портмоне", 5);
	MerfiDictionary[39].setEnglWord("wing", "крыло", 5);
	/*************** End of init Lesson 5 ****************************************************************/

	/****************** Lesson 6: *************************************************************************/
	MerfiDictionary[40].setEnglWord("petrol", "бензин", 6);
	MerfiDictionary[41].setEnglWord("go to the movies", "ходить в кино", 6);
	MerfiDictionary[42].setEnglWord("at weekends", "по выходным", 6);
	MerfiDictionary[43].setEnglWord("on Friday", "по пятницам", 6);
	MerfiDictionary[44].setEnglWord("stranger", "незнакомец", 6);
	/*************** End of init Lesson 6 ****************************************************************/

	/****************** Lesson 7: *************************************************************************/
	MerfiDictionary[45].setEnglWord("guitar", "гитара", 7);
	MerfiDictionary[46].setEnglWord("How do I get...?", "Как мне добраться...?", 7);
	MerfiDictionary[47].setEnglWord("ever", "когда-либо", 7);
	MerfiDictionary[48].setEnglWord("avenue", "авеню", 7);
	/*************** End of init Lesson 7 ****************************************************************/	

	/****************** Lesson 8: *************************************************************************/
	MerfiDictionary[49].setEnglWord("have fun", "веселиться", 8);
	MerfiDictionary[50].setEnglWord("see the doctor", "идти на прием к врачу", 8);
	MerfiDictionary[51].setEnglWord("tell lies", "говорить неправду", 8);
	MerfiDictionary[52].setEnglWord("feel well", "хорошо себя чувствовать", 8);
	/*************** End of init Lesson 8 ****************************************************************/

	/****************** Lesson 9: *************************************************************************/
	MerfiDictionary[53].setEnglWord("headache", "головная боль", 9);
	MerfiDictionary[54].setEnglWord("silence", "тишина, молчание", 9);
	MerfiDictionary[55].setEnglWord("pay attention", "обращать внимание", 9);
	MerfiDictionary[56].setEnglWord("loud", "громкий", 9);
	MerfiDictionary[57].setEnglWord("get married", "жениться", 9);
	MerfiDictionary[58].setEnglWord("have a holiday", "быть на каникулах", 9);
	/*************** End of init Lesson 9 ****************************************************************/

	/****************** Lesson 10: *************************************************************************/
	MerfiDictionary[59].setEnglWord("be asleep", "спать", 10);
	MerfiDictionary[60].setEnglWord("be scared of", "быть напуганным (пр)", 10);
	MerfiDictionary[61].setEnglWord("journey", "путешествие", 10);
	MerfiDictionary[62].setEnglWord("at work", "на работе", 10);
	MerfiDictionary[63].setEnglWord("at the party", "на вечеринке, на празднике", 10);
	MerfiDictionary[64].setEnglWord("accident", "несчастный случай", 10);						// эксидент
	MerfiDictionary[65].setEnglWord("be hurt", "пострадать", 10);					// хёт
	MerfiDictionary[66].setEnglWord("be fond of", "любить что-то, увлекаться чем-то", 10);
	MerfiDictionary[67].setEnglWord("be good at", "хорошо знать, разбираться в чем-то", 10);
	MerfiDictionary[68].setEnglWord("be married to", "быть женатым на (пр.)", 10);
	MerfiDictionary[69].setEnglWord("cross", "пересечь", 10);
	MerfiDictionary[70].setEnglWord("switch off", "выключить", 10);
	MerfiDictionary[71].setEnglWord("degrees", "градусы", 10);
	/*************** End of init Lesson 10 ****************************************************************/

	/****************** Lesson 11: *************************************************************************/
	MerfiDictionary[72].setEnglWord("take off", "снять (об одежде)", 11);
	MerfiDictionary[73].setEnglWord("sit down", "сесть", 11);
	MerfiDictionary[74].setEnglWord("have a lot of fun", "отлично повеселиться", 11);
	MerfiDictionary[75].setEnglWord("look out", "выглянуть", 11);
	MerfiDictionary[76].setEnglWord("pack a suitcase", "паковать чемодан", 11);
	MerfiDictionary[77].setEnglWord("beforehand", "заранее", 11);
	MerfiDictionary[78].setEnglWord("then", "затем, потом", 11);
	MerfiDictionary[79].setEnglWord("than", "чем", 11);
	MerfiDictionary[80].setEnglWord("celebrity", "знаменитость", 11);
	MerfiDictionary[81].setEnglWord("decision", "решение", 11);
	/*************** End of init Lesson 11 ****************************************************************/

	/****************** Lesson 12: *************************************************************************/
	MerfiDictionary[82].setEnglWord("do the shopping", "делать покупки", 12);
	/*************** End of init Lesson 12 ****************************************************************/

	/****************** Lesson 13: *************************************************************************/
	MerfiDictionary[83].setEnglWord("tablet", "планешт", 13);
	MerfiDictionary[84].setEnglWord("listen to the radio", "слушать радио", 13);
	MerfiDictionary[85].setEnglWord("solve the crossword", "решать кроссворд", 13);
	MerfiDictionary[86].setEnglWord("photos", "фотографии", 13);
	MerfiDictionary[87].setEnglWord("be crowded with", "быть наполненным, быть переполненым (пр.)", 13);	// краудид
	MerfiDictionary[88].setEnglWord("half", "половина", 13);
	MerfiDictionary[89].setEnglWord("pass by", "проходить мимо", 13);
	MerfiDictionary[90].setEnglWord("explosion", "взрыв", 13);												// иксплоушн
	MerfiDictionary[91].setEnglWord("earthquake", "землетрясение", 13);
	/*************** End of init Lesson 13 ****************************************************************/

	/****************** Lesson 14: *************************************************************************/
	// empty
	/*************** End of init Lesson 14 ****************************************************************/

	/****************** Lesson 15: *************************************************************************/
	MerfiDictionary[92].setEnglWord("work for...", "работать на...(кого-то)", 15);
	/*************** End of init Lesson 15 ****************************************************************/

	/****************** Lesson 16: *************************************************************************/
	MerfiDictionary[93].setEnglWord("snail", "улитка", 16);
	/*************** End of init Lesson 16 ****************************************************************/

	/****************** Lesson 17: *************************************************************************/
	MerfiDictionary[94].setEnglWord("ride a horse", "ездить на лошади", 17);
	/*************** End of init Lesson 17 ****************************************************************/

	/****************** Lesson 18: *************************************************************************/
	MerfiDictionary[95].setEnglWord("vacation", "отпуск", 18);											// вэкейшн
	/*************** End of init Lesson 18 ****************************************************************/

	/****************** Lesson 19: *************************************************************************/
	// empty
	/*************** End of init Lesson 19 ****************************************************************/

	/****************** Lesson 20: *************************************************************************/
	MerfiDictionary[96].setEnglWord("in ink", "чернилами", 20);
	MerfiDictionary[97].setEnglWord("aim", "цель", 20);
	MerfiDictionary[98].setEnglWord("steam", "пар", 20);
	MerfiDictionary[99].setEnglWord("steam engine", "паровой двигатель", 20);
	MerfiDictionary[100].setEnglWord("jubilee", "юбилей", 20);											// джубили
	MerfiDictionary[101].setEnglWord("coach", "паровоз", 20);
	MerfiDictionary[102].setEnglWord("vehicle", "транспортное средство", 20);							// вэикл
	MerfiDictionary[103].setEnglWord("Singapore", "Сингапур", 20);
	/*************** End of init Lesson 20 ****************************************************************/


	/****************** Lesson 21: *************************************************************************/
	MerfiDictionary[104].setEnglWord("It is said...", "Говорят...(пассив)", 21);
	MerfiDictionary[105].setEnglWord("It is known...", "(Как) известно...(пассив)", 21);
	MerfiDictionary[106].setEnglWord("temple", "храм", 21);
	MerfiDictionary[107].setEnglWord("crops", "урожай", 21);
	MerfiDictionary[108].setEnglWord("launch", "запускать, стартовать", 21);							// лонч
	MerfiDictionary[109].setEnglWord("technician", "техник", 21);										// текнишн
	MerfiDictionary[110].setEnglWord("invent", "изобретать", 21);
	/*************** End of init Lesson 21 ****************************************************************/

	/****************** Lesson 22: *************************************************************************/
	// empty
	/*************** End of init Lesson 22 ****************************************************************/

	/****************** Lesson 23: *************************************************************************/
	// empty
	/*************** End of init Lesson 23 ****************************************************************/

	/****************** Lesson 24: *************************************************************************/
	MerfiDictionary[111].setEnglWord("soul mate", "родственная душа", 24);
	MerfiDictionary[112].setEnglWord("experience", "опыт", 24);											// икспириенс
	MerfiDictionary[113].setEnglWord("drawer", "выдвижной ящик", 24);									// дроор
	MerfiDictionary[114].setEnglWord("real estate agent", "риелтор", 24);
	MerfiDictionary[115].setEnglWord("feel embarrassed", "чувствовать себя виноватым, смущенным", 24);	// имберест
	MerfiDictionary[116].setEnglWord("by chance", "случайно", 24);
	MerfiDictionary[117].setEnglWord("in my opinion", "по моему мнению", 24);
	MerfiDictionary[118].setEnglWord("for ages", "100 лет", 24);
	MerfiDictionary[119].setEnglWord("ask for something", "просить чего-то", 24);
	MerfiDictionary[120].setEnglWord("apply for a job", "устраиваться на работу", 24);
	MerfiDictionary[121].setEnglWord("at first sight", "с первого взгляда", 24);
	MerfiDictionary[122].setEnglWord("as soon as possible", "как можно скорее (ASAP)", 24);
	/*************** End of init Lesson 24 ****************************************************************/

	/****************** Lesson 25: *************************************************************************/
	// empty
	/*************** End of init Lesson 25 ****************************************************************/

	/****************** Lesson 26: *************************************************************************/
	MerfiDictionary[123].setEnglWord("gonna", "going to (сакращение)", 26);
	MerfiDictionary[124].setEnglWord("attend", "посещать", 26);
	MerfiDictionary[125].setEnglWord("brick", "кирпич", 26);
	MerfiDictionary[126].setEnglWord("pale", "бледный", 26);
	MerfiDictionary[127].setEnglWord("Christmas", "рождество", 26);				// крисмас
	MerfiDictionary[128].setEnglWord("astronaut", "астронавт", 26);				// астронот
	MerfiDictionary[129].setEnglWord("iron", "утюг", 26);
	/*************** End of init Lesson 26 ****************************************************************/

	/****************** Lesson 27: *************************************************************************/
	MerfiDictionary[130].setEnglWord("jogging", "бег разминочным темпом", 27);	// джогин
	MerfiDictionary[131].setEnglWord("hurricane", "ураган", 27);				// харикэн 
	MerfiDictionary[132].setEnglWord("scarf", "шарф", 27);						// скааф
	MerfiDictionary[133].setEnglWord("They say...", "Говорят...", 27);
	MerfiDictionary[134].setEnglWord("condition", "условие", 27);
	MerfiDictionary[135].setEnglWord("bother", "беспокоить", 27);
	MerfiDictionary[136].setEnglWord("sooner or later", "раньше или позже", 27);
	/*************** End of init Lesson 27 ****************************************************************/

	/****************** Lesson 28: *************************************************************************/
	MerfiDictionary[137].setEnglWord("fill in", "заполнять", 28);
	MerfiDictionary[138].setEnglWord("a will", "завещание", 28);
	MerfiDictionary[139].setEnglWord("dishwasher", "посудомойка", 28);
	MerfiDictionary[140].setEnglWord("sandwich", "бутерброд", 28);
	MerfiDictionary[141].setEnglWord("bolt", "болт", 28);
	MerfiDictionary[142].setEnglWord("wherever", "в любом месте, где угодно (w)", 28);
	/*************** End of init Lesson 28 ****************************************************************/

	/****************** Lesson 29: *************************************************************************/
	MerfiDictionary[143].setEnglWord("lottery ticket", "лоторейный билет", 29);
	MerfiDictionary[144].setEnglWord("catch a cold", "простудиться", 29);
	MerfiDictionary[145].setEnglWord("firefighter", "пожарный", 29);
	MerfiDictionary[146].setEnglWord("lair", "лжец", 29);
	MerfiDictionary[147].setEnglWord("billionaire", "миллиордер", 29);			// бил-ё-нЕер
	MerfiDictionary[148].setEnglWord("dream on", "мечтать не вредно", 29);
	MerfiDictionary[149].setEnglWord("murderer", "убийца", 29);					// мЁдерер
	MerfiDictionary[150].setEnglWord("come and see", "навещать", 29);
	MerfiDictionary[151].setEnglWord("groom", "жених", 29);
	MerfiDictionary[152].setEnglWord("best man", "шафер", 29);
	MerfiDictionary[153].setEnglWord("borrow", "одолжить", 29);
	/*************** End of init Lesson 29 *****************************************************************/

	/****************** Lesson 30: *************************************************************************/
	MerfiDictionary[154].setEnglWord("piano", "пианино", 30);
	MerfiDictionary[155].setEnglWord("young", "молодой", 30);
	MerfiDictionary[156].setEnglWord("go on", "продолжаться", 30);
	MerfiDictionary[157].setEnglWord("anymore", "больше (в отрицаниях)", 30);
	MerfiDictionary[158].setEnglWord("come in", "войти", 30);
	MerfiDictionary[159].setEnglWord("write down", "записывать", 30);
	MerfiDictionary[160].setEnglWord("polite", "вежливый", 30);
	MerfiDictionary[161].setEnglWord("compete", "соревноваться, состязаться", 30);
	MerfiDictionary[162].setEnglWord("What has happened to them?", "Что с ними случилось?", 30);
	MerfiDictionary[163].setEnglWord("Can I have some coffee?", "Могли бы вы принести мне кофе? (Просьба)", 30);
	MerfiDictionary[164].setEnglWord("certainly", "конечно", 30);
	/*************** End of init Lesson 30 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[165].setEnglWord("maiden name", "девичья фамилия", 500);
	MerfiDictionary[166].setEnglWord("cheek", "щека", 500);
	MerfiDictionary[167].setEnglWord("chest", "грудь", 500);
	MerfiDictionary[168].setEnglWord("fist", "кулак", 500);
	MerfiDictionary[169].setEnglWord("jaw", "челюсть", 500);
	MerfiDictionary[170].setEnglWord("forehead", "лоб", 500);
	MerfiDictionary[171].setEnglWord("muscle", "мышца", 500);
	MerfiDictionary[172].setEnglWord("cute", "милый", 500);
	MerfiDictionary[173].setEnglWord("freckles", "веснушки", 500);
	MerfiDictionary[174].setEnglWord("haircut", "прическа, стрижка", 500);
	MerfiDictionary[175].setEnglWord("curious", "любопытный", 500);

	MerfiDictionary[176].setEnglWord("fair", "честный", 500);
	MerfiDictionary[177].setEnglWord("easy-going", "легкий на подъем", 500);
	MerfiDictionary[178].setEnglWord("excited", "взволнованный", 500);
	MerfiDictionary[179].setEnglWord("wise", "мудрый", 500);			// вайз
	MerfiDictionary[180].setEnglWord("bride", "невеста", 500);
	MerfiDictionary[181].setEnglWord("widow", "вдова", 500);
	MerfiDictionary[182].setEnglWord("cloak", "плащ", 500);
	MerfiDictionary[183].setEnglWord("earrings", "серьги", 500);
	MerfiDictionary[184].setEnglWord("slippers", "тапочки", 500);		// слипез
	MerfiDictionary[185].setEnglWord("trainers", "кроссовки", 500);
	MerfiDictionary[186].setEnglWord("underwear", "нижнее белье", 500);

	MerfiDictionary[187].setEnglWord("dress up", "наряжаться", 500);
	MerfiDictionary[188].setEnglWord("career", "карьера", 500);
	MerfiDictionary[189].setEnglWord("razor", "бритва", 500);			// рейзе
	MerfiDictionary[190].setEnglWord("towel", "полотенце", 500);		// тауэл таул (э почти нет)
	MerfiDictionary[191].setEnglWord("kettle", "чайник", 500);
	MerfiDictionary[192].setEnglWord("knife", "нож", 500);
	MerfiDictionary[193].setEnglWord("mug", "кружка", 500);
	MerfiDictionary[194].setEnglWord("backpack", "рюкзак", 500);
	MerfiDictionary[195].setEnglWord("bonfire", "костер", 500);
	MerfiDictionary[196].setEnglWord("yield", "производить, приносить, давать (плоды, доход)", 500);	// еилд
	MerfiDictionary[197].setEnglWord("envelope", "конверт", 500);		// Энвелоуп
	/*************** End of 1025 popular words: *****************************************************************/

	/****************** Lesson 31: *************************************************************************/
	MerfiDictionary[198].setEnglWord("day after day", "день ото дня", 31);
	MerfiDictionary[199].setEnglWord("politness", "вежливость", 31);
	MerfiDictionary[200].setEnglWord("relative", "родственник", 31);
	MerfiDictionary[201].setEnglWord("keep myself fit", "держать себя в форме", 31);
	MerfiDictionary[202].setEnglWord("come of age", "повзрослеть, достичь совершеннолетия", 31);
	MerfiDictionary[203].setEnglWord("mention", "упомянуть", 31);
	MerfiDictionary[204].setEnglWord("fridge", "холодильник", 31);
	MerfiDictionary[205].setEnglWord("appointment", "встреча", 31);
	MerfiDictionary[206].setEnglWord("groceries", "продукты, крупы", 31);;
	MerfiDictionary[207].setEnglWord("be kind to the elephants", "быть добрым к слонам", 31);
	MerfiDictionary[208].setEnglWord("blame", "винить, упрекать, вина, упрек", 31);				// Урок 63
	MerfiDictionary[209].setEnglWord("Israel", "Израиль", 31);
	MerfiDictionary[210].setEnglWord("keep smiling", "продолжай улыбаться", 31);
	MerfiDictionary[211].setEnglWord("park in the street", "парковаться на улице", 31);
	MerfiDictionary[212].setEnglWord("in a friendly way", "по-дружески", 31);
	MerfiDictionary[213].setEnglWord("grocery", "бакалея", 31);					// гросери
	/*************** End of init Lesson 31 *****************************************************************/
	
	/****************** Lesson 32: *************************************************************************/
	MerfiDictionary[214].setEnglWord("go on a diet", "сесть на диету", 32);
	MerfiDictionary[215].setEnglWord("beware of", "остерегаться (пр)", 32);
	MerfiDictionary[216].setEnglWord("patient", "терпеливый", 32);
	MerfiDictionary[217].setEnglWord("outfit", "наряд, одежда", 32);
	MerfiDictionary[218].setEnglWord("cheat on", "изменять (пр), обманывать", 32);
	MerfiDictionary[219].setEnglWord("be rude to", "быть грубым (пр)", 32);
	MerfiDictionary[220].setEnglWord("if you don't mind", "если ты не против", 32);
	MerfiDictionary[221].setEnglWord("definitely", "определенно, однозначно, точно", 32);
	MerfiDictionary[222].setEnglWord("each other", "друг с другом", 32);
	MerfiDictionary[223].setEnglWord("make friends with", "подружиться (пр)", 32);
	/*************** End of init Lesson 32 *****************************************************************/

	/****************** Lesson 33: *************************************************************************/
	MerfiDictionary[224].setEnglWord("driving licence", "водительские права", 33);	// лайсенс
	MerfiDictionary[225].setEnglWord("babysitter", "нянка, сиделка", 33);
	MerfiDictionary[226].setEnglWord("hire", "нанимать", 33);
	MerfiDictionary[227].setEnglWord("overpay", "переплачивать", 33);
	MerfiDictionary[228].setEnglWord("all day long", "день деньской, весь день", 33);
	MerfiDictionary[229].setEnglWord("complaint", "жалоба", 33);
	MerfiDictionary[230].setEnglWord("soldier", "солдат", 33);						// солжер
	MerfiDictionary[231].setEnglWord("chemistry", "химия", 33);						// кеместри 
	MerfiDictionary[232].setEnglWord("it's my turn", "моя очередь", 33);
	MerfiDictionary[233].setEnglWord("do the dishes", "мыть посуду", 33);
	MerfiDictionary[234].setEnglWord("primary school", "начальная школа", 33);
	MerfiDictionary[235].setEnglWord("in time", "вовремя", 33);
	MerfiDictionary[236].setEnglWord("even", "даже", 33);
	MerfiDictionary[237].setEnglWord("promotion", "продвижение, повышение", 33);
	/*************** End of init Lesson 33 *****************************************************************/

	/****************** Lesson 34: *************************************************************************/
	MerfiDictionary[238].setEnglWord("to be honest", "если честно", 34);
	MerfiDictionary[239].setEnglWord("date him", "встречаться с ним, ходить на свидание", 34);
	MerfiDictionary[240].setEnglWord("That would be very kind of you.", "Это было бы очень мило с вашей стороны.", 34);
	MerfiDictionary[241].setEnglWord("perhaps", "возможно, наверное", 34);
	MerfiDictionary[242].setEnglWord("do me a favor", "окажи мне услугу", 34);		// фейвор
	MerfiDictionary[243].setEnglWord("I'd love to", "с радостью (would)", 34);	
	/*************** End of init Lesson 34 *****************************************************************/

	/****************** Lesson 35 *************************************************************************/
	MerfiDictionary[244].setEnglWord("lay the table", "накрыть на стол", 35);
	MerfiDictionary[245].setEnglWord("do the hair", "сделать прическу, уложить волосы", 35);
	MerfiDictionary[246].setEnglWord("watch out!", "берегись!", 35);
	MerfiDictionary[247].setEnglWord("watch your steps", "смотри под ноги", 35);
	MerfiDictionary[248].setEnglWord("glasses", "очки, стаканы", 35);
	MerfiDictionary[249].setEnglWord("take care", "береги себя", 35);
	MerfiDictionary[250].setEnglWord("take your time", "не торопись, не спеши", 35);
	MerfiDictionary[251].setEnglWord("mess", "беспорядок", 35);
	MerfiDictionary[252].setEnglWord("silly", "глупый", 35);
	/*************** End of init Lesson 35 *****************************************************************/

	/****************** Lesson 36 *************************************************************************/
	MerfiDictionary[253].setEnglWord("homicide", "убийство, убийца, убивать", 36);					// хомисайд
	MerfiDictionary[254].setEnglWord("nurse", "медсестра", 36);
	MerfiDictionary[255].setEnglWord("hike", "ходить пешком, совершать пешую прогулку", 36);
	MerfiDictionary[256].setEnglWord("go jogging", "заниматься бегом трусцой", 36);
	MerfiDictionary[257].setEnglWord("a hell of a lot of...", "чертовски много...", 36);
	MerfiDictionary[258].setEnglWord("be retired", "быть на пенсии", 36);							// ритаед
	MerfiDictionary[259].setEnglWord("criminal", "преступник", 36);
	MerfiDictionary[260].setEnglWord("drug", "наркотик, лекарство", 36);
	MerfiDictionary[261].setEnglWord("work out", "заниматься спортом", 36);
	/*************** End of init Lesson 36 *****************************************************************/

	/****************** Lesson 37 *************************************************************************/
	MerfiDictionary[262].setEnglWord("hardly", "едва ли", 37);
	MerfiDictionary[263].setEnglWord("fearless", "бесстаршный", 37);
	MerfiDictionary[264].setEnglWord("politician", "политик", 37);										// политИшн
	MerfiDictionary[265].setEnglWord("among", "среди", 37);
	MerfiDictionary[266].setEnglWord("worry", "беспокоиться", 37);
	MerfiDictionary[267].setEnglWord("pocket", "карман", 37);
	MerfiDictionary[268].setEnglWord("cigarette", "сигарета", 37);
	MerfiDictionary[269].setEnglWord("unfortunately", "к несчатью", 37);
	MerfiDictionary[270].setEnglWord("painkiller", "обезболивающее", 37);
	MerfiDictionary[271].setEnglWord("medical kit", "аптечка", 37);
	MerfiDictionary[272].setEnglWord("pharmacy", "аптека (p...)", 37);										// фармеси
	/*************** End of init Lesson 37 *****************************************************************/

	/****************** Lesson 38 *************************************************************************/
	MerfiDictionary[273].setEnglWord("at the concert", "на концерте", 38);
	MerfiDictionary[274].setEnglWord("go out of the cafe", "выйти из кафе", 38);
	MerfiDictionary[275].setEnglWord("anywhere", "в любом месте", 38);
	MerfiDictionary[276].setEnglWord("look for", "искать", 38);
	MerfiDictionary[277].setEnglWord("crash", "авария, сломаться, крах", 38);
	MerfiDictionary[278].setEnglWord("innovation", "инновация, новшество", 38);
	MerfiDictionary[279].setEnglWord("increase of prices", "повышение цен", 38);					// Инкрис
	MerfiDictionary[280].setEnglWord("fuel", "топливо", 38);
	MerfiDictionary[281].setEnglWord("recently", "недавно, в последнее время", 38);					// рИснтли
	MerfiDictionary[282].setEnglWord("challenge", "вызов, испытание", 38);							// чЕлиндж
	MerfiDictionary[283].setEnglWord("shift", "сдвиг, прорыв", 38);
	MerfiDictionary[284].setEnglWord("misunderstanding", "недопонимание, недоразумение", 38);
	MerfiDictionary[285].setEnglWord("so far", "на данный момент, до тех пор, пока", 38);
	MerfiDictionary[286].setEnglWord("change for the better", "измениться к лучшему", 38);
	MerfiDictionary[287].setEnglWord("carefully", "внимательно, тщательно", 38);
	/*************** End of init Lesson 38 *****************************************************************/

	/****************** Lesson 39 *************************************************************************/
	MerfiDictionary[288].setEnglWord("Oh gosh", "О Боже мой", 39);
	MerfiDictionary[289].setEnglWord("quite", "вполне, достаточно (к прилагательному)", 39);
	MerfiDictionary[290].setEnglWord("Are you kidding?", "Ты шутишь?", 39);
	MerfiDictionary[291].setEnglWord("rain cats and dogs", "лить, как из ведра", 39);
	MerfiDictionary[292].setEnglWord("You are reading my mind", "Ты читаешь мои мысли", 39);
	MerfiDictionary[293].setEnglWord("far", "далеко (в вопросах и отрицаниях)", 39);
	MerfiDictionary[294].setEnglWord("a long way", "далеко (в утверждениях)", 39);
	MerfiDictionary[295].setEnglWord("foggy", "туманный, туманно", 39);
	MerfiDictionary[296].setEnglWord("cloudy", "облачно, облачный", 39);
	/*************** End of init Lesson 39 *****************************************************************/

	/****************** Lesson 40 *************************************************************************/
	MerfiDictionary[297].setEnglWord("at all", "в целом, вообще", 40);
	MerfiDictionary[298].setEnglWord("principle", "принцып, правило", 40);									// прИнсипл
	MerfiDictionary[299].setEnglWord("if so", "если так, если это так", 40);
	MerfiDictionary[300].setEnglWord("have a rest", "отдыхать", 40);
	MerfiDictionary[301].setEnglWord("traffic jam", "пробка", 40);
	MerfiDictionary[302].setEnglWord("insane", "безумный, ненормальный", 40);								// инсЕйн
	MerfiDictionary[303].setEnglWord("noticeable", "заметный, приметный", 40);								// нОутисэбл
	MerfiDictionary[304].setEnglWord("fasten your seat belts", "пристегните ваши ремни безопасности", 40);	// фесн, фасн
	MerfiDictionary[305].setEnglWord("positively", "положительно, безусловно, несомненно", 40);				// пОзетивли
	MerfiDictionary[306].setEnglWord("expectation", "ожидание, надежда", 40);								// экспектЕйшн		
	MerfiDictionary[307].setEnglWord("a little bit", "чуть-чуть", 40);
	MerfiDictionary[308].setEnglWord("God bless you", "будь здоров (после пчиха)", 40);
	MerfiDictionary[309].setEnglWord("get well", "выздоравливать, поправляться", 40);
	MerfiDictionary[310].setEnglWord("sneeze", "чихать", 40);
	MerfiDictionary[311].setEnglWord("necessary", "необходимо", 40);
	MerfiDictionary[312].setEnglWord("I'm terribly sorry", "Я ужасно извиняюсь", 40);
	/*************** End of init Lesson 40 *****************************************************************/

	/****************** Lesson 41 *************************************************************************/
	MerfiDictionary[313].setEnglWord("mice", "мыши", 41);
	MerfiDictionary[314].setEnglWord("sibling", "родной брат или сестра", 41);								// сИблин
	MerfiDictionary[315].setEnglWord("be similar to each other", "быть похожими друг на друга", 41);		// сИмулэ
	MerfiDictionary[316].setEnglWord("in another way", "по-другому", 41);
	/*************** End of init Lesson 41 *****************************************************************/

	/****************** Lesson 42 *************************************************************************/
	MerfiDictionary[317].setEnglWord("lawyer", "юрист, адвокат", 42);
	MerfiDictionary[318].setEnglWord("run the something", "управлять чем-то, следить за чем-то", 42);
	MerfiDictionary[319].setEnglWord("do the chores", "вести домашние дела", 42);							// чорз
	MerfiDictionary[320].setEnglWord("band", "музыкальная группа", 42);
	MerfiDictionary[321].setEnglWord("get hooked on...", "подсесть на...", 42);
	MerfiDictionary[322].setEnglWord("relevant", "уместный, относящийся к делу, релевантный", 42);			// рЭливент
	MerfiDictionary[323].setEnglWord("consider", "считать, полагать, учитывать", 42);						// кэнсИдер						
	/*************** End of init Lesson 42 *****************************************************************/

	/****************** Lesson 43 *************************************************************************/
	MerfiDictionary[324].setEnglWord("makeup", "макияж", 43);
	MerfiDictionary[325].setEnglWord("wallet", "бумажник", 43);												// уолет
	MerfiDictionary[326].setEnglWord("no one", "никто", 43);
	MerfiDictionary[327].setEnglWord("have nothing to do with", "не иметь ничего общего к, никак не относится к", 43);
	MerfiDictionary[328].setEnglWord("treat somebody this way", "обойтись с кем-то таким образом", 43);
	MerfiDictionary[329].setEnglWord("treat myself strictly", "относиться к себе строго", 43);				// Урок 63
	MerfiDictionary[330].setEnglWord("care about", "заботиться о", 43);
	/*************** End of init Lesson 43 *****************************************************************/

	/****************** Lesson 44 *************************************************************************/
	MerfiDictionary[331].setEnglWord("share with", "делиться с", 44);
	MerfiDictionary[332].setEnglWord("Why don't you...?", "Почему бы тебе...?", 44);	// Вопрос в повелительном наклонении
	/*************** End of init Lesson 44 *****************************************************************/

	/****************** Lesson 45 *************************************************************************/
	MerfiDictionary[333].setEnglWord("be present", "присутстовать", 45);
	MerfiDictionary[334].setEnglWord("guilty", "виновный", 45);
	MerfiDictionary[335].setEnglWord("make mother laugh", "заставить маму смеяться (кого-то что-то делать)", 45);
	MerfiDictionary[336].setEnglWord("TV series", "сериал", 45);					// сИрис
	MerfiDictionary[337].setEnglWord("like best", "нравится больше всего", 45);
	MerfiDictionary[338].setEnglWord("laugh till one cries", "смеяться до слез", 45);
	MerfiDictionary[339].setEnglWord("Greek cuisine", "греческая кухня", 45);		// квизИн
	/*************** End of init Lesson 45 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[340].setEnglWord("lantern", "фонарь", 500);						// лЭнтёрн, лЕнтён
	MerfiDictionary[341].setEnglWord("teardrop", "слеза, слезинка", 500);			// тИэдроп
	MerfiDictionary[342].setEnglWord("calendar", "календарь", 500);					// кЭлиндэ
	MerfiDictionary[343].setEnglWord("black currant", "черная смородина", 500);		// кАрент
	MerfiDictionary[344].setEnglWord("fragrance", "аромат", 500);					// фрЕйгренс
	/*************** End of popular words: **********************************************************************/

	/****************** Lesson 46 *************************************************************************/
	MerfiDictionary[345].setEnglWord("Thailand", "Тайланд", 46);
	MerfiDictionary[346].setEnglWord("play for", "играть за (команда)", 46);
	MerfiDictionary[347].setEnglWord("stay at a hotel", "остановиться в отеле (каком-то)", 46);
	MerfiDictionary[348].setEnglWord("talk about", "говорить о", 46);
	MerfiDictionary[349].setEnglWord("wish for happiness", "желать счастья, стремиться к счастью", 46);
	MerfiDictionary[350].setEnglWord("stuff", "материал, вещи, хлам, вещество, все", 46);
	MerfiDictionary[351].setEnglWord("look like", "выглядеть каким-то образом", 46);
	/*************** End of init Lesson 46 *****************************************************************/

	/****************** Lesson 47 *************************************************************************/
	MerfiDictionary[352].setEnglWord("magazine", "журнал", 47);
	MerfiDictionary[353].setEnglWord("commit a crime", "совершить преступление", 47);
	MerfiDictionary[354].setEnglWord("accountant", "бухгалтер", 47);							// экАунтент
	MerfiDictionary[355].setEnglWord("hold a position", "занимать должность", 47);
	MerfiDictionary[356].setEnglWord("well-paid", "высокооплачиваемый", 47);
	MerfiDictionary[357].setEnglWord("enjoyable", "приносящий удовольствие", 47);				// инджоибл
	MerfiDictionary[358].setEnglWord("orchard", "фруктовый сад", 47);							// Очэд
	/*************** End of init Lesson 47 *****************************************************************/

	/****************** Lesson 48 *************************************************************************/
	MerfiDictionary[359].setEnglWord("omelette", "омлет", 48);									// Омлит Омлет
	MerfiDictionary[360].setEnglWord("master", "овладеть, хозяин", 48);
	MerfiDictionary[361].setEnglWord("permission", "разрешение", 48);
	MerfiDictionary[362].setEnglWord("practice makes perfect", "практика приводит к совершенству", 48);
	MerfiDictionary[363].setEnglWord("shipping", "доставка", 48);
	MerfiDictionary[364].setEnglWord("get the refund", "получить возврат", 48);					// рифАнд
	MerfiDictionary[365].setEnglWord("as a rule", "как правило", 48);
	MerfiDictionary[366].setEnglWord("couple", "пара, два, чета", 48);							// капл
	MerfiDictionary[367].setEnglWord("typically", "типично, обычно", 48);						// тИпикли
	MerfiDictionary[368].setEnglWord("bake", "печь", 48);
	MerfiDictionary[369].setEnglWord("get her forgiveness", "получить ее прощение", 48);			// фогИвнес 
	MerfiDictionary[370].setEnglWord("fixed terms", "фиксированные сроки", 48);
	/*************** End of init Lesson 48 *****************************************************************/

	/****************** Lesson 49 *************************************************************************/
	MerfiDictionary[371].setEnglWord("bring up a child", "воспитать, поднимать ребенка", 49);
	MerfiDictionary[372].setEnglWord("believe", "верить", 49);
	MerfiDictionary[373].setEnglWord("finally", "наконец-то", 49);
	MerfiDictionary[374].setEnglWord("take place", "иметь место, происходить, случиться", 49);
	MerfiDictionary[375].setEnglWord("have a baby", "родить ребенка", 49);
	MerfiDictionary[376].setEnglWord("restroom", "туалет, уборная", 49);
	MerfiDictionary[377].setEnglWord("obvious", "очевидный, ясный, тривиальный", 49);			// Обвиос
	MerfiDictionary[378].setEnglWord("for sure", "наверняка, несомненно", 49);
	MerfiDictionary[379].setEnglWord("get along with", "ладить, быть в хороших отношениях (пр)", 49);
	MerfiDictionary[380].setEnglWord("go off", "уезжать, уходить, сбегать (пр)", 49);
	MerfiDictionary[381].setEnglWord("be satisfied", "быть удовлетворенным, быть довольным", 49);
	MerfiDictionary[382].setEnglWord("I have no idea", "Я не имею ни малейшего представления", 49);
	/*************** End of init Lesson 49 *****************************************************************/

	/****************** Lesson 50: *************************************************************************/
	MerfiDictionary[383].setEnglWord("granny", "бабушка (сокр.)", 50);
	MerfiDictionary[384].setEnglWord("brush your teeth", "почисть свои зубы", 50);
	MerfiDictionary[385].setEnglWord("till the age of eight", "до восьми лет", 50);
	MerfiDictionary[386].setEnglWord("wrapper", "оболочка, обертка, халат", 50);				// рЭпер
	/*************** End of init Lesson 50 ****************************************************************/

	/****************** Lesson 51: *************************************************************************/
	MerfiDictionary[387].setEnglWord("umbrella", "зонт", 51);
	MerfiDictionary[388].setEnglWord("selfish", "эгоист", 51);
	MerfiDictionary[389].setEnglWord("Would you mind...?", "Ты не против...?", 51);
	MerfiDictionary[390].setEnglWord("passion", "страсть", 51);									// пЭшн
	MerfiDictionary[391].setEnglWord("day off", "выходной", 51);
	/*************** End of init Lesson 51 ****************************************************************/

	/****************** Lesson 52: *************************************************************************/
	MerfiDictionary[392].setEnglWord("refuse", "отказывать, отвергать, отходы, мусор", 52);				// рифьЮз
	MerfiDictionary[393].setEnglWord("mind", "возражать", 52);
	MerfiDictionary[394].setEnglWord("never mind", "ничего, пустяки, не бери в голову", 52);
	MerfiDictionary[395].setEnglWord("rubbish", "вздор, ерунда, чушь, хлам, мусор", 52);
	MerfiDictionary[396].setEnglWord("suggest", "предлагать, советовать", 52);							// седжЕст
	MerfiDictionary[397].setEnglWord("reward", "награда, вознаграждение, награждать", 52);				// риВод
	MerfiDictionary[398].setEnglWord("waste", "тратить в пустую, отходы, потери", 52);
	MerfiDictionary[399].setEnglWord("procrastinate", "мешкать, отсрачивать, откладывать на потом", 52);// прокрЭстинейт
	MerfiDictionary[400].setEnglWord("most of all", "больше всего", 52);
	MerfiDictionary[401].setEnglWord("explain", "объяснять", 52);
	MerfiDictionary[402].setEnglWord("applaud", "аплодировать", 52);									// эплОд
	/*************** End of init Lesson 52 ****************************************************************/

	/****************** Lesson 53: *************************************************************************/
	MerfiDictionary[403].setEnglWord("lend", "одалживать (l)", 53);
	MerfiDictionary[404].setEnglWord("advise", "советовать", 53);
	MerfiDictionary[405].setEnglWord("advice", "совет", 53);
	MerfiDictionary[406].setEnglWord("persuade", "убеждать, уговаривать", 53);							// пёсвЕйд
	MerfiDictionary[407].setEnglWord("at last", "наконец", 53);
	MerfiDictionary[408].setEnglWord("reveal a secret", "раскрыть секрет", 53);							// ривИл
	MerfiDictionary[409].setEnglWord("break up", "разбивать, разойтись, расстаться", 53);
	MerfiDictionary[410].setEnglWord("cruel", "жестокий, кровожадный", 53);
	MerfiDictionary[411].setEnglWord("invest", "вкладывать, инвестировать", 53);
	MerfiDictionary[412].setEnglWord("stress-resistant", "стрессо-устойчивый", 53);						// ризИстент
	MerfiDictionary[413].setEnglWord("confidently", "уверенно, убежденно (одно слово)", 53);			// кОнфидентли
	MerfiDictionary[414].setEnglWord("apologize", "извиняться, просить прощения", 53);					// эпОлоджайз
	MerfiDictionary[415].setEnglWord("self-confidently", "самонадеянно", 53);							// селф-кОнфидентли
	MerfiDictionary[416].setEnglWord("clothes", "одежда", 53);											// клОоз или Клоутс
	MerfiDictionary[417].setEnglWord("make somebody", "заставить кого-то", 53);
	MerfiDictionary[418].setEnglWord("dancing isn't your cup of tea", "танцы это не твое", 53);
	/*************** End of init Lesson 53 ****************************************************************/

	/****************** Lesson 54: *************************************************************************/
	MerfiDictionary[419].setEnglWord("invite to the wedding", "пригласить на свадьбу", 54);
	MerfiDictionary[420].setEnglWord("correctly", "правильно", 54);
	MerfiDictionary[421].setEnglWord("achieve your goal", "достичь вашей цели", 54);
	MerfiDictionary[422].setEnglWord("It's worth that.", "Это того стоит.", 54);						// вЁрз									
	MerfiDictionary[423].setEnglWord("get used to", "привыкнуть к, притерпеться (пр)", 54);
	MerfiDictionary[424].setEnglWord("achieve", "достигать, добиваться", 54);
	MerfiDictionary[425].setEnglWord("soda", "газировка", 54);											// сОуда
	MerfiDictionary[426].setEnglWord("pay them a visit", "нанесть им визит", 54);
	MerfiDictionary[427].setEnglWord("have a break", "иметь перерыв", 54);
	MerfiDictionary[428].setEnglWord("long for", "ожидать с нетерпеием, тосковать", 54);
	/*************** End of init Lesson 54 ****************************************************************/

	/****************** Lesson 55: *************************************************************************/
	MerfiDictionary[429].setEnglWord("go to sleep", "заснуть", 55);
	MerfiDictionary[430].setEnglWord("go home", "идти домой", 55);
	MerfiDictionary[431].setEnglWord("go for a swim", "пойти поплавать (go)", 55);
	MerfiDictionary[432].setEnglWord("excursion", "экскурсия", 55);										// икскЁшн															
	MerfiDictionary[433].setEnglWord("cruise", "круиз", 55);											// круз
	MerfiDictionary[434].setEnglWord("strike", "забастовка, удар, бить", 55);
	MerfiDictionary[435].setEnglWord("go for a coffee", "пойти выпить кофе", 55);
	MerfiDictionary[436].setEnglWord("harvest festival", "праздник урожая", 55);						// хАвист фЕстивл
	MerfiDictionary[437].setEnglWord("fair", "ярмарка", 55);
	MerfiDictionary[438].setEnglWord("go sightseeing", "смотреть достопримечательности (go)", 55);		// сАйтсиинг
	MerfiDictionary[439].setEnglWord("nearby", "поблизости, неподолеку", 55);							// ниабАй
	MerfiDictionary[440].setEnglWord("I'm in!", "Я только за! Я в деле!", 55);
	/*************** End of init Lesson 55 ****************************************************************/

	/****************** Lesson 56: *************************************************************************/
	MerfiDictionary[441].setEnglWord("get fat/lost/dressed/wet", "растолстеть/потеряться/одеться/промокнуть", 56);
	MerfiDictionary[442].setEnglWord("parcel", "посылка, почтовый пакет", 56);
	MerfiDictionary[443].setEnglWord("toddler", "дошколенок (возраст от грудничка до школы)", 56);
	MerfiDictionary[444].setEnglWord("get serious", "стать серьезным", 56);
	MerfiDictionary[445].setEnglWord("luggage delivery", "доставка багажа", 56);
	MerfiDictionary[446].setEnglWord("get in a car", "сесть в машину (какую-то)", 56);
	MerfiDictionary[447].setEnglWord("get out of a car", "выйти из машины (какой-то)", 56);
	MerfiDictionary[448].setEnglWord("get on a train/plane/bus", "сесть на поезд/самолет/автобус", 56);
	MerfiDictionary[449].setEnglWord("get off a train/plane/bus", "сойти с поезда/самолета/автобуса", 56);
	MerfiDictionary[450].setEnglWord("It's time to get serious", "Пора стать серьезным", 56);
	/*************** End of init Lesson 56 ****************************************************************/

	/****************** Lesson 57: *************************************************************************/
	MerfiDictionary[451].setEnglWord("do the ironing/washing", "гладить/стирать", 57);
	MerfiDictionary[452].setEnglWord("do an exam", "сдавать экзамен", 57);
	MerfiDictionary[453].setEnglWord("make a mistake", "сделать ошибку", 57);
	MerfiDictionary[454].setEnglWord("make a noise", "шуметь", 57);
	MerfiDictionary[455].setEnglWord("make an appointment", "назначить встречу, свидание", 57);
	MerfiDictionary[456].setEnglWord("make a bed", "убрать кровать", 57);
	MerfiDictionary[457].setEnglWord("take a photogragh", "сфотографировать, сделать снимок", 57);
	MerfiDictionary[458].setEnglWord("How do you do?", "Как дела?", 57);						// Ответ: How do you do?
	MerfiDictionary[459].setEnglWord("What do you do?", "Кем ты работаешь?", 57);
	MerfiDictionary[460].setEnglWord("do a research", "проводить исследование", 57);
	MerfiDictionary[461].setEnglWord("do repairs", "заниматься ремонтом, починкой", 57);		// далее идет действие
	MerfiDictionary[462].setEnglWord("drugstore", "аптека (d...)", 57);
	MerfiDictionary[463].setEnglWord("To make a long story short...", "Короче говоря...", 57);	// в начале предложения
	MerfiDictionary[464].setEnglWord("make an impression", "произвести впечатление", 57);
	MerfiDictionary[465].setEnglWord("make the situation clear", "прояснить ситуацию (the)", 57);
	MerfiDictionary[466].setEnglWord("make a fortune", "разбогатеть, нажить состояние", 57);	// фОчен
	MerfiDictionary[467].setEnglWord("skill", "навык, умение, мастерство", 57);
	MerfiDictionary[468].setEnglWord("make a deal", "заключить сделку, договриться", 57);
	MerfiDictionary[469].setEnglWord("make a confession to the crime", "признать вину в совершении приступления", 57);	// кэнфЭшн
	MerfiDictionary[470].setEnglWord("confess a fault", "признать (исповедаться) ошибку", 57);	// кэнфЭс
	MerfiDictionary[471].setEnglWord("do wrong", "поступить неправильно", 57);
	/*************** End of init Lesson 57 ****************************************************************/

	/****************** Lesson 58: *************************************************************************/
	MerfiDictionary[472].setEnglWord("cough", "кашель, кашлять", 58);							// коф
	MerfiDictionary[473].setEnglWord("sore throat", "больное горло", 58);
	MerfiDictionary[474].setEnglWord("I have flu", "У меня грипп", 58);							// без артикля
	MerfiDictionary[475].setEnglWord("have a pizza/glass of milk", "съесть пиццу/стакан молока", 58);
	MerfiDictionary[476].setEnglWord("have breakfast/lunch/dinner", "завтракать/обедать/ужинать", 58);
	MerfiDictionary[477].setEnglWord("have a dream", "видеть сон", 58);
	MerfiDictionary[478].setEnglWord("have a look at something", "посмотерть на что-то", 58);
	MerfiDictionary[479].setEnglWord("heart diseases", "болезни сердца", 58);					// дизИз
	MerfiDictionary[480].setEnglWord("have a right to vote", "иметь право голосовать", 58);
	MerfiDictionary[481].setEnglWord("have a bad temper", "иметь плохой характкер", 58);
	MerfiDictionary[482].setEnglWord("have a tendency to", "иметь склонность, тенденцию к", 58);// тЭндэнси
	MerfiDictionary[483].setEnglWord("have a big mouth", "рот не закрывается (о человеке)", 58);// идиома
	MerfiDictionary[484].setEnglWord("have a brush with the law", "иметь терки с законом", 58);	// идиома	
	MerfiDictionary[485].setEnglWord("have a sweet tooth", "быть сладкоежкой", 58);				// идиома
	MerfiDictionary[486].setEnglWord("take seriously", "принимать всерьез", 58);
	MerfiDictionary[487].setEnglWord("have a familiar ring", "звучать знакомо", 58);			// идиома
	MerfiDictionary[488].setEnglWord("have a chip on one's shoulder", "быть задирой, искать повод к драке", 58);// идиома
	MerfiDictionary[489].setEnglWord("movement", "движение", 58);
	MerfiDictionary[490].setEnglWord("work long hours", "работать сверхурочно", 58);
	MerfiDictionary[491].setEnglWord("give up the idea", "отказаться от идеи (конкретной)", 58);
	MerfiDictionary[492].setEnglWord("be alert", "быть начеку", 58);							// элЁрт (тревога, бдительный)
	MerfiDictionary[493].setEnglWord("enough", "достаточно", 58);
	/*************** End of init Lesson 58 ****************************************************************/

	/****************** Lesson 59: *************************************************************************/
	MerfiDictionary[494].setEnglWord("in amazement", "с удивлением, изумлением", 59);			// эмЕйзмэнт
	MerfiDictionary[495].setEnglWord("adjust", "регулировать, устанавливать, приводить в порядок", 59);
	MerfiDictionary[496].setEnglWord("insist", "настаивать, утверждать", 59);					// инсИст
	MerfiDictionary[497].setEnglWord("distinctly", "отчетливо, четко", 59);						// дистИнктли
	MerfiDictionary[498].setEnglWord("over there", "вон там", 59);
	MerfiDictionary[499].setEnglWord("bicycle rack", "велосипедная стойка, подставка, стеллаж", 59);
	MerfiDictionary[500].setEnglWord("stray dog", "дворняга, бродячий пес", 59);				// забулдившийся
	MerfiDictionary[501].setEnglWord("male/female", "мужской/женский (о поле)", 59);
	MerfiDictionary[502].setEnglWord("a funny kind of hat", "нелепая шляпа", 59);
	MerfiDictionary[503].setEnglWord("knowledge is power", "знание это сила", 59);
	/*************** End of init Lesson 59 ****************************************************************/

	/****************** Lesson 60: *************************************************************************/
	MerfiDictionary[504].setEnglWord("they seem to steal our food", "кажется, они воруют нашу еду", 60);
	MerfiDictionary[505].setEnglWord("mean", "скупой, среднее, середина, значить", 60);
	MerfiDictionary[506].setEnglWord("subscription", "подписка", 60);
	MerfiDictionary[507].setEnglWord("pets are like their owners", "питомцы, как их хозяева", 60);
	MerfiDictionary[508].setEnglWord("greedy for money", "жадный до денег", 60);
	MerfiDictionary[509].setEnglWord("The Simpsons", "Симпсоны", 60);
	MerfiDictionary[510].setEnglWord("in order to", "для того, чтобы", 60);
	MerfiDictionary[511].setEnglWord("daughter", "дочь", 60);
	MerfiDictionary[512].setEnglWord("neighbor", "сосед", 60);
	MerfiDictionary[513].setEnglWord("have a crash on", "втюриться, втрескаться в", 60);
	/*************** End of init Lesson 60 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[514].setEnglWord("escape", "побег, выход, совершить побег", 500);				// искЕйп
	MerfiDictionary[515].setEnglWord("disturb", "беспокоить, волновать, доставлять хлопоты", 500);	// дистЁб
	MerfiDictionary[516].setEnglWord("deserve", "заслуживать, быть достойным", 500);				// дизЁв
	MerfiDictionary[517].setEnglWord("defeat", "поражение, разгром, наносить поражение", 500);		// дифИт
	MerfiDictionary[518].setEnglWord("grimly", "жестоко, беспощадно, сурово", 500);
	MerfiDictionary[519].setEnglWord("exactly", "точно, именно, ровно, совершенно верно", 500);		// игзЭктли		
	MerfiDictionary[0].setEnglWord("sex", "пол (человека)", 500);
	/*************** End of popular words: ****************************************************************/

	/****************** Lesson 61: *************************************************************************/
	MerfiDictionary[520].setEnglWord("pronoun", "местоимение", 61);
	MerfiDictionary[521].setEnglWord("friends of mine", "мои друзья", 61);
	MerfiDictionary[522].setEnglWord("notice", "замечать, обращать внимание, извещение, заметка", 61);
	MerfiDictionary[523].setEnglWord("hang around the village", "шататься по деревне", 61);
	MerfiDictionary[524].setEnglWord("fellow", "парниша, приятель, дружище", 61);
	MerfiDictionary[525].setEnglWord("sarcastically", "соркастично", 61);							// соркЭстикли
	MerfiDictionary[526].setEnglWord("collar", "ошейник, воротник", 61);							// кОлэ
	MerfiDictionary[527].setEnglWord("towards", "в направлении, к, навстречу", 61);					// тувОдс
	MerfiDictionary[528].setEnglWord("overweight", "полный (о весе)", 61);
	MerfiDictionary[529].setEnglWord("firmly", "твердо", 61);
	MerfiDictionary[530].setEnglWord("adopt", "принимать, усыновлять", 61);
	MerfiDictionary[531].setEnglWord("guess", "предполагать, догадка, догадаться", 61);				// гес
	MerfiDictionary[532].setEnglWord("it was easy to guess...", "было легко догадаться...", 61);
	MerfiDictionary[533].setEnglWord("anxious", "тревожный, озабоченный", 61);						// Энккшес
	MerfiDictionary[534].setEnglWord("in her 30's", "в районе 30-ти (о возрасте женщины)", 61);
	MerfiDictionary[535].setEnglWord("hug", "обнимать, объятие", 61);
	MerfiDictionary[536].setEnglWord("tightly", "крепко, тесно", 61);								// тАйтли
	MerfiDictionary[537].setEnglWord("ordinary", "обычный", 61);									// Один(е)ри
	MerfiDictionary[538].setEnglWord("quantity", "количество", 61);									// квОнтити
	/*************** End of init Lesson 61 ****************************************************************/

	/****************** Lesson 62: *************************************************************************/
	MerfiDictionary[539].setEnglWord("be pleased", "быть давольным", 62);
	MerfiDictionary[540].setEnglWord("hairbrush", "расческа", 62);
	MerfiDictionary[541].setEnglWord("gorgeous", "шикарный, великолепный", 62);						// гОджес
	MerfiDictionary[542].setEnglWord("purchase", "покупка, закупка", 62);							// пЁтчес
	/*************** End of init Lesson 62 *****************************************************************/

	/****************** Lesson 63: *************************************************************************/
	MerfiDictionary[543].setEnglWord("Sometimes I talk to myself.", "Иногда я говорю с собой.", 63);
	MerfiDictionary[544].setEnglWord("I enjoyed myself.", "Я получил удовольствие.", 63);
	MerfiDictionary[545].setEnglWord("help yourself", "угощайся (предложение)", 63);
	MerfiDictionary[546].setEnglWord("she was by herself", "она была одна (мест.)", 63);	
	MerfiDictionary[547].setEnglWord("And I think to myself...", "И я себе думаю...", 63);
	MerfiDictionary[548].setEnglWord("psychologist", "психолог", 63);							// сайкОлоджист
	MerfiDictionary[549].setEnglWord("feed", "корм, кормить", 63);
	MerfiDictionary[550].setEnglWord("fool myself", "обманывать себя", 63);
	MerfiDictionary[551].setEnglWord("Don't make a fool of yourself.", "Не делай из себя дурака.", 63);
	MerfiDictionary[552].setEnglWord("make yourself at home", "чувствуй себя, как дома", 63);
	MerfiDictionary[553].setEnglWord("A cat prefers walking by itself.", "Кошка предпочитает гулять сама по себе.", 63);							// сайкОлоджист
	/*************** End of init Lesson 63 *****************************************************************/

	/****************** Lesson 64: *************************************************************************/
	MerfiDictionary[554].setEnglWord("because of", "по причине, из-за", 64);
	MerfiDictionary[555].setEnglWord("cause", "причина, повод, вызывать, быть причиной", 64);
	MerfiDictionary[556].setEnglWord("colleague", "коллега", 64);								// кАлиг
	MerfiDictionary[557].setEnglWord("approve", "одобрять, утверждать", 64);
	MerfiDictionary[558].setEnglWord("masterpiece", "шедевр", 64);
	MerfiDictionary[559].setEnglWord("my wife's parents' house", "дом родителей моей жены", 64);
	MerfiDictionary[560].setEnglWord("densely", "плотно, густно", 64);							// дЕнсли
	MerfiDictionary[561].setEnglWord("double-decker", "двухпалубный, двухэтажный, двойной (бутерброд)", 64);
	MerfiDictionary[562].setEnglWord("citizen", "житель", 64);
	/*************** End of init Lesson 64 *****************************************************************/

	/****************** Lesson 65: *************************************************************************/
	MerfiDictionary[563].setEnglWord("robber", "грабитель, разбойник", 65);
	MerfiDictionary[564].setEnglWord("hawk", "ястреб, сокол", 65);								// хок
	MerfiDictionary[565].setEnglWord("beak", "клюв", 65);
	MerfiDictionary[566].setEnglWord("claw", "коготь, зубец, клешня, царапать, рвать", 65);		// кло
	MerfiDictionary[567].setEnglWord("stage", "этап, сцена, стадия, организовывать", 65);
	MerfiDictionary[568].setEnglWord("composer", "композитор", 65);								// компОузер
	MerfiDictionary[569].setEnglWord("succeed", "преуспевать, иметь успех", 65);
	MerfiDictionary[570].setEnglWord("coroner", "субмедэксперт", 65);
	MerfiDictionary[571].setEnglWord("nowadays", "настоящее время, наши дни", 65);
	MerfiDictionary[572].setEnglWord("engineer", "инженер", 65);
	/*************** End of init Lesson 65 *****************************************************************/

	/****************** Lesson 66: *************************************************************************/
	MerfiDictionary[573].setEnglWord("shelf", "полка", 66);
	MerfiDictionary[574].setEnglWord("scissors", "ножницы", 66);								
	MerfiDictionary[575].setEnglWord("a pair of pyjamas", "пара пижамы", 66);					// педжЕмез
	MerfiDictionary[576].setEnglWord("tights", "колготки", 66);	
	MerfiDictionary[577].setEnglWord("ox/oxen", "бык/быки", 66);
	MerfiDictionary[578].setEnglWord("cactus/cacti", "кактус/кактусы", 66);						// кЕктес			
	MerfiDictionary[579].setEnglWord("the native peoples of Mexico", "коренные народы Мексики (арт.)", 66);
	MerfiDictionary[580].setEnglWord("cookery book", "поваренная книга", 66);
	MerfiDictionary[581].setEnglWord("binoculars", "бинокль", 66);								// бинОкъюларс
	MerfiDictionary[582].setEnglWord("headphones", "наушники, гарнитура", 66);
	MerfiDictionary[583].setEnglWord("handy", "удобный, портативный", 66);
	MerfiDictionary[584].setEnglWord("be about to", "как раз собирался", 66);
	MerfiDictionary[585].setEnglWord("kindergarten", "детский сад", 66);						// киндергАтен
	MerfiDictionary[586].setEnglWord("community", "сообщество", 66);
	MerfiDictionary[587].setEnglWord("striped", "в полоску, полосатый", 66);					// стрАйпт
	/*************** End of init Lesson 66 *****************************************************************/

	/****************** Lesson 67: *************************************************************************/
	MerfiDictionary[588].setEnglWord("a jug of juice", "кувшин сока", 67);
	MerfiDictionary[589].setEnglWord("a jar of honey", "баночка меда", 67);						// jar
	MerfiDictionary[590].setEnglWord("a bar of soap", "брусок мыла", 67);
	MerfiDictionary[591].setEnglWord("a loaf of bread", "буханка хлеба", 67);
	MerfiDictionary[592].setEnglWord("a slice of bread", "кусок хлеба", 67);					// слАйс
	MerfiDictionary[593].setEnglWord("a can of cola", "баночка колы", 67);
	MerfiDictionary[594].setEnglWord("a bowl of rice", "миска риса", 67);
	MerfiDictionary[595].setEnglWord("a bag of flour", "мешок муки", 67);						// флАуэ
	MerfiDictionary[596].setEnglWord("a bottle of perfume", "бутылек духов", 67);				// пефьЮм
	MerfiDictionary[597].setEnglWord("a packet of onion chips", "пачка луковых чипсов", 67);
	MerfiDictionary[598].setEnglWord("a piece of music", "музыкальное произведение", 67);
	MerfiDictionary[599].setEnglWord("a kilo of pork", "килограмм свинины", 67);
	MerfiDictionary[600].setEnglWord("life isn't a piece of cake", "жизнь не проста", 67);
	MerfiDictionary[601].setEnglWord("a piece of news", "новость", 67);
	MerfiDictionary[602].setEnglWord("cash", "наличные", 67);
	MerfiDictionary[603].setEnglWord("take out garbage", "вынеси мусор", 67);					// гАбидж
	MerfiDictionary[604].setEnglWord("fall in love with", "влюбиться в (пр.)", 67);
	MerfiDictionary[605].setEnglWord("wisdom", "мудрость", 67);									// уИздом
	MerfiDictionary[606].setEnglWord("antique forniture", "старинная (античная) мебель", 67);	// Энтик
	MerfiDictionary[607].setEnglWord("mansion", "имение, дворец", 67);							// мЭншн
	MerfiDictionary[608].setEnglWord("ceiling", "потолок", 67);									// сИлинg
	MerfiDictionary[609].setEnglWord("cereal", "злаковый, каша", 67);							// сИриэл								
	MerfiDictionary[610].setEnglWord("it's not for nothing", "это не с проста", 67);
	MerfiDictionary[611].setEnglWord("scientist", "ученый", 67);
	MerfiDictionary[612].setEnglWord("violence", "насилие, жестокость", 67);					// вАйленс
	MerfiDictionary[613].setEnglWord("respect", "уважение", 67);
	MerfiDictionary[614].setEnglWord("a tin of tuna", "банка тунца", 67);
	/*************** End of init Lesson 67 *****************************************************************/

	/****************** Lesson 68: *************************************************************************/
	MerfiDictionary[615].setEnglWord("cupboard", "буфет, чулан", 68);							// кАбед
	MerfiDictionary[616].setEnglWord("coffee pot", "кофейник", 68);
	MerfiDictionary[617].setEnglWord("inspiration", "вдохновение, вводушевление, инспирация", 68);
	MerfiDictionary[618].setEnglWord("productive", "продуктивный, плодотворный", 68);
	MerfiDictionary[619].setEnglWord("opportunity", "возможность, удобрый случай", 68);
	MerfiDictionary[620].setEnglWord("sorrow", "печаль, горе, скорбеть, грустить", 68);			// сОроу
	MerfiDictionary[621].setEnglWord("behave", "вести себя, поступать", 68);					// бихЕйв
	MerfiDictionary[622].setEnglWord("candies", "конфеты", 68);
	MerfiDictionary[623].setEnglWord("cognac", "коньяк", 68);									// коньяк
	MerfiDictionary[624].setEnglWord("a medium roast beef", "говядина средней прожарки (порция)", 68);
	MerfiDictionary[625].setEnglWord("allow me a moment", "позвольте одну секундочку", 68);
	/*************** End of init Lesson 68 *****************************************************************/
	
	/****************** Lesson 69: *************************************************************************/
	MerfiDictionary[626].setEnglWord("rhythm", "ритм, периодичность", 69);						// рИзэм							
	MerfiDictionary[627].setEnglWord("buzz", "гудеть, жужжать, жужжание, гул, молва", 69);
	MerfiDictionary[628].setEnglWord("settle", "скамья, селиться, устроиться", 69);
	MerfiDictionary[629].setEnglWord("inspire", "вдохновлять, воодушевлять", 69);
	MerfiDictionary[630].setEnglWord("routine", "рутина, рутиный, шаблон", 69);					// рутИн
	MerfiDictionary[631].setEnglWord("responsibility", "ответственность", 69);	
	MerfiDictionary[632].setEnglWord("feel free from", "чувствовать свободу от (пр.)", 69);
	MerfiDictionary[633].setEnglWord("the countryside", "загород (арт.)", 69);
	MerfiDictionary[634].setEnglWord("I would rather to...", "Я бы лучше..., я бы предпочел (пр.)...", 69);
	/*************** End of init Lesson 69 *****************************************************************/

	/****************** Lesson 70: *************************************************************************/
	MerfiDictionary[635].setEnglWord("trumpet", "труба", 70);						// трАмпит												
	MerfiDictionary[636].setEnglWord("immediately", "немедленно", 70);				// имИдиэтли
	MerfiDictionary[637].setEnglWord("be wanted", "разыскивается", 70);
	MerfiDictionary[638].setEnglWord("draft", "отбирать, отбор", 70);				// дрЭфт дРофт
	MerfiDictionary[639].setEnglWord("an honor", "честь, почет (арт.)", 70);
	MerfiDictionary[640].setEnglWord("it's about to rain", "вот-вот пойдет дождь", 70);
	MerfiDictionary[641].setEnglWord("musician", "музыкант", 70);					// музИшн
	MerfiDictionary[642].setEnglWord("my family and I", "я и моя семья", 70);
	MerfiDictionary[643].setEnglWord("talented", "талантливый", 70);
	/*************** End of init Lesson 70 *****************************************************************/

	/****************** Lesson 71: *************************************************************************/
	MerfiDictionary[644].setEnglWord("take me along with you", "возьми меня с собой", 71);	
	MerfiDictionary[645].setEnglWord("stay out of trouble", "держаться подальше от неприятностей", 71);
	MerfiDictionary[646].setEnglWord("stay up late", "не ложиться до поздна", 71);
	MerfiDictionary[647].setEnglWord("afford", "позволить себе, иметь возможность", 71);
	MerfiDictionary[648].setEnglWord("be fired", "быть уволенным", 71);
	MerfiDictionary[649].setEnglWord("resident", "постоянный житель", 71);			// рЭзидент
	MerfiDictionary[650].setEnglWord("usually", "обычно (u...)", 71);		
	/*************** End of init Lesson 71 *****************************************************************/

	/****************** Lesson 72: *************************************************************************/
	MerfiDictionary[651].setEnglWord("forensic", "судебный", 72);						// форЕнзик
	MerfiDictionary[652].setEnglWord("forensics", "судмедэкспертиза", 72);				// форЕнзикс
	MerfiDictionary[653].setEnglWord("struggle", "борьба, усилие, сражаться", 72);
	MerfiDictionary[654].setEnglWord("biology/geography/physics", "биология/география/физика", 72);
	MerfiDictionary[655].setEnglWord("boxing is an Olimpic discipline", "бокс - это олимпийский вид", 72);
	MerfiDictionary[656].setEnglWord("puzzle", "головоломка, загадка, запутывать", 72);
	MerfiDictionary[657].setEnglWord("expression", "выражение", 72);
	MerfiDictionary[658].setEnglWord("be considered to be...", "считается что...", 72);
	MerfiDictionary[659].setEnglWord("sence of humor", "чувство юмора", 72);
	MerfiDictionary[660].setEnglWord("quality", "качество", 72);	
	MerfiDictionary[661].setEnglWord("triumph of evil", "торжество зла", 72);			// трАйамф оф ивл
	MerfiDictionary[662].setEnglWord("foreigner", "иностранец", 72);					// фОренер
	MerfiDictionary[663].setEnglWord("especially", "особенно", 72);
	MerfiDictionary[664].setEnglWord("biathlon", "биатлон", 72);						// байЭслэн
	MerfiDictionary[665].setEnglWord("European", "европеец, европейский", 72);			// юрЭпиэн
	MerfiDictionary[666].setEnglWord("Chinese", "китайский", 72);
	MerfiDictionary[667].setEnglWord("Japanese", "японский", 72);
	MerfiDictionary[668].setEnglWord("philosophy", "философия", 72);
	MerfiDictionary[669].setEnglWord("I'll do my best", "я очень постараюсь", 72);
	MerfiDictionary[670].setEnglWord("well-wisher", "доброжелатель", 72);
	/*************** End of init Lesson 72 *****************************************************************/

	/****************** Lesson 73: *************************************************************************/
	MerfiDictionary[671].setEnglWord("the Netherlands", "Нидерланды", 73);				// нЕзерлендс		
	MerfiDictionary[672].setEnglWord("the Canary Islands", "Канарские острова", 73);	// кэнЕри
	MerfiDictionary[673].setEnglWord("the Alps", "Альпы", 73);							// Алпс
	MerfiDictionary[674].setEnglWord("the Pacific Ocean", "Тихий океан", 73);
	MerfiDictionary[675].setEnglWord("the Mediterranean Sea", "Средиземное море", 73);	// медитерЕйниен
	MerfiDictionary[676].setEnglWord("the Suez Canal", "Суэцкий канал", 73);			// сУез кэнЭл
	MerfiDictionary[677].setEnglWord("Westminster Abbey", "Вестминское аббатство", 73);	// вЕстминстер Эби
	MerfiDictionary[678].setEnglWord("London Zoo", "лондонский зоопарк", 73);
	MerfiDictionary[679].setEnglWord("Edinburgh Castle", "Эдинбургский замок", 73);		// Эдинбере Касл
	MerfiDictionary[680].setEnglWord("the Science Museum", "музей науки", 73);
	MerfiDictionary[681].setEnglWord("the Great Wall of China", "Великая китайская стена", 73);
	MerfiDictionary[682].setEnglWord("the Tower of London", "лондонский Тауэр", 73);
	MerfiDictionary[683].setEnglWord("misbelief", "заблуждение, ересь", 73);			// мисбилИф
	MerfiDictionary[684].setEnglWord("Argentina", "Аргентина", 73);						// адженТинэ
	MerfiDictionary[685].setEnglWord("Mount Everest", "гора Эверест", 73);				// Эверист
	MerfiDictionary[686].setEnglWord("surface", "поверхность", 73);						// сЁрфис
	MerfiDictionary[687].setEnglWord("sunrise", "восход", 73);							// сАнрайз
	MerfiDictionary[688].setEnglWord("the Himalayas", "Гималаи", 73);					// химелЕиз
	MerfiDictionary[689].setEnglWord("Antarctica", "Антарктида", 73);					// энтАктикэ
	MerfiDictionary[690].setEnglWord("Istanbul", "Стамбул", 73);						// истанбУл
	MerfiDictionary[691].setEnglWord("the Eiffel Tower", "Эйфелевая башня", 73);		// Айфел
	MerfiDictionary[692].setEnglWord("exhibit", "экспонавт, выставлять", 73);			// эгзИбит
	MerfiDictionary[693].setEnglWord("exhibition", "выставка, показ", 73);				// эксибИшн
	MerfiDictionary[694].setEnglWord("educational institution", "образовательное учреждение", 73);
	MerfiDictionary[695].setEnglWord("Saint Sophia Cathedral", "собор святой Софии", 73);// кэсИдрел
	MerfiDictionary[696].setEnglWord("exciting", "захватывающий, увлекательный", 73);	// иксАйтинг
	MerfiDictionary[697].setEnglWord("volcano", "вулкан", 73);							// волкЕйно
	MerfiDictionary[698].setEnglWord("be located", "быть расположенным, располгагаться", 73);	
	MerfiDictionary[699].setEnglWord("We've been to Lisbon.", "Мы были в Лисабоне.", 73);	
	/*************** End of init Lesson 73 *****************************************************************/

	/****************** Lesson 74: *************************************************************************/
	MerfiDictionary[700].setEnglWord("That's all right.", "Все в порядке.", 74);	
	MerfiDictionary[701].setEnglWord("That's right.", "Все верно.", 74);
	MerfiDictionary[702].setEnglWord("try on", "примерить (пр.)", 74);
	MerfiDictionary[703].setEnglWord("actually", "по правде говоря", 74);
	MerfiDictionary[704].setEnglWord("long to...", "очень сильно что-то хотеть сделать...", 74);
	MerfiDictionary[705].setEnglWord("cowboy", "ковбой", 74);
	MerfiDictionary[706].setEnglWord("awful", "ужасный", 74);
	MerfiDictionary[707].setEnglWord("Don't even look at...", "Даже не смотри на...", 74);
	MerfiDictionary[708].setEnglWord("That's true.", "Это правда.", 74);
	MerfiDictionary[709].setEnglWord("in your shoes", "на твоем месте", 74);
	MerfiDictionary[710].setEnglWord("question", "вопрос", 74);
	/*************** End of init Lesson 74 *****************************************************************/

	/****************** Lesson 75: *************************************************************************/
	MerfiDictionary[711].setEnglWord("the one", "тот самый, единственный", 75);
	MerfiDictionary[712].setEnglWord("swear", "поклясться, клятва, присяга, ругательство", 75);
	MerfiDictionary[713].setEnglWord("opposite", "напротив, противоположный", 75);				// Опозит
	MerfiDictionary[714].setEnglWord("staff", "персонал, штат", 75);							// стэф
	MerfiDictionary[715].setEnglWord("violet", "фиолетовый", 75);								
	MerfiDictionary[716].setEnglWord("beard", "борода", 75);									// бирд
	MerfiDictionary[717].setEnglWord("mitten", "варежка, рукавица", 75);						// митн
	MerfiDictionary[718].setEnglWord("yummy", "ням-ням, вкусный, аппетитный", 75);				// Ями
	MerfiDictionary[719].setEnglWord("keep something in mind", "держать что-то в голове", 75);
	MerfiDictionary[720].setEnglWord("stripe", "полоска", 75);
	/*************** End of init Lesson 75 *****************************************************************/

	/****************** Lesson 76: *************************************************************************/
	MerfiDictionary[721].setEnglWord("biscuit", "печенье, галета", 76);							// бИскит
	MerfiDictionary[722].setEnglWord("suggestion", "предложение", 76);							// сэджЕстшен
	MerfiDictionary[723].setEnglWord("arrange", "договориться, устраивать, располагать", 76);	// эрЕйнж
	MerfiDictionary[724].setEnglWord("nope", "нет (разг.)", 76);
	MerfiDictionary[725].setEnglWord("sounds good", "звучит отлично", 76);
	MerfiDictionary[726].setEnglWord("debt", "долг", 76);										// дет
	MerfiDictionary[727].setEnglWord("witness", "свидетель", 76);
	MerfiDictionary[728].setEnglWord("surprise", "сюрприз", 76);								// сепрАйз
	MerfiDictionary[729].setEnglWord("for yesterday", "на вчера", 76);
	/*************** End of init Lesson 76 *****************************************************************/

	/****************** Lesson 77: *************************************************************************/
	MerfiDictionary[730].setEnglWord("puddle", "лужа", 77);
	MerfiDictionary[731].setEnglWord("successful", "успешный", 77);
	MerfiDictionary[732].setEnglWord("freezer", "морозильная камера", 77);
	MerfiDictionary[733].setEnglWord("suspect", "подозревать", 77);
	MerfiDictionary[734].setEnglWord("pedestrian", "пешеход", 77);								// пидЕстриэн
	MerfiDictionary[735].setEnglWord("trace", "след, отпечаток", 77);
	MerfiDictionary[736].setEnglWord("Is there any milk left in the fridge?", "В холодильнике осталось молоко?", 77);
	/*************** End of init Lesson 77 *****************************************************************/

	/****************** Lesson 78: *************************************************************************/
	MerfiDictionary[737].setEnglWord("he seems to live in here", "кажется, он живет здесь", 78);
	MerfiDictionary[738].setEnglWord("nobody is perfect", "никто не совершенен", 78);
	MerfiDictionary[739].setEnglWord("in here", "здесь, сюда", 78);
	MerfiDictionary[740].setEnglWord("It's just fate.", "Это просто судьба (рок, участь).", 78);
	MerfiDictionary[741].setEnglWord("There's nothing left to say.", "Больше нечего сказать.", 78);
	MerfiDictionary[742].setEnglWord("when it comes to money", "когда дело доходит до денег", 78);
	MerfiDictionary[743].setEnglWord("carry", "нести, перенос", 78);
	MerfiDictionary[744].setEnglWord("suspicious", "подозрительный, сомнительный", 78);			// сеспИшес
	MerfiDictionary[745].setEnglWord("prepare", "готовить, готовиться, подготавливать", 78);
	/*************** End of init Lesson 78 *****************************************************************/

	/****************** Lesson 79: *************************************************************************/
	MerfiDictionary[746].setEnglWord("the middle of nowhere", "ебеня, черт знает где", 79);
	MerfiDictionary[747].setEnglWord("look around", "оглядеться, осмотреться", 79);
	MerfiDictionary[748].setEnglWord("secretly", "тайно, в тайне", 79);
	MerfiDictionary[749].setEnglWord("intelligent", "с высоким интеллектом, смысшленый", 79);	// интЕлиджент
	MerfiDictionary[750].setEnglWord("fluently", "свободно, бегло", 79);						// флУентли
	MerfiDictionary[751].setEnglWord("I can't give you anything but love.", "Я не могу ничего тебе дать кроме любви.", 79);
	MerfiDictionary[752].setEnglWord("Is there something wrong?", "Что-то не так?", 79);
	/*************** End of init Lesson 79 *****************************************************************/

	/****************** Lesson 80: *************************************************************************/
	MerfiDictionary[753].setEnglWord("unique", "уникальный, неповторимый", 80);
	MerfiDictionary[754].setEnglWord("in its own way", "по-своему", 80);
	MerfiDictionary[755].setEnglWord("hit the panic button", "жать тревожную кнопку", 80);		// бАтн
	MerfiDictionary[756].setEnglWord("everything is under control", "все под контролем", 80);
	MerfiDictionary[757].setEnglWord("it seems...", "мне кажется...", 80);						
	MerfiDictionary[758].setEnglWord("actress", "актриса", 80);									// Эктрес
	MerfiDictionary[759].setEnglWord("All I need for Christmas is you.", "Лучший мой подарочек (на Рождество) это ты.", 80);
	MerfiDictionary[760].setEnglWord("Compared to all people I know...", "По сравнению со всеми людьми, кого я знаю...", 80);
	MerfiDictionary[761].setEnglWord("exercise", "упражнение", 80);
	MerfiDictionary[762].setEnglWord("c'mon", "ну давай (сокр.)", 80);
	MerfiDictionary[763].setEnglWord("Everybody move your body!", "Танцуют все!", 80);
	MerfiDictionary[764].setEnglWord("a long way before", "давно", 80);
	/*************** End of init Lesson 80 *****************************************************************/

	/****************** Lesson 81: *************************************************************************/
	MerfiDictionary[765].setEnglWord("none of my friends", "никто из моих друзей", 81);
	MerfiDictionary[766].setEnglWord("Most people drive too fast.", "Большинство людей ездят очень быстро.", 81);
	MerfiDictionary[767].setEnglWord("all of it", "весь (о предмете)", 81);
	MerfiDictionary[768].setEnglWord("none of them", "ни один из них, ни одну из них", 81);
	MerfiDictionary[769].setEnglWord("as different as chalk and cheese", "разные, как небо и земля", 81);
	MerfiDictionary[770].setEnglWord("chalk", "мел", 81);										// чОк
	MerfiDictionary[771].setEnglWord("ambition", "амбиция, стремление, цель", 81);				// эмбИшн
	MerfiDictionary[772].setEnglWord("unavailable luxury", "недоступная роскошь", 81);			// анэвЕйлэб(э)л лАкш(е)ри
	MerfiDictionary[773].setEnglWord("advantage", "преимущество", 81);							// эдвЭнтидж
	MerfiDictionary[774].setEnglWord("app", "приложение (сокр.)", 81);
	MerfiDictionary[775].setEnglWord("reply", "ответ, отвечать", 81);							// рипЛай
	// Subject + used to + inginitive: относится к прошлому
	MerfiDictionary[776].setEnglWord("I used to...", "раньше я...(модл.гл.)", 81);
	MerfiDictionary[777].setEnglWord("courage", "мужество, смелость", 81);						// кАридж
	MerfiDictionary[778].setEnglWord("There were no any doubts", "Не было никаких сомнений", 81);// дАутс
	/*************** End of init Lesson 81 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[779].setEnglWord("huge influence", "огромное влияние, воздействие", 500);		// Инфлуенц		
	MerfiDictionary[780].setEnglWord("admirable", "восхитительный, замечательный (a)", 500);		// Эдм(э)рэб(э)л
	MerfiDictionary[781].setEnglWord("disappoint", "разочаровывать, лишать", 500);					// дисэпОинт
	MerfiDictionary[782].setEnglWord("comical", "смешной, комичный, забавный", 500);				// кОмик(э)л
	MerfiDictionary[783].setEnglWord("cheerful", "веселый, бодрый, светлый, яркий", 500);			// чИэф(у)л
	MerfiDictionary[784].setEnglWord("dull", "скучный, тупой, унылый, пасмурный", 500);
	MerfiDictionary[785].setEnglWord("admire", "восхищаться, любоваться", 500);
	// Subject + "to be" + used to + noun: относится как, к прошлому, так и настоящему
	MerfiDictionary[786].setEnglWord("I'm used to pain.", "Я привык к боли.", 500);
	/*************** End of popular words: **********************************************************************/

	/****************** Lesson 82: *************************************************************************/
	MerfiDictionary[787].setEnglWord("neither of my sisters is attractive", "ни одна из моих (двух) сестер не привлекательна", 82);
	MerfiDictionary[788].setEnglWord("remarkable", "замечательный, удивительный (r)", 82);
	MerfiDictionary[789].setEnglWord("be appropiate for", "быть подходящим для, соответствовать (пр.)", 82);	// эпрУприэт
	MerfiDictionary[790].setEnglWord("in my humble opinion", "по моему скромному мнению (IMHO)", 82);
	MerfiDictionary[791].setEnglWord("outstanding", "выдающийся", 82);
	MerfiDictionary[792].setEnglWord("fabulous beast", "неверояное, сказочное, мифическое животное", 82);		// фЭбьюлэс
	MerfiDictionary[793].setEnglWord("fabulous wealth", "сказочное, баснословное богатство", 82);				// уэл(TH)
	MerfiDictionary[794].setEnglWord("discription", "описание", 82);											// дискрИпшн
	MerfiDictionary[795].setEnglWord("either of them will be fine", "одно из двух (либо то, либо это) будет хорошо", 82);
	/*************** End of init Lesson 82 *****************************************************************/

	/****************** Lesson 83: *************************************************************************/
	MerfiDictionary[796].setEnglWord("almost", "почти", 83);
	MerfiDictionary[797].setEnglWord("necklace", "ожерелье", 83);										// нЕклэйс
	MerfiDictionary[798].setEnglWord("I'll call you back.", "Я тебе перезвоню.", 83);
	MerfiDictionary[799].setEnglWord("If memory serves me right...", "Если память мне не изменяет...", 83);
	MerfiDictionary[800].setEnglWord("That's too much.", "Это слишком много.", 83);
	MerfiDictionary[801].setEnglWord("I'm quite sure of it.", "Я вполне уверен в этом.", 83);
	MerfiDictionary[802].setEnglWord("Long time no see", "Давно не виделись", 83);						// устойчивое выражение
	MerfiDictionary[803].setEnglWord("Why don't we...?", "Почему бы нам...?", 83);
	MerfiDictionary[804].setEnglWord("I used to be.", "Раньше я был.", 83);
	/*************** End of init Lesson 83 *****************************************************************/

	/****************** Lesson 84: *************************************************************************/
	MerfiDictionary[805].setEnglWord("very few strawberries", "очень мало клубники", 84);
	MerfiDictionary[806].setEnglWord("a few candles", "немного свечей", 84);
	MerfiDictionary[807].setEnglWord("a little/little use", "немного/мало пользы", 84);
	MerfiDictionary[808].setEnglWord("yap", "лаять, трепаться, ворчать", 84);						// йеп
	MerfiDictionary[809].setEnglWord("stubborn", "упрямый, упорный", 84);							// стАбон
	MerfiDictionary[810].setEnglWord("I feel like...", "Я чувствую как будто, мне кажется...", 84);
	MerfiDictionary[811].setEnglWord("weakness", "слабость, недостаток", 84);
	MerfiDictionary[812].setEnglWord("old-fashioned", "старинный, старомодный", 84);				// фЭшенд
	MerfiDictionary[813].setEnglWord("clown", "клоун, шут, паяц", 84);								// клАун
	/*************** End of init Lesson 84 *****************************************************************/

	/****************** Lesson 85: *************************************************************************/
	MerfiDictionary[814].setEnglWord("homeless", "бездомный", 85);
	MerfiDictionary[815].setEnglWord("breakable", "бьющийся", 85);
	MerfiDictionary[816].setEnglWord("for instance", "например (for i...)", 85);
	MerfiDictionary[817].setEnglWord("well off", "обеспеченный", 85);
	MerfiDictionary[818].setEnglWord("cozy", "уютный (c...)", 85);									// кОузи
	MerfiDictionary[819].setEnglWord("wounded", "раненный, уизвленный", 85);						// вУндид		
	MerfiDictionary[820].setEnglWord("wound", "рана, ранить", 85);									// вУнд
	MerfiDictionary[821].setEnglWord("confident", "уверенный", 85);
	/*************** End of init Lesson 85 *****************************************************************/

	/****************** Lesson 86: *************************************************************************/
	MerfiDictionary[822].setEnglWord("sudden/suddenly", "неожиданный/неожиданно", 86);
	MerfiDictionary[823].setEnglWord("heavy/heavily", "тяжелый/сильно, тяжело, с трудом", 86);
	MerfiDictionary[824].setEnglWord("honestly", "честно", 86);
	MerfiDictionary[825].setEnglWord("obviously", "очевидно", 86);
	MerfiDictionary[826].setEnglWord("journalist", "журналист", 86);
	MerfiDictionary[827].setEnglWord("impatient/impatiently", "нетерпеливый/импульсивно, нетерпеливо", 86);
	MerfiDictionary[828].setEnglWord("gentle/gently", "нежный/нежно", 86);
	MerfiDictionary[829].setEnglWord("love deeply", "сильно (глубоко) любить", 86);
	MerfiDictionary[830].setEnglWord("fortunately", "к счастью", 86);
	MerfiDictionary[831].setEnglWord("lately", "недавно, в последнее время (l...)", 86);
	/*************** End of init Lesson 86 *****************************************************************/

	/****************** Lesson 87: *************************************************************************/
	MerfiDictionary[832].setEnglWord("Athens", "Афины", 87);								// Эthинс
	MerfiDictionary[833].setEnglWord("worse", "хуже", 87);
	MerfiDictionary[834].setEnglWord("further/farther", "дальше u/a", 87);							// фЕзер 
	MerfiDictionary[835].setEnglWord("elder child", "старший ребенок", 87);					// о детях в семье
	MerfiDictionary[836].setEnglWord("innocent", "невинный, наивный, простак", 87);			// Иносент
	MerfiDictionary[837].setEnglWord("juicer", "соковыжималка", 87);
	MerfiDictionary[838].setEnglWord("hairdryer", "фен", 87);
	MerfiDictionary[839].setEnglWord("household appliance", "прибор бытовой техники", 87);	// эплАйенс
	MerfiDictionary[840].setEnglWord("convenient", "удобный, подходящий", 87);				// кэнвИниент	
	MerfiDictionary[841].setEnglWord("You know what?", "А знаешь что?", 87);
	MerfiDictionary[842].setEnglWord("optional", "дополнительный, необязательный, вспомогательный", 87);	// Апшенл
	MerfiDictionary[843].setEnglWord("buy a pig in a poke", "купить кота в мешке", 87);		// поук - мешок
	MerfiDictionary[844].setEnglWord("be crazy about...", "помешаться на (пр)...", 87);
	/*************** End of init Lesson 87 *****************************************************************/
	/*
	Замеание: 
	1) older и elder одно и то же. Но elder применяется к детям в семье.
	elder нельзя использовать без существительного:
	- He is older. (Он старше)
	- He is elder child. (ERROR: He is elder.)
	
	2) farther и further: одно и то же, когда говорим о растоянии (дальше).
	Но у further есть второе значение: дальнейший, добавочный (требует существительное)
	We were not happy to get the further task. Мы не обрадовались получению дополнительного задания.
	*/

	/****************** Lesson 88: *************************************************************************/
	MerfiDictionary[845].setEnglWord("district", "район, участок", 88);	
	MerfiDictionary[846].setEnglWord("wake up", "проснуться", 88);
	MerfiDictionary[847].setEnglWord("Asia", "Азия", 88);										// Эйже
	MerfiDictionary[848].setEnglWord("fascinating", "завораживающий, обворожительный (f)", 88);		// фЭсинейтинг
	MerfiDictionary[849].setEnglWord("author", "автор", 88);									// Осер
	MerfiDictionary[850].setEnglWord("responsible", "ответственный, сознательный", 88);
	MerfiDictionary[851].setEnglWord("talkative", "болтливый, разговорчивый", 88);				// тОкэтив
	MerfiDictionary[852].setEnglWord("ridiculous", "смешной, нелепый, смехотворный", 88);		// ридИкъюлес
	MerfiDictionary[853].setEnglWord("She cooks worse than him.", "Она готовит хуже него (мест.).", 88);
	MerfiDictionary[854].setEnglWord("She was taller than he was.", "Она была выше него (гл.).", 88);
	MerfiDictionary[855].setEnglWord("the Mississippi", "Мисисипи", 88);
	MerfiDictionary[856].setEnglWord("victim", "жертва", 88);
	MerfiDictionary[857].setEnglWord("in gratitude", "в благодарность", 88);					// грЭтитьюд
	MerfiDictionary[858].setEnglWord("Hell is empty, and all the devils are here.", "Ад пуст, и все бесы здесь.", 88);
	MerfiDictionary[859].setEnglWord("undying", "вечный", 88);
	/*************** End of init Lesson 88 *****************************************************************/

	/****************** Lesson 89: *************************************************************************/
	MerfiDictionary[860].setEnglWord("She's not as old as him.", "Она не такая старая, как он (мест.).", 89);
	MerfiDictionary[861].setEnglWord("The weather is the same as yesterday.", "Погода такая же как вчера.", 89);
	MerfiDictionary[862].setEnglWord("as brave as a lion", "храбрый, как лев", 89);
	MerfiDictionary[863].setEnglWord("spy", "хитрый", 89);
	MerfiDictionary[864].setEnglWord("He's not as stupid as it seems.", "Он не такой глупый, как кажется.", 89);
	MerfiDictionary[865].setEnglWord("gifted", "одаренный", 89);
	MerfiDictionary[866].setEnglWord("The Devil isn't as black as he is painted.", "Не так страшен черт, как его малюют.", 89);
	MerfiDictionary[867].setEnglWord("it's unfair", "это несправедливо", 89);
	MerfiDictionary[868].setEnglWord("creative", "креативный", 89);
	MerfiDictionary[869].setEnglWord("pretend", "притворяться, делать вид (p)", 89);
	MerfiDictionary[870].setEnglWord("His car is the same as mine.", "Его машина такая же как моя (мест.).", 89);
	MerfiDictionary[871].setEnglWord("income", "доход, прибыль", 89);								// Инкам
	MerfiDictionary[872].setEnglWord("salary", "зарплата", 89);										
	MerfiDictionary[873].setEnglWord("employee", "работник, служащий", 89);							// ипплОйи
	/*************** End of init Lesson 89 *****************************************************************/

	/****************** Lesson 90: *************************************************************************/
	MerfiDictionary[874].setEnglWord("the worst", "худший", 90);
	MerfiDictionary[875].setEnglWord("the solar system", "солнечная система", 90);
	MerfiDictionary[876].setEnglWord("Jupiter", "Юпитер", 90);										// джЮпитер
	MerfiDictionary[877].setEnglWord("veteran of WW2", "ветеран Втрой Мировой Войны (сокр.)", 90);	// вЭтерэн
	MerfiDictionary[878].setEnglWord("the furthest row in the hall", "самый дальний ряд в зале", 90);
	MerfiDictionary[879].setEnglWord("tomb", "гробница, могила, склеп, хоронить", 90);				// тум
	MerfiDictionary[880].setEnglWord("deque", "двусторонняя очередь", 90);
	MerfiDictionary[881].setEnglWord("queue", "очередь, хвост", 90);								// кю
	MerfiDictionary[882].setEnglWord("heap", "куча, ворох, груда", 90);
	MerfiDictionary[883].setEnglWord("derived", "производный, вторичный", 90);						// дирАйвд
	MerfiDictionary[884].setEnglWord("the tomb of Alexander the Great", "гробница Александра Македонского", 90);
	MerfiDictionary[885].setEnglWord("easy peasy lemon squeezy", "проще простого (лимон)", 90);
	MerfiDictionary[886].setEnglWord("as easy as a pie", "проще простого", 90);
	/*************** End of init Lesson 90 *****************************************************************/

	/****************** Lesson 91: *************************************************************************/
	MerfiDictionary[887].setEnglWord("conversation", "беседа, разговор", 91);
	MerfiDictionary[888].setEnglWord("I've had enough.", "С меня хватит, мне достаточно.", 91);
	MerfiDictionary[889].setEnglWord("pullover", "пуловер, свитер", 91);								// пУловер
	MerfiDictionary[890].setEnglWord("That guy is angry enough.", "Этот парень достаточно зол.", 91);	// Важно: после прилагательного
	MerfiDictionary[891].setEnglWord("patience", "терпение", 91);
	MerfiDictionary[892].setEnglWord("At your absolute best...", "В твоем наилучшем виде...", 91);
	MerfiDictionary[893].setEnglWord("Someday you will be old enough...", "Однажды вы постараете настолько...", 91);
	MerfiDictionary[894].setEnglWord("Be strong enough to let go.", "Будь достаточно сильным, чтобы отпустить.", 91);
	/*************** End of init Lesson 91 *****************************************************************/

	/****************** Lesson 92: *************************************************************************/
	MerfiDictionary[895].setEnglWord("Ann studies too much.", "Аня слишком много учится.", 92);
	MerfiDictionary[896].setEnglWord("I'm too tired to go out.", "Я слишком устал, чтобы выходить на улицу.", 92);
	MerfiDictionary[897].setEnglWord("He's far too sick.", "Он очень (усиление) слишком болен.", 92);
	MerfiDictionary[898].setEnglWord("looks like...", "похоже на то, выглядит как буд-то...", 92);
	MerfiDictionary[899].setEnglWord("the Bible", "Библия", 92);
	MerfiDictionary[900].setEnglWord("So be it.", "Да будет так.", 92);
	MerfiDictionary[901].setEnglWord("from zero to hero", "из грязи в князи", 92);
	MerfiDictionary[902].setEnglWord("fate", "судьба, рок", 92);
	MerfiDictionary[903].setEnglWord("no offence", "без обид", 92);										// эфЕнс
	MerfiDictionary[904].setEnglWord("Let's talk heart to heart.", "Давай поговрим по душам.", 92);
	MerfiDictionary[905].setEnglWord("get off", "отвали", 92);
	MerfiDictionary[906].setEnglWord("at dawn", "на рассвете", 92);										// дАн/дОн
	/*************** End of init Lesson 92 *****************************************************************/

	/****************** Lesson 93: *************************************************************************/
	MerfiDictionary[907].setEnglWord("Smoking is strictly forbidden in the public areas.", "Курение строго запрещено в общественных местах.", 93);
	MerfiDictionary[908].setEnglWord("She was the cutest baby ever.", "Она была самым милым ребенком из всех.", 93);
	MerfiDictionary[909].setEnglWord("It was good to accompany you.", "Было приятно сопровождать тебя.", 93);
	MerfiDictionary[910].setEnglWord("reveal the feelings", "признаться в чувствах", 93);
	MerfiDictionary[911].setEnglWord("It's illegal to buy drugs.", "Незаконно покупать наркотики.", 93);	// илИг(э)л
	MerfiDictionary[912].setEnglWord("though", "хотя", 93);
	MerfiDictionary[913].setEnglWord("subject", "подлежащее", 93);
	MerfiDictionary[914].setEnglWord("verb", "глагол, сказуемое", 93);
	MerfiDictionary[915].setEnglWord("restaurant", "ресторан", 93);								// рЕсторант
	MerfiDictionary[916].setEnglWord("injure", "ранить, повредить, обидеть", 93);				// Индже
	MerfiDictionary[917].setEnglWord("bearly", "едва, еле-еле, лишь", 93);						// бЭ(р)ли
	MerfiDictionary[918].setEnglWord("forbid", "запрещать", 93);								// фо(р)бИд
	MerfiDictionary[919].setEnglWord("be abroad", "быть за границей", 93);
	MerfiDictionary[920].setEnglWord("invitation", "приглашение", 93);							// инвитЕйшн
	MerfiDictionary[921].setEnglWord("accompany", "сопровождать, аккомпанировать", 93);			// экАмпени
	MerfiDictionary[922].setEnglWord("exception", "исключение, особая ситуация", 93);			// иксЕпшн
	/*************** End of init Lesson 93 *****************************************************************/

	/****************** Lesson 94: *************************************************************************/
	MerfiDictionary[923].setEnglWord("I never forgive my enemies.", "Я никогда не прощаю своих врагов", 94);
	MerfiDictionary[924].setEnglWord("enemy", "вран", 94);										// Энеми
	MerfiDictionary[925].setEnglWord("rarely", "редко (r)", 94);								// рЭали
	MerfiDictionary[926].setEnglWord("burger", "бутерброд, бургер", 94);						// бЁ(р)гер
	MerfiDictionary[927].setEnglWord("expel", "исключить", 94);									// Икспел
	MerfiDictionary[928].setEnglWord("I still haven't seen him.", "Я все еще не видел его.", 94);	// ИСКЛЮЧЕНИЕ
	MerfiDictionary[929].setEnglWord("grade", "оценка, ранг, степень", 94);
	MerfiDictionary[930].setEnglWord("They all live in here.", "Они все живут здесь.", 94);
	/*************** End of init Lesson 94 *****************************************************************/

	/****************** Lesson 95: *************************************************************************/
	MerfiDictionary[923].setEnglWord("I haven't had breakfast yet.", "Я все еще не завтракал.", 95);
	MerfiDictionary[923].setEnglWord("He's still out.", "Он все еще не дома (снаружи).", 95);
	MerfiDictionary[923].setEnglWord("get separated", "разойтись, развестись", 95);
	MerfiDictionary[923].setEnglWord("What's going on in the world?", "Что происходит в мире?", 95);
	MerfiDictionary[923].setEnglWord("nothing unusual", "ничего необычного", 95);
	MerfiDictionary[923].setEnglWord("plenty of problems", "много (достаточно, изрядно) проблем", 95);
	MerfiDictionary[923].setEnglWord("manage", "руководить, управлять, справляться", 95);
	MerfiDictionary[923].setEnglWord("We still haven't told him.", "Мы ему еще не сказали.", 95);
	/*************** End of init Lesson 95 *****************************************************************/

	/****************** Lesson 96: *************************************************************************/
	MerfiDictionary[924].setEnglWord("postcard", "открытка", 96);
	MerfiDictionary[925].setEnglWord("recipe", "рецепт", 96);									// рЕсепи
	MerfiDictionary[926].setEnglWord("request to the department", "запрос в депортамент", 96);
	MerfiDictionary[927].setEnglWord("instructions", "инструкции", 96);
	MerfiDictionary[928].setEnglWord("data", "информация, данные", 96);							// дЕйтэ
	MerfiDictionary[929].setEnglWord("lend", "одалживать (кому-то)", 96);
	MerfiDictionary[930].setEnglWord("Give it to me.", "Дай это мне.", 96);
	MerfiDictionary[931].setEnglWord("lend", "одалживать (кому-то)", 96);
	MerfiDictionary[932].setEnglWord("pass", "передать", 95);
	/*************** End of init Lesson 96 *****************************************************************/

	/****************** Lesson 97: *************************************************************************/
	MerfiDictionary[933].setEnglWord("To be or not to be, that is the question", "Быть или не быть, вот в чем вопрос.", 97);
	MerfiDictionary[934].setEnglWord("conjunction", "предлог", 97);			// кэнджАкшн
	MerfiDictionary[935].setEnglWord("comma", "запятая", 97);
	MerfiDictionary[936].setEnglWord("at the same time", "одновременно, в то же самое время", 97);
	MerfiDictionary[937].setEnglWord("stay awake", "бодорствовать, не ложиться спать", 97);
	MerfiDictionary[938].setEnglWord("be free but not wild", "будь свободным, но не диким", 97);
	MerfiDictionary[939].setEnglWord("condenced milk", "сгущеное молоко", 97);
	MerfiDictionary[940].setEnglWord("intend", "намереваться, собираться", 97);
	MerfiDictionary[941].setEnglWord("act confidently", "действовать уверенно", 97);
	MerfiDictionary[942].setEnglWord("be on the right way", "быть на правильном пути", 97);
	MerfiDictionary[943].setEnglWord("be in a good fit", "быть в хорошей форме", 97);
	/*************** End of init Lesson 97 *****************************************************************/

	/****************** Lesson 98: *************************************************************************/
	MerfiDictionary[944].setEnglWord("When it comes to me...", "Когда дело доходит до меня...", 98);
	MerfiDictionary[945].setEnglWord("How come?", "Как так?", 98);
	MerfiDictionary[946].setEnglWord("I bite my bottom lip when I feel nervous.", "Я кусаю свою верхнюю губу, когда я нервничаю.", 98);
	MerfiDictionary[947].setEnglWord("feel nervous", "нервничать", 98);
	MerfiDictionary[948].setEnglWord("Cuba", "Куба", 98);							// кьЮба
	MerfiDictionary[949].setEnglWord("perfection", "совершенство", 98);				// перфЕкшн
	MerfiDictionary[950].setEnglWord("If there is a cause, there is an effect.", "Если есть причина, то есть и следствие", 98);
	MerfiDictionary[951].setEnglWord("oversleep", "проспать", 98);
	MerfiDictionary[952].setEnglWord("dangerous", "опасный", 98);
	MerfiDictionary[953].setEnglWord("set an alarm clock", "установить будильник (неопр.)", 98);
	/*************** End of init Lesson 98 *****************************************************************/

	/****************** Lesson 99: *************************************************************************/
	MerfiDictionary[954].setEnglWord("If I go there, I'll pick you up.", "Если я поеду туда, я тебя захвачу.", 99);
	MerfiDictionary[955].setEnglWord("If I'm a mother...", "Если я стану мамой...", 99);
	MerfiDictionary[956].setEnglWord("mustache", "усы", 99);
	MerfiDictionary[957].setEnglWord("shave off", "сбрить", 99);
	MerfiDictionary[958].setEnglWord("Mom will be angry if I am late.", "Мама рассердится, если я опоздаю.", 99);
	MerfiDictionary[959].setEnglWord("When pigs fly...", "Когда рак на горе свистнет...", 99);
	MerfiDictionary[960].setEnglWord("at once", "сразу, мгновенно", 99);
	MerfiDictionary[961].setEnglWord("I won't do anything if you don't help me.", "Я не буду ничего делать, если ты мне не поможешь.", 99);
	/*************** End of init Lesson 99 *****************************************************************/

	/****************** Lesson 100: *************************************************************************/
	MerfiDictionary[962].setEnglWord("I'd help you if I could.", "Я бы помог тебе, если мог.", 100);
	MerfiDictionary[963].setEnglWord("If I were you...", "Если бы я был на твоем месте...", 100);			
	MerfiDictionary[964].setEnglWord("If I had the money, I would buy...", "Если бы у меня были деньги, я бы...", 100);
	MerfiDictionary[965].setEnglWord("If I new the answer, I would...", "Если бы я знал ответ, я бы...", 100);
	MerfiDictionary[966].setEnglWord("If I had time/If I have time", "Если бы у меня было время/Если у меня будет время", 100);
	MerfiDictionary[967].setEnglWord("If I can/If I could", "Если я смогу/Если бы я мог", 100);
	MerfiDictionary[968].setEnglWord("If I were president...", "Если бы я был президентом...", 100);
	MerfiDictionary[969].setEnglWord("If I liked pizza, I would order it.", "Если бы я любил пиццу, я бы заказал ее.", 100);	
	MerfiDictionary[970].setEnglWord("rival", "соперник, соперничать", 100);					// рАйв(э)л
	MerfiDictionary[971].setEnglWord("hurry up", "торопиться, поторапливаться", 100);
	MerfiDictionary[972].setEnglWord("be on time", "быть вовремя", 100);
	MerfiDictionary[973].setEnglWord("giggle", "хихикать, хихиканье", 100);						// гигл
	MerfiDictionary[974].setEnglWord("instead of...", "в место...", 100);
	MerfiDictionary[975].setEnglWord("cope with", "справляться (пр)", 100);						// кОуп
	MerfiDictionary[976].setEnglWord("hesitate", "стесняться, колебаться,сомневаться", 100);	// хЕзитейт
	MerfiDictionary[977].setEnglWord("ill-mannered", "невоспитанный, с плохими манерами", 100);	// иллмЭнед
	MerfiDictionary[978].setEnglWord("poison", "яд, отравить", 100);
	MerfiDictionary[979].setEnglWord("If you were my wife...", "Если бы вы были моей женой...", 100);
	MerfiDictionary[980].setEnglWord("loan", "ссуда, кредит", 100);								// лОун
	MerfiDictionary[981].setEnglWord("shy", "застенчивый, стеснительный", 100);					
	/*************** End of init Lesson 100 *****************************************************************/

	/****************** Lesson 101: *************************************************************************/
	MerfiDictionary[982].setEnglWord("thief", "вор", 101);
	MerfiDictionary[983].setEnglWord("The man who called...", "Человек, который звонил...", 101);
	MerfiDictionary[984].setEnglWord("A thief is a person who steals things.", "Вор это личность, которая вороует вещи.", 101);
	MerfiDictionary[985].setEnglWord("machine", "машина", 101);
	MerfiDictionary[986].setEnglWord("A thing that/which...", "Вешь, которая (t/w)", 101);
	MerfiDictionary[987].setEnglWord("investigation", "расследование, следствие", 101);
	MerfiDictionary[988].setEnglWord("lead", "вести, приводить, свинец", 101);
	MerfiDictionary[989].setEnglWord("blunt pencil", "топой (грубый) карандаш", 101);
	MerfiDictionary[990].setEnglWord("avenge", "мстить", 101);									// эвЭндж
	MerfiDictionary[991].setEnglWord("own", "владеть", 101);
	MerfiDictionary[992].setEnglWord("pavement", "тротуар, мостовая", 101);						// пЕйвмент
	/*************** End of init Lesson 101 *****************************************************************/

	/****************** Lesson 102: *************************************************************************/
	MerfiDictionary[993].setEnglWord("I like the film I saw yesterday.", "Мне нравится фильм, который я посмотрел вчера.", 102);
	MerfiDictionary[994].setEnglWord("...the money Kate won.", "...деньги, которые Катя выиграла.", 102);
	MerfiDictionary[995].setEnglWord("...the books you wanted.", "...книги, которые ты хотел.", 102);
	MerfiDictionary[996].setEnglWord("...the people we met.", "...люди, которых мы встеритили.", 102);
	MerfiDictionary[997].setEnglWord("The room I was led in was dark.", "Комната, в которую меня ввели была темной.", 102);
	MerfiDictionary[998].setEnglWord("awesome", "устрашающий, потрясающий, приводящий в трепет.", 102);	// Осэм
	MerfiDictionary[999].setEnglWord("...the doctor I visit twice a month.", "...доктор, которого я посещаю дважды в месяц.", 102);
	MerfiDictionary[1000].setEnglWord("...the food you cook.", "...еда, которую ты готовишь.", 102);
	MerfiDictionary[1001].setEnglWord("tasteless", "безвкусный", 102);
	MerfiDictionary[1002].setEnglWord("defense", "защита, оборона", 102);								// дифЕнс
	/*************** End of init Lesson 102 *****************************************************************/

	/****************** Lesson 103: *************************************************************************/
	MerfiDictionary[1003].setEnglWord("at Easter", "на пасху (пр.)", 103);
	MerfiDictionary[1004].setEnglWord("bowling", "боулинг", 103);										// бОулин
	MerfiDictionary[1005].setEnglWord("at noon", "в полдень", 103);
	MerfiDictionary[1006].setEnglWord("in the future", "в будущем", 103);
	MerfiDictionary[1007].setEnglWord("Don't go out at night.", "Не выходи на улицу ночю.", 103);
	MerfiDictionary[1008].setEnglWord("at 10 in the evening on Monday", "в 10 вечером в понедельник", 103);
	/*************** End of init Lesson 103 *****************************************************************/

	/****************** Lesson 104: *************************************************************************/
	MerfiDictionary[1009].setEnglWord("until/till", "пока (.../...)", 104);
	MerfiDictionary[1010].setEnglWord("from time to time", "время от времени", 104);
	MerfiDictionary[1011].setEnglWord("walk to work", "иди (w) на работу", 104);
	MerfiDictionary[1012].setEnglWord("recover", "восстанваливать, оздоравливаться", 104);
	MerfiDictionary[1013].setEnglWord("for the rest of your life", "до конца твоей жизни", 104);
	MerfiDictionary[1014].setEnglWord("approval", "одобрение", 104);									// эпрУв(э)л
	MerfiDictionary[1015].setEnglWord("Stay here till I come back.", "Оставайся здесь, пока я не вернусь.", 104);
	/*************** End of init Lesson 104 *****************************************************************/


	/*
/*
*poke
* 
* destiny
	//urge
	creepyё
	helpless
	whatever
	knowledge is pain. i'm used to that
	out of the ordinary
	gardener

	have a seat
	attempt
	absolutely
	terrific
	convict
	lots of money
	inocent


injury
is it safe to say
suppress
duress
farewell
arrogant
sloppy
damage
admire
cleverness
evidence
affair
dare
noble
disquise
gotta
wonna
day of
motion
even a brocken clock gets to be right twice a day
take it easy
plug
outlet
election
old sport
admit
grave
// desire
trial
fracture

admire


it has to be you 

	*/
}

// Функция заполнения словаря сложных слов (массива EnglishWord) значениями
void initDifficultMerfiDictionary(EnglishWord* MerfiDictionary)
{
	MerfiDictionary[0].setEnglWord("designer", "дизайнер", 1);					// дизайне
	MerfiDictionary[1].setEnglWord("stranger", "незнакомец", 6);
	MerfiDictionary[2].setEnglWord("decision", "решение", 11);
	MerfiDictionary[3].setEnglWord("jubilee", "юбилей", 20);					// джубили
	MerfiDictionary[4].setEnglWord("vehicle", "транспортное средство", 20);	// вэикл
	MerfiDictionary[5].setEnglWord("experience", "опыт", 24);					// икспириенс
	MerfiDictionary[6].setEnglWord("attend", "посещать", 26);
	MerfiDictionary[7].setEnglWord("astronaut", "астронавт", 26);				// астронот
	MerfiDictionary[8].setEnglWord("towel", "полотенце", 500);				// тауэл таул (э почти нет)
	MerfiDictionary[9].setEnglWord("yield", "производить, приносить, давать доход)", 500);	// еилд
	MerfiDictionary[10].setEnglWord("envelope", "конверт", 500);		// Энвелоуп
	MerfiDictionary[11].setEnglWord("definitely", "определенно, однозначно, точно", 32);
	MerfiDictionary[12].setEnglWord("to be honest", "если честно", 34);
	MerfiDictionary[13].setEnglWord("That would be very kind of you.", "Это было бы очень мило с вашей стороны.", 34);
	MerfiDictionary[14].setEnglWord("a hell of a lot of...", "чертовски много...", 36);
	MerfiDictionary[15].setEnglWord("be retired", "быть на пенсии", 36);							// ритаед
	MerfiDictionary[16].setEnglWord("unfortunately", "к несчатью", 37);
	MerfiDictionary[17].setEnglWord("increase of prices", "повышение цен", 38);					// Инкрис
	MerfiDictionary[18].setEnglWord("positively", "положительно, безусловно, несомненно", 40);		// пОзетивли
	MerfiDictionary[19].setEnglWord("expectation", "ожидание, надежда", 40);						// экспектЕйшн		
	MerfiDictionary[20].setEnglWord("necessary", "необходимо", 40);
	MerfiDictionary[21].setEnglWord("run the something", "управлять чем-то, следить за чем-то", 42);
	MerfiDictionary[22].setEnglWord("have nothing to do with", "не иметь ничего общего к, никак не относится к", 43);
	MerfiDictionary[23].setEnglWord("lantern", "фонарь", 500);										// лЭнтёрн, лЕнтён
	MerfiDictionary[24].setEnglWord("fragrance", "аромат", 500);									// фрЕйгренс
	MerfiDictionary[25].setEnglWord("wish for happiness", "желать счастья, стремиться к счастью", 46);
	MerfiDictionary[26].setEnglWord("accountant", "бухгалтер", 47);							// экАунтент
	MerfiDictionary[27].setEnglWord("hold a position", "занимать должность", 47);
	MerfiDictionary[28].setEnglWord("well-paid", "высокооплачиваемый", 47);
	MerfiDictionary[29].setEnglWord("for sure", "наверняка, несомненно", 49);
	MerfiDictionary[30].setEnglWord("get along with", "ладить, быть в хороших отношениях (пр)", 49);
	MerfiDictionary[31].setEnglWord("till the age of eight", "до восьми лет", 50);
	MerfiDictionary[32].setEnglWord("suggest", "предлагать, советовать", 52);							// седжЕст
	MerfiDictionary[33].setEnglWord("reward", "награда, вознаграждение, награждать", 52);				// риВод
	MerfiDictionary[34].setEnglWord("procrastinate", "мешкать, отсрачивать, откладывать на потом", 52);// прокрЭстинейт
	MerfiDictionary[35].setEnglWord("applaud", "аплодировать", 52);									// эплОд
	MerfiDictionary[36].setEnglWord("confidently", "уверенно, убежденно (одно слово)", 53);			// кОнфидентли
	MerfiDictionary[37].setEnglWord("apologize", "извиняться, просить прощения", 53);					// эпОлоджайз
	MerfiDictionary[38].setEnglWord("self-confidently", "самонадеянно", 53);							// селф-кОнфидентли
	MerfiDictionary[38].setEnglWord("It's worth that.", "Это того стоит.", 54);						// вЁрз									
	MerfiDictionary[39].setEnglWord("get used to", "привыкнуть к, притерпеться (пр)", 54);
	MerfiDictionary[40].setEnglWord("pay them a visit", "нанесть им визит", 54);
	MerfiDictionary[41].setEnglWord("long for", "ожидать с нетерпеием, тосковать", 54);
	MerfiDictionary[42].setEnglWord("take a photogragh", "сфотографировать, сделать снимок", 57);
	MerfiDictionary[43].setEnglWord("do a research", "проводить исследование", 57);
	MerfiDictionary[44].setEnglWord("do repairs", "заниматься ремонтом, починкой", 57);		
	MerfiDictionary[45].setEnglWord("heart diseases", "болезни сердца", 58);					// дизИз
	MerfiDictionary[46].setEnglWord("have a familiar ring", "звучать знакомо", 58);			// идиома
	MerfiDictionary[47].setEnglWord("work long hours", "работать сверхурочно", 58);
	MerfiDictionary[48].setEnglWord("give up the idea", "отказаться от идеи (конкретной)", 58);
	MerfiDictionary[49].setEnglWord("be alert", "быть начеку", 58);							// элЁрт (тревога, бдительный)
	MerfiDictionary[50].setEnglWord("in amazement", "с удивлением, изумлением", 59);			// эмЕйзмэнт
	MerfiDictionary[51].setEnglWord("adjust", "регулировать, устанавливать, приводить в порядок", 59);
	MerfiDictionary[52].setEnglWord("distinctly", "отчетливо, четко", 59);						// дистИнктли
	MerfiDictionary[53].setEnglWord("in order to", "для того, чтобы", 60);
	MerfiDictionary[54].setEnglWord("daughter", "дочь", 60);
	MerfiDictionary[55].setEnglWord("neighbor", "сосед", 60);
	MerfiDictionary[56].setEnglWord("have a crash on", "втюриться, втрескаться в", 60);
	MerfiDictionary[57].setEnglWord("disturb", "беспокоить, волновать, доставлять хлопоты", 500);	// дистЁб
	MerfiDictionary[58].setEnglWord("deserve", "заслуживать, быть достойным", 500);					// дизЁв
	MerfiDictionary[59].setEnglWord("defeat", "поражение, разгром, наносить поражение", 500);		// дифИт
	MerfiDictionary[60].setEnglWord("grimly", "жестоко, беспощадно, сурово", 500);
	MerfiDictionary[61].setEnglWord("exactly", "точно, именно, ровно, совершенно верно", 500);		// игзЭктли		
	MerfiDictionary[62].setEnglWord("sarcastically", "соркастично", 61);							// соркЭстикли
	MerfiDictionary[63].setEnglWord("anxious", "тревожный, озабоченный", 61);						// Энккшес
	MerfiDictionary[64].setEnglWord("quantity", "количество", 61);									// квОнтити
	MerfiDictionary[65].setEnglWord("", "", 63);
	MerfiDictionary[66].setEnglWord("psychologist", "психолог", 63);								// сайкОлоджист
	MerfiDictionary[67].setEnglWord("A cat prefers walking by itself.", "Кошка предпочитает гулять сама по себе.", 63);							// сайкОлоджист
	MerfiDictionary[68].setEnglWord("colleague", "коллега", 64);								// кАлиг
	MerfiDictionary[69].setEnglWord("approve", "одобрять, утверждать", 64);
	MerfiDictionary[70].setEnglWord("succeed", "преуспевать, иметь успех", 65);
	MerfiDictionary[71].setEnglWord("coroner", "субмедэксперт", 65);
	MerfiDictionary[72].setEnglWord("engineer", "инженер", 65);
	MerfiDictionary[73].setEnglWord("scissors", "ножницы", 66);
	MerfiDictionary[74].setEnglWord("a pair of pyjamas", "пара пижамы", 66);					// педжЕмез
	MerfiDictionary[75].setEnglWord("life isn't a piece of cake", "жизнь не проста", 67);
	MerfiDictionary[76].setEnglWord("ceiling", "потолок", 67);									// сИлинg
	MerfiDictionary[77].setEnglWord("cereal", "злаковый, каша", 67);							// сИриэл								
	MerfiDictionary[78].setEnglWord("it's not for nothing", "это не с проста", 67);
	MerfiDictionary[79].setEnglWord("scientist", "ученый", 67);
	MerfiDictionary[80].setEnglWord("violence", "насилие, жестокость", 67);					// вАйленс
	MerfiDictionary[81].setEnglWord("rhythm", "ритм, периодичность", 69);						// рИзэм							
	MerfiDictionary[82].setEnglWord("I would rather to...", "Я бы лучше..., я бы предпочел (пр.)...", 69);
	MerfiDictionary[83].setEnglWord("it's about to rain", "вот-вот пойдет дождь", 70);
	MerfiDictionary[84].setEnglWord("take me along with you", "возьми меня с собой", 71);
	MerfiDictionary[85].setEnglWord("stay out of trouble", "держаться подальше от неприятностей", 71);
	MerfiDictionary[86].setEnglWord("stay up late", "не ложиться до поздна", 71);
	MerfiDictionary[87].setEnglWord("afford", "позволить себе, иметь возможность", 71);
	MerfiDictionary[88].setEnglWord("be considered to be...", "считается что...", 72);
	MerfiDictionary[89].setEnglWord("quality", "качество", 72);
	MerfiDictionary[90].setEnglWord("triumph of evil", "торжество зла", 72);			// трАйамф оф ивл
	MerfiDictionary[91].setEnglWord("foreigner", "иностранец", 72);					// фОренер
	MerfiDictionary[92].setEnglWord("especially", "особенно", 72);
	MerfiDictionary[93].setEnglWord("I'll do my best", "я очень постараюсь", 72);
	MerfiDictionary[94].setEnglWord("the Mediterranean Sea", "Средиземное море", 73);	// медитерЕйниен
	MerfiDictionary[95].setEnglWord("Westminster Abbey", "Вестминское аббатство", 73);	// вЕстминстер Эби
	MerfiDictionary[96].setEnglWord("Edinburgh Castle", "Эдинбургский замок", 73);		// Эдинбере Касл
	MerfiDictionary[97].setEnglWord("the Himalayas", "Гималаи", 73);					// химелЕиз
	MerfiDictionary[98].setEnglWord("exciting", "захватывающий, увлекательный", 73);	// иксАйтинг
	MerfiDictionary[99].setEnglWord("actually", "по правде говоря", 74);
	MerfiDictionary[100].setEnglWord("long to...", "очень сильно что-то хотеть сделать...", 74);
	MerfiDictionary[101].setEnglWord("arrange", "договориться, устраивать, располагать", 76);	// эрЕйнж
	MerfiDictionary[102].setEnglWord("successful", "успешный", 77);
	MerfiDictionary[103].setEnglWord("", "", 77);
	MerfiDictionary[104].setEnglWord("suspect", "подозревать", 77);
	MerfiDictionary[105].setEnglWord("pedestrian", "пешеход", 77);								// пидЕстриэн
	MerfiDictionary[106].setEnglWord("in here", "здесь, сюда", 78);
	MerfiDictionary[107].setEnglWord("suspicious", "подозрительный, сомнительный", 78);			// сеспИшес
	MerfiDictionary[108].setEnglWord("exercise", "упражнение", 80);
	MerfiDictionary[109].setEnglWord("a long way before", "давно", 80);
	MerfiDictionary[110].setEnglWord("unavailable luxury", "недоступная роскошь", 81);			// анэвЕйлэб(э)л лАкш(е)ри
	MerfiDictionary[111].setEnglWord("advantage", "преимущество", 81);							// эдвЭнтидж
	MerfiDictionary[112].setEnglWord("courage", "мужество, смелость", 81);						// кАридж
	MerfiDictionary[113].setEnglWord("admirable", "восхитительный, замечательный (a)", 500);		// Эдм(э)рэб(э)л
	MerfiDictionary[114].setEnglWord("disappoint", "разочаровывать, лишать", 500);					// дисэпОинт
	MerfiDictionary[115].setEnglWord("remarkable", "замечательный, удивительный (r)", 82);
	MerfiDictionary[116].setEnglWord("be appropiate for", "быть подходящим для, соответствовать (пр.)", 82);	// эпрУприэт
	MerfiDictionary[117].setEnglWord("outstanding", "выдающийся", 82);
	MerfiDictionary[118].setEnglWord("fabulous wealth", "сказочное, баснословное богатство", 82);				// уэл(TH)
	MerfiDictionary[119].setEnglWord("discription", "описание", 82);											// дискрИпшн
	MerfiDictionary[120].setEnglWord("either of them will be fine", "одно из двух (либо то, либо это) будет хорошо", 82);
	MerfiDictionary[121].setEnglWord("If memory serves me right...", "Если память мне не изменяет...", 83);
	MerfiDictionary[122].setEnglWord("I'm quite sure of it.", "Я вполне уверен в этом.", 83);
	MerfiDictionary[123].setEnglWord("Long time no see", "Давно не виделись", 83);								// устойчивое выражение
	MerfiDictionary[124].setEnglWord("very few strawberries", "очень мало клубники", 84);
	MerfiDictionary[125].setEnglWord("a few candles", "немного свечей", 84);
	MerfiDictionary[126].setEnglWord("yap", "лаять, трепаться, ворчать", 84);									// йеп
	MerfiDictionary[127].setEnglWord("stubborn", "упрямый, упорный", 84);										// стАбон
	MerfiDictionary[128].setEnglWord("heavy/heavily", "тяжелый/сильно, тяжело, с трудом", 86);
	MerfiDictionary[129].setEnglWord("honestly", "честно", 86);
	MerfiDictionary[130].setEnglWord("fortunately", "к счастью", 86);
	MerfiDictionary[131].setEnglWord("innocent", "невинный, наивный, простак", 87);			// Иносент
	MerfiDictionary[132].setEnglWord("hairdryer", "фен", 87);
	MerfiDictionary[133].setEnglWord("household appliance", "прибор бытовой техники", 87);	// эплАйенс
	MerfiDictionary[134].setEnglWord("convenient", "удобный, подходящий", 87);				// кэнвИниент	
	MerfiDictionary[135].setEnglWord("be crazy about...", "помешаться на (пр)...", 87);
	MerfiDictionary[136].setEnglWord("district", "район, участок", 88);
	MerfiDictionary[137].setEnglWord("fascinating", "завораживающий, обворожительный (f)", 88);	// фЭсинейтинг
	MerfiDictionary[138].setEnglWord("author", "автор", 88);									// Осер
	MerfiDictionary[139].setEnglWord("responsible", "ответственный, сознательный", 88);
	MerfiDictionary[140].setEnglWord("talkative", "болтливый, разговорчивый", 88);				// тОкэтив
	MerfiDictionary[141].setEnglWord("ridiculous", "смешной, нелепый, смехотворный", 88);		// ридИкъюлес
	MerfiDictionary[142].setEnglWord("in gratitude", "в благодарность", 88);					// грЭтитьюд
	MerfiDictionary[143].setEnglWord("undying", "вечный", 88);
	MerfiDictionary[144].setEnglWord("He's not as stupid as it seems.", "Он не такой глупый, как кажется.", 89);
	MerfiDictionary[145].setEnglWord("The Devil isn't as black as he is painted.", "Не так страшен черт, как его малюют.", 89);
	MerfiDictionary[146].setEnglWord("pretend", "притворяться, делать вид (p)", 89);
	MerfiDictionary[147].setEnglWord("the worst", "худший", 90);
	MerfiDictionary[148].setEnglWord("the solar system", "солнечная система", 90);
	MerfiDictionary[149].setEnglWord("derived", "производный, вторичный", 90);					// дирАйвд
	MerfiDictionary[150].setEnglWord("I've had enough.", "С меня хватит, мне достаточно.", 91);
	MerfiDictionary[151].setEnglWord("pullover", "пуловер, свитер", 91);						// пУловер
	MerfiDictionary[152].setEnglWord("At your absolute best...", "В твоем наилучшем виде...", 91);
	MerfiDictionary[153].setEnglWord("Someday you will be old enough...", "Однажды вы постараете настолько...", 91);
	MerfiDictionary[154].setEnglWord("So be it.", "Да будет так.", 92);
	MerfiDictionary[155].setEnglWord("no offence", "без обид", 92);								// эфЕнс
	MerfiDictionary[156].setEnglWord("Let's talk heart to heart.", "Давай поговрим по душам.", 92);
	MerfiDictionary[157].setEnglWord("excited", "взволнованный", 500);
}

/*
* Интересные предложения с каждого урока
MerfiDictionary[163].setEnglWord("Can I have some coffee?", "Могли бы вы принести мне кофе? (Просьба)", 30);

MerfiDictionary[163].setEnglWord("Why don't you come and visit us?", "Почему бы тебе не навестить нас?", 44);	// Повелительное наклонение

MerfiDictionary[163].setEnglWord("Who do you study with?", "С кем ты учишься?", 45);

MerfiDictionary[163].setEnglWord("Who is she talking to?", "С кем она разговаривает?", 46);
MerfiDictionary[163].setEnglWord("What is your new house like?", "Какой он твой новый дом?", 46);				// What...like? (какой?)
MerfiDictionary[163].setEnglWord("Who did she fall in love with?", "В кого она влюбилась?", 46);			
MerfiDictionary[163].setEnglWord("What is it all about?", "Из-за чего это все?", 46);

// What..., Which..., Who...
MerfiDictionary[163].setEnglWord("What country will you go next?", "В какую страну ты поедешь далее?", 47);
MerfiDictionary[163].setEnglWord("What is it all about?", "Из-за чего это все?", 47);
MerfiDictionary[163].setEnglWord("Which do you like best - reading or dancing?", "Что ты любишь больше - читать или танцевать?", 47);
MerfiDictionary[163].setEnglWord("Who many trees are there in this orchard?", "Сколько деревьев в этом фруктовом саду?", 47);

 // How long does it takes....?
 MerfiDictionary[163].setEnglWord("How long does it takes to master English?", "Сколько понадобится времени чтобы полностью овладеть английским?", 48);
 MerfiDictionary[163].setEnglWord("I'm not sure she has fully forgiven me.", "Я не уверен, что она полностью простила меня.", 48);

// Вопрос к длинному предложению, когда есть придаточное
MerfiDictionary[163].setEnglWord("Do you know if Jack is at home?", "Ты не знаешь Джек дома? (i)", 49);
MerfiDictionary[163].setEnglWord("I don't know whether Brain can swim.", "Я не знаю, уммет ли Браин плавать. (w)", 49);
MerfiDictionary[163].setEnglWord("Don't you know how much I love you?", "Разве ты не знаешь насколько сильно я люблю тебя?", 49);
// важен только в первой части предложения, в придаточной части порядок, как в утверждении. 
 
 // Косвенная речь
 MerfiDictionary[163].setEnglWord("Granny told Kate that she had to listen to her parents.", "Бабушка сказала Кате, что она должна слушаться родителей. (must)", 49);
 
 MerfiDictionary[380].setEnglWord("Would you mind helping me with it?", "Ты не против помочь мне с этим?", 51);

 // used to 
 MerfiDictionary[380].setEnglWord("He used to be a famous actor, but now he is completely forgotten.", "В прошлом он был знаменитым актером, но сейчас его полностью забыли. ", 36);

 // Герундий и инфинитив
 MerfiDictionary[163].setEnglWord("Most of all she enjoys spending a quiet evening with a good book.", "Больше всего ей нравится проводить тихий вечер с хорошей книгной.", 52);
 MerfiDictionary[163].setEnglWord("I would like to talk to you.", "Я бы хотел поговорить с тобой.", 52);

 // I WANT кто-то TO действие; LET кто-то (без TO) действие
  MerfiDictionary[163].setEnglWord("I want him to become a man at last.", "Я хочу чтобы он стал мужиком наконец.", 53);
  MerfiDictionary[163].setEnglWord("Let's be honest: dancing isn't his cup of tea.", "Давайте будем честными: танцы это не его, 53);

  // Инфинитив в значении причины: TO + глагол ("для того, чтобы...")
  // Существительное в значении причины: for something (без TO)
  MerfiDictionary[163].setEnglWord("It takes a lot of patience to achieve your goal.", "Требуется много терпения, чтобы достичь совей цели.", 54);
  MerfiDictionary[163].setEnglWord("My kids are always longing for Christmas.", "Мои дети всегда с нетерпением ожижают рождества.", 54);

 // Глагол GO с разными предлогами (TO, FOR,go + -ING, ON)
  MerfiDictionary[163].setEnglWord("If you have a dream, go for it. Never stop!", "Если у тебя есть мечта, иди за ней. Никогда не останавливайся!", 55);
  MerfiDictionary[163].setEnglWord("Go for a swim and come out a new man.", "Искупнись и вынерни другим человеком", 55);

  // Глагол GET 
  MerfiDictionary[163].setEnglWord("I got up and got dressed quiсkly.", "Я встал и быстро оделся", 56);

// Глагол DO или MAKE
  MerfiDictionary[163].setEnglWord("I do my best to make world better.", "Я из-зо все сил стараюсь сделать мир лучше", 57);
  MerfiDictionary[449].setEnglWord("Let's make the situation clear: did you use drugs?", "Давай проясним ситуацию: ты принимал нароктики?", 57);
MerfiDictionary[449].setEnglWord("Let's make a deal never to fight in front of the baby.", "Давай договоримся никогда не ссориться перед ребенком", 57);
 
 // Глагол HAVE
  MerfiDictionary[163].setEnglWord("Sandra has just had a baby.", "Сандра только что родила ребенка.", 58);
  MerfiDictionary[163].setEnglWord("I never had a tendency to be selfish.", "У меня никогда не было склонности к эгоизму.", 58);

  // Местоимения (I - ME, WE - US, YOU - YOU, HE - HIS, SHE - HER, THEY - THEM)
  MerfiDictionary[163].setEnglWord("How it was said: knowledge is power.", "Как было сказано: знание это сила.", 59);

  // Притяжательные Местоимения (MY OUR YOUR HIS HER THEIR ITS)
  MerfiDictionary[163].setEnglWord("Well, pets are like their owners.", "Чтож, животные как их хозяева.", 60);
  MerfiDictionary[163].setEnglWord("But I'm still an optimist.", "Но я все еще оптимист..", 60);
  MerfiDictionary[163].setEnglWord("His son seems to have a crash on my daughter.", "Его сын кажется втюрился в мою дочь", 60);

   // Притяжательные местоимения (не называем предмет) (MINE, HIS, HERS, OURS, THEIRS, ITS, YOURS)
  MerfiDictionary[163].setEnglWord("Elsa is a friend of mine.", "Эльза - мой друг.", 61); 

// Все местоимения
  MerfiDictionary[163].setEnglWord("He wants to talk to you.", "Он хочет поговорить с тобой.", 62);
  MerfiDictionary[163].setEnglWord("The toys are ours.", "Игрушки наши.", 62);

  // Возвратные местоимения (-SELF, -SELVES)
  MerfiDictionary[163].setEnglWord("He cut himself with a knife.", "Он порезался ножом.", 63);
  MerfiDictionary[163].setEnglWord("Sometimes I talk to myself.", "Иногда я говорю с собой.", 63);
  MerfiDictionary[163].setEnglWord("And I think to myself what a wonderful world.", "И я себе думаю как прекрасен мир.", 63);
  MerfiDictionary[553].setEnglWord("Their words speak for themselves.", "Их слова говорят сами за себя", 63);

  // Притяжательный падеж (Kitty'S cat)
  MerfiDictionary[163].setEnglWord("My wife's parents' house is gorgeous.", "Дом родителей моей жены великолепен.", 64);

  // Неопределенный артикль (A, AN)
  MerfiDictionary[163].setEnglWord("An owl is a bird with a hooked beak.", "Сова это птица с крючковатым клювом.", 65);

  // Множественное число
  MerfiDictionary[163].setEnglWord("The Boy in the Striped Pyjamas is a gorgeous drama film.", "Мальчик в полосатой пижаме - великолепная драма.", 66);
 
  // Неисчисляемое
  MerfiDictionary[163].setEnglWord("Old age isn't pleasant.", "Старость не радость.", 67);
  MerfiDictionary[163].setEnglWord("Life isn't a piece of cake for some people", "Жизнь не сахар для некоторых людей.", 67);

  // Определенный артикль THE
  MerfiDictionary[163].setEnglWord("Sometimes, the truth is worse than a white lie.", "Иногда, правда хуже, чем белая ложь.", 70);

   // Определенный артикль THE надо или НЕТ
  MerfiDictionary[163].setEnglWord("Children grow up quickly and leave their homes.", "Дети растут быстро и покидают свои дома.", 71);

// Определенный артикль THE (частные случаи)
  MerfiDictionary[163].setEnglWord("There is no love without pain.", "Не бывает любви ьез боли.", 72);

// Определенный артикль THE (георгафические объекты)
  MerfiDictionary[163].setEnglWord("The Eiffel Tower is a symbol of Paris.", "Эйфелевая башня это символ Парижа.", 73);
  MerfiDictionary[163].setEnglWord("Istanbul is the only city located over two continents", "Станбул единственный город, расположенный на двух континентах.", 73);

  // Указательные местоимения (THIS, THESE, THOSE, THAT)
  MerfiDictionary[163].setEnglWord("These books are cheaper than those.", "Эти книги дешевлее чем те.", 74);

  // Указательные местоимения (THIS, THESE, THOSE, THAT)
  MerfiDictionary[163].setEnglWord("These cups are dirty. Can we have some clean ones?", "Эти чашки грязные. Мы можем получить какие-то чистые?", 75);

  // Местоимения (SOME, ANY, SOMETHING, SOMEBODY (SOMEONE), ANYTHING, ANYBODY (ANYONE))
  MerfiDictionary[163].setEnglWord("Can I borrow some money from you?", "Я могу одолжить у тебя денег?", 76);

  // Местоимения (NOT...ANY, NO, NONE, NO ONE)
  MerfiDictionary[736].setEnglWord("Is there any milk left in the fridge?", "В холодильнике осталось молоко?", 77);

  // Местоимения (NOT...ANYBODY, NOBODY)
  MerfiDictionary[730].setEnglWord("There's nothing left to say.", "Больше нечего сказать", 78);

   // Местоимения (NOwhere, ANYthing, SOMEbody,...)
  MerfiDictionary[730].setEnglWord("I'm in the middle of nowhere.", "Я в ебенях.", 79);
  MerfiDictionary[730].setEnglWord("So many people to hate, and almost nobody to love.", "Так много людей для ненависти, я потчи никого для любви.", 79);
  MerfiDictionary[730].setEnglWord("I can't give you anithing but love.", "Я не могу ничего тебе дать кроме любви.", 79);
  MerfiDictionary[737].setEnglWord("I have nothing to hide.", "Мне нечего скрывать.", 79);

  // Местоимения (EVERY (...where, body, thing), ALL)
  MerfiDictionary[730].setEnglWord("Every season is good in its own way.", "Каждый сезон по-своему хорош.", 80);

  // Количественные местоимения (ALL MOST SOME ANY NO/NONE + of...)
  MerfiDictionary[753].setEnglWord("Most people drive too fast.", "Большинство людей ездят очень быстро.", 81);
  MerfiDictionary[753].setEnglWord("You can have some of this cake, but not all of it.", "Ты можешь съесть часть этого торта, но не весь.", 81);
  MerfiDictionary[753].setEnglWord("We all aren't as different as you think.", "Мы все не так отличаемся, как ты думаешь.", 81);
 
  // Местоимения (BOTH, EITHER, NEITHER)
  MerfiDictionary[753].setEnglWord("Neither of us will be here tomorrow.", "Никто из нас (двоих) не будет здесь завтра (n).", 82);
  MerfiDictionary[753].setEnglWord("I didn't read either of these books.", "Я не читал ни одну из этих (двух) книг(e).", 82);

  // Местоимения (MUCH, MANY, A LOT)
  MerfiDictionary[753].setEnglWord("How much coffee fo you drink a day?", "Сколько кофе ты пьешь в день?", 83);

  // Местоимения (A (LITTLE), A (FEW))
  MerfiDictionary[753].setEnglWord("You make very few mistakes.", "Ты делаешь очень мало ошибок.", 84);

  // Прилагательные (Adjectives)
  MerfiDictionary[753].setEnglWord("That smells awful.", "Пахнет ужасно.", 85);

   // Наречия (Adverb)
  MerfiDictionary[753].setEnglWord("I've never loved anyone so deeply.", "Я никого не любила так сильно.", 86);

  // Сравнение прилагтаельных (BIG -> BIGGER)
  MerfiDictionary[753].setEnglWord("Do you feel better or worse today?", "Тебе сегодня лучше или хуже?", 87);

// Сравнение прилагтаельных (THAN	A BIT BIGGER	MUCH BIGGER	)
  MerfiDictionary[753].setEnglWord("She swims faster than him.", "Она плавает быстрее чем он (мест.).", 88);
  MerfiDictionary[753].setEnglWord("She was taller than he was.", "Она была выше него (...was).", 88);
  

 // Сравнение прилагтаельных ((NOT) AS ... AS; (NOT) AS MUCH...AS; (NOT) AS MANY...AS;)
  MerfiDictionary[753].setEnglWord("Rome is not as old as Athens.", "Рим не такой старый, как Афины.", 89);
  MerfiDictionary[845].setEnglWord("You don't work as hard as me.", "Ты не работаешь также тяжело, как я", 89);

  // Превосходная степень прилагательных
  MerfiDictionary[753].setEnglWord("Our solar system is the best.", "Наша солнечная система лучшая.", 90);

// Наречие (и прилагательное) enough
  MerfiDictionary[753].setEnglWord("I've had enough.", "С меня хватит.", 91);
  MerfiDictionary[753].setEnglWord("There aren't enough apples in the basket.", "В корзине недостаточно яблок.", 91);
  MerfiDictionary[753].setEnglWord("Someday you will be old enough to start reading fairy tales again.", 
  "Однажды вы постареете настолько, что начнете снова читать сказки.", 91);

  // Наречие TOO (TOO much; TOO many; TOO...FOR somebody TO do something)
  MerfiDictionary[887].setEnglWord("I'm too tired to go out.", "Я слишком устал, чтобы выходить на улицу.", 92);
  MerfiDictionary[887].setEnglWord("She speaks too fast for me to undrerstand.", "Она говрит слишком быстро, чтобы я мог понять.", 92);

// Порядок слов в английском предложении
 MerfiDictionary[907].setEnglWord("Smoking is strictly forbidden in the public areas.", "Курение строго запрещено в общественных местах.", 93);
  MerfiDictionary[895].setEnglWord("She was the cutest baby ever.", "Она была самым милым ребенком из всех.", 93);
  
 
// Место наречия времени в предложении
	MerfiDictionary[907].setEnglWord("I never forgive my enemies.", "Я никогда не прощаю своих врагов", 94);
	MerfiDictionary[907].setEnglWord("It hardly happens that dreams come true.", "Едва ли случается, что мечты становятся реальными.", 94);
  
  // STILL, ALREADY, YET
  MerfiDictionary[923].setEnglWord("I haven't had breakfast yet.", "Я все еще не завтракал.", 95);
  MerfiDictionary[923].setEnglWord("He's still out.", "Он все еще не дома (снаружи).", 95);
  MerfiDictionary[923].setEnglWord("Does he already sold his car?", "Он уже проодал свою машину? (Pr. Sim.)", 95);

   // Дополнение после GIVE, LEND, PASS, SHOW, SEND
  MerfiDictionary[923].setEnglWord("I showed mother what I could do.", "Я показал маме, что я могу делать.", 95);

   // Дополнение после AND, SO, BUT, BECAUSE, OR
  MerfiDictionary[924].setEnglWord("To be or not to be, that is the question", "Быть или не быть, вот в чем вопрос.", 97);

   // Условные предложения с WHEN
	MerfiDictionary[933].setEnglWord("I bite my bottom lip when I feel nervous.", "Я кусаю свою верхнюю губу, когда я нервничаю.", 98);

	// Условные предложения 1-го типа с IF
	MerfiDictionary[954].setEnglWord("If I go there, I'll pick you up.", "Если я поеду туда, я тебя захвачу.", 99);
	MerfiDictionary[958].setEnglWord("Mom will be angry if I am late.", "Мама рассердится, если я опоздаю.", 99);
	MerfiDictionary[961].setEnglWord("I won't do anything if you don't help me.", "Я не буду ничего делать, если ты мне не поможешь.", 99);
  
  // Условные предложения 2-го типа с IF (Если бы)
	MerfiDictionary[954].setEnglWord("It would be nice if the weather were better.", "Было бы мило, если бы погода была лучше.", 100);
	MerfiDictionary[954].setEnglWord("I wouldn't go out if I were you.", "Я бы вышел наружу, если бы был на твоем месте.", 100);

	// Условные предложения, когда не нужно THAT, WHO, THAT
	MerfiDictionary[954].setEnglWord("These are the books I told you about.", "Вот книги, о которых  я тебе говорил.", 102);


	// Предлоги времени AT ON IN
	MerfiDictionary[1003].setEnglWord("Don't go out at night.", "Не выходи на улицу ночью.", 103);
	
  */



 // Функция случайным образом выбирает numberOfWords слов из словаря СЛОЖНЫХ слов:
 // Для каждого слова выводит перевод и ждет, пока пользователь не введет оригинал.
 // При ошибке выводится оригинал выражения.
int CheckKnowledgesDifficultMerfiDictionary(EnglishWord* MerfiDictionary, int numberOfWords)
{
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = rand() % DICTIONARY_DIFF_SIZE;

		// Исключаем повторы слов в тестировании
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ищем новое слово
			wordNumber = rand() % DICTIONARY_DIFF_SIZE;

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// Подсчет правильных ответов для ваставления оценки
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ответы совпали
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// отметили, что вопрос был в тесте
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// отметили ошибку 
		}

		// Отслеживание % выполненного теста и текущего результата (выводим только для больших тестов)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\nВы выполнили " << count * 100 / numberOfWords << " % теста."
				<< " С текущим результатом " << rightAnswer * 100 / count << " %.\n" << endl;
		}

	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;

	return numberOfWords - rightAnswer;		// количество ошибок
}

/* Замечание: почти полнростью совпадает с функцией обычных слов, за исключением размера словаря.
Переписать!*/