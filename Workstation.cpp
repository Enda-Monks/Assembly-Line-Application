// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#include <iostream>
#include <algorithm>
#include "Workstation.h"

using namespace std;
namespace sdds
{
	// global queues
	std::deque<CustomerOrder> pending;
	std::deque<CustomerOrder> completed;
	std::deque<CustomerOrder> incomplete;

	void Workstation::fill(std::ostream& os)
	{
		if (!m_orders.empty())
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	bool Workstation::attemptToMoveOrder()
	{
		bool isMoved{ false };

		if (!m_orders.empty()) // ensure there are current orders
		{
			if (m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() == 0)
			{
				if (m_pNextStation)
				{
					*m_pNextStation += move(m_orders.front());
				}
				else if (m_orders.front().isFilled())
				{
					completed.push_back(move(m_orders.front()));
				}
				else
				{
					incomplete.push_back(move(m_orders.front()));
				}
				m_orders.pop_front();
				isMoved = true;
			}
		}
		return isMoved;
	}

	void Workstation::setNextStation(Workstation* station = nullptr)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const
	{
		return m_pNextStation;
	}
	void Workstation::display(std::ostream& os) const
	{

		if (m_pNextStation)
		{
			// this station item
			os << getItemName();
			os << " --> ";
			// next station item
			os << m_pNextStation->getItemName();
		}
		else
		{
			// last station item
			os << getItemName();
			os << " --> End of Line";
		}

		os << endl;
	}

	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) 
	{
		m_orders.push_back(move(newOrder));
		return *this;
    }
}

   