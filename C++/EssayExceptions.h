#ifndef __ESSAYEXCEPTIONS_H
#define __ESSAYEXCEPTIONS_H

#include <iostream>
#include <string.h>
#pragma warning(disable:4290)

using namespace std;
//decleration of class
class EssayExceptions
{
protected:
	std::string Magazine, EssayName;
public:
	EssayExceptions(const std::string& Magazine, const std::string& EssayName) {}
	virtual void print() const = 0;
};
class InvalidNameMagazineExceptions : public EssayExceptions
{
public:
	InvalidNameMagazineExceptions(const std::string& Magazine, const std::string& EssayName) : EssayExceptions(Magazine, EssayName) {}
	virtual void print() const { cout << "An empty name of a Magazine isn't valid for an Essay." << endl << endl; }
};
class InvalidNameEssayExceptions : public EssayExceptions
{
public:
	InvalidNameEssayExceptions(const std::string& Magazine, const std::string& EssayName) : EssayExceptions(Magazine, EssayName) {}
	virtual void print() const { cout << "An empty name  isn't valid for an Essay." << endl << endl; }
};
#endif 


