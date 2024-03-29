#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include <exception>
using namespace std;

struct NumericException : public exception
{
    const char *what() const throw()
    {
        return "Numeric input not valid.\nPlease input only integers.\n";
    }
};

struct TextFileException : public exception
{
    const char *what() const throw()
    {
        return "File configuration is invalid. Make sure the configuration format is [Color] [Number] and use the valid Color or Number\n";
    }
};

struct CommandException : public exception
{
    const char *what() const throw()
    {
        return "Command input not valid.\nPlease input the right command\n";
    }
};

struct AbilityNotHaveException : public exception {
    const char *what() const throw()
    {
        return "You don't have the ability card!\nPlease input other command\n";
    }
};

struct AllAbilityUsedException : public exception {
    const char *what() const throw()
    {
        return "Every player has used their abilities! Oopsie you got your own ability affected to yourself HAHAHAHA :o\n";
    }
};

struct CommandInactiveException : public exception
{
    const char *what() const throw()
    {
        return "Ability was deactivated by another player.\n";
    }
};

struct StringException : public exception
{
    const char *what() const throw()
    {
        return "Input is invalid. Try input a valid string\n";
    }
};

struct IntegerException : public exception
{
    const char *what() const throw()
    {
        return "Input is invalid. Try input a valid integer\n";
    }
};

struct NicknameException : public exception
{
    const char *what() const throw()
    {
        return "No player with that nickname is found.\n";
    }
};

struct PointException : public exception
{
    const char *what() const throw()
    {
        return "The set point is already 1 so it cant be changed.\n";
    }
};

struct PointException2 : public exception
{
    const char *what() const throw()
    {
        return "The set point is already 2 so it cant be quartered.\n";
    }
};

struct FilenameException : public exception{
    const char *what() const throw(){
        return "File not found. Please input the correct file and follow this format [filename].txt\n";
    }
};

struct OptionException : public exception{
    const char *what() const throw(){
        return "Option not valid. Please input valid option.\n";
    }
};

#endif