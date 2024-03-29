#include "MainDeck.hpp"
using namespace std;

MainDeck::MainDeck()
{
}

void MainDeck::fillDeck()
{
    // Coloring
    Coloring clr;

    // SELECT OPTION
    int option = -1;
    do
    {
        try
        {
            clr.white(true);
            cout << "\nHow do you want to fill the Main Deck?" << endl;
            clr.reset();

            cout << "[1] Auto Randomized" << endl;
            cout << "[2] Input from file .txt" << endl;

            int inputOption;
            cout << "Option : ";

            clr.lgreen();
            cin >> inputOption;
            clr.reset();

            if (cin.fail() || inputOption < 1 || inputOption > 2)
            {
                throw OptionException();
            }
            else
            {
                option = inputOption;
            }
        }
        catch (OptionException &err)
        {
            clr.red();
            cout << err.what();
            clr.reset();

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (option == -1);

    switch (option)
    {
    case 1:
        for (int i = 0; i < static_cast<int>(Color::Last); ++i)
        {
            Color c = static_cast<Color>(i);
            for (int j = 1; j < 14; j++)
            {
                ColorCard cardObj(c, j);
                this->deck.push_back(cardObj);
            }
        }

        this->randomizeCard();

        break;

    case 2:
        this->readCard();
        break;

    default:
        break;
    }
}

void MainDeck::randomizeCard()
{
    srand(time(NULL));
    random_shuffle(deck.begin(), deck.end());
}

void MainDeck::addCard(ColorCard card)
{
    (*this) + card;
}

void MainDeck::readCard()
{
    this->deck.clear();

    // Relative path disini harus disesuaikan dari executable file, bukan dari MainDeck.cpp
    string relativePath = "test/";

    string fileName;
    bool ready = false;

    do
    {
        try
        {
            // input file name
            cout << "Input file name [filename].txt in test folder : ";
            cin >> fileName;

            // concat relative path and filename
            string relativeFileName = relativePath + fileName;

            // try to read file
            ifstream file(relativeFileName);

            // check if file is opened
            if (file.is_open())
            {
                string line;
                while (getline(file, line))
                {
                    // split each line into color and number
                    string color, number;
                    stringstream ss(line);
                    getline(ss, color, ' ');
                    getline(ss, number, ' ');

                    // convert enum to string
                    Color colorToInsert = stringToColor(color);

                    // convert number to integer and check
                    int numberToInsert = stoi(number);
                    if (numberToInsert < 1 || numberToInsert > 13)
                    {
                        throw TextFileException();
                    }

                    // create object and push to deck
                    ColorCard cardObj(colorToInsert, numberToInsert);
                    this->deck.push_back(cardObj);
                }
                ready = true;
            }
            else
            { // file fail to opened
                throw FilenameException();
            }
        }
        catch (FilenameException &err)
        {
            cout << err.what();
        }
        catch (TextFileException &err)
        {
            cout << err.what();
        }
    } while (!ready);
}

Color MainDeck::stringToColor(const string &color)
{
    if (color == "Green")
        return Color::Green;
    if (color == "Blue")
        return Color::Blue;
    if (color == "Yellow")
        return Color::Yellow;
    if (color == "Red")
        return Color::Red;
    throw TextFileException();
}

ColorCard MainDeck::getFromMainDeck()
{
    ColorCard toRemove = this->deck.back();
    (*this) - toRemove;
    return toRemove;
}

MainDeck &MainDeck::operator=(const MainDeck &other)
{
    this->deck.clear();
    for (auto c : other.deck)
    {
        this->deck.push_back(c);
    }
    return *this;
}

void MainDeck::print()
{
    for (int i = 0; i < this->deck.size(); i++)
    {
        this->deck[i].printInfo();
        cout << endl;
    }
}

MainDeck::~MainDeck()
{
}