#include "englishWord.h"
#include <string>
#include <iomanip>
using namespace std;

#define DICTIONARY_SIZE 1016								// �� 1 ������, ��� ��������� ������� ����
#define DICTIONARY_DIFF_SIZE 158							// �� 1 ������, ��� ��������� ������� ������� ����

void initMerfiDictionary(EnglishWord*);						// ������������� �������
int CheckKnowledgesMerfiDictionary(EnglishWord*, int);		// ������� ������� ��������� ���� �� �������
void mistakesMerfiDictionary(EnglishWord*, int);			// ����� ������ ����� ������������
void initDifficultMerfiDictionary(EnglishWord*);			// ������������� ������� ������� ����
void flagsMerfiDictionary(EnglishWord*);					// ����� ������ ����� ������������
void CheckKnowledgesMerfiDictionaryUnit(EnglishWord*, int);	// �������� ��������� ������ �����
void searchWordInTheMerfiDictionary(EnglishWord*, string);	// ����� ��������� � �������
int CheckKnowledgesIntervalMerfiDictionary(EnglishWord*,
					const int, const int, const int = 0);	// ������� ������� ��������� ���� �� ������� � ���������

int CheckKnowledgesDifficultMerfiDictionary(EnglishWord*, int);	// ������� ������� ��������� ������� ���� �� �������

int main()
{
	// ������� setlocate ������ ������ ��� ���������
	setlocale(LC_ALL, "rus");								// ��� ����������� ����������� ������� ��������
	srand((unsigned int)time(NULL));						// ������������ ������
	int errors;

	/* ������������� ������� ������ �������  */
	EnglishWord MerfiDictionary[DICTIONARY_SIZE];
	initMerfiDictionary(MerfiDictionary);							// ������������� �������
	//errors = CheckKnowledgesMerfiDictionary(MerfiDictionary, 906);	// �������� ������ (�������� �������)

	//errors = CheckKnowledgesIntervalMerfiDictionary(MerfiDictionary, 67, 67);	// �������� ������ ���������
	//mistakesMerfiDictionary(MerfiDictionary, errors);				// ����� ������ ������, ����� �������� ������
	//flagsMerfiDictionary(MerfiDictionary);							// ����� ��������� ������ �������

	//CheckKnowledgesMerfiDictionaryUnit(MerfiDictionary, 88);
	searchWordInTheMerfiDictionary(MerfiDictionary, "in tim");			// ����� ��������� � �������

	/********************************** �������� ������� ���� ***************************************************/
	/* ������������� ������� �������� �������  */
	//EnglishWord difficultMerfiDictionary[DICTIONARY_DIFF_SIZE];
	//initDifficultMerfiDictionary(difficultMerfiDictionary);					// ������������� �������
	//errors = CheckKnowledgesDifficultMerfiDictionary(difficultMerfiDictionary, 157);	// �������� ������ (�������� �������)

	//mistakesMerfiDictionary(difficultMerfiDictionary, errors);				// ����� ������ ������, ����� �������� ������
	//flagsMerfiDictionary(difficultMerfiDictionary);							// ����� ��������� ������ �������
	/**************************** ����� ������ �������� ������� ���� ********************************************/

	/* ������� ���� �� ������� 
	
	2) ����� ��� ���� � ����� CheckKnowledgesIntervalMerfiDictionary �������� �����������*/

	/*
	�����: ������ ����������� ��������.
	- ������������ �� ������� ���� ������ + ���� ��� ������� �������.
	- ����������� � ���� ������ ����
	- ������������ �����
	- ������� ����� ������������
	- �������� ����� � ������ ������� (�� ���� ������ ������� ������� �� ���� ��������� ����, ����� ������ ������)
	

	3) ���������� ������� CheckKnowledgesMerfiDictionary ����� ����� ���� ������ ������ �������
	*/
	

	return 0;
}

// ������� ��������� ������� �������� numberOfWords ���� �� �������:
// ��� ������� ����� ������� ������� � ����, ���� ������������ �� ������ �����.
// ����� ��������� �������� ��������� � ������������ ����� ���������.
int CheckKnowledgesMerfiDictionary(EnglishWord* MerfiDictionary, int numberOfWords)
{
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = rand() % DICTIONARY_SIZE;

		// ��������� ������� ���� � ������������
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ���� ����� �����
			wordNumber = rand() % DICTIONARY_SIZE;			

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// ������� ���������� ������� ��� ����������� ������
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ������ �������
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// ��������, ��� ������ ��� � �����
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// �������� ������ 
		}

		// ������������ % ������������ ����� � �������� ���������� (������� ������ ��� ������� ������)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\n�� ��������� " << count * 100 / numberOfWords << " % �����."
				<< " � ������� ����������� " << rightAnswer * 100 / count << " %.\n" << endl;
		}
		
	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;
	
	return numberOfWords - rightAnswer;		// ���������� ������
}

// ������� ������� ������������ ������ ����� ������������ �� ������� (������� numberOfWords)
void mistakesMerfiDictionary(EnglishWord* MerfiDictionary, int errorCount)
{
	if (errorCount == 0)
		cout << "Congratulations! There are no any mistakes!\n";
	else 
	{
		cout << "List of mistakes is:" << endl;
		for (int count = 1; count < EnglishWord::getWordCount(); count++)
			if (MerfiDictionary[count].getFlag() == 2)	// ������ ��� ������������
			{
				cout << "Lesson �" << setfill(' ') << setw(3) << setiosflags(ios::right) << MerfiDictionary[count].getLesson() << ": ";
				MerfiDictionary[count].print();
			}
	}
}

// ������� ������� ��� ����� ���� �� ������� (������� numberOfWords) (��������� ����������� �� ������)
void flagsMerfiDictionary(EnglishWord* MerfiDictionary)
{
	cout << "\nList of flags:\n 0 - ����� �� ���� � ������������;\n"
		<< " 1 - ������ �����;\n 2 - ������;";
	for (int count = 0; count < EnglishWord::getWordCount(); count++)
	{
		if (count % 86 == 0)	cout << endl;

		cout << MerfiDictionary[count].getFlag();
	}
	cout << "\n";
}

// ������� �������� ������ ������ ����������� ����� �� numberOfWords ���� �� �������:
// ��� ������� ����� ������� ������� � ����, ���� ������������ �� ������ �����.
// ����� ��������� �������� ��������� � ������ ������.
void CheckKnowledgesMerfiDictionaryUnit(EnglishWord* MerfiDictionary, int unitNumber)
{
	string temp;			// ��������� ���������� ��� ��������� ������������ ������
	int rightAnswer = 0;	// ���������� ���������� �������
	int numberOfWords = 0;	// ���������� ���� � �����	
	cout << "Let's check a lexicon of the lesson �" << unitNumber << ':' << endl;

	for (int count = 0; count < DICTIONARY_SIZE; count++)		// ��������� �� ���� ������
	{
		if (MerfiDictionary[count].getLesson() == unitNumber)	// ����� ������� �����
		{
			numberOfWords++;
			MerfiDictionary[count].printTranslation();

			cout << "Enter your answer: ";
			getline(cin, temp);

			// ������� ���������� ������� ��� ����������� ������
			if (MerfiDictionary[count].getWord() == temp)	// ������ �������
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
			// ���� ����� ����� ������ ������� ���������� ����
			//if ((MerfiDictionary[count].getLesson() > unitNumber) && (MerfiDictionary[count].getLesson() != 125))	
			//{
			//	break;
			//}		
	}

	if (numberOfWords == 0)					// ���� ������
		cout << "There are no any words in unit �" << unitNumber << '.' << endl;
	else
	{
		cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " quastions.";
		cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;
	}
}

// ������� ������ ���� � �������
// ��������: ������� ������� ��������� ������ substring � ������� numberOfWords,
// ��� �� ������� (������� �����), ��� � �� ���������� (�������� �����) �
// �������� ������ ���� ����������. 
// ������ ��� ������ �������� ��� ������ �������.
void searchWordInTheMerfiDictionary(EnglishWord* MerfiDictionary, string substring)
{
	int flag = 0;												// ��� ������������ ����������
	for (int count = 0; count < DICTIONARY_SIZE; count++)		// ��������� �� ���� ������
	{
		/*
		������� find() ���������� ������ ������� ��������� ��������� ��� ���������� ������� � ������ �
		���� �������� ���� size_t.
		���� ������ ��� ������ �� �������, �� ������������ ����������� ��������� std::string::npos.
		������:		
			string text {"My friend loves apples"};
			cout << text.find("apple") << std::endl;      // 16
		*/
		// ����� ����������
		if ((MerfiDictionary[count].getWord().find(substring) != std::string::npos) ||		// � ���������,
			(MerfiDictionary[count].getTranslation().find(substring) != std::string::npos))	// ��� � ��������
		{
			cout << "Lesson �" << setfill(' ') << setw(3) << setiosflags(ios::right)
				<< MerfiDictionary[count].getLesson() << ": ";
			MerfiDictionary[count].print();
			flag++;
		}
	}
	if (flag == 0)											// ���������� �� ����
		cout << "There is no substring '" << substring << "' in the dictionary.";
}

// �������, ������� ��������� ������ ����� ����� ��������� �������. 
// ������� ��������� ������� �������� ��� ����� �� ������� ����� ��������� �������.
// ��� ������� ����� ������� ������� � ����, ���� ������������ �� ������ �����.
// ����� ��������� �������� ��������� � ������������ ����� ���������.
// ***************************************************************************************
// ���������:
// - MerfiDictionary - ������� (������ �������� EnglishWord)
// - leftUnit - ����� �������� ����� � ���������
// - rightUnit - ����� �������� ����� � ���������
// - umberOfWords = 0 - ���������� ����������� ����, �� ��������� 0 (0: ��������� ��� ����� ���������)
// ***************************************************************************************
// ����������: ��������, ��� ������ ����������� ���������������.
// �����: ������ POPULAR WORDS ������ ������� (���� ����� ������� ����)
// ***************************************************************************************
// ������� �������� ���������:
// 1) ������� ����� ������� ����� ��������� ��������� (������ ����� ����� � ������� leftUnit): minIndex
// 2) ������� ����� ���������� ����� ��������� ��������� (��������� ����� ����� � ������� rightUnit): maxUndex
// 3) �������� �������� ������� (�� ����������� ���������)
int CheckKnowledgesIntervalMerfiDictionary(EnglishWord* MerfiDictionary, const int leftUnit, 
											const int rightUnit, int numberOfWords)
{
	int minIndex = -1;		// ������ ������� ����� ��������� ���������
	int maxIndex = -1;		// ������ ���������� ����� ��������� ���������
	
	// ������ ����� � ���������
	for (int count = 0; count < DICTIONARY_SIZE; count++)
		if (MerfiDictionary[count].getLesson() == leftUnit)
		{
			minIndex = count;
			break;	// ��� ������ ���������� ������� �� �����
		}
	
	// ��������� ����� � ��������� (�������� ����� � minIndex)
	// ���������: ��� ��� � popular_words = 500 � ���� �� �� �������, ���������� ��������� ���� �������
	for (int count = minIndex; count < DICTIONARY_SIZE; count++)
		if (MerfiDictionary[count].getLesson() == rightUnit)
			maxIndex = count;

	cout << "first index: " << minIndex << endl;
	cout << "last index: " << maxIndex << endl;
	cout << "Number of test-words: " << maxIndex - minIndex + 1 << endl;

	if (numberOfWords == 0 || (numberOfWords > maxIndex - minIndex + 1))	// �������� �� ���������
		numberOfWords = maxIndex - minIndex + 1;	// ��������� ��� �����

	// �������� �������� �������, �� ����������� ���������
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = minIndex + rand() % (maxIndex - minIndex + 1);

		// ��������� ������� ���� � ������������
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ���� ����� �����
			wordNumber = minIndex + rand() % (maxIndex - minIndex + 1);

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// ������� ���������� ������� ��� ����������� ������
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ������ �������
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// ��������, ��� ������ ��� � �����
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// �������� ������ 
		}

		// ������������ % ������������ ����� � �������� ���������� (������� ������ ��� ������� ������)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\n�� ��������� " << count * 100 / numberOfWords << " % �����."
					<< " � ������� ����������� " << rightAnswer * 100 / count << " %.\n" << endl;
		}

	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;

	return numberOfWords - rightAnswer;		// ���������� ������
}

