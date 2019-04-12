#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\LinkedList.h"

#include "Order.h"
#include "load.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file

	int totalWaitingOrders;

	int Normal[4];
	int Frozen[4];
	int VIP[4];


	
	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

	PriorityQueue<Order*> VIPOrdersRegionA;	// Queue of all active VIP orders of region A
	PriorityQueue<Order*> VIPOrdersRegionB;	// Queue of all active VIP orders of region B
	PriorityQueue<Order*> VIPOrdersRegionC;	// Queue of all active VIP orders of region C
	PriorityQueue<Order*> VIPOrdersRegionD;	// Queue of all active VIP orders of region D

	Queue<Order*> frozenOrdersRegionA;	// Queue of all active Frozen orders of region A
	Queue<Order*> frozenOrdersRegionB;	// Queue of all active Frozen orders of region B
	Queue<Order*> frozenOrdersRegionC;	// Queue of all active Frozen orders of region C
	Queue<Order*> frozenOrdersRegionD;	// Queue of all active Frozen orders of region D

	LinkedList<Order*> normalOrdersRegionA;	// Queue of all active Normal orders of region A
	LinkedList<Order*> normalOrdersRegionB;	// Queue of all active Normal orders of region B
	LinkedList<Order*> normalOrdersRegionC;	// Queue of all active Normal orders of region C
	LinkedList<Order*> normalOrdersRegionD;	// Queue of all active Normal orders of region D


	int waitingVIPA;
	int waitingVIPB;
	int waitingVIPC;
	int waitingVIPD;

	int waitingFrozenA;
	int waitingFrozenB;
	int waitingFrozenC;
	int waitingFrozenD;

	int waitingNormalA;
	int waitingNormalB;
	int waitingNormalC;
	int waitingNormalD;


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

	// All VIP Orders ------------------------------------------------------------------------------
	void addToVIPQueueRegionA(Order* ord);	// Adds orders to VIP queue
	Order* getVIPOrderRegionA();	// Returns the front VIP order

	void addToVIPQueueRegionB(Order* ord);	// Adds orders to VIP queue
	Order* getVIPOrderRegionB();	// Returns the front VIP order

	void addToVIPQueueRegionC(Order* ord);	// Adds orders to VIP queue
	Order* getVIPOrderRegionC();	// Returns the front VIP order

	void addToVIPQueueRegionD(Order* ord);	// Adds orders to VIP queue
	Order* getVIPOrderRegionD();	// Returns the front VIP order
	// -----------------------------------------------------------------------------------------------

	// All Frozen Orders -----------------------------------------------------------------------------
	void addToFrozenQueueRegionA(Order* ord);	// Adds orders to Frozen queue
	Order* getFrozenOrderRegionA();			// Returns the front Frozen order

	void addToFrozenQueueRegionB(Order* ord);	// Adds orders to Frozen queue
	Order* getFrozenOrderRegionB();			// Returns the front Frozen order

	void addToFrozenQueueRegionC(Order* ord);	// Adds orders to Frozen queue
	Order* getFrozenOrderRegionC();			// Returns the front Frozen order

	void addToFrozenQueueRegionD(Order* ord);	// Adds orders to Frozen queue
	Order* getFrozenOrderRegionD();			// Returns the front Frozen order
	// -----------------------------------------------------------------------------------------------

	// All Normal Orders -----------------------------------------------------------------------------
	void addToNormalQueueRegionA(Order* ord);	// Adds orders to Normal queue
	Order* getNormalOrderRegionA();			// Returns the front normal order

	void addToNormalQueueRegionB(Order* ord);	// Adds orders to Normal queue
	Order* getNormalOrderRegionB();			// Returns the front normal order

	void addToNormalQueueRegionC(Order* ord);	// Adds orders to Normal queue
	Order* getNormalOrderRegionC();			// Returns the front normal order

	void addToNormalQueueRegionD(Order* ord);	// Adds orders to Normal queue
	Order* getNormalOrderRegionD();			// Returns the front normal order
	// -----------------------------------------------------------------------------------------------
	void cancelOrder(int id);			// Cancels an order from all normal orders

	
	void setMCs(int MCNormal[], int MCFrozen[], int MCVIP[]);


	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 

private:
	void drawOneQueue(Queue<Order*>& queue);	// Draws one queue
	void drawOneQueue(PriorityQueue<Order*>& queue);
	void drawOneQueue(LinkedList<Order*>& queue);
	void drawOrdersToScreen();			// Draws all active orders
	void deleteOrdersEachTimeStep();	// deletes orders each time step as if assigning them to bikes
	void printStatusBarInfo(int currentTimeStep);	// prints all info in status bar
	bool cancelFromCertainQueue(int id, Queue<Order*> & queue);	// Cancel order from certain queue
	bool cancelFromCertainQueue(int id, PriorityQueue<Order*>& queue);
	bool dequeueFromOneQueue(Queue<Order*> & queue);	// dequeue one order
	bool dequeueFromOneQueue(PriorityQueue<Order*>& queue);
	bool dequeueFromOneQueue(LinkedList<Order*>& queue);
	bool cancelFromCertainQueue(int id, LinkedList<Order*>& queue);
	void lastTimeStep(int currentTimeStep);	// To see last Time step
};

#endif