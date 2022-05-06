// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_

#include <iostream>
#include "Utilities.h"

namespace sdds
{
	class Station
	{
	private:
		int m_id{ 0 };
		std::string m_item{ "" };
		std::string m_desc{ "" };
		size_t m_serialNumber{ 0u };
		size_t m_noOfItems{ 0u };
		static size_t m_wField; // initialized in .cpp
		static int id_generator; // initialized in .cpp
	public:
		Station(const std::string& record);
		const std::string& getItemName() const;
		size_t getNextSerialNumber();
		size_t getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}
#endif //!SDDS_STATION_H_

