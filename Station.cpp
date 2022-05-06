// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#include <iostream>
#include <string>
#include <algorithm>
#include "Station.h"

using namespace std;
namespace sdds
{
	// Initialize Class Variables
	// ==========================
	size_t Station::m_wField{ 0u };
	int Station::id_generator{ 0u };

	// Class Constraints
	// =================
	const size_t id_widthField{ 3 };
	const size_t serialNo__widthField{ 6 };

	Station::Station(const std::string& record)
	{
		Utilities util;
		size_t next_pos{ 0u };
		bool more{ true };

		id_generator++;
		m_id = id_generator;

		m_item = util.extractToken(record, next_pos, more); 

		m_serialNumber = std::stoi(util.extractToken(record, next_pos, more));

		m_noOfItems = std::stoi(util.extractToken(record, next_pos, more));

		m_wField = std::max(util.getFieldWidth(), m_wField);

		m_desc = util.extractToken(record, next_pos, more);
	}
	const std::string& Station::getItemName() const
	{
		return m_item;
	}
	size_t Station::getNextSerialNumber()
	{
		return m_serialNumber++;
	}
	size_t Station::getQuantity() const
	{
		return m_noOfItems;
	}
	void Station::updateQuantity()
	{
		if (m_noOfItems > 0)
		{
			m_noOfItems--;
		}
	}
	void Station::display(std::ostream& os, bool full) const
	{
		if (!full)
		{
			// id
			os << '[';
			os.fill('0');
			os.width(id_widthField);
			os.setf(ios::right);
			os << m_id;
			os.unsetf(ios::right);
			os << ']';

			// item 
			os << " Item: ";
			os.fill(' ');
			os.width(m_wField);
			os.setf(ios::left);
			os << m_item;
			os.unsetf(ios::left);

			// serialNumber
			os << " [";
			os.fill('0');
			os.width(serialNo__widthField);
			os.setf(ios::right);
			os << m_serialNumber;
			os.unsetf(ios::right);
			os << ']';
		}
		else
		{	
			// id
			os << '[';
			os.fill('0');
			os.width(id_widthField);
			os.setf(ios::right);
			os << m_id;
			os.unsetf(ios::right);
			os << ']';

			// item 
			os << " Item: ";
			os.fill(' ');
			os.width(m_wField);
			os.setf(ios::left);
			os << m_item;
			os.unsetf(ios::left);
			
			// serialNumber
			os << " [";
			os.fill('0');
			os.width(serialNo__widthField);
			os.setf(ios::right);
			os << m_serialNumber;
			os.unsetf(ios::right);
			os << ']';

			// noOfItems 
			os << " Quantity: ";
			os.fill(' ');
			os.width(m_wField);
			os.setf(ios::left);
			os << m_noOfItems;
			os.unsetf(ios::left);

			// desc
			os << " Description: ";
			os.setf(ios::left);
			os << m_desc;
			os.unsetf(ios::left);
		}

		os << endl;
	}
}

