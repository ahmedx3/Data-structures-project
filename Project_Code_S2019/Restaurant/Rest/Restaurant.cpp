#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;

	totalWaitingOrders = 0;

	waitingVIPA = 0;
	waitingVIPB = 0;
	waitingVIPC = 0;
	waitingVIPD = 0;

	waitingFrozenA = 0;
	waitingFrozenB = 0;
	waitingFrozenC = 0;
	waitingFrozenD = 0;

	waitingNormalA = 0;
	waitingNormalB = 0;
	waitingNormalC = 0;
	waitingNormalD = 0;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		simulationTestRun();
	};
}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	delete pGUI;
}

// Main test run for phase 1
void Restaurant::simulationTestRun() {

	load File("D:\\DsProject\\Data-structures-project\\Project_Code_S2019\\Restaurant\\sample.txt", this);		// Loading the files
	File.printInfo();

	int currentTimeStep = 1;

	while (!EventsQueue.isEmpty()) {

		// Execute events now
		ExecuteEvents(currentTimeStep);

		// Print all info in status bar
		printStatusBarInfo(currentTimeStep);

		// Draw orders to screen
		drawOrdersToScreen();

		// Deleting an order from each type in each region
		deleteOrdersEachTimeStep();
		
		// Advance to next timestep
		pGUI->waitForClick();
		currentTimeStep++;
	}

	// continue until no orders are left
	while (totalWaitingOrders > 0) {

		// Print all info in status bar
		printStatusBarInfo(currentTimeStep);

		// Draw orders to screen
		drawOrdersToScreen();

		// Deleting an order from each type in each region
		deleteOrdersEachTimeStep();

		// Advance to next timestep
		pGUI->waitForClick();
		currentTimeStep++;
	}
	// To see last time step
	lastTimeStep(currentTimeStep);
	
	pGUI->PrintMessage("Simulation Over, Click anywhere to exit!");
	pGUI->waitForClick();
}

// Last Time Step too see everything
void Restaurant::lastTimeStep(int currentTimeStep) {
	
	// Print all info in status bar
	printStatusBarInfo(currentTimeStep);

	// Draw orders to screen
	drawOrdersToScreen();

	pGUI->waitForClick();
}

void Restaurant::printStatusBarInfo(int currentTimeStep)
{
	pGUI->ClearStatusBar();

	int lineNo = 0;
	string Time = "Time Step: ";

	// current time step
	char timeStep[10];
	itoa(currentTimeStep, timeStep, 10);
	Time += timeStep;
	pGUI->PrintStatusMessages(Time, lineNo++);

	string FirstLine = "                                   VIP                             Frozen                            Normal";
	pGUI->PrintStatusMessages(FirstLine, lineNo++);

	// Formatting all orders into chars -----------------------------------------------
	char VIPOrdersA[10];
	itoa(waitingVIPA, VIPOrdersA, 10);
	char VIPOrdersB[10];
	itoa(waitingVIPB, VIPOrdersB, 10);
	char VIPOrdersC[10];
	itoa(waitingVIPC, VIPOrdersC, 10);
	char VIPOrdersD[10];
	itoa(waitingVIPD, VIPOrdersD, 10);

	char frozenOrdersA[10];
	itoa(waitingFrozenA, frozenOrdersA, 10);
	char frozenOrdersB[10];
	itoa(waitingFrozenB, frozenOrdersB, 10);
	char frozenOrdersC[10];
	itoa(waitingFrozenC, frozenOrdersC, 10);
	char frozenOrdersD[10];
	itoa(waitingFrozenD, frozenOrdersD, 10);

	char normalOrdersA[10];
	itoa(waitingNormalA, normalOrdersA, 10);
	char normalOrdersB[10];
	itoa(waitingNormalB, normalOrdersB, 10);
	char normalOrdersC[10];
	itoa(waitingNormalC, normalOrdersC, 10);
	char normalOrdersD[10];
	itoa(waitingNormalD, normalOrdersD, 10);
	// -------------------------------------------------------------------------------------

	string regionA = "Region A";
	regionA += "                     ";
	regionA += VIPOrdersA;
	regionA += "                                     ";
	regionA += frozenOrdersA;
	regionA += "                                      ";
	regionA += normalOrdersA;
	pGUI->PrintStatusMessages(regionA, lineNo++);

	string regionB = "Region B";
	regionB += "                    ";
	regionB += VIPOrdersB;
	regionB += "                                     ";
	regionB += frozenOrdersB;
	regionB += "                                      ";
	regionB += normalOrdersB;
	pGUI->PrintStatusMessages(regionB, lineNo++);

	string regionC = "Region C";
	regionC += "                    ";
	regionC += VIPOrdersC;
	regionC += "                                     ";
	regionC += frozenOrdersC;
	regionC += "                                      ";
	regionC += normalOrdersC;
	pGUI->PrintStatusMessages(regionC, lineNo++);

	string regionD = "Region D";
	regionD += "                    ";
	regionD += VIPOrdersD;
	regionD += "                                     ";
	regionD += frozenOrdersD;
	regionD += "                                      ";
	regionD += normalOrdersD;
	pGUI->PrintStatusMessages(regionD, lineNo++);
}

