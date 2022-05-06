// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================
#ifndef SDDS_LINESTATION_H_
#define SDDS_LINESTATION_H_

#include <iostream>
#include <vector>
#include "Workstation.h"

namespace sdds
{
	class LineManager
	{
	private:

		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder{ 0u };
		Workstation* m_firstStation{ nullptr };

	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);
		void linkStations();
		bool run(std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif //!SDDS_LINESTATION_H_


