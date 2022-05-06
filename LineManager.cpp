// Author: Kathleen Monks
// Purpose: Final Project for Seneca's OOP345  
// Date of completion: 2021-11-27
// ==========================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;
namespace sdds
{

	LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
	{
		ifstream ifstr;
		ifstr.open(file);

		if (!ifstr.is_open())
		{
			throw "Error: Failure to open " + file;
		}
		else
		{
			string record{ "" };
			string stationName{ "" };
			string nextStationName{ "" };
			
			Utilities util; // to extract
			size_t next_pos{0u};
			bool more;

			while (!ifstr.eof())
			{
				getline(ifstr, record); // stationName|nextStationName
				
				next_pos = 0u;
				more = true;

				stationName = util.extractToken(record, next_pos, more);
				
				auto station = *find_if(stations.begin(), stations.end(), [stationName](Workstation* ws) // find matching station
				{
					return ws->getItemName() == stationName;
				});

				if (more) // ensure next station exists
				{
					nextStationName = util.extractToken(record, next_pos, more);

					// find matching next station
					auto nextStation = *find_if(stations.begin(), stations.end(), [nextStationName](Workstation* ws)
					{
						return ws->getItemName() == nextStationName;
					});

					station->setNextStation(nextStation);
				}
				activeLine.push_back(station); // set instance vector
			}

			ifstr.close();

			auto firstActive = *std::find_if(activeLine.begin(), activeLine.end(), [&](Workstation* ws)
			{
				return *std::find_if(activeLine.begin(), activeLine.end(), [&ws](Workstation* next)
				{
					return (next->getNextStation() && next->getNextStation()->getItemName() == ws->getItemName()) ? false : true;
				});
					
			}); 
			m_firstStation = firstActive; // set instance vars
			m_cntCustomerOrder = pending.size(); 
		}
	}

	void LineManager::linkStations() 
	{	
		vector<Workstation*> sortedLine;
		auto it = m_firstStation;
		while (it)
		{
			sortedLine.push_back(it);
			it = it->getNextStation();
		}
		activeLine = sortedLine;
	}

	bool LineManager::run(std::ostream& os)
	{
		static size_t count{0u}; 
		bool isFilled{false};

		count++;
		os << "Line Manager Iteration: " << count << endl;
		
		if (!pending.empty()) // has a CustomerOrder object
		{
			*m_firstStation += move(pending.front()); // place front of pending line into first station 
			pending.pop_front(); // clean up
		}
		for (auto& s : activeLine)
		{
			s->fill(os);

		}
		for (auto& s : activeLine)
		{
			s->attemptToMoveOrder();
		}
		if (completed.size() + incomplete.size() == m_cntCustomerOrder)
		{
			isFilled = true;
		}
		return isFilled;
	}

	void LineManager::display(std::ostream& os)const
	{
		for_each(activeLine.begin(), activeLine.end(), [&os](Workstation* ws)
		{
			ws->display(os);
		});
	}

}
