#include "NoteBook.h"

std::wstring NoteBook::getPersonIdentifier() const
{
	return this->identifier.Surname 
			+ L" " + this->identifier.Name
			+ L" " + this->identifier.MiddleName;
}
std::wstring NoteBook::getBirthday() const
{
	return std::to_wstring(this->birthday.BirthDay) 
			+ L"." + std::to_wstring(this->birthday.BirthMonth) 
			+ L"." + std::to_wstring(this->birthday.BirthYear);
}

std::wstring NoteBook::getHeader() const
{
	return L"id,FullName,Phone,Address,Birthday";
}
std::wstring NoteBook::to_csv() const
{
	return this->getPersonIdentifier() 
			+ L"," + std::to_wstring(this->Phone) 
			+ L"," + this->Address + L"," 
			+ this->getBirthday() + L"\n";
}