#include <string>

#pragma once
class NoteBook
{
	private:

		struct Identifier
		{
			std::wstring Surname;
			std::wstring Name;
			std::wstring MiddleName;
		};

		struct Birthday
		{
			uint8_t BirthDay;
			uint8_t BirthMonth;
			uint8_t BirthYear;
		};

	public:

		Identifier identifier;
		Birthday birthday;
		uint8_t Phone;
		std::wstring Address;

		std::wstring getPersonIdentifier() const;
		std::wstring getBirthday() const;

		std::wstring getHeader() const;
		std::wstring to_csv() const;

};

