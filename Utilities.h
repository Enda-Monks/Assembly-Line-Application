// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#ifndef SDDS_UTILITIES_H_
#define SDDS_UTILITIES_H_

#include <iostream>

namespace sdds
{
	class Utilities
	{
	private:
		size_t m_widthField{ 1 };
		static char m_delimiter; // initialized in .cpp
		void setFieldWidth(size_t newWidth){m_widthField = newWidth;}
	public:
		static void setDelimiter(char newDelimiter);
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
		size_t getFieldWidth()const{return m_widthField;}
		static char getDelimiter(); 

	};
}
#endif //!SDDS_UTILITIES_H_