// ������� ���������� ������� (������� EnglishWord) ����������
// - �������� �����
// - �������
// - ����� ����� (�� ��������� 0)
// - ���� ������������ ������ �� ������������ (�� ��������� true)
void initMerfiDictionary(EnglishWord* MerfiDictionary)
{
	/****************** Lesson 1: *************************************************************************/
	MerfiDictionary[1].setEnglWord("hospital", "��������", 1);
	MerfiDictionary[2].setEnglWord("shop assistant", "��������", 1);
	MerfiDictionary[3].setEnglWord("Tokyo", "�����", 1);
	MerfiDictionary[4].setEnglWord("designer", "��������", 1);										// �������
	MerfiDictionary[5].setEnglWord("be interested in", "�������������� ���-��", 1);
	MerfiDictionary[6].setEnglWord("be thirsty", "������ ����", 1);
	MerfiDictionary[7].setEnglWord("be afraid of", "������� ����-�� (��)", 1);
	MerfiDictionary[8].setEnglWord("feel depressed", "����������� ���� ������������, ���� � ���������", 1);	// �������
	MerfiDictionary[9].setEnglWord("get ill", "��������", 1);
	MerfiDictionary[10].setEnglWord("for over", "�����(� �������)", 1);
	MerfiDictionary[11].setEnglWord("take medicine", "��������� ���������", 1);								// �����
	MerfiDictionary[12].setEnglWord("sharp", "������", 1);													// ���� 63
	/*************** End of init Lesson 1 ****************************************************************/

	/****************** Lesson 2: *************************************************************************/
	MerfiDictionary[13].setEnglWord("a little", "�������", 2);
	MerfiDictionary[14].setEnglWord("a snack", "������� (���.)", 2);
	MerfiDictionary[15].setEnglWord("on the internet", "�� ���������", 2);
	MerfiDictionary[16].setEnglWord("discussion", "����������", 2);
	MerfiDictionary[17].setEnglWord("by the next week", "� ��������� ������", 2);
	/*************** End of init Lesson 2 ****************************************************************/

	/****************** Lesson 3: *************************************************************************/
	MerfiDictionary[18].setEnglWord("take a shower", "��������� ���", 3);
	MerfiDictionary[19].setEnglWord("right now", "����� ������, � ������ ������", 3);
	MerfiDictionary[20].setEnglWord("at the moment", "� ������ ������, ����� ������", 3);
	MerfiDictionary[21].setEnglWord("listen to", "�������", 3);
	MerfiDictionary[22].setEnglWord("quiet", "�����", 3);
	MerfiDictionary[23].setEnglWord("improve", "��������", 3);
	MerfiDictionary[24].setEnglWord("come late", "����������", 3);
	MerfiDictionary[25].setEnglWord("argue", "�������", 3);
	MerfiDictionary[26].setEnglWord("complain", "����������", 3);
	MerfiDictionary[27].setEnglWord("currently", "������, � ������� ������", 3);
	MerfiDictionary[28].setEnglWord("belong to", "������������ (��)", 3);
	MerfiDictionary[29].setEnglWord("at least", "�� ������� ����, ��� �������", 3);
	MerfiDictionary[30].setEnglWord("wrong", "��������, ���������", 3);
	MerfiDictionary[31].setEnglWord("think of", "������ �", 3);
	/*************** End of init Lesson 3 ****************************************************************/

	/****************** Lesson 4: *************************************************************************/
	MerfiDictionary[32].setEnglWord("look at", "�������� �� (���-��)", 4);
	MerfiDictionary[33].setEnglWord("shout at", "������� �� (����-��)", 4);
	MerfiDictionary[34].setEnglWord("look after", "�������, ������������� �� (���-��)", 4);
	MerfiDictionary[35].setEnglWord("critisize", "�����������", 4);
	MerfiDictionary[36].setEnglWord("answer the phone", "�������� �� �����", 4);
	/*************** End of init Lesson 4 ****************************************************************/

	/****************** Lesson 5: *************************************************************************/
	MerfiDictionary[37].setEnglWord("violin", "�������", 5);
	MerfiDictionary[38].setEnglWord("purse", "�������, �������, ��������", 5);
	MerfiDictionary[39].setEnglWord("wing", "�����", 5);
	/*************** End of init Lesson 5 ****************************************************************/

	/****************** Lesson 6: *************************************************************************/
	MerfiDictionary[40].setEnglWord("petrol", "������", 6);
	MerfiDictionary[41].setEnglWord("go to the movies", "������ � ����", 6);
	MerfiDictionary[42].setEnglWord("at weekends", "�� ��������", 6);
	MerfiDictionary[43].setEnglWord("on Friday", "�� ��������", 6);
	MerfiDictionary[44].setEnglWord("stranger", "����������", 6);
	/*************** End of init Lesson 6 ****************************************************************/

	/****************** Lesson 7: *************************************************************************/
	MerfiDictionary[45].setEnglWord("guitar", "������", 7);
	MerfiDictionary[46].setEnglWord("How do I get...?", "��� ��� ���������...?", 7);
	MerfiDictionary[47].setEnglWord("ever", "�����-����", 7);
	MerfiDictionary[48].setEnglWord("avenue", "�����", 7);
	/*************** End of init Lesson 7 ****************************************************************/	

	/****************** Lesson 8: *************************************************************************/
	MerfiDictionary[49].setEnglWord("have fun", "����������", 8);
	MerfiDictionary[50].setEnglWord("see the doctor", "���� �� ����� � �����", 8);
	MerfiDictionary[51].setEnglWord("tell lies", "�������� ��������", 8);
	MerfiDictionary[52].setEnglWord("feel well", "������ ���� �����������", 8);
	/*************** End of init Lesson 8 ****************************************************************/

	/****************** Lesson 9: *************************************************************************/
	MerfiDictionary[53].setEnglWord("headache", "�������� ����", 9);
	MerfiDictionary[54].setEnglWord("silence", "������, ��������", 9);
	MerfiDictionary[55].setEnglWord("pay attention", "�������� ��������", 9);
	MerfiDictionary[56].setEnglWord("loud", "�������", 9);
	MerfiDictionary[57].setEnglWord("get married", "��������", 9);
	MerfiDictionary[58].setEnglWord("have a holiday", "���� �� ���������", 9);
	/*************** End of init Lesson 9 ****************************************************************/

	/****************** Lesson 10: *************************************************************************/
	MerfiDictionary[59].setEnglWord("be asleep", "�����", 10);
	MerfiDictionary[60].setEnglWord("be scared of", "���� ���������� (��)", 10);
	MerfiDictionary[61].setEnglWord("journey", "�����������", 10);
	MerfiDictionary[62].setEnglWord("at work", "�� ������", 10);
	MerfiDictionary[63].setEnglWord("at the party", "�� ���������, �� ���������", 10);
	MerfiDictionary[64].setEnglWord("accident", "���������� ������", 10);						// ��������
	MerfiDictionary[65].setEnglWord("be hurt", "����������", 10);					// ���
	MerfiDictionary[66].setEnglWord("be fond of", "������ ���-��, ���������� ���-��", 10);
	MerfiDictionary[67].setEnglWord("be good at", "������ �����, ����������� � ���-��", 10);
	MerfiDictionary[68].setEnglWord("be married to", "���� ������� �� (��.)", 10);
	MerfiDictionary[69].setEnglWord("cross", "��������", 10);
	MerfiDictionary[70].setEnglWord("switch off", "���������", 10);
	MerfiDictionary[71].setEnglWord("degrees", "�������", 10);
	/*************** End of init Lesson 10 ****************************************************************/

	/****************** Lesson 11: *************************************************************************/
	MerfiDictionary[72].setEnglWord("take off", "����� (�� ������)", 11);
	MerfiDictionary[73].setEnglWord("sit down", "�����", 11);
	MerfiDictionary[74].setEnglWord("have a lot of fun", "������� ������������", 11);
	MerfiDictionary[75].setEnglWord("look out", "���������", 11);
	MerfiDictionary[76].setEnglWord("pack a suitcase", "�������� �������", 11);
	MerfiDictionary[77].setEnglWord("beforehand", "�������", 11);
	MerfiDictionary[78].setEnglWord("then", "�����, �����", 11);
	MerfiDictionary[79].setEnglWord("than", "���", 11);
	MerfiDictionary[80].setEnglWord("celebrity", "������������", 11);
	MerfiDictionary[81].setEnglWord("decision", "�������", 11);
	/*************** End of init Lesson 11 ****************************************************************/

	/****************** Lesson 12: *************************************************************************/
	MerfiDictionary[82].setEnglWord("do the shopping", "������ �������", 12);
	/*************** End of init Lesson 12 ****************************************************************/

	/****************** Lesson 13: *************************************************************************/
	MerfiDictionary[83].setEnglWord("tablet", "�������", 13);
	MerfiDictionary[84].setEnglWord("listen to the radio", "������� �����", 13);
	MerfiDictionary[85].setEnglWord("solve the crossword", "������ ���������", 13);
	MerfiDictionary[86].setEnglWord("photos", "����������", 13);
	MerfiDictionary[87].setEnglWord("be crowded with", "���� �����������, ���� ������������ (��.)", 13);	// �������
	MerfiDictionary[88].setEnglWord("half", "��������", 13);
	MerfiDictionary[89].setEnglWord("pass by", "��������� ����", 13);
	MerfiDictionary[90].setEnglWord("explosion", "�����", 13);												// ���������
	MerfiDictionary[91].setEnglWord("earthquake", "�������������", 13);
	/*************** End of init Lesson 13 ****************************************************************/

	/****************** Lesson 14: *************************************************************************/
	// empty
	/*************** End of init Lesson 14 ****************************************************************/

	/****************** Lesson 15: *************************************************************************/
	MerfiDictionary[92].setEnglWord("work for...", "�������� ��...(����-��)", 15);
	/*************** End of init Lesson 15 ****************************************************************/

	/****************** Lesson 16: *************************************************************************/
	MerfiDictionary[93].setEnglWord("snail", "������", 16);
	/*************** End of init Lesson 16 ****************************************************************/

	/****************** Lesson 17: *************************************************************************/
	MerfiDictionary[94].setEnglWord("ride a horse", "������ �� ������", 17);
	/*************** End of init Lesson 17 ****************************************************************/

	/****************** Lesson 18: *************************************************************************/
	MerfiDictionary[95].setEnglWord("vacation", "������", 18);											// �������
	/*************** End of init Lesson 18 ****************************************************************/

	/****************** Lesson 19: *************************************************************************/
	// empty
	/*************** End of init Lesson 19 ****************************************************************/

	/****************** Lesson 20: *************************************************************************/
	MerfiDictionary[96].setEnglWord("in ink", "���������", 20);
	MerfiDictionary[97].setEnglWord("aim", "����", 20);
	MerfiDictionary[98].setEnglWord("steam", "���", 20);
	MerfiDictionary[99].setEnglWord("steam engine", "������� ���������", 20);
	MerfiDictionary[100].setEnglWord("jubilee", "������", 20);											// �������
	MerfiDictionary[101].setEnglWord("coach", "�������", 20);
	MerfiDictionary[102].setEnglWord("vehicle", "������������ ��������", 20);							// �����
	MerfiDictionary[103].setEnglWord("Singapore", "��������", 20);
	/*************** End of init Lesson 20 ****************************************************************/


	/****************** Lesson 21: *************************************************************************/
	MerfiDictionary[104].setEnglWord("It is said...", "�������...(������)", 21);
	MerfiDictionary[105].setEnglWord("It is known...", "(���) ��������...(������)", 21);
	MerfiDictionary[106].setEnglWord("temple", "����", 21);
	MerfiDictionary[107].setEnglWord("crops", "������", 21);
	MerfiDictionary[108].setEnglWord("launch", "���������, ����������", 21);							// ����
	MerfiDictionary[109].setEnglWord("technician", "������", 21);										// �������
	MerfiDictionary[110].setEnglWord("invent", "����������", 21);
	/*************** End of init Lesson 21 ****************************************************************/

	/****************** Lesson 22: *************************************************************************/
	// empty
	/*************** End of init Lesson 22 ****************************************************************/

	/****************** Lesson 23: *************************************************************************/
	// empty
	/*************** End of init Lesson 23 ****************************************************************/

	/****************** Lesson 24: *************************************************************************/
	MerfiDictionary[111].setEnglWord("soul mate", "����������� ����", 24);
	MerfiDictionary[112].setEnglWord("experience", "����", 24);											// ����������
	MerfiDictionary[113].setEnglWord("drawer", "��������� ����", 24);									// �����
	MerfiDictionary[114].setEnglWord("real estate agent", "�������", 24);
	MerfiDictionary[115].setEnglWord("feel embarrassed", "����������� ���� ���������, ���������", 24);	// ��������
	MerfiDictionary[116].setEnglWord("by chance", "��������", 24);
	MerfiDictionary[117].setEnglWord("in my opinion", "�� ����� ������", 24);
	MerfiDictionary[118].setEnglWord("for ages", "100 ���", 24);
	MerfiDictionary[119].setEnglWord("ask for something", "������� ����-��", 24);
	MerfiDictionary[120].setEnglWord("apply for a job", "������������ �� ������", 24);
	MerfiDictionary[121].setEnglWord("at first sight", "� ������� �������", 24);
	MerfiDictionary[122].setEnglWord("as soon as possible", "��� ����� ������ (ASAP)", 24);
	/*************** End of init Lesson 24 ****************************************************************/

	/****************** Lesson 25: *************************************************************************/
	// empty
	/*************** End of init Lesson 25 ****************************************************************/

	/****************** Lesson 26: *************************************************************************/
	MerfiDictionary[123].setEnglWord("gonna", "going to (����������)", 26);
	MerfiDictionary[124].setEnglWord("attend", "��������", 26);
	MerfiDictionary[125].setEnglWord("brick", "������", 26);
	MerfiDictionary[126].setEnglWord("pale", "�������", 26);
	MerfiDictionary[127].setEnglWord("Christmas", "���������", 26);				// �������
	MerfiDictionary[128].setEnglWord("astronaut", "���������", 26);				// ��������
	MerfiDictionary[129].setEnglWord("iron", "����", 26);
	/*************** End of init Lesson 26 ****************************************************************/

	/****************** Lesson 27: *************************************************************************/
	MerfiDictionary[130].setEnglWord("jogging", "��� ����������� ������", 27);	// ������
	MerfiDictionary[131].setEnglWord("hurricane", "������", 27);				// ������� 
	MerfiDictionary[132].setEnglWord("scarf", "����", 27);						// �����
	MerfiDictionary[133].setEnglWord("They say...", "�������...", 27);
	MerfiDictionary[134].setEnglWord("condition", "�������", 27);
	MerfiDictionary[135].setEnglWord("bother", "����������", 27);
	MerfiDictionary[136].setEnglWord("sooner or later", "������ ��� �����", 27);
	/*************** End of init Lesson 27 ****************************************************************/

	/****************** Lesson 28: *************************************************************************/
	MerfiDictionary[137].setEnglWord("fill in", "���������", 28);
	MerfiDictionary[138].setEnglWord("a will", "���������", 28);
	MerfiDictionary[139].setEnglWord("dishwasher", "�����������", 28);
	MerfiDictionary[140].setEnglWord("sandwich", "���������", 28);
	MerfiDictionary[141].setEnglWord("bolt", "����", 28);
	MerfiDictionary[142].setEnglWord("wherever", "� ����� �����, ��� ������ (w)", 28);
	/*************** End of init Lesson 28 ****************************************************************/

	/****************** Lesson 29: *************************************************************************/
	MerfiDictionary[143].setEnglWord("lottery ticket", "���������� �����", 29);
	MerfiDictionary[144].setEnglWord("catch a cold", "������������", 29);
	MerfiDictionary[145].setEnglWord("firefighter", "��������", 29);
	MerfiDictionary[146].setEnglWord("lair", "����", 29);
	MerfiDictionary[147].setEnglWord("billionaire", "����������", 29);			// ���-�-����
	MerfiDictionary[148].setEnglWord("dream on", "������� �� ������", 29);
	MerfiDictionary[149].setEnglWord("murderer", "������", 29);					// ������
	MerfiDictionary[150].setEnglWord("come and see", "��������", 29);
	MerfiDictionary[151].setEnglWord("groom", "�����", 29);
	MerfiDictionary[152].setEnglWord("best man", "�����", 29);
	MerfiDictionary[153].setEnglWord("borrow", "��������", 29);
	/*************** End of init Lesson 29 *****************************************************************/

	/****************** Lesson 30: *************************************************************************/
	MerfiDictionary[154].setEnglWord("piano", "�������", 30);
	MerfiDictionary[155].setEnglWord("young", "�������", 30);
	MerfiDictionary[156].setEnglWord("go on", "������������", 30);
	MerfiDictionary[157].setEnglWord("anymore", "������ (� ����������)", 30);
	MerfiDictionary[158].setEnglWord("come in", "�����", 30);
	MerfiDictionary[159].setEnglWord("write down", "����������", 30);
	MerfiDictionary[160].setEnglWord("polite", "��������", 30);
	MerfiDictionary[161].setEnglWord("compete", "�������������, �����������", 30);
	MerfiDictionary[162].setEnglWord("What has happened to them?", "��� � ���� ���������?", 30);
	MerfiDictionary[163].setEnglWord("Can I have some coffee?", "����� �� �� �������� ��� ����? (�������)", 30);
	MerfiDictionary[164].setEnglWord("certainly", "�������", 30);
	/*************** End of init Lesson 30 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[165].setEnglWord("maiden name", "������� �������", 500);
	MerfiDictionary[166].setEnglWord("cheek", "����", 500);
	MerfiDictionary[167].setEnglWord("chest", "�����", 500);
	MerfiDictionary[168].setEnglWord("fist", "�����", 500);
	MerfiDictionary[169].setEnglWord("jaw", "�������", 500);
	MerfiDictionary[170].setEnglWord("forehead", "���", 500);
	MerfiDictionary[171].setEnglWord("muscle", "�����", 500);
	MerfiDictionary[172].setEnglWord("cute", "�����", 500);
	MerfiDictionary[173].setEnglWord("freckles", "��������", 500);
	MerfiDictionary[174].setEnglWord("haircut", "��������, �������", 500);
	MerfiDictionary[175].setEnglWord("curious", "����������", 500);

	MerfiDictionary[176].setEnglWord("fair", "�������", 500);
	MerfiDictionary[177].setEnglWord("easy-going", "������ �� ������", 500);
	MerfiDictionary[178].setEnglWord("excited", "�������������", 500);
	MerfiDictionary[179].setEnglWord("wise", "������", 500);			// ����
	MerfiDictionary[180].setEnglWord("bride", "�������", 500);
	MerfiDictionary[181].setEnglWord("widow", "�����", 500);
	MerfiDictionary[182].setEnglWord("cloak", "����", 500);
	MerfiDictionary[183].setEnglWord("earrings", "������", 500);
	MerfiDictionary[184].setEnglWord("slippers", "�������", 500);		// ������
	MerfiDictionary[185].setEnglWord("trainers", "���������", 500);
	MerfiDictionary[186].setEnglWord("underwear", "������ �����", 500);

	MerfiDictionary[187].setEnglWord("dress up", "����������", 500);
	MerfiDictionary[188].setEnglWord("career", "�������", 500);
	MerfiDictionary[189].setEnglWord("razor", "������", 500);			// �����
	MerfiDictionary[190].setEnglWord("towel", "���������", 500);		// ����� ���� (� ����� ���)
	MerfiDictionary[191].setEnglWord("kettle", "������", 500);
	MerfiDictionary[192].setEnglWord("knife", "���", 500);
	MerfiDictionary[193].setEnglWord("mug", "������", 500);
	MerfiDictionary[194].setEnglWord("backpack", "������", 500);
	MerfiDictionary[195].setEnglWord("bonfire", "������", 500);
	MerfiDictionary[196].setEnglWord("yield", "�����������, ���������, ������ (�����, �����)", 500);	// ����
	MerfiDictionary[197].setEnglWord("envelope", "�������", 500);		// ��������
	/*************** End of 1025 popular words: *****************************************************************/

	/****************** Lesson 31: *************************************************************************/
	MerfiDictionary[198].setEnglWord("day after day", "���� ��� ���", 31);
	MerfiDictionary[199].setEnglWord("politness", "����������", 31);
	MerfiDictionary[200].setEnglWord("relative", "�����������", 31);
	MerfiDictionary[201].setEnglWord("keep myself fit", "������� ���� � �����", 31);
	MerfiDictionary[202].setEnglWord("come of age", "�����������, ������� ���������������", 31);
	MerfiDictionary[203].setEnglWord("mention", "���������", 31);
	MerfiDictionary[204].setEnglWord("fridge", "�����������", 31);
	MerfiDictionary[205].setEnglWord("appointment", "�������", 31);
	MerfiDictionary[206].setEnglWord("groceries", "��������, �����", 31);;
	MerfiDictionary[207].setEnglWord("be kind to the elephants", "���� ������ � ������", 31);
	MerfiDictionary[208].setEnglWord("blame", "������, ��������, ����, �����", 31);				// ���� 63
	MerfiDictionary[209].setEnglWord("Israel", "�������", 31);
	MerfiDictionary[210].setEnglWord("keep smiling", "��������� ���������", 31);
	MerfiDictionary[211].setEnglWord("park in the street", "����������� �� �����", 31);
	MerfiDictionary[212].setEnglWord("in a friendly way", "��-��������", 31);
	MerfiDictionary[213].setEnglWord("grocery", "�������", 31);					// �������
	/*************** End of init Lesson 31 *****************************************************************/
	
	/****************** Lesson 32: *************************************************************************/
	MerfiDictionary[214].setEnglWord("go on a diet", "����� �� �����", 32);
	MerfiDictionary[215].setEnglWord("beware of", "������������ (��)", 32);
	MerfiDictionary[216].setEnglWord("patient", "����������", 32);
	MerfiDictionary[217].setEnglWord("outfit", "�����, ������", 32);
	MerfiDictionary[218].setEnglWord("cheat on", "�������� (��), ����������", 32);
	MerfiDictionary[219].setEnglWord("be rude to", "���� ������ (��)", 32);
	MerfiDictionary[220].setEnglWord("if you don't mind", "���� �� �� ������", 32);
	MerfiDictionary[221].setEnglWord("definitely", "�����������, ����������, �����", 32);
	MerfiDictionary[222].setEnglWord("each other", "���� � ������", 32);
	MerfiDictionary[223].setEnglWord("make friends with", "����������� (��)", 32);
	/*************** End of init Lesson 32 *****************************************************************/

	/****************** Lesson 33: *************************************************************************/
	MerfiDictionary[224].setEnglWord("driving licence", "������������ �����", 33);	// �������
	MerfiDictionary[225].setEnglWord("babysitter", "�����, �������", 33);
	MerfiDictionary[226].setEnglWord("hire", "��������", 33);
	MerfiDictionary[227].setEnglWord("overpay", "�������������", 33);
	MerfiDictionary[228].setEnglWord("all day long", "���� ��������, ���� ����", 33);
	MerfiDictionary[229].setEnglWord("complaint", "������", 33);
	MerfiDictionary[230].setEnglWord("soldier", "������", 33);						// ������
	MerfiDictionary[231].setEnglWord("chemistry", "�����", 33);						// �������� 
	MerfiDictionary[232].setEnglWord("it's my turn", "��� �������", 33);
	MerfiDictionary[233].setEnglWord("do the dishes", "���� ������", 33);
	MerfiDictionary[234].setEnglWord("primary school", "��������� �����", 33);
	MerfiDictionary[235].setEnglWord("in time", "�������", 33);
	MerfiDictionary[236].setEnglWord("even", "����", 33);
	MerfiDictionary[237].setEnglWord("promotion", "�����������, ���������", 33);
	/*************** End of init Lesson 33 *****************************************************************/

	/****************** Lesson 34: *************************************************************************/
	MerfiDictionary[238].setEnglWord("to be honest", "���� ������", 34);
	MerfiDictionary[239].setEnglWord("date him", "����������� � ���, ������ �� ��������", 34);
	MerfiDictionary[240].setEnglWord("That would be very kind of you.", "��� ���� �� ����� ���� � ����� �������.", 34);
	MerfiDictionary[241].setEnglWord("perhaps", "��������, ��������", 34);
	MerfiDictionary[242].setEnglWord("do me a favor", "����� ��� ������", 34);		// ������
	MerfiDictionary[243].setEnglWord("I'd love to", "� �������� (would)", 34);	
	/*************** End of init Lesson 34 *****************************************************************/

	/****************** Lesson 35 *************************************************************************/
	MerfiDictionary[244].setEnglWord("lay the table", "������� �� ����", 35);
	MerfiDictionary[245].setEnglWord("do the hair", "������� ��������, ������� ������", 35);
	MerfiDictionary[246].setEnglWord("watch out!", "��������!", 35);
	MerfiDictionary[247].setEnglWord("watch your steps", "������ ��� ����", 35);
	MerfiDictionary[248].setEnglWord("glasses", "����, �������", 35);
	MerfiDictionary[249].setEnglWord("take care", "������ ����", 35);
	MerfiDictionary[250].setEnglWord("take your time", "�� ��������, �� �����", 35);
	MerfiDictionary[251].setEnglWord("mess", "����������", 35);
	MerfiDictionary[252].setEnglWord("silly", "������", 35);
	/*************** End of init Lesson 35 *****************************************************************/

	/****************** Lesson 36 *************************************************************************/
	MerfiDictionary[253].setEnglWord("homicide", "��������, ������, �������", 36);					// ��������
	MerfiDictionary[254].setEnglWord("nurse", "���������", 36);
	MerfiDictionary[255].setEnglWord("hike", "������ ������, ��������� ����� ��������", 36);
	MerfiDictionary[256].setEnglWord("go jogging", "���������� ����� �������", 36);
	MerfiDictionary[257].setEnglWord("a hell of a lot of...", "��������� �����...", 36);
	MerfiDictionary[258].setEnglWord("be retired", "���� �� ������", 36);							// ������
	MerfiDictionary[259].setEnglWord("criminal", "����������", 36);
	MerfiDictionary[260].setEnglWord("drug", "��������, ���������", 36);
	MerfiDictionary[261].setEnglWord("work out", "���������� �������", 36);
	/*************** End of init Lesson 36 *****************************************************************/

	/****************** Lesson 37 *************************************************************************/
	MerfiDictionary[262].setEnglWord("hardly", "���� ��", 37);
	MerfiDictionary[263].setEnglWord("fearless", "�����������", 37);
	MerfiDictionary[264].setEnglWord("politician", "�������", 37);										// ��������
	MerfiDictionary[265].setEnglWord("among", "�����", 37);
	MerfiDictionary[266].setEnglWord("worry", "������������", 37);
	MerfiDictionary[267].setEnglWord("pocket", "������", 37);
	MerfiDictionary[268].setEnglWord("cigarette", "��������", 37);
	MerfiDictionary[269].setEnglWord("unfortunately", "� ��������", 37);
	MerfiDictionary[270].setEnglWord("painkiller", "��������������", 37);
	MerfiDictionary[271].setEnglWord("medical kit", "�������", 37);
	MerfiDictionary[272].setEnglWord("pharmacy", "������ (p...)", 37);										// �������
	/*************** End of init Lesson 37 *****************************************************************/

	/****************** Lesson 38 *************************************************************************/
	MerfiDictionary[273].setEnglWord("at the concert", "�� ��������", 38);
	MerfiDictionary[274].setEnglWord("go out of the cafe", "����� �� ����", 38);
	MerfiDictionary[275].setEnglWord("anywhere", "� ����� �����", 38);
	MerfiDictionary[276].setEnglWord("look for", "������", 38);
	MerfiDictionary[277].setEnglWord("crash", "������, ���������, ����", 38);
	MerfiDictionary[278].setEnglWord("innovation", "���������, ���������", 38);
	MerfiDictionary[279].setEnglWord("increase of prices", "��������� ���", 38);					// ������
	MerfiDictionary[280].setEnglWord("fuel", "�������", 38);
	MerfiDictionary[281].setEnglWord("recently", "�������, � ��������� �����", 38);					// �������
	MerfiDictionary[282].setEnglWord("challenge", "�����, ���������", 38);							// �������
	MerfiDictionary[283].setEnglWord("shift", "�����, ������", 38);
	MerfiDictionary[284].setEnglWord("misunderstanding", "�������������, �������������", 38);
	MerfiDictionary[285].setEnglWord("so far", "�� ������ ������, �� ��� ���, ����", 38);
	MerfiDictionary[286].setEnglWord("change for the better", "���������� � �������", 38);
	MerfiDictionary[287].setEnglWord("carefully", "�����������, ���������", 38);
	/*************** End of init Lesson 38 *****************************************************************/

	/****************** Lesson 39 *************************************************************************/
	MerfiDictionary[288].setEnglWord("Oh gosh", "� ���� ���", 39);
	MerfiDictionary[289].setEnglWord("quite", "������, ���������� (� ���������������)", 39);
	MerfiDictionary[290].setEnglWord("Are you kidding?", "�� ������?", 39);
	MerfiDictionary[291].setEnglWord("rain cats and dogs", "����, ��� �� �����", 39);
	MerfiDictionary[292].setEnglWord("You are reading my mind", "�� ������� ��� �����", 39);
	MerfiDictionary[293].setEnglWord("far", "������ (� �������� � ����������)", 39);
	MerfiDictionary[294].setEnglWord("a long way", "������ (� ������������)", 39);
	MerfiDictionary[295].setEnglWord("foggy", "��������, �������", 39);
	MerfiDictionary[296].setEnglWord("cloudy", "�������, ��������", 39);
	/*************** End of init Lesson 39 *****************************************************************/

	/****************** Lesson 40 *************************************************************************/
	MerfiDictionary[297].setEnglWord("at all", "� �����, ������", 40);
	MerfiDictionary[298].setEnglWord("principle", "�������, �������", 40);									// ��������
	MerfiDictionary[299].setEnglWord("if so", "���� ���, ���� ��� ���", 40);
	MerfiDictionary[300].setEnglWord("have a rest", "��������", 40);
	MerfiDictionary[301].setEnglWord("traffic jam", "������", 40);
	MerfiDictionary[302].setEnglWord("insane", "��������, ������������", 40);								// ������
	MerfiDictionary[303].setEnglWord("noticeable", "��������, ���������", 40);								// ���������
	MerfiDictionary[304].setEnglWord("fasten your seat belts", "����������� ���� ����� ������������", 40);	// ����, ����
	MerfiDictionary[305].setEnglWord("positively", "������������, ����������, ����������", 40);				// ���������
	MerfiDictionary[306].setEnglWord("expectation", "��������, �������", 40);								// �����������		
	MerfiDictionary[307].setEnglWord("a little bit", "����-����", 40);
	MerfiDictionary[308].setEnglWord("God bless you", "���� ������ (����� �����)", 40);
	MerfiDictionary[309].setEnglWord("get well", "��������������, ������������", 40);
	MerfiDictionary[310].setEnglWord("sneeze", "������", 40);
	MerfiDictionary[311].setEnglWord("necessary", "����������", 40);
	MerfiDictionary[312].setEnglWord("I'm terribly sorry", "� ������ ���������", 40);
	/*************** End of init Lesson 40 *****************************************************************/

	/****************** Lesson 41 *************************************************************************/
	MerfiDictionary[313].setEnglWord("mice", "����", 41);
	MerfiDictionary[314].setEnglWord("sibling", "������ ���� ��� ������", 41);								// ������
	MerfiDictionary[315].setEnglWord("be similar to each other", "���� �������� ���� �� �����", 41);		// ������
	MerfiDictionary[316].setEnglWord("in another way", "��-�������", 41);
	/*************** End of init Lesson 41 *****************************************************************/

	/****************** Lesson 42 *************************************************************************/
	MerfiDictionary[317].setEnglWord("lawyer", "�����, �������", 42);
	MerfiDictionary[318].setEnglWord("run the something", "��������� ���-��, ������� �� ���-��", 42);
	MerfiDictionary[319].setEnglWord("do the chores", "����� �������� ����", 42);							// ����
	MerfiDictionary[320].setEnglWord("band", "����������� ������", 42);
	MerfiDictionary[321].setEnglWord("get hooked on...", "�������� ��...", 42);
	MerfiDictionary[322].setEnglWord("relevant", "��������, ����������� � ����, �����������", 42);			// ��������
	MerfiDictionary[323].setEnglWord("consider", "�������, ��������, ���������", 42);						// ��������						
	/*************** End of init Lesson 42 *****************************************************************/

	/****************** Lesson 43 *************************************************************************/
	MerfiDictionary[324].setEnglWord("makeup", "������", 43);
	MerfiDictionary[325].setEnglWord("wallet", "��������", 43);												// �����
	MerfiDictionary[326].setEnglWord("no one", "�����", 43);
	MerfiDictionary[327].setEnglWord("have nothing to do with", "�� ����� ������ ������ �, ����� �� ��������� �", 43);
	MerfiDictionary[328].setEnglWord("treat somebody this way", "�������� � ���-�� ����� �������", 43);
	MerfiDictionary[329].setEnglWord("treat myself strictly", "���������� � ���� ������", 43);				// ���� 63
	MerfiDictionary[330].setEnglWord("care about", "���������� �", 43);
	/*************** End of init Lesson 43 *****************************************************************/

	/****************** Lesson 44 *************************************************************************/
	MerfiDictionary[331].setEnglWord("share with", "�������� �", 44);
	MerfiDictionary[332].setEnglWord("Why don't you...?", "������ �� ����...?", 44);	// ������ � ������������� ����������
	/*************** End of init Lesson 44 *****************************************************************/

	/****************** Lesson 45 *************************************************************************/
	MerfiDictionary[333].setEnglWord("be present", "�������������", 45);
	MerfiDictionary[334].setEnglWord("guilty", "��������", 45);
	MerfiDictionary[335].setEnglWord("make mother laugh", "��������� ���� �������� (����-�� ���-�� ������)", 45);
	MerfiDictionary[336].setEnglWord("TV series", "������", 45);					// �����
	MerfiDictionary[337].setEnglWord("like best", "�������� ������ �����", 45);
	MerfiDictionary[338].setEnglWord("laugh till one cries", "�������� �� ����", 45);
	MerfiDictionary[339].setEnglWord("Greek cuisine", "��������� �����", 45);		// ������
	/*************** End of init Lesson 45 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[340].setEnglWord("lantern", "������", 500);						// ������, �����
	MerfiDictionary[341].setEnglWord("teardrop", "�����, ��������", 500);			// �������
	MerfiDictionary[342].setEnglWord("calendar", "���������", 500);					// �������
	MerfiDictionary[343].setEnglWord("black currant", "������ ���������", 500);		// ������
	MerfiDictionary[344].setEnglWord("fragrance", "������", 500);					// ���������
	/*************** End of popular words: **********************************************************************/

	/****************** Lesson 46 *************************************************************************/
	MerfiDictionary[345].setEnglWord("Thailand", "�������", 46);
	MerfiDictionary[346].setEnglWord("play for", "������ �� (�������)", 46);
	MerfiDictionary[347].setEnglWord("stay at a hotel", "������������ � ����� (�����-��)", 46);
	MerfiDictionary[348].setEnglWord("talk about", "�������� �", 46);
	MerfiDictionary[349].setEnglWord("wish for happiness", "������ �������, ���������� � �������", 46);
	MerfiDictionary[350].setEnglWord("stuff", "��������, ����, ����, ��������, ���", 46);
	MerfiDictionary[351].setEnglWord("look like", "��������� �����-�� �������", 46);
	/*************** End of init Lesson 46 *****************************************************************/

	/****************** Lesson 47 *************************************************************************/
	MerfiDictionary[352].setEnglWord("magazine", "������", 47);
	MerfiDictionary[353].setEnglWord("commit a crime", "��������� ������������", 47);
	MerfiDictionary[354].setEnglWord("accountant", "���������", 47);							// ���������
	MerfiDictionary[355].setEnglWord("hold a position", "�������� ���������", 47);
	MerfiDictionary[356].setEnglWord("well-paid", "������������������", 47);
	MerfiDictionary[357].setEnglWord("enjoyable", "���������� ������������", 47);				// ��������
	MerfiDictionary[358].setEnglWord("orchard", "��������� ���", 47);							// ����
	/*************** End of init Lesson 47 *****************************************************************/

	/****************** Lesson 48 *************************************************************************/
	MerfiDictionary[359].setEnglWord("omelette", "�����", 48);									// ����� �����
	MerfiDictionary[360].setEnglWord("master", "��������, ������", 48);
	MerfiDictionary[361].setEnglWord("permission", "����������", 48);
	MerfiDictionary[362].setEnglWord("practice makes perfect", "�������� �������� � ������������", 48);
	MerfiDictionary[363].setEnglWord("shipping", "��������", 48);
	MerfiDictionary[364].setEnglWord("get the refund", "�������� �������", 48);					// ������
	MerfiDictionary[365].setEnglWord("as a rule", "��� �������", 48);
	MerfiDictionary[366].setEnglWord("couple", "����, ���, ����", 48);							// ����
	MerfiDictionary[367].setEnglWord("typically", "�������, ������", 48);						// �������
	MerfiDictionary[368].setEnglWord("bake", "����", 48);
	MerfiDictionary[369].setEnglWord("get her forgiveness", "�������� �� ��������", 48);			// �������� 
	MerfiDictionary[370].setEnglWord("fixed terms", "������������� �����", 48);
	/*************** End of init Lesson 48 *****************************************************************/

	/****************** Lesson 49 *************************************************************************/
	MerfiDictionary[371].setEnglWord("bring up a child", "���������, ��������� �������", 49);
	MerfiDictionary[372].setEnglWord("believe", "������", 49);
	MerfiDictionary[373].setEnglWord("finally", "�������-��", 49);
	MerfiDictionary[374].setEnglWord("take place", "����� �����, �����������, ���������", 49);
	MerfiDictionary[375].setEnglWord("have a baby", "������ �������", 49);
	MerfiDictionary[376].setEnglWord("restroom", "������, �������", 49);
	MerfiDictionary[377].setEnglWord("obvious", "���������, �����, �����������", 49);			// ������
	MerfiDictionary[378].setEnglWord("for sure", "���������, ����������", 49);
	MerfiDictionary[379].setEnglWord("get along with", "������, ���� � ������� ���������� (��)", 49);
	MerfiDictionary[380].setEnglWord("go off", "�������, �������, ������� (��)", 49);
	MerfiDictionary[381].setEnglWord("be satisfied", "���� ���������������, ���� ���������", 49);
	MerfiDictionary[382].setEnglWord("I have no idea", "� �� ���� �� ��������� �������������", 49);
	/*************** End of init Lesson 49 *****************************************************************/

	/****************** Lesson 50: *************************************************************************/
	MerfiDictionary[383].setEnglWord("granny", "������� (����.)", 50);
	MerfiDictionary[384].setEnglWord("brush your teeth", "������� ���� ����", 50);
	MerfiDictionary[385].setEnglWord("till the age of eight", "�� ������ ���", 50);
	MerfiDictionary[386].setEnglWord("wrapper", "��������, �������, �����", 50);				// �����
	/*************** End of init Lesson 50 ****************************************************************/

	/****************** Lesson 51: *************************************************************************/
	MerfiDictionary[387].setEnglWord("umbrella", "����", 51);
	MerfiDictionary[388].setEnglWord("selfish", "������", 51);
	MerfiDictionary[389].setEnglWord("Would you mind...?", "�� �� ������...?", 51);
	MerfiDictionary[390].setEnglWord("passion", "�������", 51);									// ����
	MerfiDictionary[391].setEnglWord("day off", "��������", 51);
	/*************** End of init Lesson 51 ****************************************************************/

	/****************** Lesson 52: *************************************************************************/
	MerfiDictionary[392].setEnglWord("refuse", "����������, ���������, ������, �����", 52);				// ������
	MerfiDictionary[393].setEnglWord("mind", "���������", 52);
	MerfiDictionary[394].setEnglWord("never mind", "������, �������, �� ���� � ������", 52);
	MerfiDictionary[395].setEnglWord("rubbish", "�����, ������, ����, ����, �����", 52);
	MerfiDictionary[396].setEnglWord("suggest", "����������, ����������", 52);							// �������
	MerfiDictionary[397].setEnglWord("reward", "�������, ��������������, ����������", 52);				// �����
	MerfiDictionary[398].setEnglWord("waste", "������� � ������, ������, ������", 52);
	MerfiDictionary[399].setEnglWord("procrastinate", "�������, �����������, ����������� �� �����", 52);// �������������
	MerfiDictionary[400].setEnglWord("most of all", "������ �����", 52);
	MerfiDictionary[401].setEnglWord("explain", "���������", 52);
	MerfiDictionary[402].setEnglWord("applaud", "������������", 52);									// �����
	/*************** End of init Lesson 52 ****************************************************************/

	/****************** Lesson 53: *************************************************************************/
	MerfiDictionary[403].setEnglWord("lend", "���������� (l)", 53);
	MerfiDictionary[404].setEnglWord("advise", "����������", 53);
	MerfiDictionary[405].setEnglWord("advice", "�����", 53);
	MerfiDictionary[406].setEnglWord("persuade", "��������, �����������", 53);							// ������
	MerfiDictionary[407].setEnglWord("at last", "�������", 53);
	MerfiDictionary[408].setEnglWord("reveal a secret", "�������� ������", 53);							// �����
	MerfiDictionary[409].setEnglWord("break up", "���������, ���������, ����������", 53);
	MerfiDictionary[410].setEnglWord("cruel", "��������, �����������", 53);
	MerfiDictionary[411].setEnglWord("invest", "����������, �������������", 53);
	MerfiDictionary[412].setEnglWord("stress-resistant", "�������-����������", 53);						// ���������
	MerfiDictionary[413].setEnglWord("confidently", "��������, ��������� (���� �����)", 53);			// �����������
	MerfiDictionary[414].setEnglWord("apologize", "����������, ������� ��������", 53);					// ����������
	MerfiDictionary[415].setEnglWord("self-confidently", "������������", 53);							// ����-�����������
	MerfiDictionary[416].setEnglWord("clothes", "������", 53);											// ����� ��� ������
	MerfiDictionary[417].setEnglWord("make somebody", "��������� ����-��", 53);
	MerfiDictionary[418].setEnglWord("dancing isn't your cup of tea", "����� ��� �� ����", 53);
	/*************** End of init Lesson 53 ****************************************************************/

	/****************** Lesson 54: *************************************************************************/
	MerfiDictionary[419].setEnglWord("invite to the wedding", "���������� �� �������", 54);
	MerfiDictionary[420].setEnglWord("correctly", "���������", 54);
	MerfiDictionary[421].setEnglWord("achieve your goal", "������� ����� ����", 54);
	MerfiDictionary[422].setEnglWord("It's worth that.", "��� ���� �����.", 54);						// ���									
	MerfiDictionary[423].setEnglWord("get used to", "���������� �, ������������ (��)", 54);
	MerfiDictionary[424].setEnglWord("achieve", "���������, ����������", 54);
	MerfiDictionary[425].setEnglWord("soda", "���������", 54);											// �����
	MerfiDictionary[426].setEnglWord("pay them a visit", "������� �� �����", 54);
	MerfiDictionary[427].setEnglWord("have a break", "����� �������", 54);
	MerfiDictionary[428].setEnglWord("long for", "������� � ����������, ���������", 54);
	/*************** End of init Lesson 54 ****************************************************************/

	/****************** Lesson 55: *************************************************************************/
	MerfiDictionary[429].setEnglWord("go to sleep", "�������", 55);
	MerfiDictionary[430].setEnglWord("go home", "���� �����", 55);
	MerfiDictionary[431].setEnglWord("go for a swim", "����� ��������� (go)", 55);
	MerfiDictionary[432].setEnglWord("excursion", "���������", 55);										// ������															
	MerfiDictionary[433].setEnglWord("cruise", "�����", 55);											// ����
	MerfiDictionary[434].setEnglWord("strike", "����������, ����, ����", 55);
	MerfiDictionary[435].setEnglWord("go for a coffee", "����� ������ ����", 55);
	MerfiDictionary[436].setEnglWord("harvest festival", "�������� ������", 55);						// ������ �������
	MerfiDictionary[437].setEnglWord("fair", "�������", 55);
	MerfiDictionary[438].setEnglWord("go sightseeing", "�������� ��������������������� (go)", 55);		// ���������
	MerfiDictionary[439].setEnglWord("nearby", "����������, ����������", 55);							// ������
	MerfiDictionary[440].setEnglWord("I'm in!", "� ������ ��! � � ����!", 55);
	/*************** End of init Lesson 55 ****************************************************************/

	/****************** Lesson 56: *************************************************************************/
	MerfiDictionary[441].setEnglWord("get fat/lost/dressed/wet", "�����������/����������/�������/����������", 56);
	MerfiDictionary[442].setEnglWord("parcel", "�������, �������� �����", 56);
	MerfiDictionary[443].setEnglWord("toddler", "���������� (������� �� ��������� �� �����)", 56);
	MerfiDictionary[444].setEnglWord("get serious", "����� ���������", 56);
	MerfiDictionary[445].setEnglWord("luggage delivery", "�������� ������", 56);
	MerfiDictionary[446].setEnglWord("get in a car", "����� � ������ (�����-��)", 56);
	MerfiDictionary[447].setEnglWord("get out of a car", "����� �� ������ (�����-��)", 56);
	MerfiDictionary[448].setEnglWord("get on a train/plane/bus", "����� �� �����/�������/�������", 56);
	MerfiDictionary[449].setEnglWord("get off a train/plane/bus", "����� � ������/��������/��������", 56);
	MerfiDictionary[450].setEnglWord("It's time to get serious", "���� ����� ���������", 56);
	/*************** End of init Lesson 56 ****************************************************************/

	/****************** Lesson 57: *************************************************************************/
	MerfiDictionary[451].setEnglWord("do the ironing/washing", "�������/�������", 57);
	MerfiDictionary[452].setEnglWord("do an exam", "������� �������", 57);
	MerfiDictionary[453].setEnglWord("make a mistake", "������� ������", 57);
	MerfiDictionary[454].setEnglWord("make a noise", "������", 57);
	MerfiDictionary[455].setEnglWord("make an appointment", "��������� �������, ��������", 57);
	MerfiDictionary[456].setEnglWord("make a bed", "������ �������", 57);
	MerfiDictionary[457].setEnglWord("take a photogragh", "����������������, ������� ������", 57);
	MerfiDictionary[458].setEnglWord("How do you do?", "��� ����?", 57);						// �����: How do you do?
	MerfiDictionary[459].setEnglWord("What do you do?", "��� �� ���������?", 57);
	MerfiDictionary[460].setEnglWord("do a research", "��������� ������������", 57);
	MerfiDictionary[461].setEnglWord("do repairs", "���������� ��������, ��������", 57);		// ����� ���� ��������
	MerfiDictionary[462].setEnglWord("drugstore", "������ (d...)", 57);
	MerfiDictionary[463].setEnglWord("To make a long story short...", "������ ������...", 57);	// � ������ �����������
	MerfiDictionary[464].setEnglWord("make an impression", "���������� �����������", 57);
	MerfiDictionary[465].setEnglWord("make the situation clear", "��������� �������� (the)", 57);
	MerfiDictionary[466].setEnglWord("make a fortune", "�����������, ������ ���������", 57);	// �����
	MerfiDictionary[467].setEnglWord("skill", "�����, ������, ����������", 57);
	MerfiDictionary[468].setEnglWord("make a deal", "��������� ������, �����������", 57);
	MerfiDictionary[469].setEnglWord("make a confession to the crime", "�������� ���� � ���������� ������������", 57);	// �������
	MerfiDictionary[470].setEnglWord("confess a fault", "�������� (������������) ������", 57);	// ������
	MerfiDictionary[471].setEnglWord("do wrong", "��������� �����������", 57);
	/*************** End of init Lesson 57 ****************************************************************/

	/****************** Lesson 58: *************************************************************************/
	MerfiDictionary[472].setEnglWord("cough", "������, �������", 58);							// ���
	MerfiDictionary[473].setEnglWord("sore throat", "������� �����", 58);
	MerfiDictionary[474].setEnglWord("I have flu", "� ���� �����", 58);							// ��� �������
	MerfiDictionary[475].setEnglWord("have a pizza/glass of milk", "������ �����/������ ������", 58);
	MerfiDictionary[476].setEnglWord("have breakfast/lunch/dinner", "����������/�������/�������", 58);
	MerfiDictionary[477].setEnglWord("have a dream", "������ ���", 58);
	MerfiDictionary[478].setEnglWord("have a look at something", "���������� �� ���-��", 58);
	MerfiDictionary[479].setEnglWord("heart diseases", "������� ������", 58);					// �����
	MerfiDictionary[480].setEnglWord("have a right to vote", "����� ����� ����������", 58);
	MerfiDictionary[481].setEnglWord("have a bad temper", "����� ������ ���������", 58);
	MerfiDictionary[482].setEnglWord("have a tendency to", "����� ����������, ��������� �", 58);// ��������
	MerfiDictionary[483].setEnglWord("have a big mouth", "��� �� ����������� (� ��������)", 58);// ������
	MerfiDictionary[484].setEnglWord("have a brush with the law", "����� ����� � �������", 58);	// ������	
	MerfiDictionary[485].setEnglWord("have a sweet tooth", "���� �����������", 58);				// ������
	MerfiDictionary[486].setEnglWord("take seriously", "��������� �������", 58);
	MerfiDictionary[487].setEnglWord("have a familiar ring", "������� �������", 58);			// ������
	MerfiDictionary[488].setEnglWord("have a chip on one's shoulder", "���� �������, ������ ����� � �����", 58);// ������
	MerfiDictionary[489].setEnglWord("movement", "��������", 58);
	MerfiDictionary[490].setEnglWord("work long hours", "�������� �����������", 58);
	MerfiDictionary[491].setEnglWord("give up the idea", "���������� �� ���� (����������)", 58);
	MerfiDictionary[492].setEnglWord("be alert", "���� ������", 58);							// ���� (�������, ����������)
	MerfiDictionary[493].setEnglWord("enough", "����������", 58);
	/*************** End of init Lesson 58 ****************************************************************/

	/****************** Lesson 59: *************************************************************************/
	MerfiDictionary[494].setEnglWord("in amazement", "� ����������, ����������", 59);			// ���������
	MerfiDictionary[495].setEnglWord("adjust", "������������, �������������, ��������� � �������", 59);
	MerfiDictionary[496].setEnglWord("insist", "����������, ����������", 59);					// ������
	MerfiDictionary[497].setEnglWord("distinctly", "���������, �����", 59);						// ����������
	MerfiDictionary[498].setEnglWord("over there", "��� ���", 59);
	MerfiDictionary[499].setEnglWord("bicycle rack", "������������ ������, ���������, �������", 59);
	MerfiDictionary[500].setEnglWord("stray dog", "��������, �������� ���", 59);				// �������������
	MerfiDictionary[501].setEnglWord("male/female", "�������/������� (� ����)", 59);
	MerfiDictionary[502].setEnglWord("a funny kind of hat", "������� �����", 59);
	MerfiDictionary[503].setEnglWord("knowledge is power", "������ ��� ����", 59);
	/*************** End of init Lesson 59 ****************************************************************/

	/****************** Lesson 60: *************************************************************************/
	MerfiDictionary[504].setEnglWord("they seem to steal our food", "�������, ��� ������ ���� ���", 60);
	MerfiDictionary[505].setEnglWord("mean", "������, �������, ��������, �������", 60);
	MerfiDictionary[506].setEnglWord("subscription", "��������", 60);
	MerfiDictionary[507].setEnglWord("pets are like their owners", "�������, ��� �� �������", 60);
	MerfiDictionary[508].setEnglWord("greedy for money", "������ �� �����", 60);
	MerfiDictionary[509].setEnglWord("The Simpsons", "��������", 60);
	MerfiDictionary[510].setEnglWord("in order to", "��� ����, �����", 60);
	MerfiDictionary[511].setEnglWord("daughter", "����", 60);
	MerfiDictionary[512].setEnglWord("neighbor", "�����", 60);
	MerfiDictionary[513].setEnglWord("have a crash on", "���������, ����������� �", 60);
	/*************** End of init Lesson 60 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[514].setEnglWord("escape", "�����, �����, ��������� �����", 500);				// ������
	MerfiDictionary[515].setEnglWord("disturb", "����������, ���������, ���������� �������", 500);	// �����
	MerfiDictionary[516].setEnglWord("deserve", "�����������, ���� ���������", 500);				// ����
	MerfiDictionary[517].setEnglWord("defeat", "���������, �������, �������� ���������", 500);		// �����
	MerfiDictionary[518].setEnglWord("grimly", "�������, ����������, ������", 500);
	MerfiDictionary[519].setEnglWord("exactly", "�����, ������, �����, ���������� �����", 500);		// ��������		
	MerfiDictionary[0].setEnglWord("sex", "��� (��������)", 500);
	/*************** End of popular words: ****************************************************************/

	/****************** Lesson 61: *************************************************************************/
	MerfiDictionary[520].setEnglWord("pronoun", "�����������", 61);
	MerfiDictionary[521].setEnglWord("friends of mine", "��� ������", 61);
	MerfiDictionary[522].setEnglWord("notice", "��������, �������� ��������, ���������, �������", 61);
	MerfiDictionary[523].setEnglWord("hang around the village", "�������� �� �������", 61);
	MerfiDictionary[524].setEnglWord("fellow", "�������, ��������, �������", 61);
	MerfiDictionary[525].setEnglWord("sarcastically", "�����������", 61);							// �����������
	MerfiDictionary[526].setEnglWord("collar", "�������, ��������", 61);							// ����
	MerfiDictionary[527].setEnglWord("towards", "� �����������, �, ���������", 61);					// ������
	MerfiDictionary[528].setEnglWord("overweight", "������ (� ����)", 61);
	MerfiDictionary[529].setEnglWord("firmly", "������", 61);
	MerfiDictionary[530].setEnglWord("adopt", "���������, ����������", 61);
	MerfiDictionary[531].setEnglWord("guess", "������������, �������, ����������", 61);				// ���
	MerfiDictionary[532].setEnglWord("it was easy to guess...", "���� ����� ����������...", 61);
	MerfiDictionary[533].setEnglWord("anxious", "���������, �����������", 61);						// �������
	MerfiDictionary[534].setEnglWord("in her 30's", "� ������ 30-�� (� �������� �������)", 61);
	MerfiDictionary[535].setEnglWord("hug", "��������, �������", 61);
	MerfiDictionary[536].setEnglWord("tightly", "������, �����", 61);								// ������
	MerfiDictionary[537].setEnglWord("ordinary", "�������", 61);									// ����(�)��
	MerfiDictionary[538].setEnglWord("quantity", "����������", 61);									// ��������
	/*************** End of init Lesson 61 ****************************************************************/

	/****************** Lesson 62: *************************************************************************/
	MerfiDictionary[539].setEnglWord("be pleased", "���� ���������", 62);
	MerfiDictionary[540].setEnglWord("hairbrush", "��������", 62);
	MerfiDictionary[541].setEnglWord("gorgeous", "��������, ������������", 62);						// ������
	MerfiDictionary[542].setEnglWord("purchase", "�������, �������", 62);							// �����
	/*************** End of init Lesson 62 *****************************************************************/

	/****************** Lesson 63: *************************************************************************/
	MerfiDictionary[543].setEnglWord("Sometimes I talk to myself.", "������ � ������ � �����.", 63);
	MerfiDictionary[544].setEnglWord("I enjoyed myself.", "� ������� ������������.", 63);
	MerfiDictionary[545].setEnglWord("help yourself", "�������� (�����������)", 63);
	MerfiDictionary[546].setEnglWord("she was by herself", "��� ���� ���� (����.)", 63);	
	MerfiDictionary[547].setEnglWord("And I think to myself...", "� � ���� �����...", 63);
	MerfiDictionary[548].setEnglWord("psychologist", "��������", 63);							// ������������
	MerfiDictionary[549].setEnglWord("feed", "����, �������", 63);
	MerfiDictionary[550].setEnglWord("fool myself", "���������� ����", 63);
	MerfiDictionary[551].setEnglWord("Don't make a fool of yourself.", "�� ����� �� ���� ������.", 63);
	MerfiDictionary[552].setEnglWord("make yourself at home", "�������� ����, ��� ����", 63);
	MerfiDictionary[553].setEnglWord("A cat prefers walking by itself.", "����� ������������ ������ ���� �� ����.", 63);							// ������������
	/*************** End of init Lesson 63 *****************************************************************/

	/****************** Lesson 64: *************************************************************************/
	MerfiDictionary[554].setEnglWord("because of", "�� �������, ��-��", 64);
	MerfiDictionary[555].setEnglWord("cause", "�������, �����, ��������, ���� ��������", 64);
	MerfiDictionary[556].setEnglWord("colleague", "�������", 64);								// �����
	MerfiDictionary[557].setEnglWord("approve", "��������, ����������", 64);
	MerfiDictionary[558].setEnglWord("masterpiece", "������", 64);
	MerfiDictionary[559].setEnglWord("my wife's parents' house", "��� ��������� ���� ����", 64);
	MerfiDictionary[560].setEnglWord("densely", "������, ������", 64);							// ������
	MerfiDictionary[561].setEnglWord("double-decker", "������������, �����������, ������� (���������)", 64);
	MerfiDictionary[562].setEnglWord("citizen", "������", 64);
	/*************** End of init Lesson 64 *****************************************************************/

	/****************** Lesson 65: *************************************************************************/
	MerfiDictionary[563].setEnglWord("robber", "���������, ���������", 65);
	MerfiDictionary[564].setEnglWord("hawk", "������, �����", 65);								// ���
	MerfiDictionary[565].setEnglWord("beak", "����", 65);
	MerfiDictionary[566].setEnglWord("claw", "������, �����, ������, ��������, �����", 65);		// ���
	MerfiDictionary[567].setEnglWord("stage", "����, �����, ������, ��������������", 65);
	MerfiDictionary[568].setEnglWord("composer", "����������", 65);								// ���������
	MerfiDictionary[569].setEnglWord("succeed", "�����������, ����� �����", 65);
	MerfiDictionary[570].setEnglWord("coroner", "�������������", 65);
	MerfiDictionary[571].setEnglWord("nowadays", "��������� �����, ���� ���", 65);
	MerfiDictionary[572].setEnglWord("engineer", "�������", 65);
	/*************** End of init Lesson 65 *****************************************************************/

	/****************** Lesson 66: *************************************************************************/
	MerfiDictionary[573].setEnglWord("shelf", "�����", 66);
	MerfiDictionary[574].setEnglWord("scissors", "�������", 66);								
	MerfiDictionary[575].setEnglWord("a pair of pyjamas", "���� ������", 66);					// ��������
	MerfiDictionary[576].setEnglWord("tights", "��������", 66);	
	MerfiDictionary[577].setEnglWord("ox/oxen", "���/����", 66);
	MerfiDictionary[578].setEnglWord("cactus/cacti", "������/�������", 66);						// ������			
	MerfiDictionary[579].setEnglWord("the native peoples of Mexico", "�������� ������ ������� (���.)", 66);
	MerfiDictionary[580].setEnglWord("cookery book", "���������� �����", 66);
	MerfiDictionary[581].setEnglWord("binoculars", "�������", 66);								// �����������
	MerfiDictionary[582].setEnglWord("headphones", "��������, ���������", 66);
	MerfiDictionary[583].setEnglWord("handy", "�������, �����������", 66);
	MerfiDictionary[584].setEnglWord("be about to", "��� ��� ���������", 66);
	MerfiDictionary[585].setEnglWord("kindergarten", "������� ���", 66);						// �����������
	MerfiDictionary[586].setEnglWord("community", "����������", 66);
	MerfiDictionary[587].setEnglWord("striped", "� �������, ���������", 66);					// �������
	/*************** End of init Lesson 66 *****************************************************************/

	/****************** Lesson 67: *************************************************************************/
	MerfiDictionary[588].setEnglWord("a jug of juice", "������ ����", 67);
	MerfiDictionary[589].setEnglWord("a jar of honey", "������� ����", 67);						// jar
	MerfiDictionary[590].setEnglWord("a bar of soap", "������ ����", 67);
	MerfiDictionary[591].setEnglWord("a loaf of bread", "������� �����", 67);
	MerfiDictionary[592].setEnglWord("a slice of bread", "����� �����", 67);					// �����
	MerfiDictionary[593].setEnglWord("a can of cola", "������� ����", 67);
	MerfiDictionary[594].setEnglWord("a bowl of rice", "����� ����", 67);
	MerfiDictionary[595].setEnglWord("a bag of flour", "����� ����", 67);						// �����
	MerfiDictionary[596].setEnglWord("a bottle of perfume", "������� �����", 67);				// ������
	MerfiDictionary[597].setEnglWord("a packet of onion chips", "����� ������� ������", 67);
	MerfiDictionary[598].setEnglWord("a piece of music", "����������� ������������", 67);
	MerfiDictionary[599].setEnglWord("a kilo of pork", "��������� �������", 67);
	MerfiDictionary[600].setEnglWord("life isn't a piece of cake", "����� �� ������", 67);
	MerfiDictionary[601].setEnglWord("a piece of news", "�������", 67);
	MerfiDictionary[602].setEnglWord("cash", "��������", 67);
	MerfiDictionary[603].setEnglWord("take out garbage", "������ �����", 67);					// ������
	MerfiDictionary[604].setEnglWord("fall in love with", "��������� � (��.)", 67);
	MerfiDictionary[605].setEnglWord("wisdom", "��������", 67);									// ������
	MerfiDictionary[606].setEnglWord("antique forniture", "��������� (��������) ������", 67);	// �����
	MerfiDictionary[607].setEnglWord("mansion", "������, ������", 67);							// �����
	MerfiDictionary[608].setEnglWord("ceiling", "�������", 67);									// �����g
	MerfiDictionary[609].setEnglWord("cereal", "��������, ����", 67);							// ������								
	MerfiDictionary[610].setEnglWord("it's not for nothing", "��� �� � ������", 67);
	MerfiDictionary[611].setEnglWord("scientist", "������", 67);
	MerfiDictionary[612].setEnglWord("violence", "�������, ����������", 67);					// �������
	MerfiDictionary[613].setEnglWord("respect", "��������", 67);
	MerfiDictionary[614].setEnglWord("a tin of tuna", "����� �����", 67);
	/*************** End of init Lesson 67 *****************************************************************/

	/****************** Lesson 68: *************************************************************************/
	MerfiDictionary[615].setEnglWord("cupboard", "�����, �����", 68);							// �����
	MerfiDictionary[616].setEnglWord("coffee pot", "��������", 68);
	MerfiDictionary[617].setEnglWord("inspiration", "�����������, �������������, ����������", 68);
	MerfiDictionary[618].setEnglWord("productive", "������������, ������������", 68);
	MerfiDictionary[619].setEnglWord("opportunity", "�����������, ������� ������", 68);
	MerfiDictionary[620].setEnglWord("sorrow", "������, ����, ��������, ��������", 68);			// �����
	MerfiDictionary[621].setEnglWord("behave", "����� ����, ���������", 68);					// ������
	MerfiDictionary[622].setEnglWord("candies", "�������", 68);
	MerfiDictionary[623].setEnglWord("cognac", "������", 68);									// ������
	MerfiDictionary[624].setEnglWord("a medium roast beef", "�������� ������� �������� (������)", 68);
	MerfiDictionary[625].setEnglWord("allow me a moment", "��������� ���� ����������", 68);
	/*************** End of init Lesson 68 *****************************************************************/
	
	/****************** Lesson 69: *************************************************************************/
	MerfiDictionary[626].setEnglWord("rhythm", "����, �������������", 69);						// �����							
	MerfiDictionary[627].setEnglWord("buzz", "������, �������, ��������, ���, �����", 69);
	MerfiDictionary[628].setEnglWord("settle", "������, ��������, ����������", 69);
	MerfiDictionary[629].setEnglWord("inspire", "�����������, ������������", 69);
	MerfiDictionary[630].setEnglWord("routine", "������, �������, ������", 69);					// �����
	MerfiDictionary[631].setEnglWord("responsibility", "���������������", 69);	
	MerfiDictionary[632].setEnglWord("feel free from", "����������� ������� �� (��.)", 69);
	MerfiDictionary[633].setEnglWord("the countryside", "������� (���.)", 69);
	MerfiDictionary[634].setEnglWord("I would rather to...", "� �� �����..., � �� ��������� (��.)...", 69);
	/*************** End of init Lesson 69 *****************************************************************/

	/****************** Lesson 70: *************************************************************************/
	MerfiDictionary[635].setEnglWord("trumpet", "�����", 70);						// �������												
	MerfiDictionary[636].setEnglWord("immediately", "����������", 70);				// ���������
	MerfiDictionary[637].setEnglWord("be wanted", "�������������", 70);
	MerfiDictionary[638].setEnglWord("draft", "��������, �����", 70);				// ����� �����
	MerfiDictionary[639].setEnglWord("an honor", "�����, ����� (���.)", 70);
	MerfiDictionary[640].setEnglWord("it's about to rain", "���-��� ������ �����", 70);
	MerfiDictionary[641].setEnglWord("musician", "��������", 70);					// ������
	MerfiDictionary[642].setEnglWord("my family and I", "� � ��� �����", 70);
	MerfiDictionary[643].setEnglWord("talented", "�����������", 70);
	/*************** End of init Lesson 70 *****************************************************************/

	/****************** Lesson 71: *************************************************************************/
	MerfiDictionary[644].setEnglWord("take me along with you", "������ ���� � �����", 71);	
	MerfiDictionary[645].setEnglWord("stay out of trouble", "��������� �������� �� �������������", 71);
	MerfiDictionary[646].setEnglWord("stay up late", "�� �������� �� ������", 71);
	MerfiDictionary[647].setEnglWord("afford", "��������� ����, ����� �����������", 71);
	MerfiDictionary[648].setEnglWord("be fired", "���� ���������", 71);
	MerfiDictionary[649].setEnglWord("resident", "���������� ������", 71);			// ��������
	MerfiDictionary[650].setEnglWord("usually", "������ (u...)", 71);		
	/*************** End of init Lesson 71 *****************************************************************/

	/****************** Lesson 72: *************************************************************************/
	MerfiDictionary[651].setEnglWord("forensic", "��������", 72);						// ��������
	MerfiDictionary[652].setEnglWord("forensics", "����������������", 72);				// ���������
	MerfiDictionary[653].setEnglWord("struggle", "������, ������, ���������", 72);
	MerfiDictionary[654].setEnglWord("biology/geography/physics", "��������/���������/������", 72);
	MerfiDictionary[655].setEnglWord("boxing is an Olimpic discipline", "���� - ��� ����������� ���", 72);
	MerfiDictionary[656].setEnglWord("puzzle", "�����������, �������, ����������", 72);
	MerfiDictionary[657].setEnglWord("expression", "���������", 72);
	MerfiDictionary[658].setEnglWord("be considered to be...", "��������� ���...", 72);
	MerfiDictionary[659].setEnglWord("sence of humor", "������� �����", 72);
	MerfiDictionary[660].setEnglWord("quality", "��������", 72);	
	MerfiDictionary[661].setEnglWord("triumph of evil", "��������� ���", 72);			// ������� �� ���
	MerfiDictionary[662].setEnglWord("foreigner", "����������", 72);					// �������
	MerfiDictionary[663].setEnglWord("especially", "��������", 72);
	MerfiDictionary[664].setEnglWord("biathlon", "�������", 72);						// ��������
	MerfiDictionary[665].setEnglWord("European", "��������, �����������", 72);			// �������
	MerfiDictionary[666].setEnglWord("Chinese", "���������", 72);
	MerfiDictionary[667].setEnglWord("Japanese", "��������", 72);
	MerfiDictionary[668].setEnglWord("philosophy", "���������", 72);
	MerfiDictionary[669].setEnglWord("I'll do my best", "� ����� ����������", 72);
	MerfiDictionary[670].setEnglWord("well-wisher", "�������������", 72);
	/*************** End of init Lesson 72 *****************************************************************/

	/****************** Lesson 73: *************************************************************************/
	MerfiDictionary[671].setEnglWord("the Netherlands", "����������", 73);				// ����������		
	MerfiDictionary[672].setEnglWord("the Canary Islands", "��������� �������", 73);	// ������
	MerfiDictionary[673].setEnglWord("the Alps", "�����", 73);							// ����
	MerfiDictionary[674].setEnglWord("the Pacific Ocean", "����� �����", 73);
	MerfiDictionary[675].setEnglWord("the Mediterranean Sea", "����������� ����", 73);	// �������������
	MerfiDictionary[676].setEnglWord("the Suez Canal", "������� �����", 73);			// ���� �����
	MerfiDictionary[677].setEnglWord("Westminster Abbey", "����������� ���������", 73);	// ����������� ���
	MerfiDictionary[678].setEnglWord("London Zoo", "���������� �������", 73);
	MerfiDictionary[679].setEnglWord("Edinburgh Castle", "������������ �����", 73);		// �������� ����
	MerfiDictionary[680].setEnglWord("the Science Museum", "����� �����", 73);
	MerfiDictionary[681].setEnglWord("the Great Wall of China", "������� ��������� �����", 73);
	MerfiDictionary[682].setEnglWord("the Tower of London", "���������� �����", 73);
	MerfiDictionary[683].setEnglWord("misbelief", "�����������, �����", 73);			// ��������
	MerfiDictionary[684].setEnglWord("Argentina", "���������", 73);						// ���������
	MerfiDictionary[685].setEnglWord("Mount Everest", "���� �������", 73);				// �������
	MerfiDictionary[686].setEnglWord("surface", "�����������", 73);						// �����
	MerfiDictionary[687].setEnglWord("sunrise", "������", 73);							// �������
	MerfiDictionary[688].setEnglWord("the Himalayas", "�������", 73);					// ��������
	MerfiDictionary[689].setEnglWord("Antarctica", "����������", 73);					// ���������
	MerfiDictionary[690].setEnglWord("Istanbul", "�������", 73);						// ��������
	MerfiDictionary[691].setEnglWord("the Eiffel Tower", "��������� �����", 73);		// �����
	MerfiDictionary[692].setEnglWord("exhibit", "���������, ����������", 73);			// �������
	MerfiDictionary[693].setEnglWord("exhibition", "��������, �����", 73);				// ��������
	MerfiDictionary[694].setEnglWord("educational institution", "��������������� ����������", 73);
	MerfiDictionary[695].setEnglWord("Saint Sophia Cathedral", "����� ������ �����", 73);// ��������
	MerfiDictionary[696].setEnglWord("exciting", "�������������, �������������", 73);	// ���������
	MerfiDictionary[697].setEnglWord("volcano", "������", 73);							// ��������
	MerfiDictionary[698].setEnglWord("be located", "���� �������������, ��������������", 73);	
	MerfiDictionary[699].setEnglWord("We've been to Lisbon.", "�� ���� � ��������.", 73);	
	/*************** End of init Lesson 73 *****************************************************************/

	/****************** Lesson 74: *************************************************************************/
	MerfiDictionary[700].setEnglWord("That's all right.", "��� � �������.", 74);	
	MerfiDictionary[701].setEnglWord("That's right.", "��� �����.", 74);
	MerfiDictionary[702].setEnglWord("try on", "��������� (��.)", 74);
	MerfiDictionary[703].setEnglWord("actually", "�� ������ ������", 74);
	MerfiDictionary[704].setEnglWord("long to...", "����� ������ ���-�� ������ �������...", 74);
	MerfiDictionary[705].setEnglWord("cowboy", "������", 74);
	MerfiDictionary[706].setEnglWord("awful", "�������", 74);
	MerfiDictionary[707].setEnglWord("Don't even look at...", "���� �� ������ ��...", 74);
	MerfiDictionary[708].setEnglWord("That's true.", "��� ������.", 74);
	MerfiDictionary[709].setEnglWord("in your shoes", "�� ����� �����", 74);
	MerfiDictionary[710].setEnglWord("question", "������", 74);
	/*************** End of init Lesson 74 *****************************************************************/

	/****************** Lesson 75: *************************************************************************/
	MerfiDictionary[711].setEnglWord("the one", "��� �����, ������������", 75);
	MerfiDictionary[712].setEnglWord("swear", "����������, ������, �������, ������������", 75);
	MerfiDictionary[713].setEnglWord("opposite", "��������, ���������������", 75);				// ������
	MerfiDictionary[714].setEnglWord("staff", "��������, ����", 75);							// ����
	MerfiDictionary[715].setEnglWord("violet", "����������", 75);								
	MerfiDictionary[716].setEnglWord("beard", "������", 75);									// ����
	MerfiDictionary[717].setEnglWord("mitten", "�������, ��������", 75);						// ����
	MerfiDictionary[718].setEnglWord("yummy", "���-���, �������, ����������", 75);				// ���
	MerfiDictionary[719].setEnglWord("keep something in mind", "������� ���-�� � ������", 75);
	MerfiDictionary[720].setEnglWord("stripe", "�������", 75);
	/*************** End of init Lesson 75 *****************************************************************/

	/****************** Lesson 76: *************************************************************************/
	MerfiDictionary[721].setEnglWord("biscuit", "�������, ������", 76);							// ������
	MerfiDictionary[722].setEnglWord("suggestion", "�����������", 76);							// ����������
	MerfiDictionary[723].setEnglWord("arrange", "������������, ����������, �����������", 76);	// ������
	MerfiDictionary[724].setEnglWord("nope", "��� (����.)", 76);
	MerfiDictionary[725].setEnglWord("sounds good", "������ �������", 76);
	MerfiDictionary[726].setEnglWord("debt", "����", 76);										// ���
	MerfiDictionary[727].setEnglWord("witness", "���������", 76);
	MerfiDictionary[728].setEnglWord("surprise", "�������", 76);								// �������
	MerfiDictionary[729].setEnglWord("for yesterday", "�� �����", 76);
	/*************** End of init Lesson 76 *****************************************************************/

	/****************** Lesson 77: *************************************************************************/
	MerfiDictionary[730].setEnglWord("puddle", "����", 77);
	MerfiDictionary[731].setEnglWord("successful", "��������", 77);
	MerfiDictionary[732].setEnglWord("freezer", "����������� ������", 77);
	MerfiDictionary[733].setEnglWord("suspect", "�����������", 77);
	MerfiDictionary[734].setEnglWord("pedestrian", "�������", 77);								// ����������
	MerfiDictionary[735].setEnglWord("trace", "����, ���������", 77);
	MerfiDictionary[736].setEnglWord("Is there any milk left in the fridge?", "� ������������ �������� ������?", 77);
	/*************** End of init Lesson 77 *****************************************************************/

	/****************** Lesson 78: *************************************************************************/
	MerfiDictionary[737].setEnglWord("he seems to live in here", "�������, �� ����� �����", 78);
	MerfiDictionary[738].setEnglWord("nobody is perfect", "����� �� ����������", 78);
	MerfiDictionary[739].setEnglWord("in here", "�����, ����", 78);
	MerfiDictionary[740].setEnglWord("It's just fate.", "��� ������ ������ (���, ������).", 78);
	MerfiDictionary[741].setEnglWord("There's nothing left to say.", "������ ������ �������.", 78);
	MerfiDictionary[742].setEnglWord("when it comes to money", "����� ���� ������� �� �����", 78);
	MerfiDictionary[743].setEnglWord("carry", "�����, �������", 78);
	MerfiDictionary[744].setEnglWord("suspicious", "��������������, ������������", 78);			// ��������
	MerfiDictionary[745].setEnglWord("prepare", "��������, ����������, ��������������", 78);
	/*************** End of init Lesson 78 *****************************************************************/

	/****************** Lesson 79: *************************************************************************/
	MerfiDictionary[746].setEnglWord("the middle of nowhere", "�����, ���� ����� ���", 79);
	MerfiDictionary[747].setEnglWord("look around", "����������, �����������", 79);
	MerfiDictionary[748].setEnglWord("secretly", "�����, � �����", 79);
	MerfiDictionary[749].setEnglWord("intelligent", "� ������� �����������, ����������", 79);	// �����������
	MerfiDictionary[750].setEnglWord("fluently", "��������, �����", 79);						// ��������
	MerfiDictionary[751].setEnglWord("I can't give you anything but love.", "� �� ���� ������ ���� ���� ����� �����.", 79);
	MerfiDictionary[752].setEnglWord("Is there something wrong?", "���-�� �� ���?", 79);
	/*************** End of init Lesson 79 *****************************************************************/

	/****************** Lesson 80: *************************************************************************/
	MerfiDictionary[753].setEnglWord("unique", "����������, ������������", 80);
	MerfiDictionary[754].setEnglWord("in its own way", "��-������", 80);
	MerfiDictionary[755].setEnglWord("hit the panic button", "���� ��������� ������", 80);		// ����
	MerfiDictionary[756].setEnglWord("everything is under control", "��� ��� ���������", 80);
	MerfiDictionary[757].setEnglWord("it seems...", "��� �������...", 80);						
	MerfiDictionary[758].setEnglWord("actress", "�������", 80);									// ������
	MerfiDictionary[759].setEnglWord("All I need for Christmas is you.", "������ ��� ��������� (�� ���������) ��� ��.", 80);
	MerfiDictionary[760].setEnglWord("Compared to all people I know...", "�� ��������� �� ����� ������, ���� � ����...", 80);
	MerfiDictionary[761].setEnglWord("exercise", "����������", 80);
	MerfiDictionary[762].setEnglWord("c'mon", "�� ����� (����.)", 80);
	MerfiDictionary[763].setEnglWord("Everybody move your body!", "������� ���!", 80);
	MerfiDictionary[764].setEnglWord("a long way before", "�����", 80);
	/*************** End of init Lesson 80 *****************************************************************/

	/****************** Lesson 81: *************************************************************************/
	MerfiDictionary[765].setEnglWord("none of my friends", "����� �� ���� ������", 81);
	MerfiDictionary[766].setEnglWord("Most people drive too fast.", "����������� ����� ����� ����� ������.", 81);
	MerfiDictionary[767].setEnglWord("all of it", "���� (� ��������)", 81);
	MerfiDictionary[768].setEnglWord("none of them", "�� ���� �� ���, �� ���� �� ���", 81);
	MerfiDictionary[769].setEnglWord("as different as chalk and cheese", "������, ��� ���� � �����", 81);
	MerfiDictionary[770].setEnglWord("chalk", "���", 81);										// ���
	MerfiDictionary[771].setEnglWord("ambition", "�������, ����������, ����", 81);				// ������
	MerfiDictionary[772].setEnglWord("unavailable luxury", "����������� �������", 81);			// ���������(�)� ����(�)��
	MerfiDictionary[773].setEnglWord("advantage", "������������", 81);							// ���������
	MerfiDictionary[774].setEnglWord("app", "���������� (����.)", 81);
	MerfiDictionary[775].setEnglWord("reply", "�����, ��������", 81);							// ������
	// Subject + used to + inginitive: ��������� � ��������
	MerfiDictionary[776].setEnglWord("I used to...", "������ �...(����.��.)", 81);
	MerfiDictionary[777].setEnglWord("courage", "��������, ��������", 81);						// ������
	MerfiDictionary[778].setEnglWord("There were no any doubts", "�� ���� ������� ��������", 81);// �����
	/*************** End of init Lesson 81 *****************************************************************/

	/****************** popular words: *************************************************************************/
	MerfiDictionary[779].setEnglWord("huge influence", "�������� �������, �����������", 500);		// ��������		
	MerfiDictionary[780].setEnglWord("admirable", "��������������, ������������� (a)", 500);		// ���(�)���(�)�
	MerfiDictionary[781].setEnglWord("disappoint", "��������������, ������", 500);					// ���������
	MerfiDictionary[782].setEnglWord("comical", "�������, ��������, ��������", 500);				// �����(�)�
	MerfiDictionary[783].setEnglWord("cheerful", "�������, ������, �������, �����", 500);			// ����(�)�
	MerfiDictionary[784].setEnglWord("dull", "�������, �����, ������, ���������", 500);
	MerfiDictionary[785].setEnglWord("admire", "�����������, ����������", 500);
	// Subject + "to be" + used to + noun: ��������� ���, � ��������, ��� � ����������
	MerfiDictionary[786].setEnglWord("I'm used to pain.", "� ������ � ����.", 500);
	/*************** End of popular words: **********************************************************************/

	/****************** Lesson 82: *************************************************************************/
	MerfiDictionary[787].setEnglWord("neither of my sisters is attractive", "�� ���� �� ���� (����) ������ �� ��������������", 82);
	MerfiDictionary[788].setEnglWord("remarkable", "�������������, ������������ (r)", 82);
	MerfiDictionary[789].setEnglWord("be appropiate for", "���� ���������� ���, ��������������� (��.)", 82);	// ���������
	MerfiDictionary[790].setEnglWord("in my humble opinion", "�� ����� ��������� ������ (IMHO)", 82);
	MerfiDictionary[791].setEnglWord("outstanding", "����������", 82);
	MerfiDictionary[792].setEnglWord("fabulous beast", "����������, ���������, ���������� ��������", 82);		// ��������
	MerfiDictionary[793].setEnglWord("fabulous wealth", "���������, ������������ ���������", 82);				// ���(TH)
	MerfiDictionary[794].setEnglWord("discription", "��������", 82);											// ���������
	MerfiDictionary[795].setEnglWord("either of them will be fine", "���� �� ���� (���� ��, ���� ���) ����� ������", 82);
	/*************** End of init Lesson 82 *****************************************************************/

	/****************** Lesson 83: *************************************************************************/
	MerfiDictionary[796].setEnglWord("almost", "�����", 83);
	MerfiDictionary[797].setEnglWord("necklace", "��������", 83);										// �������
	MerfiDictionary[798].setEnglWord("I'll call you back.", "� ���� ���������.", 83);
	MerfiDictionary[799].setEnglWord("If memory serves me right...", "���� ������ ��� �� ��������...", 83);
	MerfiDictionary[800].setEnglWord("That's too much.", "��� ������� �����.", 83);
	MerfiDictionary[801].setEnglWord("I'm quite sure of it.", "� ������ ������ � ����.", 83);
	MerfiDictionary[802].setEnglWord("Long time no see", "����� �� ��������", 83);						// ���������� ���������
	MerfiDictionary[803].setEnglWord("Why don't we...?", "������ �� ���...?", 83);
	MerfiDictionary[804].setEnglWord("I used to be.", "������ � ���.", 83);
	/*************** End of init Lesson 83 *****************************************************************/

	/****************** Lesson 84: *************************************************************************/
	MerfiDictionary[805].setEnglWord("very few strawberries", "����� ���� ��������", 84);
	MerfiDictionary[806].setEnglWord("a few candles", "������� ������", 84);
	MerfiDictionary[807].setEnglWord("a little/little use", "�������/���� ������", 84);
	MerfiDictionary[808].setEnglWord("yap", "�����, ���������, �������", 84);						// ���
	MerfiDictionary[809].setEnglWord("stubborn", "�������, �������", 84);							// ������
	MerfiDictionary[810].setEnglWord("I feel like...", "� �������� ��� �����, ��� �������...", 84);
	MerfiDictionary[811].setEnglWord("weakness", "��������, ����������", 84);
	MerfiDictionary[812].setEnglWord("old-fashioned", "���������, �����������", 84);				// ������
	MerfiDictionary[813].setEnglWord("clown", "�����, ���, ����", 84);								// �����
	/*************** End of init Lesson 84 *****************************************************************/

	/****************** Lesson 85: *************************************************************************/
	MerfiDictionary[814].setEnglWord("homeless", "���������", 85);
	MerfiDictionary[815].setEnglWord("breakable", "��������", 85);
	MerfiDictionary[816].setEnglWord("for instance", "�������� (for i...)", 85);
	MerfiDictionary[817].setEnglWord("well off", "������������", 85);
	MerfiDictionary[818].setEnglWord("cozy", "������ (c...)", 85);									// �����
	MerfiDictionary[819].setEnglWord("wounded", "��������, ����������", 85);						// ������		
	MerfiDictionary[820].setEnglWord("wound", "����, ������", 85);									// ����
	MerfiDictionary[821].setEnglWord("confident", "���������", 85);
	/*************** End of init Lesson 85 *****************************************************************/

	/****************** Lesson 86: *************************************************************************/
	MerfiDictionary[822].setEnglWord("sudden/suddenly", "�����������/����������", 86);
	MerfiDictionary[823].setEnglWord("heavy/heavily", "�������/������, ������, � ������", 86);
	MerfiDictionary[824].setEnglWord("honestly", "������", 86);
	MerfiDictionary[825].setEnglWord("obviously", "��������", 86);
	MerfiDictionary[826].setEnglWord("journalist", "���������", 86);
	MerfiDictionary[827].setEnglWord("impatient/impatiently", "������������/�����������, �����������", 86);
	MerfiDictionary[828].setEnglWord("gentle/gently", "������/�����", 86);
	MerfiDictionary[829].setEnglWord("love deeply", "������ (�������) ������", 86);
	MerfiDictionary[830].setEnglWord("fortunately", "� �������", 86);
	MerfiDictionary[831].setEnglWord("lately", "�������, � ��������� ����� (l...)", 86);
	/*************** End of init Lesson 86 *****************************************************************/

	/****************** Lesson 87: *************************************************************************/
	MerfiDictionary[832].setEnglWord("Athens", "�����", 87);								// �th���
	MerfiDictionary[833].setEnglWord("worse", "����", 87);
	MerfiDictionary[834].setEnglWord("further/farther", "������ u/a", 87);							// ����� 
	MerfiDictionary[835].setEnglWord("elder child", "������� �������", 87);					// � ����� � �����
	MerfiDictionary[836].setEnglWord("innocent", "��������, �������, �������", 87);			// �������
	MerfiDictionary[837].setEnglWord("juicer", "�������������", 87);
	MerfiDictionary[838].setEnglWord("hairdryer", "���", 87);
	MerfiDictionary[839].setEnglWord("household appliance", "������ ������� �������", 87);	// ��������
	MerfiDictionary[840].setEnglWord("convenient", "�������, ����������", 87);				// ����������	
	MerfiDictionary[841].setEnglWord("You know what?", "� ������ ���?", 87);
	MerfiDictionary[842].setEnglWord("optional", "��������������, ��������������, ���������������", 87);	// ������
	MerfiDictionary[843].setEnglWord("buy a pig in a poke", "������ ���� � �����", 87);		// ���� - �����
	MerfiDictionary[844].setEnglWord("be crazy about...", "���������� �� (��)...", 87);
	/*************** End of init Lesson 87 *****************************************************************/
	/*
	��������: 
	1) older � elder ���� � �� ��. �� elder ����������� � ����� � �����.
	elder ������ ������������ ��� ����������������:
	- He is older. (�� ������)
	- He is elder child. (ERROR: He is elder.)
	
	2) farther � further: ���� � �� ��, ����� ������� � ��������� (������).
	�� � further ���� ������ ��������: ����������, ���������� (������� ���������������)
	We were not happy to get the further task. �� �� ������������ ��������� ��������������� �������.
	*/

	/****************** Lesson 88: *************************************************************************/
	MerfiDictionary[845].setEnglWord("district", "�����, �������", 88);	
	MerfiDictionary[846].setEnglWord("wake up", "����������", 88);
	MerfiDictionary[847].setEnglWord("Asia", "����", 88);										// ����
	MerfiDictionary[848].setEnglWord("fascinating", "��������������, ��������������� (f)", 88);		// �����������
	MerfiDictionary[849].setEnglWord("author", "�����", 88);									// ����
	MerfiDictionary[850].setEnglWord("responsible", "�������������, ������������", 88);
	MerfiDictionary[851].setEnglWord("talkative", "���������, �������������", 88);				// �������
	MerfiDictionary[852].setEnglWord("ridiculous", "�������, �������, ������������", 88);		// ����������
	MerfiDictionary[853].setEnglWord("She cooks worse than him.", "��� ������� ���� ���� (����.).", 88);
	MerfiDictionary[854].setEnglWord("She was taller than he was.", "��� ���� ���� ���� (��.).", 88);
	MerfiDictionary[855].setEnglWord("the Mississippi", "��������", 88);
	MerfiDictionary[856].setEnglWord("victim", "������", 88);
	MerfiDictionary[857].setEnglWord("in gratitude", "� �������������", 88);					// ���������
	MerfiDictionary[858].setEnglWord("Hell is empty, and all the devils are here.", "�� ����, � ��� ���� �����.", 88);
	MerfiDictionary[859].setEnglWord("undying", "������", 88);
	/*************** End of init Lesson 88 *****************************************************************/

	/****************** Lesson 89: *************************************************************************/
	MerfiDictionary[860].setEnglWord("She's not as old as him.", "��� �� ����� ������, ��� �� (����.).", 89);
	MerfiDictionary[861].setEnglWord("The weather is the same as yesterday.", "������ ����� �� ��� �����.", 89);
	MerfiDictionary[862].setEnglWord("as brave as a lion", "�������, ��� ���", 89);
	MerfiDictionary[863].setEnglWord("spy", "������", 89);
	MerfiDictionary[864].setEnglWord("He's not as stupid as it seems.", "�� �� ����� ������, ��� �������.", 89);
	MerfiDictionary[865].setEnglWord("gifted", "���������", 89);
	MerfiDictionary[866].setEnglWord("The Devil isn't as black as he is painted.", "�� ��� ������� ����, ��� ��� ������.", 89);
	MerfiDictionary[867].setEnglWord("it's unfair", "��� �������������", 89);
	MerfiDictionary[868].setEnglWord("creative", "����������", 89);
	MerfiDictionary[869].setEnglWord("pretend", "������������, ������ ��� (p)", 89);
	MerfiDictionary[870].setEnglWord("His car is the same as mine.", "��� ������ ����� �� ��� ��� (����.).", 89);
	MerfiDictionary[871].setEnglWord("income", "�����, �������", 89);								// �����
	MerfiDictionary[872].setEnglWord("salary", "��������", 89);										
	MerfiDictionary[873].setEnglWord("employee", "��������, ��������", 89);							// �������
	/*************** End of init Lesson 89 *****************************************************************/

	/****************** Lesson 90: *************************************************************************/
	MerfiDictionary[874].setEnglWord("the worst", "������", 90);
	MerfiDictionary[875].setEnglWord("the solar system", "��������� �������", 90);
	MerfiDictionary[876].setEnglWord("Jupiter", "������", 90);										// ��������
	MerfiDictionary[877].setEnglWord("veteran of WW2", "������� ����� ������� ����� (����.)", 90);	// �������
	MerfiDictionary[878].setEnglWord("the furthest row in the hall", "����� ������� ��� � ����", 90);
	MerfiDictionary[879].setEnglWord("tomb", "��������, ������, �����, ��������", 90);				// ���
	MerfiDictionary[880].setEnglWord("deque", "������������ �������", 90);
	MerfiDictionary[881].setEnglWord("queue", "�������, �����", 90);								// ��
	MerfiDictionary[882].setEnglWord("heap", "����, �����, �����", 90);
	MerfiDictionary[883].setEnglWord("derived", "�����������, ���������", 90);						// �������
	MerfiDictionary[884].setEnglWord("the tomb of Alexander the Great", "�������� ���������� ������������", 90);
	MerfiDictionary[885].setEnglWord("easy peasy lemon squeezy", "����� �������� (�����)", 90);
	MerfiDictionary[886].setEnglWord("as easy as a pie", "����� ��������", 90);
	/*************** End of init Lesson 90 *****************************************************************/

	/****************** Lesson 91: *************************************************************************/
	MerfiDictionary[887].setEnglWord("conversation", "������, ��������", 91);
	MerfiDictionary[888].setEnglWord("I've had enough.", "� ���� ������, ��� ����������.", 91);
	MerfiDictionary[889].setEnglWord("pullover", "�������, ������", 91);								// �������
	MerfiDictionary[890].setEnglWord("That guy is angry enough.", "���� ������ ���������� ���.", 91);	// �����: ����� ���������������
	MerfiDictionary[891].setEnglWord("patience", "��������", 91);
	MerfiDictionary[892].setEnglWord("At your absolute best...", "� ����� ��������� ����...", 91);
	MerfiDictionary[893].setEnglWord("Someday you will be old enough...", "������� �� ���������� ���������...", 91);
	MerfiDictionary[894].setEnglWord("Be strong enough to let go.", "���� ���������� �������, ����� ���������.", 91);
	/*************** End of init Lesson 91 *****************************************************************/

	/****************** Lesson 92: *************************************************************************/
	MerfiDictionary[895].setEnglWord("Ann studies too much.", "��� ������� ����� ������.", 92);
	MerfiDictionary[896].setEnglWord("I'm too tired to go out.", "� ������� �����, ����� �������� �� �����.", 92);
	MerfiDictionary[897].setEnglWord("He's far too sick.", "�� ����� (��������) ������� �����.", 92);
	MerfiDictionary[898].setEnglWord("looks like...", "������ �� ��, �������� ��� ���-��...", 92);
	MerfiDictionary[899].setEnglWord("the Bible", "������", 92);
	MerfiDictionary[900].setEnglWord("So be it.", "�� ����� ���.", 92);
	MerfiDictionary[901].setEnglWord("from zero to hero", "�� ����� � �����", 92);
	MerfiDictionary[902].setEnglWord("fate", "������, ���", 92);
	MerfiDictionary[903].setEnglWord("no offence", "��� ����", 92);										// �����
	MerfiDictionary[904].setEnglWord("Let's talk heart to heart.", "����� �������� �� �����.", 92);
	MerfiDictionary[905].setEnglWord("get off", "������", 92);
	MerfiDictionary[906].setEnglWord("at dawn", "�� ��������", 92);										// ���/���
	/*************** End of init Lesson 92 *****************************************************************/

	/****************** Lesson 93: *************************************************************************/
	MerfiDictionary[907].setEnglWord("Smoking is strictly forbidden in the public areas.", "������� ������ ��������� � ������������ ������.", 93);
	MerfiDictionary[908].setEnglWord("She was the cutest baby ever.", "��� ���� ����� ����� �������� �� ����.", 93);
	MerfiDictionary[909].setEnglWord("It was good to accompany you.", "���� ������� ������������ ����.", 93);
	MerfiDictionary[910].setEnglWord("reveal the feelings", "���������� � ��������", 93);
	MerfiDictionary[911].setEnglWord("It's illegal to buy drugs.", "��������� �������� ���������.", 93);	// ����(�)�
	MerfiDictionary[912].setEnglWord("though", "����", 93);
	MerfiDictionary[913].setEnglWord("subject", "����������", 93);
	MerfiDictionary[914].setEnglWord("verb", "������, ���������", 93);
	MerfiDictionary[915].setEnglWord("restaurant", "��������", 93);								// ���������
	MerfiDictionary[916].setEnglWord("injure", "������, ���������, �������", 93);				// �����
	MerfiDictionary[917].setEnglWord("bearly", "����, ���-���, ����", 93);						// ��(�)��
	MerfiDictionary[918].setEnglWord("forbid", "���������", 93);								// ��(�)���
	MerfiDictionary[919].setEnglWord("be abroad", "���� �� ��������", 93);
	MerfiDictionary[920].setEnglWord("invitation", "�����������", 93);							// ���������
	MerfiDictionary[921].setEnglWord("accompany", "������������, ���������������", 93);			// ��������
	MerfiDictionary[922].setEnglWord("exception", "����������, ������ ��������", 93);			// �������
	/*************** End of init Lesson 93 *****************************************************************/

	/****************** Lesson 94: *************************************************************************/
	MerfiDictionary[923].setEnglWord("I never forgive my enemies.", "� ������� �� ������ ����� ������", 94);
	MerfiDictionary[924].setEnglWord("enemy", "����", 94);										// �����
	MerfiDictionary[925].setEnglWord("rarely", "����� (r)", 94);								// �����
	MerfiDictionary[926].setEnglWord("burger", "���������, ������", 94);						// �(�)���
	MerfiDictionary[927].setEnglWord("expel", "���������", 94);									// ������
	MerfiDictionary[928].setEnglWord("I still haven't seen him.", "� ��� ��� �� ����� ���.", 94);	// ����������
	MerfiDictionary[929].setEnglWord("grade", "������, ����, �������", 94);
	MerfiDictionary[930].setEnglWord("They all live in here.", "��� ��� ����� �����.", 94);
	/*************** End of init Lesson 94 *****************************************************************/

	/****************** Lesson 95: *************************************************************************/
	MerfiDictionary[923].setEnglWord("I haven't had breakfast yet.", "� ��� ��� �� ���������.", 95);
	MerfiDictionary[923].setEnglWord("He's still out.", "�� ��� ��� �� ���� (�������).", 95);
	MerfiDictionary[923].setEnglWord("get separated", "���������, ����������", 95);
	MerfiDictionary[923].setEnglWord("What's going on in the world?", "��� ���������� � ����?", 95);
	MerfiDictionary[923].setEnglWord("nothing unusual", "������ ����������", 95);
	MerfiDictionary[923].setEnglWord("plenty of problems", "����� (����������, �������) �������", 95);
	MerfiDictionary[923].setEnglWord("manage", "����������, ���������, �����������", 95);
	MerfiDictionary[923].setEnglWord("We still haven't told him.", "�� ��� ��� �� �������.", 95);
	/*************** End of init Lesson 95 *****************************************************************/

	/****************** Lesson 96: *************************************************************************/
	MerfiDictionary[924].setEnglWord("postcard", "��������", 96);
	MerfiDictionary[925].setEnglWord("recipe", "������", 96);									// ������
	MerfiDictionary[926].setEnglWord("request to the department", "������ � �����������", 96);
	MerfiDictionary[927].setEnglWord("instructions", "����������", 96);
	MerfiDictionary[928].setEnglWord("data", "����������, ������", 96);							// �����
	MerfiDictionary[929].setEnglWord("lend", "���������� (����-��)", 96);
	MerfiDictionary[930].setEnglWord("Give it to me.", "��� ��� ���.", 96);
	MerfiDictionary[931].setEnglWord("lend", "���������� (����-��)", 96);
	MerfiDictionary[932].setEnglWord("pass", "��������", 95);
	/*************** End of init Lesson 96 *****************************************************************/

	/****************** Lesson 97: *************************************************************************/
	MerfiDictionary[933].setEnglWord("To be or not to be, that is the question", "���� ��� �� ����, ��� � ��� ������.", 97);
	MerfiDictionary[934].setEnglWord("conjunction", "�������", 97);			// ���������
	MerfiDictionary[935].setEnglWord("comma", "�������", 97);
	MerfiDictionary[936].setEnglWord("at the same time", "������������, � �� �� ����� �����", 97);
	MerfiDictionary[937].setEnglWord("stay awake", "�������������, �� �������� �����", 97);
	MerfiDictionary[938].setEnglWord("be free but not wild", "���� ���������, �� �� �����", 97);
	MerfiDictionary[939].setEnglWord("condenced milk", "�������� ������", 97);
	MerfiDictionary[940].setEnglWord("intend", "������������, ����������", 97);
	MerfiDictionary[941].setEnglWord("act confidently", "����������� ��������", 97);
	MerfiDictionary[942].setEnglWord("be on the right way", "���� �� ���������� ����", 97);
	MerfiDictionary[943].setEnglWord("be in a good fit", "���� � ������� �����", 97);
	/*************** End of init Lesson 97 *****************************************************************/

	/****************** Lesson 98: *************************************************************************/
	MerfiDictionary[944].setEnglWord("When it comes to me...", "����� ���� ������� �� ����...", 98);
	MerfiDictionary[945].setEnglWord("How come?", "��� ���?", 98);
	MerfiDictionary[946].setEnglWord("I bite my bottom lip when I feel nervous.", "� ����� ���� ������� ����, ����� � ���������.", 98);
	MerfiDictionary[947].setEnglWord("feel nervous", "����������", 98);
	MerfiDictionary[948].setEnglWord("Cuba", "����", 98);							// �����
	MerfiDictionary[949].setEnglWord("perfection", "������������", 98);				// ��������
	MerfiDictionary[950].setEnglWord("If there is a cause, there is an effect.", "���� ���� �������, �� ���� � ���������", 98);
	MerfiDictionary[951].setEnglWord("oversleep", "��������", 98);
	MerfiDictionary[952].setEnglWord("dangerous", "�������", 98);
	MerfiDictionary[953].setEnglWord("set an alarm clock", "���������� ��������� (�����.)", 98);
	/*************** End of init Lesson 98 *****************************************************************/

	/****************** Lesson 99: *************************************************************************/
	MerfiDictionary[954].setEnglWord("If I go there, I'll pick you up.", "���� � ����� ����, � ���� �������.", 99);
	MerfiDictionary[955].setEnglWord("If I'm a mother...", "���� � ����� �����...", 99);
	MerfiDictionary[956].setEnglWord("mustache", "���", 99);
	MerfiDictionary[957].setEnglWord("shave off", "������", 99);
	MerfiDictionary[958].setEnglWord("Mom will be angry if I am late.", "���� �����������, ���� � �������.", 99);
	MerfiDictionary[959].setEnglWord("When pigs fly...", "����� ��� �� ���� ��������...", 99);
	MerfiDictionary[960].setEnglWord("at once", "�����, ���������", 99);
	MerfiDictionary[961].setEnglWord("I won't do anything if you don't help me.", "� �� ���� ������ ������, ���� �� ��� �� ��������.", 99);
	/*************** End of init Lesson 99 *****************************************************************/

	/****************** Lesson 100: *************************************************************************/
	MerfiDictionary[962].setEnglWord("I'd help you if I could.", "� �� ����� ����, ���� ���.", 100);
	MerfiDictionary[963].setEnglWord("If I were you...", "���� �� � ��� �� ����� �����...", 100);			
	MerfiDictionary[964].setEnglWord("If I had the money, I would buy...", "���� �� � ���� ���� ������, � ��...", 100);
	MerfiDictionary[965].setEnglWord("If I new the answer, I would...", "���� �� � ���� �����, � ��...", 100);
	MerfiDictionary[966].setEnglWord("If I had time/If I have time", "���� �� � ���� ���� �����/���� � ���� ����� �����", 100);
	MerfiDictionary[967].setEnglWord("If I can/If I could", "���� � �����/���� �� � ���", 100);
	MerfiDictionary[968].setEnglWord("If I were president...", "���� �� � ��� �����������...", 100);
	MerfiDictionary[969].setEnglWord("If I liked pizza, I would order it.", "���� �� � ����� �����, � �� ������� ��.", 100);	
	MerfiDictionary[970].setEnglWord("rival", "��������, �����������", 100);					// ����(�)�
	MerfiDictionary[971].setEnglWord("hurry up", "����������, ���������������", 100);
	MerfiDictionary[972].setEnglWord("be on time", "���� �������", 100);
	MerfiDictionary[973].setEnglWord("giggle", "��������, ���������", 100);						// ����
	MerfiDictionary[974].setEnglWord("instead of...", "� �����...", 100);
	MerfiDictionary[975].setEnglWord("cope with", "����������� (��)", 100);						// ����
	MerfiDictionary[976].setEnglWord("hesitate", "����������, ����������,�����������", 100);	// ��������
	MerfiDictionary[977].setEnglWord("ill-mannered", "�������������, � ������� ��������", 100);	// ��������
	MerfiDictionary[978].setEnglWord("poison", "��, ��������", 100);
	MerfiDictionary[979].setEnglWord("If you were my wife...", "���� �� �� ���� ���� �����...", 100);
	MerfiDictionary[980].setEnglWord("loan", "�����, ������", 100);								// ����
	MerfiDictionary[981].setEnglWord("shy", "�����������, �������������", 100);					
	/*************** End of init Lesson 100 *****************************************************************/

	/****************** Lesson 101: *************************************************************************/
	MerfiDictionary[982].setEnglWord("thief", "���", 101);
	MerfiDictionary[983].setEnglWord("The man who called...", "�������, ������� ������...", 101);
	MerfiDictionary[984].setEnglWord("A thief is a person who steals things.", "��� ��� ��������, ������� ������� ����.", 101);
	MerfiDictionary[985].setEnglWord("machine", "������", 101);
	MerfiDictionary[986].setEnglWord("A thing that/which...", "����, ������� (t/w)", 101);
	MerfiDictionary[987].setEnglWord("investigation", "�������������, ���������", 101);
	MerfiDictionary[988].setEnglWord("lead", "�����, ���������, ������", 101);
	MerfiDictionary[989].setEnglWord("blunt pencil", "����� (������) ��������", 101);
	MerfiDictionary[990].setEnglWord("avenge", "������", 101);									// ������
	MerfiDictionary[991].setEnglWord("own", "�������", 101);
	MerfiDictionary[992].setEnglWord("pavement", "�������, ��������", 101);						// ��������
	/*************** End of init Lesson 101 *****************************************************************/

	/****************** Lesson 102: *************************************************************************/
	MerfiDictionary[993].setEnglWord("I like the film I saw yesterday.", "��� �������� �����, ������� � ��������� �����.", 102);
	MerfiDictionary[994].setEnglWord("...the money Kate won.", "...������, ������� ���� ��������.", 102);
	MerfiDictionary[995].setEnglWord("...the books you wanted.", "...�����, ������� �� �����.", 102);
	MerfiDictionary[996].setEnglWord("...the people we met.", "...����, ������� �� ����������.", 102);
	MerfiDictionary[997].setEnglWord("The room I was led in was dark.", "�������, � ������� ���� ����� ���� ������.", 102);
	MerfiDictionary[998].setEnglWord("awesome", "�����������, �����������, ���������� � ������.", 102);	// ����
	MerfiDictionary[999].setEnglWord("...the doctor I visit twice a month.", "...������, �������� � ������� ������ � �����.", 102);
	MerfiDictionary[1000].setEnglWord("...the food you cook.", "...���, ������� �� ��������.", 102);
	MerfiDictionary[1001].setEnglWord("tasteless", "����������", 102);
	MerfiDictionary[1002].setEnglWord("defense", "������, �������", 102);								// ������
	/*************** End of init Lesson 102 *****************************************************************/

	/****************** Lesson 103: *************************************************************************/
	MerfiDictionary[1003].setEnglWord("at Easter", "�� ����� (��.)", 103);
	MerfiDictionary[1004].setEnglWord("bowling", "�������", 103);										// ������
	MerfiDictionary[1005].setEnglWord("at noon", "� �������", 103);
	MerfiDictionary[1006].setEnglWord("in the future", "� �������", 103);
	MerfiDictionary[1007].setEnglWord("Don't go out at night.", "�� ������ �� ����� ����.", 103);
	MerfiDictionary[1008].setEnglWord("at 10 in the evening on Monday", "� 10 ������� � �����������", 103);
	/*************** End of init Lesson 103 *****************************************************************/

	/****************** Lesson 104: *************************************************************************/
	MerfiDictionary[1009].setEnglWord("until/till", "���� (.../...)", 104);
	MerfiDictionary[1010].setEnglWord("from time to time", "����� �� �������", 104);
	MerfiDictionary[1011].setEnglWord("walk to work", "��� (w) �� ������", 104);
	MerfiDictionary[1012].setEnglWord("recover", "���������������, ���������������", 104);
	MerfiDictionary[1013].setEnglWord("for the rest of your life", "�� ����� ����� �����", 104);
	MerfiDictionary[1014].setEnglWord("approval", "���������", 104);									// �����(�)�
	MerfiDictionary[1015].setEnglWord("Stay here till I come back.", "��������� �����, ���� � �� �������.", 104);
	/*************** End of init Lesson 104 *****************************************************************/


	/*
/*
*poke
* 
* destiny
	//urge
	creepy�
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

// ������� ���������� ������� ������� ���� (������� EnglishWord) ����������
void initDifficultMerfiDictionary(EnglishWord* MerfiDictionary)
{
	MerfiDictionary[0].setEnglWord("designer", "��������", 1);					// �������
	MerfiDictionary[1].setEnglWord("stranger", "����������", 6);
	MerfiDictionary[2].setEnglWord("decision", "�������", 11);
	MerfiDictionary[3].setEnglWord("jubilee", "������", 20);					// �������
	MerfiDictionary[4].setEnglWord("vehicle", "������������ ��������", 20);	// �����
	MerfiDictionary[5].setEnglWord("experience", "����", 24);					// ����������
	MerfiDictionary[6].setEnglWord("attend", "��������", 26);
	MerfiDictionary[7].setEnglWord("astronaut", "���������", 26);				// ��������
	MerfiDictionary[8].setEnglWord("towel", "���������", 500);				// ����� ���� (� ����� ���)
	MerfiDictionary[9].setEnglWord("yield", "�����������, ���������, ������ �����)", 500);	// ����
	MerfiDictionary[10].setEnglWord("envelope", "�������", 500);		// ��������
	MerfiDictionary[11].setEnglWord("definitely", "�����������, ����������, �����", 32);
	MerfiDictionary[12].setEnglWord("to be honest", "���� ������", 34);
	MerfiDictionary[13].setEnglWord("That would be very kind of you.", "��� ���� �� ����� ���� � ����� �������.", 34);
	MerfiDictionary[14].setEnglWord("a hell of a lot of...", "��������� �����...", 36);
	MerfiDictionary[15].setEnglWord("be retired", "���� �� ������", 36);							// ������
	MerfiDictionary[16].setEnglWord("unfortunately", "� ��������", 37);
	MerfiDictionary[17].setEnglWord("increase of prices", "��������� ���", 38);					// ������
	MerfiDictionary[18].setEnglWord("positively", "������������, ����������, ����������", 40);		// ���������
	MerfiDictionary[19].setEnglWord("expectation", "��������, �������", 40);						// �����������		
	MerfiDictionary[20].setEnglWord("necessary", "����������", 40);
	MerfiDictionary[21].setEnglWord("run the something", "��������� ���-��, ������� �� ���-��", 42);
	MerfiDictionary[22].setEnglWord("have nothing to do with", "�� ����� ������ ������ �, ����� �� ��������� �", 43);
	MerfiDictionary[23].setEnglWord("lantern", "������", 500);										// ������, �����
	MerfiDictionary[24].setEnglWord("fragrance", "������", 500);									// ���������
	MerfiDictionary[25].setEnglWord("wish for happiness", "������ �������, ���������� � �������", 46);
	MerfiDictionary[26].setEnglWord("accountant", "���������", 47);							// ���������
	MerfiDictionary[27].setEnglWord("hold a position", "�������� ���������", 47);
	MerfiDictionary[28].setEnglWord("well-paid", "������������������", 47);
	MerfiDictionary[29].setEnglWord("for sure", "���������, ����������", 49);
	MerfiDictionary[30].setEnglWord("get along with", "������, ���� � ������� ���������� (��)", 49);
	MerfiDictionary[31].setEnglWord("till the age of eight", "�� ������ ���", 50);
	MerfiDictionary[32].setEnglWord("suggest", "����������, ����������", 52);							// �������
	MerfiDictionary[33].setEnglWord("reward", "�������, ��������������, ����������", 52);				// �����
	MerfiDictionary[34].setEnglWord("procrastinate", "�������, �����������, ����������� �� �����", 52);// �������������
	MerfiDictionary[35].setEnglWord("applaud", "������������", 52);									// �����
	MerfiDictionary[36].setEnglWord("confidently", "��������, ��������� (���� �����)", 53);			// �����������
	MerfiDictionary[37].setEnglWord("apologize", "����������, ������� ��������", 53);					// ����������
	MerfiDictionary[38].setEnglWord("self-confidently", "������������", 53);							// ����-�����������
	MerfiDictionary[38].setEnglWord("It's worth that.", "��� ���� �����.", 54);						// ���									
	MerfiDictionary[39].setEnglWord("get used to", "���������� �, ������������ (��)", 54);
	MerfiDictionary[40].setEnglWord("pay them a visit", "������� �� �����", 54);
	MerfiDictionary[41].setEnglWord("long for", "������� � ����������, ���������", 54);
	MerfiDictionary[42].setEnglWord("take a photogragh", "����������������, ������� ������", 57);
	MerfiDictionary[43].setEnglWord("do a research", "��������� ������������", 57);
	MerfiDictionary[44].setEnglWord("do repairs", "���������� ��������, ��������", 57);		
	MerfiDictionary[45].setEnglWord("heart diseases", "������� ������", 58);					// �����
	MerfiDictionary[46].setEnglWord("have a familiar ring", "������� �������", 58);			// ������
	MerfiDictionary[47].setEnglWord("work long hours", "�������� �����������", 58);
	MerfiDictionary[48].setEnglWord("give up the idea", "���������� �� ���� (����������)", 58);
	MerfiDictionary[49].setEnglWord("be alert", "���� ������", 58);							// ���� (�������, ����������)
	MerfiDictionary[50].setEnglWord("in amazement", "� ����������, ����������", 59);			// ���������
	MerfiDictionary[51].setEnglWord("adjust", "������������, �������������, ��������� � �������", 59);
	MerfiDictionary[52].setEnglWord("distinctly", "���������, �����", 59);						// ����������
	MerfiDictionary[53].setEnglWord("in order to", "��� ����, �����", 60);
	MerfiDictionary[54].setEnglWord("daughter", "����", 60);
	MerfiDictionary[55].setEnglWord("neighbor", "�����", 60);
	MerfiDictionary[56].setEnglWord("have a crash on", "���������, ����������� �", 60);
	MerfiDictionary[57].setEnglWord("disturb", "����������, ���������, ���������� �������", 500);	// �����
	MerfiDictionary[58].setEnglWord("deserve", "�����������, ���� ���������", 500);					// ����
	MerfiDictionary[59].setEnglWord("defeat", "���������, �������, �������� ���������", 500);		// �����
	MerfiDictionary[60].setEnglWord("grimly", "�������, ����������, ������", 500);
	MerfiDictionary[61].setEnglWord("exactly", "�����, ������, �����, ���������� �����", 500);		// ��������		
	MerfiDictionary[62].setEnglWord("sarcastically", "�����������", 61);							// �����������
	MerfiDictionary[63].setEnglWord("anxious", "���������, �����������", 61);						// �������
	MerfiDictionary[64].setEnglWord("quantity", "����������", 61);									// ��������
	MerfiDictionary[65].setEnglWord("", "", 63);
	MerfiDictionary[66].setEnglWord("psychologist", "��������", 63);								// ������������
	MerfiDictionary[67].setEnglWord("A cat prefers walking by itself.", "����� ������������ ������ ���� �� ����.", 63);							// ������������
	MerfiDictionary[68].setEnglWord("colleague", "�������", 64);								// �����
	MerfiDictionary[69].setEnglWord("approve", "��������, ����������", 64);
	MerfiDictionary[70].setEnglWord("succeed", "�����������, ����� �����", 65);
	MerfiDictionary[71].setEnglWord("coroner", "�������������", 65);
	MerfiDictionary[72].setEnglWord("engineer", "�������", 65);
	MerfiDictionary[73].setEnglWord("scissors", "�������", 66);
	MerfiDictionary[74].setEnglWord("a pair of pyjamas", "���� ������", 66);					// ��������
	MerfiDictionary[75].setEnglWord("life isn't a piece of cake", "����� �� ������", 67);
	MerfiDictionary[76].setEnglWord("ceiling", "�������", 67);									// �����g
	MerfiDictionary[77].setEnglWord("cereal", "��������, ����", 67);							// ������								
	MerfiDictionary[78].setEnglWord("it's not for nothing", "��� �� � ������", 67);
	MerfiDictionary[79].setEnglWord("scientist", "������", 67);
	MerfiDictionary[80].setEnglWord("violence", "�������, ����������", 67);					// �������
	MerfiDictionary[81].setEnglWord("rhythm", "����, �������������", 69);						// �����							
	MerfiDictionary[82].setEnglWord("I would rather to...", "� �� �����..., � �� ��������� (��.)...", 69);
	MerfiDictionary[83].setEnglWord("it's about to rain", "���-��� ������ �����", 70);
	MerfiDictionary[84].setEnglWord("take me along with you", "������ ���� � �����", 71);
	MerfiDictionary[85].setEnglWord("stay out of trouble", "��������� �������� �� �������������", 71);
	MerfiDictionary[86].setEnglWord("stay up late", "�� �������� �� ������", 71);
	MerfiDictionary[87].setEnglWord("afford", "��������� ����, ����� �����������", 71);
	MerfiDictionary[88].setEnglWord("be considered to be...", "��������� ���...", 72);
	MerfiDictionary[89].setEnglWord("quality", "��������", 72);
	MerfiDictionary[90].setEnglWord("triumph of evil", "��������� ���", 72);			// ������� �� ���
	MerfiDictionary[91].setEnglWord("foreigner", "����������", 72);					// �������
	MerfiDictionary[92].setEnglWord("especially", "��������", 72);
	MerfiDictionary[93].setEnglWord("I'll do my best", "� ����� ����������", 72);
	MerfiDictionary[94].setEnglWord("the Mediterranean Sea", "����������� ����", 73);	// �������������
	MerfiDictionary[95].setEnglWord("Westminster Abbey", "����������� ���������", 73);	// ����������� ���
	MerfiDictionary[96].setEnglWord("Edinburgh Castle", "������������ �����", 73);		// �������� ����
	MerfiDictionary[97].setEnglWord("the Himalayas", "�������", 73);					// ��������
	MerfiDictionary[98].setEnglWord("exciting", "�������������, �������������", 73);	// ���������
	MerfiDictionary[99].setEnglWord("actually", "�� ������ ������", 74);
	MerfiDictionary[100].setEnglWord("long to...", "����� ������ ���-�� ������ �������...", 74);
	MerfiDictionary[101].setEnglWord("arrange", "������������, ����������, �����������", 76);	// ������
	MerfiDictionary[102].setEnglWord("successful", "��������", 77);
	MerfiDictionary[103].setEnglWord("", "", 77);
	MerfiDictionary[104].setEnglWord("suspect", "�����������", 77);
	MerfiDictionary[105].setEnglWord("pedestrian", "�������", 77);								// ����������
	MerfiDictionary[106].setEnglWord("in here", "�����, ����", 78);
	MerfiDictionary[107].setEnglWord("suspicious", "��������������, ������������", 78);			// ��������
	MerfiDictionary[108].setEnglWord("exercise", "����������", 80);
	MerfiDictionary[109].setEnglWord("a long way before", "�����", 80);
	MerfiDictionary[110].setEnglWord("unavailable luxury", "����������� �������", 81);			// ���������(�)� ����(�)��
	MerfiDictionary[111].setEnglWord("advantage", "������������", 81);							// ���������
	MerfiDictionary[112].setEnglWord("courage", "��������, ��������", 81);						// ������
	MerfiDictionary[113].setEnglWord("admirable", "��������������, ������������� (a)", 500);		// ���(�)���(�)�
	MerfiDictionary[114].setEnglWord("disappoint", "��������������, ������", 500);					// ���������
	MerfiDictionary[115].setEnglWord("remarkable", "�������������, ������������ (r)", 82);
	MerfiDictionary[116].setEnglWord("be appropiate for", "���� ���������� ���, ��������������� (��.)", 82);	// ���������
	MerfiDictionary[117].setEnglWord("outstanding", "����������", 82);
	MerfiDictionary[118].setEnglWord("fabulous wealth", "���������, ������������ ���������", 82);				// ���(TH)
	MerfiDictionary[119].setEnglWord("discription", "��������", 82);											// ���������
	MerfiDictionary[120].setEnglWord("either of them will be fine", "���� �� ���� (���� ��, ���� ���) ����� ������", 82);
	MerfiDictionary[121].setEnglWord("If memory serves me right...", "���� ������ ��� �� ��������...", 83);
	MerfiDictionary[122].setEnglWord("I'm quite sure of it.", "� ������ ������ � ����.", 83);
	MerfiDictionary[123].setEnglWord("Long time no see", "����� �� ��������", 83);								// ���������� ���������
	MerfiDictionary[124].setEnglWord("very few strawberries", "����� ���� ��������", 84);
	MerfiDictionary[125].setEnglWord("a few candles", "������� ������", 84);
	MerfiDictionary[126].setEnglWord("yap", "�����, ���������, �������", 84);									// ���
	MerfiDictionary[127].setEnglWord("stubborn", "�������, �������", 84);										// ������
	MerfiDictionary[128].setEnglWord("heavy/heavily", "�������/������, ������, � ������", 86);
	MerfiDictionary[129].setEnglWord("honestly", "������", 86);
	MerfiDictionary[130].setEnglWord("fortunately", "� �������", 86);
	MerfiDictionary[131].setEnglWord("innocent", "��������, �������, �������", 87);			// �������
	MerfiDictionary[132].setEnglWord("hairdryer", "���", 87);
	MerfiDictionary[133].setEnglWord("household appliance", "������ ������� �������", 87);	// ��������
	MerfiDictionary[134].setEnglWord("convenient", "�������, ����������", 87);				// ����������	
	MerfiDictionary[135].setEnglWord("be crazy about...", "���������� �� (��)...", 87);
	MerfiDictionary[136].setEnglWord("district", "�����, �������", 88);
	MerfiDictionary[137].setEnglWord("fascinating", "��������������, ��������������� (f)", 88);	// �����������
	MerfiDictionary[138].setEnglWord("author", "�����", 88);									// ����
	MerfiDictionary[139].setEnglWord("responsible", "�������������, ������������", 88);
	MerfiDictionary[140].setEnglWord("talkative", "���������, �������������", 88);				// �������
	MerfiDictionary[141].setEnglWord("ridiculous", "�������, �������, ������������", 88);		// ����������
	MerfiDictionary[142].setEnglWord("in gratitude", "� �������������", 88);					// ���������
	MerfiDictionary[143].setEnglWord("undying", "������", 88);
	MerfiDictionary[144].setEnglWord("He's not as stupid as it seems.", "�� �� ����� ������, ��� �������.", 89);
	MerfiDictionary[145].setEnglWord("The Devil isn't as black as he is painted.", "�� ��� ������� ����, ��� ��� ������.", 89);
	MerfiDictionary[146].setEnglWord("pretend", "������������, ������ ��� (p)", 89);
	MerfiDictionary[147].setEnglWord("the worst", "������", 90);
	MerfiDictionary[148].setEnglWord("the solar system", "��������� �������", 90);
	MerfiDictionary[149].setEnglWord("derived", "�����������, ���������", 90);					// �������
	MerfiDictionary[150].setEnglWord("I've had enough.", "� ���� ������, ��� ����������.", 91);
	MerfiDictionary[151].setEnglWord("pullover", "�������, ������", 91);						// �������
	MerfiDictionary[152].setEnglWord("At your absolute best...", "� ����� ��������� ����...", 91);
	MerfiDictionary[153].setEnglWord("Someday you will be old enough...", "������� �� ���������� ���������...", 91);
	MerfiDictionary[154].setEnglWord("So be it.", "�� ����� ���.", 92);
	MerfiDictionary[155].setEnglWord("no offence", "��� ����", 92);								// �����
	MerfiDictionary[156].setEnglWord("Let's talk heart to heart.", "����� �������� �� �����.", 92);
	MerfiDictionary[157].setEnglWord("excited", "�������������", 500);
}

/*
* ���������� ����������� � ������� �����
MerfiDictionary[163].setEnglWord("Can I have some coffee?", "����� �� �� �������� ��� ����? (�������)", 30);

MerfiDictionary[163].setEnglWord("Why don't you come and visit us?", "������ �� ���� �� ��������� ���?", 44);	// ������������� ����������

MerfiDictionary[163].setEnglWord("Who do you study with?", "� ��� �� �������?", 45);

MerfiDictionary[163].setEnglWord("Who is she talking to?", "� ��� ��� �������������?", 46);
MerfiDictionary[163].setEnglWord("What is your new house like?", "����� �� ���� ����� ���?", 46);				// What...like? (�����?)
MerfiDictionary[163].setEnglWord("Who did she fall in love with?", "� ���� ��� ���������?", 46);			
MerfiDictionary[163].setEnglWord("What is it all about?", "��-�� ���� ��� ���?", 46);

// What..., Which..., Who...
MerfiDictionary[163].setEnglWord("What country will you go next?", "� ����� ������ �� ������� �����?", 47);
MerfiDictionary[163].setEnglWord("What is it all about?", "��-�� ���� ��� ���?", 47);
MerfiDictionary[163].setEnglWord("Which do you like best - reading or dancing?", "��� �� ������ ������ - ������ ��� ���������?", 47);
MerfiDictionary[163].setEnglWord("Who many trees are there in this orchard?", "������� �������� � ���� ��������� ����?", 47);

 // How long does it takes....?
 MerfiDictionary[163].setEnglWord("How long does it takes to master English?", "������� ����������� ������� ����� ��������� �������� ����������?", 48);
 MerfiDictionary[163].setEnglWord("I'm not sure she has fully forgiven me.", "� �� ������, ��� ��� ��������� �������� ����.", 48);

// ������ � �������� �����������, ����� ���� �����������
MerfiDictionary[163].setEnglWord("Do you know if Jack is at home?", "�� �� ������ ���� ����? (i)", 49);
MerfiDictionary[163].setEnglWord("I don't know whether Brain can swim.", "� �� ����, ����� �� ����� �������. (w)", 49);
MerfiDictionary[163].setEnglWord("Don't you know how much I love you?", "����� �� �� ������ ��������� ������ � ����� ����?", 49);
// ����� ������ � ������ ����� �����������, � ����������� ����� �������, ��� � �����������. 
 
 // ��������� ����
 MerfiDictionary[163].setEnglWord("Granny told Kate that she had to listen to her parents.", "������� ������� ����, ��� ��� ������ ��������� ���������. (must)", 49);
 
 MerfiDictionary[380].setEnglWord("Would you mind helping me with it?", "�� �� ������ ������ ��� � ����?", 51);

 // used to 
 MerfiDictionary[380].setEnglWord("He used to be a famous actor, but now he is completely forgotten.", "� ������� �� ��� ���������� �������, �� ������ ��� ��������� ������. ", 36);

 // �������� � ���������
 MerfiDictionary[163].setEnglWord("Most of all she enjoys spending a quiet evening with a good book.", "������ ����� �� �������� ��������� ����� ����� � ������� �������.", 52);
 MerfiDictionary[163].setEnglWord("I would like to talk to you.", "� �� ����� ���������� � �����.", 52);

 // I WANT ���-�� TO ��������; LET ���-�� (��� TO) ��������
  MerfiDictionary[163].setEnglWord("I want him to become a man at last.", "� ���� ����� �� ���� ������� �������.", 53);
  MerfiDictionary[163].setEnglWord("Let's be honest: dancing isn't his cup of tea.", "������� ����� ��������: ����� ��� �� ���, 53);

  // ��������� � �������� �������: TO + ������ ("��� ����, �����...")
  // ��������������� � �������� �������: for something (��� TO)
  MerfiDictionary[163].setEnglWord("It takes a lot of patience to achieve your goal.", "��������� ����� ��������, ����� ������� ����� ����.", 54);
  MerfiDictionary[163].setEnglWord("My kids are always longing for Christmas.", "��� ���� ������ � ����������� ������� ���������.", 54);

 // ������ GO � ������� ���������� (TO, FOR,go + -ING, ON)
  MerfiDictionary[163].setEnglWord("If you have a dream, go for it. Never stop!", "���� � ���� ���� �����, ��� �� ���. ������� �� ��������������!", 55);
  MerfiDictionary[163].setEnglWord("Go for a swim and come out a new man.", "��������� � ������� ������ ���������", 55);

  // ������ GET 
  MerfiDictionary[163].setEnglWord("I got up and got dressed qui�kly.", "� ����� � ������ ������", 56);

// ������ DO ��� MAKE
  MerfiDictionary[163].setEnglWord("I do my best to make world better.", "� ��-�� ��� ��� �������� ������� ��� �����", 57);
  MerfiDictionary[449].setEnglWord("Let's make the situation clear: did you use drugs?", "����� �������� ��������: �� �������� ���������?", 57);
MerfiDictionary[449].setEnglWord("Let's make a deal never to fight in front of the baby.", "����� ����������� ������� �� ��������� ����� ��������", 57);
 
 // ������ HAVE
  MerfiDictionary[163].setEnglWord("Sandra has just had a baby.", "������ ������ ��� ������ �������.", 58);
  MerfiDictionary[163].setEnglWord("I never had a tendency to be selfish.", "� ���� ������� �� ���� ���������� � �������.", 58);

  // ����������� (I - ME, WE - US, YOU - YOU, HE - HIS, SHE - HER, THEY - THEM)
  MerfiDictionary[163].setEnglWord("How it was said: knowledge is power.", "��� ���� �������: ������ ��� ����.", 59);

  // �������������� ����������� (MY OUR YOUR HIS HER THEIR ITS)
  MerfiDictionary[163].setEnglWord("Well, pets are like their owners.", "����, �������� ��� �� �������.", 60);
  MerfiDictionary[163].setEnglWord("But I'm still an optimist.", "�� � ��� ��� ��������..", 60);
  MerfiDictionary[163].setEnglWord("His son seems to have a crash on my daughter.", "��� ��� ������� �������� � ��� ����", 60);

   // �������������� ����������� (�� �������� �������) (MINE, HIS, HERS, OURS, THEIRS, ITS, YOURS)
  MerfiDictionary[163].setEnglWord("Elsa is a friend of mine.", "����� - ��� ����.", 61); 

// ��� �����������
  MerfiDictionary[163].setEnglWord("He wants to talk to you.", "�� ����� ���������� � �����.", 62);
  MerfiDictionary[163].setEnglWord("The toys are ours.", "������� ����.", 62);

  // ���������� ����������� (-SELF, -SELVES)
  MerfiDictionary[163].setEnglWord("He cut himself with a knife.", "�� ��������� �����.", 63);
  MerfiDictionary[163].setEnglWord("Sometimes I talk to myself.", "������ � ������ � �����.", 63);
  MerfiDictionary[163].setEnglWord("And I think to myself what a wonderful world.", "� � ���� ����� ��� ��������� ���.", 63);
  MerfiDictionary[553].setEnglWord("Their words speak for themselves.", "�� ����� ������� ���� �� ����", 63);

  // �������������� ����� (Kitty'S cat)
  MerfiDictionary[163].setEnglWord("My wife's parents' house is gorgeous.", "��� ��������� ���� ���� �����������.", 64);

  // �������������� ������� (A, AN)
  MerfiDictionary[163].setEnglWord("An owl is a bird with a hooked beak.", "���� ��� ����� � ����������� ������.", 65);

  // ������������� �����
  MerfiDictionary[163].setEnglWord("The Boy in the Striped Pyjamas is a gorgeous drama film.", "������� � ��������� ������ - ������������ �����.", 66);
 
  // �������������
  MerfiDictionary[163].setEnglWord("Old age isn't pleasant.", "�������� �� �������.", 67);
  MerfiDictionary[163].setEnglWord("Life isn't a piece of cake for some people", "����� �� ����� ��� ��������� �����.", 67);

  // ������������ ������� THE
  MerfiDictionary[163].setEnglWord("Sometimes, the truth is worse than a white lie.", "������, ������ ����, ��� ����� ����.", 70);

   // ������������ ������� THE ���� ��� ���
  MerfiDictionary[163].setEnglWord("Children grow up quickly and leave their homes.", "���� ������ ������ � �������� ���� ����.", 71);

// ������������ ������� THE (������� ������)
  MerfiDictionary[163].setEnglWord("There is no love without pain.", "�� ������ ����� ��� ����.", 72);

// ������������ ������� THE (�������������� �������)
  MerfiDictionary[163].setEnglWord("The Eiffel Tower is a symbol of Paris.", "��������� ����� ��� ������ ������.", 73);
  MerfiDictionary[163].setEnglWord("Istanbul is the only city located over two continents", "������� ������������ �����, ������������� �� ���� �����������.", 73);

  // ������������ ����������� (THIS, THESE, THOSE, THAT)
  MerfiDictionary[163].setEnglWord("These books are cheaper than those.", "��� ����� �������� ��� ��.", 74);

  // ������������ ����������� (THIS, THESE, THOSE, THAT)
  MerfiDictionary[163].setEnglWord("These cups are dirty. Can we have some clean ones?", "��� ����� �������. �� ����� �������� �����-�� ������?", 75);

  // ����������� (SOME, ANY, SOMETHING, SOMEBODY (SOMEONE), ANYTHING, ANYBODY (ANYONE))
  MerfiDictionary[163].setEnglWord("Can I borrow some money from you?", "� ���� �������� � ���� �����?", 76);

  // ����������� (NOT...ANY, NO, NONE, NO ONE)
  MerfiDictionary[736].setEnglWord("Is there any milk left in the fridge?", "� ������������ �������� ������?", 77);

  // ����������� (NOT...ANYBODY, NOBODY)
  MerfiDictionary[730].setEnglWord("There's nothing left to say.", "������ ������ �������", 78);

   // ����������� (NOwhere, ANYthing, SOMEbody,...)
  MerfiDictionary[730].setEnglWord("I'm in the middle of nowhere.", "� � ������.", 79);
  MerfiDictionary[730].setEnglWord("So many people to hate, and almost nobody to love.", "��� ����� ����� ��� ���������, � ����� ������ ��� �����.", 79);
  MerfiDictionary[730].setEnglWord("I can't give you anithing but love.", "� �� ���� ������ ���� ���� ����� �����.", 79);
  MerfiDictionary[737].setEnglWord("I have nothing to hide.", "��� ������ ��������.", 79);

  // ����������� (EVERY (...where, body, thing), ALL)
  MerfiDictionary[730].setEnglWord("Every season is good in its own way.", "������ ����� ��-������ �����.", 80);

  // �������������� ����������� (ALL MOST SOME ANY NO/NONE + of...)
  MerfiDictionary[753].setEnglWord("Most people drive too fast.", "����������� ����� ����� ����� ������.", 81);
  MerfiDictionary[753].setEnglWord("You can have some of this cake, but not all of it.", "�� ������ ������ ����� ����� �����, �� �� ����.", 81);
  MerfiDictionary[753].setEnglWord("We all aren't as different as you think.", "�� ��� �� ��� ����������, ��� �� �������.", 81);
 
  // ����������� (BOTH, EITHER, NEITHER)
  MerfiDictionary[753].setEnglWord("Neither of us will be here tomorrow.", "����� �� ��� (�����) �� ����� ����� ������ (n).", 82);
  MerfiDictionary[753].setEnglWord("I didn't read either of these books.", "� �� ����� �� ���� �� ���� (����) ����(e).", 82);

  // ����������� (MUCH, MANY, A LOT)
  MerfiDictionary[753].setEnglWord("How much coffee fo you drink a day?", "������� ���� �� ����� � ����?", 83);

  // ����������� (A (LITTLE), A (FEW))
  MerfiDictionary[753].setEnglWord("You make very few mistakes.", "�� ������� ����� ���� ������.", 84);

  // �������������� (Adjectives)
  MerfiDictionary[753].setEnglWord("That smells awful.", "������ ������.", 85);

   // ������� (Adverb)
  MerfiDictionary[753].setEnglWord("I've never loved anyone so deeply.", "� ������ �� ������ ��� ������.", 86);

  // ��������� �������������� (BIG -> BIGGER)
  MerfiDictionary[753].setEnglWord("Do you feel better or worse today?", "���� ������� ����� ��� ����?", 87);

// ��������� �������������� (THAN	A BIT BIGGER	MUCH BIGGER	)
  MerfiDictionary[753].setEnglWord("She swims faster than him.", "��� ������� ������� ��� �� (����.).", 88);
  MerfiDictionary[753].setEnglWord("She was taller than he was.", "��� ���� ���� ���� (...was).", 88);
  

 // ��������� �������������� ((NOT) AS ... AS; (NOT) AS MUCH...AS; (NOT) AS MANY...AS;)
  MerfiDictionary[753].setEnglWord("Rome is not as old as Athens.", "��� �� ����� ������, ��� �����.", 89);
  MerfiDictionary[845].setEnglWord("You don't work as hard as me.", "�� �� ��������� ����� ������, ��� �", 89);

  // ������������ ������� ��������������
  MerfiDictionary[753].setEnglWord("Our solar system is the best.", "���� ��������� ������� ������.", 90);

// ������� (� ��������������) enough
  MerfiDictionary[753].setEnglWord("I've had enough.", "� ���� ������.", 91);
  MerfiDictionary[753].setEnglWord("There aren't enough apples in the basket.", "� ������� ������������ �����.", 91);
  MerfiDictionary[753].setEnglWord("Someday you will be old enough to start reading fairy tales again.", 
  "������� �� ���������� ���������, ��� ������� ����� ������ ������.", 91);

  // ������� TOO (TOO much; TOO many; TOO...FOR somebody TO do something)
  MerfiDictionary[887].setEnglWord("I'm too tired to go out.", "� ������� �����, ����� �������� �� �����.", 92);
  MerfiDictionary[887].setEnglWord("She speaks too fast for me to undrerstand.", "��� ������ ������� ������, ����� � ��� ������.", 92);

// ������� ���� � ���������� �����������
 MerfiDictionary[907].setEnglWord("Smoking is strictly forbidden in the public areas.", "������� ������ ��������� � ������������ ������.", 93);
  MerfiDictionary[895].setEnglWord("She was the cutest baby ever.", "��� ���� ����� ����� �������� �� ����.", 93);
  
 
// ����� ������� ������� � �����������
	MerfiDictionary[907].setEnglWord("I never forgive my enemies.", "� ������� �� ������ ����� ������", 94);
	MerfiDictionary[907].setEnglWord("It hardly happens that dreams come true.", "���� �� ���������, ��� ����� ���������� ���������.", 94);
  
  // STILL, ALREADY, YET
  MerfiDictionary[923].setEnglWord("I haven't had breakfast yet.", "� ��� ��� �� ���������.", 95);
  MerfiDictionary[923].setEnglWord("He's still out.", "�� ��� ��� �� ���� (�������).", 95);
  MerfiDictionary[923].setEnglWord("Does he already sold his car?", "�� ��� ������� ���� ������? (Pr. Sim.)", 95);

   // ���������� ����� GIVE, LEND, PASS, SHOW, SEND
  MerfiDictionary[923].setEnglWord("I showed mother what I could do.", "� ������� ����, ��� � ���� ������.", 95);

   // ���������� ����� AND, SO, BUT, BECAUSE, OR
  MerfiDictionary[924].setEnglWord("To be or not to be, that is the question", "���� ��� �� ����, ��� � ��� ������.", 97);

   // �������� ����������� � WHEN
	MerfiDictionary[933].setEnglWord("I bite my bottom lip when I feel nervous.", "� ����� ���� ������� ����, ����� � ���������.", 98);

	// �������� ����������� 1-�� ���� � IF
	MerfiDictionary[954].setEnglWord("If I go there, I'll pick you up.", "���� � ����� ����, � ���� �������.", 99);
	MerfiDictionary[958].setEnglWord("Mom will be angry if I am late.", "���� �����������, ���� � �������.", 99);
	MerfiDictionary[961].setEnglWord("I won't do anything if you don't help me.", "� �� ���� ������ ������, ���� �� ��� �� ��������.", 99);
  
  // �������� ����������� 2-�� ���� � IF (���� ��)
	MerfiDictionary[954].setEnglWord("It would be nice if the weather were better.", "���� �� ����, ���� �� ������ ���� �����.", 100);
	MerfiDictionary[954].setEnglWord("I wouldn't go out if I were you.", "� �� ����� ������, ���� �� ��� �� ����� �����.", 100);

	// �������� �����������, ����� �� ����� THAT, WHO, THAT
	MerfiDictionary[954].setEnglWord("These are the books I told you about.", "��� �����, � �������  � ���� �������.", 102);


	// �������� ������� AT ON IN
	MerfiDictionary[1003].setEnglWord("Don't go out at night.", "�� ������ �� ����� �����.", 103);
	
  */



 // ������� ��������� ������� �������� numberOfWords ���� �� ������� ������� ����:
 // ��� ������� ����� ������� ������� � ����, ���� ������������ �� ������ ��������.
 // ��� ������ ��������� �������� ���������.
int CheckKnowledgesDifficultMerfiDictionary(EnglishWord* MerfiDictionary, int numberOfWords)
{
	int wordNumber;
	string temp;
	int rightAnswer = 0;
	for (int count = 1; count <= numberOfWords; count++)
	{
		wordNumber = rand() % DICTIONARY_DIFF_SIZE;

		// ��������� ������� ���� � ������������
		while (MerfiDictionary[wordNumber].getFlag() != 0)	 // ���� ����� �����
			wordNumber = rand() % DICTIONARY_DIFF_SIZE;

		MerfiDictionary[wordNumber].printTranslation();

		cout << "Enter your answer: ";
		getline(cin, temp);
		// ������� ���������� ������� ��� ����������� ������
		if (MerfiDictionary[wordNumber].getWord() == temp)	// ������ �������
		{
			rightAnswer++;
			cout << "***************You are right***********************" << endl;
			MerfiDictionary[wordNumber].setFlag(1);		// ��������, ��� ������ ��� � �����
		}
		else {
			cout << "***************You are wrong***********************" << endl;
			MerfiDictionary[wordNumber].printWord();
			MerfiDictionary[wordNumber].setFlag(2);		// �������� ������ 
		}

		// ������������ % ������������ ����� � �������� ���������� (������� ������ ��� ������� ������)
		if (numberOfWords > 99)
		{
			if (count % 50 == 0)
				cout << "\n�� ��������� " << count * 100 / numberOfWords << " % �����."
				<< " � ������� ����������� " << rightAnswer * 100 / count << " %.\n" << endl;
		}

	}
	cout << "You have given " << rightAnswer << " right answers from " << numberOfWords << " questions.";
	cout << "Your result is: " << (rightAnswer * 100) / numberOfWords << "%" << endl;

	return numberOfWords - rightAnswer;		// ���������� ������
}

/* ���������: ����� ���������� ��������� � �������� ������� ����, �� ����������� ������� �������.
����������!*/