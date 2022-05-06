// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#include <iostream>
#include "Utilities.h"

using namespace std;
namespace sdds
{
	// Initialize Class Variables
	// ==========================
	char Utilities::m_delimiter{ ',' }; // default

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token{ "" };
		size_t end_pos{ 0u };
		if (next_pos >= str.length()) 
		{
			more = false; // ensure 'more' is correct
		}
		else if (more == true)
		{
			end_pos = str.find_first_of(m_delimiter, next_pos);

			if (end_pos > str.length()) // no delimeter found, extract token up to end of string
			{
				token = str.substr(next_pos, str.length() - next_pos);
				next_pos = str.length() + 1;
			}
			else if (end_pos > next_pos) 
			{
				token = str.substr(next_pos, end_pos - next_pos); // extract token
				next_pos = end_pos + 1;
			}
			else if (end_pos == next_pos) // empty field
			{
				token = "";
				next_pos++;
			}
		}

		if (m_widthField < token.length())
		{
			m_widthField = token.length(); // set field width 
		}

		if (next_pos < str.length() - 1) // set 'more' for next token
		{
			more = true;
		}
		else
		{
			more = false;
		}

		if (token == "") // error
		{
			throw  "empty field";
		}

		return token;
	}


	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}
}