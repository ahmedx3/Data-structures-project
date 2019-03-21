#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"


#include "Order.h"
#include "load.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

	Queue<Order*> VIPOrders;	// Queue of all active VIP orders
	Queue<Order*> frozenOrders;	// Queue of all active Frozen orders
	Queue<Order*> normalOrders;	// Queue of all active Normal orders


public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	//
	// TODO: Add More Member Functions As Needed
	//

	// Phase 1 simulation function
	void simulationTestRun();

	
	void addToVIPQueue(Order* ord);	// Adds orders to VIP queue
	Order* getVIPOrder();	// Returns the front VIP order

	void addToFrozenQueue(Order* ord);	// Adds orders to Frozen queue
	Order* getFrozenOrder();			// Returns the front Frozen order

	void addToNormalQueue(Order* ord);	// Adds orders to Normal queue
	Order* getNormalOrder();			// Returns the front normal order

	void cancelOrder(int id);			// Cancels an order from normal orders
	


	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 

private:
	void shiftNormalOrders();			// moves Normal Orders around in queue
	void cancelFromNormalOrders();		// Cancels the order
	void drawOrdersToScreen();			// Draws all active orders
	void deleteOrdersEachTimeStep();	// deletes orders each time step as if assigning them to bikes
	void printStatusBarInfo();	// prints all info in status bar
};

#endif