void Restaurant::deleteOrdersEachTimeStep()
{
	// Remove from VIP Orders
	if (dequeueFromOneQueue(VIPOrdersRegionA))
		waitingVIPA--;
	if (dequeueFromOneQueue(VIPOrdersRegionB))
		waitingVIPB--;
	if (dequeueFromOneQueue(VIPOrdersRegionC))
		waitingVIPC--;
	if (dequeueFromOneQueue(VIPOrdersRegionD))
		waitingVIPD--;

	// Remove from Frozen Orders
	if (dequeueFromOneQueue(frozenOrdersRegionA))
		waitingFrozenA--;
	if (dequeueFromOneQueue(frozenOrdersRegionB))
		waitingFrozenB--;
	if (dequeueFromOneQueue(frozenOrdersRegionC))
		waitingFrozenC--;
	if (dequeueFromOneQueue(frozenOrdersRegionD))
		waitingFrozenD--;

	// Remove from Normal Orders
	if (dequeueFromOneQueue(normalOrdersRegionA))
		waitingNormalA--;
	if (dequeueFromOneQueue(normalOrdersRegionB))
		waitingNormalB--;
	if (dequeueFromOneQueue(normalOrdersRegionC))
		waitingNormalC--;
	if (dequeueFromOneQueue(normalOrdersRegionD))
		waitingNormalD--;
}

void Restaurant::cancelOrder(int id)
{
	if (cancelFromCertainQueue(id, normalOrdersRegionA))
		waitingNormalA--;
	if (cancelFromCertainQueue(id, normalOrdersRegionB))
		waitingNormalB--;
	if (cancelFromCertainQueue(id, normalOrdersRegionC))
		waitingNormalC--;
	if (cancelFromCertainQueue(id, normalOrdersRegionD))
		waitingNormalD--;
}

