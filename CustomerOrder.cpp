// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#include <iostream>
#include <algorithm>
#include "CustomerOrder.h"

using namespace std;
namespace sdds
{
	// Initialize Class Variables
	// ==========================
	size_t CustomerOrder::m_widthField{ 0u };

	// Class Constraints
	// =================
	const size_t serialNo__widthField{ 6 };

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		Utilities util;
		size_t next_pos{ 0u };
		bool more{ true };
		std::string itemFields{ "" };
		std::string itemField{ "" };
		size_t i;

		if (record.length() > 1) // ensure record contains data
		{

			m_name = util.extractToken(record, next_pos, more);
			m_product = util.extractToken(record, next_pos, more);
			itemFields = record.substr(next_pos, record.length() - next_pos);
			m_cntItem = std::count(itemFields.begin(), itemFields.end(), util.getDelimiter()) + 1;
			m_lstItem = new Item * [m_cntItem]; // create new instances of each item in resource
			next_pos = 0u; // reset for itemFields
			for (i = 0; i < m_cntItem && more; i++)
			{
				itemField = util.extractToken(itemFields, next_pos, more);
				m_lstItem[i] = new Item(itemField);
			}

			m_widthField = std::max(util.getFieldWidth(), m_widthField);
		}
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)noexcept
	{
		size_t i;
		if (this != &src)
		{

			if (m_lstItem)
			{
				for (i = 0u; i < m_cntItem; i++)
				{
					delete m_lstItem[i];  // deallocate current items
				}
				delete[] m_lstItem;  // deallocate current array 
			}

			m_lstItem = src.m_lstItem;  // move src's array address

			m_cntItem = src.m_cntItem; // move src count
			src.m_cntItem = 0u;

			for (i = 0u; i < m_cntItem; i++)
			{
				m_lstItem[i] = src.m_lstItem[i]; // move each Item address
			}
			src.m_lstItem = nullptr;

			// swap instance variables
			m_name = src.m_name;
			src.m_name = "";
			m_product = src.m_product;
			src.m_product = "";
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		size_t i;

		for (i = 0u; i < m_cntItem; i++)
		{
			delete m_lstItem[i];
		}

		delete[] m_lstItem;
	}

	bool CustomerOrder::isFilled()const // modified for ms3, 2021-12-04
	{
		bool result = true;
		size_t i;

		for (i = 0u; i < m_cntItem && result; i++)
		{
			if (!m_lstItem[i]->m_isFilled)
			{
				result = false;
			}
		}
		return result;
	}

	//***************************************************************
	bool CustomerOrder::isItemFilled(const std::string& itemName) const // modified for ms3, 2021-12-04
	{
		bool result = true;
		size_t i;
		for (i = 0u; i < m_cntItem && result; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
			{
				result = m_lstItem[i]->m_isFilled;
			}
		}
		return result;
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) // modified for ms3, 2021-12-04
	{
		size_t i;
		bool available{true};

		for (i = 0u; i < m_cntItem && available; i++)
		{
			if (m_lstItem[i]->m_itemName == station.getItemName()) // find item match
			{
				if (station.getQuantity() >= 1) // ensure station is not empty
				{
					station.updateQuantity(); // subtract item from station
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
				}
				else
				{
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << "]\n";
				}
			}
		}
	}
	void CustomerOrder::display(std::ostream& os) const
	{
		size_t i;

		// title
		os << m_name;
		os << " - ";
		os << m_product;
		os << endl;

		// item list
		for (i = 0u; i < m_cntItem; i++)
		{
			// serial
			os << '[';
			os.fill('0');
			os.width(serialNo__widthField);
			os.setf(ios::right);
			os << m_lstItem[i]->m_serialNumber;
			os.unsetf(ios::right);
			os << "] ";

			// name
			os.fill(' ');
			os.width(m_widthField);
			os.setf(ios::left);
			os << m_lstItem[i]->m_itemName;
			os.unsetf(ios::left);
			os << " - ";

			// status
			m_lstItem[i]->m_isFilled ? os << "FILLED" : os << "TO BE FILLED";
			os << endl;
		}
	}

}

