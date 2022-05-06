// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_

#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace sdds
{
	// global queues
	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station
	{
	private:
		std::deque<CustomerOrder> m_orders;
		Workstation* m_pNextStation{ nullptr };
	public:
		// --- prevent copies ---
		Workstation(Workstation& src) = delete;
		Workstation& operator=(const Workstation& src) = delete;
		// --- prevent moves ----
		Workstation(Workstation&& src)noexcept = delete;
		Workstation& operator=(CustomerOrder&& src)noexcept = delete;
		// ---
		Workstation(const std::string& str) : Station(str){}
		void fill(std::ostream& os);
		bool attemptToMoveOrder();
		void setNextStation(Workstation* station);
		Workstation* getNextStation() const;
		void display(std::ostream& os) const;
		Workstation& operator+=(CustomerOrder&& newOrder);
	};
}
#endif //!SDDS_WORKSTATION_H_

