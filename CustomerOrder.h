// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_

#include <iostream>
#include "Utilities.h"
#include "Station.h"

namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };
		Item(const std::string& src) : m_itemName(src){};
	};
	class CustomerOrder
	{
	private:
		std::string m_name{""};
		std::string m_product{""};
		size_t m_cntItem{0u};
		Item** m_lstItem{nullptr}; 
		static size_t m_widthField; // initialized in .cpp
	public:
		CustomerOrder(){}
		CustomerOrder(const std::string& record);
		// --- rule of 5
		CustomerOrder(CustomerOrder& src){throw "no copies allowed";}
		CustomerOrder& operator=(const CustomerOrder& src) = delete;
		CustomerOrder(CustomerOrder&& src)noexcept{*this = std::move(src);}
		CustomerOrder& operator=(CustomerOrder&& src)noexcept;
		~CustomerOrder();
		// --- rule of 5
		bool isFilled()const; 
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const; 
	};
}
#endif //!SDDS_CUSTOMERORDER_H_

