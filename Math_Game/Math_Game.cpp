// Math_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//ask user quizlevel ques.sNo  opType
#include <iostream>
using namespace std;
enum enmQuestionsLevel{ EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum  enmOperationType{ Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
struct structQuestion {
    int num1;
    int num2;
    enmOperationType OpType;
    enmQuestionsLevel QuestionLevel;
    int correctAnswer;
    int UserAnswer;
    bool isUserAnswerRight;
};
struct structQuizz {
    structQuestion QuestionList[100];
    short numberOfQuestions;
    enmQuestionsLevel QuestionsLevel;
    enmOperationType OpType;
    short numberOfRightAnswers=0;
    short numberOfWrongAnswers=0;
    bool isPass;

};
int RandomNumber(int From, int To)
{
    //Function to generate a random number
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}
structQuestion GenerateQuestion(enmOperationType opType,enmQuestionsLevel QuestionsLevel) {
    structQuestion Question;
    if (opType == enmOperationType::MixOp) {
        opType = (enmOperationType)RandomNumber(1,4);
    }
    Question.OpType = opType;
    if (QuestionsLevel == enmQuestionsLevel::Mix) {
        QuestionsLevel = (enmQuestionsLevel)RandomNumber(1, 3);
    }
    switch (QuestionsLevel)
    {
    case EasyLevel:
        Question.num1 = RandomNumber(1,10);
        Question.num2 = RandomNumber(1,10);
        Question.QuestionLevel = QuestionsLevel;
        break;
    case MedLevel:
        Question.num1 = RandomNumber(1, 20);
        Question.num2 = RandomNumber(1, 20);
        Question.QuestionLevel = QuestionsLevel;
        break;
    case HardLevel:
        Question.num1 = RandomNumber(1, 30);
        Question.num2 = RandomNumber(1, 30);
        Question.QuestionLevel = QuestionsLevel;
        break;
    case Mix:
        Question.num1 = RandomNumber(1, 30);
        Question.num2 = RandomNumber(1, 30);
        Question.QuestionLevel = QuestionsLevel;
        break;
    default:
        break;
    }
    Question.QuestionLevel = QuestionsLevel;
    return Question;
}
void GenerateQuestionList(structQuizz& Quizz) {
    for (size_t question = 0; question < Quizz.numberOfQuestions; question++)
    {
        Quizz.QuestionList[question] = GenerateQuestion(Quizz.OpType,Quizz.QuestionsLevel);
    }
}
string QuestionLevelText(enmQuestionsLevel QuestionsLevel) {

        string OpTypeText[4] = { "Easy", "Med", "Hard","Mix" };
        return OpTypeText[QuestionsLevel -1];

}
string OpTypeText(enmOperationType opType) {
    switch (opType)
    {
    case enmOperationType::Add:
        return "+";
        break;
    case enmOperationType::Sub:
        return "-";
        break;
    case enmOperationType::Mult:
        return "*";
        break;
    case enmOperationType::Div:
        return "/";
        break;
    case enmOperationType::MixOp:
      return  "mix";  
        break;
    default:
        return  "opType is invalid";
        break;  
    }
}
void PrintQuestion(structQuizz& Quizz,short questionNumber) {
    cout << "Question[" << questionNumber+1 << "] \n";
    cout << Quizz.QuestionList[questionNumber].num1 << endl;
    cout << Quizz.QuestionList[questionNumber].num2 << "  " <<
        OpTypeText(Quizz.QuestionList[questionNumber].OpType)<<endl;
    cout << "-------\n";
}
int ReadUserAnswer() {
  int  userAnswer = 0;
  cin >> userAnswer;
  return userAnswer;
}

int calclate(short num1,short num2,enmOperationType optype) {
    switch (optype)
    {   
    case Add:
        return num1+num2;
        break;
    case Sub:
        return num1 - num2;

        break;
    case Mult:
        return num1 * num2;

        break;
    case Div:
        return num1 / num2;

        break;
    case MixOp:
        return num1 + num2;
        break;
    default:
        return num1 + num2;
        break;
    }
}
void CorrectAnswer(structQuizz& Quizz,short questionNumber) 
{
    if (Quizz.QuestionList[questionNumber].UserAnswer == Quizz.QuestionList[questionNumber].correctAnswer) {
        Quizz.QuestionList[questionNumber].isUserAnswerRight = true;
        cout << "\n Right Answer ..good \n";
        system("color 2F");
        Quizz.numberOfRightAnswers++;

    }

    else {
        Quizz.QuestionList[questionNumber].isUserAnswerRight = false;
        Quizz.numberOfWrongAnswers++;
        cout << "\n wrong Answer ..bad  \n";
        system("color 4F");
        cout << "right answer is " << Quizz.QuestionList[questionNumber].correctAnswer << endl;
    }
}
void AskAndCorrectQuestionListAnswer(structQuizz& Quizz) {
    for (short questionNumber = 0; questionNumber < Quizz.numberOfQuestions; questionNumber++)
    {
        PrintQuestion(Quizz,questionNumber);
        Quizz.QuestionList[questionNumber].UserAnswer = ReadUserAnswer();
        Quizz.QuestionList[questionNumber].correctAnswer = calclate(Quizz.QuestionList[questionNumber].num1, Quizz.QuestionList[questionNumber].num2, Quizz.QuestionList[questionNumber].OpType);
        CorrectAnswer(Quizz, questionNumber);
    }

}
bool IsPass(structQuizz Quizz) {
    return (Quizz.numberOfRightAnswers > Quizz.numberOfWrongAnswers);
}
void PrintPassOrFail(structQuizz Quizz) {
    if (IsPass(Quizz)) {
        cout << "\nFinal Result Pass\n";
        system("color 2F");
    }
    else {
        cout << "\nFinal Result FAIL\n";
        system("color 4F");
    }
}
void PrintFinalResults(structQuizz Quizz) {
    PrintPassOrFail(Quizz);
    cout << "\n\nNumber of ques. :  " << Quizz.numberOfQuestions << endl;
    cout << "questions level :  " << QuestionLevelText(Quizz.QuestionsLevel) << endl;
    cout << "opType   " << OpTypeText(Quizz.OpType) << endl;
    cout << "number of right answers  " << Quizz.numberOfRightAnswers << endl;
    cout << "number of wrong answers  " << Quizz.numberOfWrongAnswers << endl;
}
void ResetScreen()
{
    system("cls");
    system("color 0F");
}
short ReadQuestionsNumber() {
    short quesNo = 0;
    do
    {
        cout << "\nHow many questions 1 to 10 ?: ";
        cin >> quesNo;
    } while (quesNo < 0 || quesNo>10);

    return quesNo;
}
enmQuestionsLevel ReadQuestionsLevel() {
    short quesLevel = 0;
    do
    {
        cout << "\nYour Choice: [1]easy, [2]Med , [3] Hard ,[4] Mix? ";
        cin >> quesLevel;
    } while (quesLevel < 1 || quesLevel>4);

    return (enmQuestionsLevel)quesLevel;
}
enmOperationType ReadOpertionType() {
    short opType = 0;
    do
    {
        cout << "\nEnter operation type [1]Add [2]Sub ,[3]Mul ,[4]Div  ,[5]Mix ?";
        cin >> opType;
    } while (opType < 1 || opType>5);

    return (enmOperationType)opType;
}
void PlayGame(structQuizz& Quizz) {
    Quizz.numberOfQuestions = ReadQuestionsNumber();
    Quizz.OpType= ReadOpertionType();
    Quizz.QuestionsLevel = ReadQuestionsLevel();
    GenerateQuestionList(Quizz);
    AskAndCorrectQuestionListAnswer(Quizz);
    PrintFinalResults(Quizz);
}
void StartGame() {
    char isAgain = 'Y';
    do
    {

        ResetScreen();
        PlayGame();
       
        cout << "do want to play again ?";
        cin >> isAgain;
    } while (isAgain == 'y' || isAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