bool Restaurant::cancelFromCertainQueue(int id, Queue<Order*> & queue) {
	Order* pOrd;
	int stopPoint;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		stopPoint = pOrd->GetID();
		if (stopPoint == id) {
			queue.dequeue(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
		else {
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
		}

		queue.peekFront(pOrd);

		while (pOrd->GetID() != stopPoint) {
			if (pOrd->GetID() == id) {
				queue.dequeue(pOrd);
				delete pOrd;
				totalWaitingOrders--;
				return true;
			}
			else {
				queue.dequeue(pOrd);
				queue.enqueue(pOrd);
				queue.peekFront(pOrd);
			}
		}
	}
	return false;
}

bool Restaurant::cancelFromCertainQueue(int id, PriorityQueue<Order*> & queue) {
	Order* pOrd;
	int stopPoint;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		stopPoint = pOrd->GetID();
		if (stopPoint == id) {
			queue.dequeue(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
		else {
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
		}

		queue.peekFront(pOrd);

		while (pOrd->GetID() != stopPoint) {
			if (pOrd->GetID() == id) {
				queue.dequeue(pOrd);
				delete pOrd;
				totalWaitingOrders--;
				return true;
			}
			else {
				queue.dequeue(pOrd);
				queue.enqueue(pOrd);
				queue.peekFront(pOrd);
			}
		}
	}
	return false;
}

bool Restaurant::dequeueFromOneQueue(Queue<Order*> & queue) {
	Order* pOrd;
	bool removed = queue.dequeue(pOrd);
	if (removed) {
		delete pOrd;
		totalWaitingOrders--;
		return true;
	}
	return false;
}

bool Restaurant::dequeueFromOneQueue(PriorityQueue<Order*> & queue) {
	Order* pOrd;
	bool removed = queue.dequeue(pOrd);
	if (removed) {
		delete pOrd;
		totalWaitingOrders--;
		return true;
	}
	return false;
}

bool Restaurant::dequeueFromOneQueue(EnhancedList<Order*> & queue) {
	Order* pOrd;
	bool removed = queue.dequeue(pOrd);
	if (removed) {
		delete pOrd;
		totalWaitingOrders--;
		return true;
	}
	return false;
}

bool Restaurant::cancelFromCertainQueue(int id, EnhancedList<Order*> & queue) {
	Order* pOrd;
	int stopPoint;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		stopPoint = pOrd->GetID();
		if (stopPoint == id) {
			queue.dequeue(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
		else {
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
		}

		queue.peekFront(pOrd);

		while (pOrd->GetID() != stopPoint) {
			if (pOrd->GetID() == id) {
				queue.dequeue(pOrd);
				delete pOrd;
				totalWaitingOrders--;
				return true;
			}
			else {
				queue.dequeue(pOrd);
				queue.enqueue(pOrd);
				queue.peekFront(pOrd);
			}
		}
	}
	return false;
}

void Restaurant::drawOneQueue(Queue<Order*> & queue) {
	Order* pOrd;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		int stopPoint = pOrd->GetID();
		pGUI->AddOrderForDrawing(pOrd);
		queue.dequeue(pOrd);
		queue.enqueue(pOrd);
		queue.peekFront(pOrd);

		while (stopPoint != pOrd->GetID())
		{
			pGUI->AddOrderForDrawing(pOrd);
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
			queue.peekFront(pOrd);
		}
	}
}

void Restaurant::drawOneQueue(PriorityQueue<Order*> & queue) {
	Order* pOrd;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		int stopPoint = pOrd->GetID();
		pGUI->AddOrderForDrawing(pOrd);
		queue.dequeue(pOrd);
		queue.enqueue(pOrd);
		queue.peekFront(pOrd);

		while (stopPoint != pOrd->GetID())
		{
			pGUI->AddOrderForDrawing(pOrd);
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
			queue.peekFront(pOrd);
		}
	}
}

void Restaurant::drawOneQueue(EnhancedList<Order*> & queue) {
	Order* pOrd;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		int stopPoint = pOrd->GetID();
		pGUI->AddOrderForDrawing(pOrd);
		queue.dequeue(pOrd);
		queue.enqueue(pOrd);
		queue.peekFront(pOrd);

		while (stopPoint != pOrd->GetID())
		{
			pGUI->AddOrderForDrawing(pOrd);
			queue.dequeue(pOrd);
			queue.enqueue(pOrd);
			queue.peekFront(pOrd);
		}
	}
}

