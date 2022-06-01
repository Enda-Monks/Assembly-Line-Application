# Assembly Line
# Auther: Kathleen Monks
# Purpose: Final Project OOP345, REFLECTION
# Date of completion: 2021-12-06


This Final Project provided hands on experience in working with various types of containers. Mainly, vectors, and deques. 

I say, "hands on", because the project centers around an Assembly Line which relies very much on sequential customer orders. 

The AssemblyLine.txt data file provides records which embody vector objects. While each station record is insequentially ordered, 
the station fields are paired with the name of the next station in line. This second field acts something like a pointer. Nodes 
in any vector container are similar in nature.

The CustomerOrder queues are more aptly placed in various deque containers. This organized fashion of pushing objects through each
workstation is sequential in nature.

	// Workstation.h
	extern std::deque<CustomerOrder> pending; // global queues
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

These containers act something like a data stream. As programmers, we can command an object be "popped from the front" of a deque 
container:

	// LineManager.cpp
	pending.pop_front(); // line 110

It's also worth noting that the Final Project provided aple practice of algorithms. Various algorithms were used to loop through the 
containers mentioned above. Including "for_each", and a more complex nesting of a "find_if" loop:

	// LineManager.cpp
	auto firstActive = *std::find_if(activeLine.begin(), activeLine.end(), [&](Workstation* ws) // line 74
	{
		return *std::find_if(activeLine.begin(), activeLine.end(), [&ws](Workstation* next)
		{
			return (next->getNextStation() && next->getNextStation()->getItemName() == ws->getItemName()) ? 						false : true;
		});
					
	}); 

Overall, I appreciated the chance to implement concepts learned throughout this term. The scale of this project being larger than any 
workshop, also happily challenged me in the debugging portion of my work.