void Restaurant::drawOrdersToScreen()
{
	// Add VIP Orders for drawing
	drawOneQueue(VIPOrdersRegionA);
	drawOneQueue(VIPOrdersRegionB);
	drawOneQueue(VIPOrdersRegionC);
	drawOneQueue(VIPOrdersRegionD);

	// Add Frozen orders for drawing
	drawOneQueue(frozenOrdersRegionA);
	drawOneQueue(frozenOrdersRegionB);
	drawOneQueue(frozenOrdersRegionC);
	drawOneQueue(frozenOrdersRegionD);

	// Add Normal Orders for drawing
	drawOneQueue(normalOrdersRegionA);
	drawOneQueue(normalOrdersRegionB);
	drawOneQueue(normalOrdersRegionC);
	drawOneQueue(normalOrdersRegionD);

	// Draw screen and clear list of drawables again
	pGUI->UpdateInterface();
	pGUI->ResetDrawingList();
}

////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order type
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}

/// ==> end of DEMO-related function




void Restaurant::addToVIPQueueRegionA(Order * ord)
{
	VIPOrdersRegionA.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPA++;
}

Order * Restaurant::getVIPOrderRegionA()
{
	Order* pOrd;
	VIPOrdersRegionA.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToVIPQueueRegionB(Order * ord)
{
	VIPOrdersRegionB.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPB++;
}

Order * Restaurant::getVIPOrderRegionB()
{
	Order* pOrd;
	VIPOrdersRegionB.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToVIPQueueRegionC(Order * ord)
{
	VIPOrdersRegionC.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPC++;
}

Order * Restaurant::getVIPOrderRegionC()
{
	Order* pOrd;
	VIPOrdersRegionC.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToVIPQueueRegionD(Order * ord)
{
	VIPOrdersRegionD.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPD++;
}

Order * Restaurant::getVIPOrderRegionD()
{
	Order* pOrd;
	VIPOrdersRegionD.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToFrozenQueueRegionA(Order * ord)
{
	frozenOrdersRegionA.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenA++;
}

Order * Restaurant::getFrozenOrderRegionA()
{
	Order* pOrd;
	frozenOrdersRegionA.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToFrozenQueueRegionB(Order * ord)
{
	frozenOrdersRegionB.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenB++;
}

Order * Restaurant::getFrozenOrderRegionB()
{
	Order* pOrd;
	frozenOrdersRegionB.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToFrozenQueueRegionC(Order * ord)
{
	frozenOrdersRegionC.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenC++;
}

Order * Restaurant::getFrozenOrderRegionC()
{
	Order* pOrd;
	frozenOrdersRegionC.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToFrozenQueueRegionD(Order * ord)
{
	frozenOrdersRegionD.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenD++;
}

Order * Restaurant::getFrozenOrderRegionD()
{
	Order* pOrd;
	frozenOrdersRegionD.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToNormalQueueRegionA(Order * ord)
{
	normalOrdersRegionA.enqueue(ord);
	totalWaitingOrders++;
	waitingNormalA++;
}

Order * Restaurant::getNormalOrderRegionA()
{
	Order* pOrd;
	normalOrdersRegionA.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToNormalQueueRegionB(Order * ord)
{
	normalOrdersRegionB.enqueue(ord);
	totalWaitingOrders++;
	waitingNormalB++;
}

Order * Restaurant::getNormalOrderRegionB()
{
	Order* pOrd;
	normalOrdersRegionB.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToNormalQueueRegionC(Order * ord)
{
	normalOrdersRegionC.enqueue(ord);
	totalWaitingOrders++;
	waitingNormalC++;
}

Order * Restaurant::getNormalOrderRegionC()
{
	Order* pOrd;
	normalOrdersRegionC.dequeue(pOrd);
	return pOrd;
}

void Restaurant::addToNormalQueueRegionD(Order * ord)
{
	normalOrdersRegionD.enqueue(ord);
	totalWaitingOrders++;
	waitingNormalD++;
}

Order * Restaurant::getNormalOrderRegionD()
{
	Order* pOrd;
	normalOrdersRegionD.dequeue(pOrd);
	return pOrd;
}