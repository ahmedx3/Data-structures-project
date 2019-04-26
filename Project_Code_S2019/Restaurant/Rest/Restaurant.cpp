#include <cstdlib>
#include <time.h>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"

struct Restaurant::info {
	double ST;
	double WT;
	double FT;
	double AT;
	int ID;
};
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
	outputFile.open("output.txt");
	outputFile << "FT ID AT WT ST" << endl;
	 noOfNormOrdersA = 0;
	 noOfNormOrdersB = 0;
	 noOfNormOrdersC = 0;
	 noOfNormOrdersD = 0;

	 noOfFrozenOrdersA = 0;
	 noOfFrozenOrdersC = 0;
	 noOfFrozenOrdersB = 0;
	 noOfFrozenOrdersD = 0;

	 noOfVipOrdersA = 0;
	 noOfVipOrdersB = 0;
	 noOfVipOrdersC = 0;
	 noOfVipOrdersD = 0;

	 totalWaitingA = 0;
	 totalWaitingC = 0;
	 totalWaitingB = 0;
	 totalWaitingD = 0;

	 totalServA = 0;
	 totalServB = 0;
	 totalServC = 0;
	 totalServD = 0;
	 curr = 0;
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	this->mode = pGUI->getGUIMode();
	simulationTestRun();
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
							//////////////////////////////////  Event handling functions   /////////////////////////////

void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Restaurant::ExecuteEvents(int CurrentTimeStep)									//Executes ALL events that should take place at current timestep
{
	
	Event *pE;
	
	while (EventsQueue.peekFront(pE))												//as long as there are more events
	{
		
		if (pE->getEventTime() > CurrentTimeStep)									//no more events at current time
			return;

		pE->Execute(this);
		//Motorcycle* m = nullptr;
		//cout << "ocupied " << occupiedA.peekFront(m) << " isempty " << occupiedA.isEmpty() << endl;
		if (EventsQueue.dequeue(pE)) {
			/*//remove event from the queue
			//outputFile << pE->getEventTime() << " " << pE->getOrderID() << " ";
			//ArrivalEvent* pA = dynamic_cast<ArrivalEvent*>(pE);						// downcast the event to get its info
			//CancelationEvent* pC = dynamic_cast<CancelationEvent*>(pE);
			//PromotionEvent* pP = dynamic_cast<PromotionEvent*>(pE);
			if (pA) {
				if (m != nullptr) {
					cout << "m ST : " << m->getST() << " "<<CurrentTimeStep<< endl;
				}
				m = nullptr;
				//outputFile << pA->getArrivaltime() << " " << CurrentTimeStep - pA->getArrivaltime() << " " ;
				if (pA->getOrderRegion() == A_REG) {

					//cout<<"ocupied "<<occupiedB.peekFront(m)<<" isempty "<<occupiedB.isEmpty()<<endl;
					//cout<<"ocupied "<<occupiedC.peekFront(m)<<" isempty "<<occupiedC.isEmpty()<<endl;

					//outputFile << m->getST() << endl;
					//totalServA += m->getST();
					if (pA->getOrderType() == TYPE_NRM) {
						noOfNormOrdersA++;
					}
					else if (pA->getOrderType() == TYPE_FROZ) {
						noOfFrozenOrdersA++;
					}
					else if (pA->getOrderType() == TYPE_VIP) {
						noOfVipOrdersA++;
					}
					totalWaitingA += CurrentTimeStep - pA->getArrivaltime();
				}
				else if (pA->getOrderRegion() == B_REG) {
				//	occupiedB.peekFront(m);
					//outputFile << m->getST() << endl;
					//totalServB += m->getST();
					totalWaitingB += CurrentTimeStep - pA->getArrivaltime();
					if (pA->getOrderType() == TYPE_NRM) {
						noOfNormOrdersB++;
					}
					else if (pA->getOrderType() == TYPE_FROZ) {
						noOfFrozenOrdersB++;
					}
					else if (pA->getOrderType() == TYPE_VIP) {
						noOfVipOrdersB++;
					}
				}
				else if (pA->getOrderRegion() == C_REG) {
				//	occupiedC.peekFront(m);
					//outputFile << m->getST() << endl;
					//totalServC += m->getST();
					totalWaitingC += CurrentTimeStep - pA->getArrivaltime();
					if (pA->getOrderType() == TYPE_NRM) {
						noOfNormOrdersC++;
					}
					else if (pA->getOrderType() == TYPE_FROZ) {
						noOfFrozenOrdersC++;
					}
					else if (pA->getOrderType() == TYPE_VIP) {
						noOfVipOrdersC++;
					}
				}
				else if (pA->getOrderRegion() == D_REG) {
					//occupiedD.peekFront(m);
					//outputFile << m->getST() << endl;
					//totalServD += m->getST();
					totalWaitingD += CurrentTimeStep - pA->getArrivaltime();
					if (pA->getOrderType() == TYPE_NRM) {
						noOfNormOrdersD++;
					}
					else if (pA->getOrderType() == TYPE_FROZ) {
						noOfFrozenOrdersD++;
					}
					else if (pA->getOrderType() == TYPE_VIP) {
						noOfVipOrdersD++;
					}
				}

			}
			else if (pC) {

			}
			else if (pP) {

			}
		}
		*/
		}
		delete pE;																	//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
	Motorcycle* motor;

	while (VIPMCA.dequeue(motor))
		delete motor;
	while (VIPMCB.dequeue(motor))
		delete motor;
	while (VIPMCC.dequeue(motor))
		delete motor;
	while (VIPMCD.dequeue(motor))
		delete motor;

	while (FrozenMCA.dequeue(motor))
		delete motor;
	while (FrozenMCB.dequeue(motor))
		delete motor;
	while (FrozenMCC.dequeue(motor))
		delete motor;
	while (FrozenMCD.dequeue(motor))
		delete motor;

	while (NormalMCA.dequeue(motor))
		delete motor;
	while (NormalMCB.dequeue(motor))
		delete motor;
	while (NormalMCC.dequeue(motor))
		delete motor;
	while (NormalMCD.dequeue(motor))
		delete motor;

	while (occupiedA.dequeue(motor))
		delete motor;
	while (occupiedB.dequeue(motor))
		delete motor;
	while (occupiedC.dequeue(motor))
		delete motor;
	while (occupiedD.dequeue(motor))
		delete motor;
	outputFile.close();
	delete pGUI;
	delete infoArr;
}

// Main test run for phase 1
void Restaurant::simulationTestRun() {
	
	/////////////////////////////////////////////////////////////////////////////// Getting the input file and processing it.
	pGUI->PrintMessage("Enter simulation file name");
	load File(this);		// Loading the files
	while (!(File.openFile("../Restaurant/" + pGUI->GetString() + ".txt"))) {
		pGUI->PrintMessage("Enter a correct file name");
	 }
	File.processFile();
	File.printInfo();
	//////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////// Initialize motors info.
	sn = File.getNormalSpeed();
	sf = File.getFrozenSpeed();
	sv = File.getVIPSpeed();
	n = File.getNormalMotorsNumber();
	f = File.getFrozenMotorsNumber();
	v = File.getVIPMotorsNumber();
	autoS = File.getTimeLimit();
	int tot = 0; // no of orders
	for (int i = 0; i < 4; i++) {
		tot += n[i] + f[i] + v[i];
	}
	infoArr = new info[tot]; // allocate arr
	setMCs();
	//////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////// Starting the simulation (executing events till all events are executed)
	int currentTimeStep = 1;
	while (!EventsQueue.isEmpty()) {
		//cout << " time " << currentTimeStep << endl;
		ExecuteEvents(currentTimeStep);				// Execute events now
		if (mode != MODE_SLNT) {			
			printStatusBarInfo(currentTimeStep);	// Print all info in status bar		
			drawOrdersToScreen();					// Draw orders to screen
		}
		autoPromoteOrders(currentTimeStep);			//It works with normal orders only if the current Time step >= arrivalTime of the order + autoS
		deleteOrdersEachTimeStep(currentTimeStep);	// Deleting an order from each type in each region
		
		
		if (mode == MODE_INTR)
			pGUI->waitForClick();
		else if (mode == MODE_STEP)
			Sleep(500);	
		currentTimeStep++;							// Advance to next timestep
	}
	//////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////// Events are all executed and the simulation continues until no orders are left

	while (totalWaitingOrders > 0) {

		if (mode != MODE_SLNT) {
			printStatusBarInfo(currentTimeStep);	// Print all info in status bar
			drawOrdersToScreen();					// Draw orders to screen
		}
		autoPromoteOrders(currentTimeStep);			//It works with normal orders only if the current Time step >= arrivalTime of the order + autoS
		deleteOrdersEachTimeStep(currentTimeStep);	// Deleting an order from each type in each region
		if (mode == MODE_INTR)
			pGUI->waitForClick();
		else if (mode == MODE_STEP)
			Sleep(500);
		currentTimeStep++;							// Advance to next timestep
	}
	
	sortInfo(infoArr, curr);
	outputFile << "FT | ID | AT | WT | ST" << endl;
	for (int i = 0; i < curr; i++) {
		outputFile << infoArr[i].FT << " | " << infoArr[i].ID << " | " << infoArr[i].AT << " | " << infoArr[i].WT << " | " << infoArr[i].ST << endl;;
	}
	outputFile << "Region A : " << endl;
	outputFile << "orders: " << noOfFrozenOrdersA + noOfNormOrdersA + noOfVipOrdersA << " [Norm:" << noOfNormOrdersA << ", frozen:" << noOfFrozenOrdersA << ", VIP:" << noOfVipOrdersA << "]" << endl;
	outputFile << "MotorC: " << n[0] + f[0] + v[0] << "[Norm:" << n[0] << ", frozen:" << f[0] << ", vip:" << v[0] << "]" << endl;
	outputFile << "Avg. waiting : " << totalWaitingA / (noOfFrozenOrdersA + noOfNormOrdersA + noOfVipOrdersA) << " Avg serving : "<<totalServA/ (noOfFrozenOrdersA + noOfNormOrdersA + noOfVipOrdersA) << endl;
	outputFile << "Region B : " << endl;
	outputFile << "orders: " << noOfFrozenOrdersB + noOfNormOrdersB + noOfVipOrdersB << " [Norm:" << noOfNormOrdersB << ", frozen:" << noOfFrozenOrdersB << ", VIP:" << noOfVipOrdersB << "]" << endl;
	outputFile << "MotorC: " << n[1] + f[1] + v[1] << "[Norm:" << n[1] << ", frozen:" << f[1] << ", vip:" << v[1] << "]" << endl;
	outputFile << "Avg. waiting : " << totalWaitingB / (noOfFrozenOrdersB + noOfNormOrdersB + noOfVipOrdersB) << " Avg serving : "<<totalServB/ (noOfFrozenOrdersB + noOfNormOrdersB + noOfVipOrdersB) << endl;
	outputFile << "Region C : " << endl;
	outputFile << "orders: " << noOfFrozenOrdersC + noOfNormOrdersC + noOfVipOrdersC << " [Norm:" << noOfNormOrdersC << ", frozen:" << noOfFrozenOrdersC << ", VIP:" << noOfVipOrdersC << "]" << endl;
	outputFile << "MotorC: " << n[2] + f[2] + v[2] << "[Norm:" << n[2] << ", frozen:" << f[2] << ", vip:" << v[2] << "]" << endl;
	outputFile << "Avg. waiting : " << totalWaitingC / (noOfFrozenOrdersC + noOfNormOrdersC + noOfVipOrdersC) << " Avg serving : "<<totalServC/ (noOfFrozenOrdersC + noOfNormOrdersC + noOfVipOrdersC) << endl;
	outputFile << "Region D : " << endl;
	outputFile << "orders: " << noOfFrozenOrdersD + noOfNormOrdersD + noOfVipOrdersD << " [Norm:" << noOfNormOrdersD << ", frozen:" << noOfFrozenOrdersD << ", VIP:" << noOfVipOrdersD << "]" << endl;
	outputFile << "MotorC: " << n[3] + f[3] + v[3] << "[Norm:" << n[3] << ", frozen:" << f[3] << ", vip:" << v[3] << "]" << endl;
	outputFile << "Avg. waiting : " << totalWaitingD / (noOfFrozenOrdersD + noOfNormOrdersD + noOfVipOrdersD) << " Avg serving : "<<totalServD/ (noOfFrozenOrdersD + noOfNormOrdersD + noOfVipOrdersD) << endl;

	//////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////// Finishing simulation
	
	lastTimeStep(currentTimeStep); // To see last time step
	pGUI->PrintMessage("Simulation Over, Click anywhere to exit!");
	pGUI->waitForClick();
	
	//////////////////////////////////////////////////////////////////////////////

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Last Time Step too see everything
void Restaurant::lastTimeStep(int currentTimeStep) {

	if (mode != MODE_SLNT) {
		// Print all info in status bar
		printStatusBarInfo(currentTimeStep);

		// Draw orders to screen
		drawOrdersToScreen();
	}

	if (mode == MODE_INTR)
		pGUI->waitForClick();
	else if (mode == MODE_STEP)
		Sleep(1000);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

	string FirstLine = "                                   VIP                             Frozen                            Normal                            VIP Motors                            Frozen Motors                            Normal Motors";
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

	if (VIP[0] < 9)
		regionA += "                                      ";
	else if (VIP[0] < 100)
		regionA += "                                     ";
	else
		regionA += "                                    ";
	char VIPMCA[10];
	itoa(VIP[0], VIPMCA, 10);
	regionA += VIPMCA;

	if (Frozen[0] < 9)
		regionA += "                                                    ";
	else if (Frozen[0] < 100)
		regionA += "                                                   ";
	else
		regionA += "                                                  ";
	char FrozenMCA[10];
	itoa(Frozen[0], FrozenMCA, 10);
	regionA += FrozenMCA;

	if (Normal[0] < 9)
		regionA += "                                                    ";
	else if (Normal[0] < 100)
		regionA += "                                                   ";
	else
		regionA += "                                                  ";
	char NormalMCA[10];
	itoa(Normal[0], NormalMCA, 10);
	regionA += NormalMCA;
	pGUI->PrintStatusMessages(regionA, lineNo++);


	string regionB = "Region B";
	regionB += "                    ";
	regionB += VIPOrdersB;
	regionB += "                                     ";
	regionB += frozenOrdersB;
	regionB += "                                      ";
	regionB += normalOrdersB;

	if (VIP[1] < 9)
		regionB += "                                      ";
	else if (VIP[1] < 100)
		regionB += "                                     ";
	else
		regionB += "                                    ";
	char VIPMCB[10];
	itoa(VIP[1], VIPMCB, 10);
	regionB += VIPMCB;

	if (Frozen[1] < 9)
		regionB += "                                                    ";
	else if (Frozen[1] < 100)
		regionB += "                                                   ";
	else
		regionB += "                                                  ";
	char FrozenMCB[10];
	itoa(Frozen[1], FrozenMCB, 10);
	regionB += FrozenMCB;

	if (Normal[1] < 9)
		regionB += "                                                    ";
	else if (Normal[1] < 100)
		regionB += "                                                   ";
	else
		regionB += "                                                  ";
	char NormalMCB[10];
	itoa(Normal[1], NormalMCB, 10);
	regionB += NormalMCB;
	pGUI->PrintStatusMessages(regionB, lineNo++);

	string regionC = "Region C";
	regionC += "                    ";
	regionC += VIPOrdersC;
	regionC += "                                     ";
	regionC += frozenOrdersC;
	regionC += "                                      ";
	regionC += normalOrdersC;

	if (VIP[2] < 9)
		regionC += "                                      ";
	else if (VIP[2] < 100)
		regionC += "                                     ";
	else
		regionC += "                                    ";
	char VIPMCC[10];
	itoa(VIP[2], VIPMCC, 10);
	regionC += VIPMCC;

	if (Frozen[2] < 9)
		regionC += "                                                    ";
	else if (Frozen[2] < 100)
		regionC += "                                                   ";
	else
		regionC += "                                                  ";
	char FrozenMCC[10];
	itoa(Frozen[2], FrozenMCC, 10);
	regionC += FrozenMCC;

	if (Normal[2] < 9)
		regionC += "                                                    ";
	else if (Normal[2] < 100)
		regionC += "                                                   ";
	else
		regionC += "                                                  ";
	char NormalMCC[10];
	itoa(Normal[2], NormalMCC, 10);
	regionC += NormalMCC;
	pGUI->PrintStatusMessages(regionC, lineNo++);

	string regionD = "Region D";
	regionD += "                    ";
	regionD += VIPOrdersD;
	regionD += "                                     ";
	regionD += frozenOrdersD;
	regionD += "                                      ";
	regionD += normalOrdersD;

	if (VIP[3] < 9)
		regionD += "                                      ";
	else if (VIP[3] < 100)
		regionD += "                                     ";
	else
		regionD += "                                    ";
	char VIPMCD[10];
	itoa(VIP[3], VIPMCD, 10);
	regionD += VIPMCD;

	if (Frozen[3] < 9)
		regionD += "                                                    ";
	else if (Frozen[3] < 100)
		regionD += "                                                   ";
	else
		regionD += "                                                  ";
	char FrozenMCD[10];
	itoa(Frozen[3], FrozenMCD, 10);
	regionD += FrozenMCD;

	if (Normal[3] < 9)
		regionD += "                                                    ";
	else if (Normal[3] < 100)
		regionD += "                                                   ";
	else
		regionD += "                                                  ";
	char NormalMCD[10];
	itoa(Normal[3], NormalMCD, 10);
	regionD += NormalMCD;
	pGUI->PrintStatusMessages(regionD, lineNo++);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Restaurant::ReturnMotors(int timeStep) {
	Motorcycle* motor;

	while (occupiedA.peekFront(motor))
	{
		if (motor->getFT() > timeStep)
			break;

		occupiedA.dequeue(motor);
		motor->deAssign();

		if (motor->getOrdType() == TYPE_VIP) {
			VIPMCA.enqueue(motor);
			VIP[0]++;
		}
		else if (motor->getOrdType() == TYPE_FROZ) {
			FrozenMCA.enqueue(motor);
			Frozen[0]++;
		}
		else {
			NormalMCA.enqueue(motor);
			Normal[0]++;
		}
	}

	while (occupiedB.peekFront(motor))
	{
		if (motor->getFT() > timeStep)
			break;

		occupiedB.dequeue(motor);
		motor->deAssign();

		if (motor->getOrdType() == TYPE_VIP) {
			VIPMCB.enqueue(motor);
			VIP[1]++;
		}
		else if (motor->getOrdType() == TYPE_FROZ) {
			FrozenMCB.enqueue(motor);
			Frozen[1]++;
		}
		else {
			NormalMCB.enqueue(motor);
			Normal[1]++;
		}
	}

	while (occupiedC.peekFront(motor))
	{
		if (motor->getFT() > timeStep)
			break;

		occupiedC.dequeue(motor);
		motor->deAssign();

		if (motor->getOrdType() == TYPE_VIP) {
			VIPMCC.enqueue(motor);
			VIP[2]++;
		}
		else if (motor->getOrdType() == TYPE_FROZ) {
			FrozenMCC.enqueue(motor);
			Frozen[2]++;
		}
		else {
			NormalMCC.enqueue(motor);
			Normal[2]++;
		}
	}

	while (occupiedD.peekFront(motor))
	{
		if (motor->getFT() > timeStep)
			break;

		occupiedD.dequeue(motor);
		motor->deAssign();

		if (motor->getOrdType() == TYPE_VIP) {
			VIPMCD.enqueue(motor);
			VIP[3]++;
		}
		else if (motor->getOrdType() == TYPE_FROZ) {
			FrozenMCD.enqueue(motor);
			Frozen[3]++;
		}
		else {
			NormalMCD.enqueue(motor);
			Normal[3]++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Order * Restaurant::getOrderById(int i)
{
	Order* order;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region A

	if (normalOrdersRegionA.peekFront(order))	//if there exist at least one order
	{
		int firstId = order->GetID();
		if (firstId == i)
		{
			return order;
		}
		normalOrdersRegionA.removeFront(order);
		normalOrdersRegionA.insertEnd(order);
		while (normalOrdersRegionA.peekFront(order) && order->GetID() != firstId)
		{
			if (order->GetID() == i)
			{
				return order;
			}
			normalOrdersRegionA.removeFront(order);
			normalOrdersRegionA.insertEnd(order);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region B

	if (normalOrdersRegionB.peekFront(order))	//if there exist at least one order
	{
		int firstId = order->GetID();
		if (firstId == i)
		{
			return order;
		}
		normalOrdersRegionB.removeFront(order);
		normalOrdersRegionB.insertEnd(order);
		while (normalOrdersRegionB.peekFront(order) && order->GetID() != firstId)
		{
			if (order->GetID() == i)
			{
				return order;
			}
			normalOrdersRegionB.removeFront(order);
			normalOrdersRegionB.insertEnd(order);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region C

	if (normalOrdersRegionC.peekFront(order))	//if there exist at least one order
	{
		int firstId = order->GetID();
		if (firstId == i)
		{
			return order;
		}
		normalOrdersRegionC.removeFront(order);
		normalOrdersRegionC.insertEnd(order);
		while (normalOrdersRegionC.peekFront(order) && order->GetID() != firstId)
		{
			if (order->GetID() == i)
			{
				return order;
			}
			normalOrdersRegionC.removeFront(order);
			normalOrdersRegionC.insertEnd(order);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region D

	if (normalOrdersRegionD.peekFront(order))	//if there exist at least one order
	{
		int firstId = order->GetID();
		if (firstId == i)
		{
			return order;
		}
		normalOrdersRegionD.removeFront(order);
		normalOrdersRegionD.insertEnd(order);
		while (normalOrdersRegionD.peekFront(order) && order->GetID() != firstId)
		{
			if (order->GetID() == i)
			{
				return order;
			}
			normalOrdersRegionD.removeFront(order);
			normalOrdersRegionD.insertEnd(order);
		}
	}
	return NULL;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::autoPromoteOrders(int TS)
{
	bool promotionExists = false;
	Order* ord;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region A
	if (normalOrdersRegionA.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
	{
		promotionExists = true;
		while (normalOrdersRegionA.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
		{
			normalOrdersRegionA.removeFront(ord);
			ord->SetType(TYPE_VIP);
			ord->setPriority();
			totalWaitingOrders--;
			waitingNormalA--;
			addToVIPQueueRegionA(ord);
			
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region B
	if (normalOrdersRegionB.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
	{
		promotionExists = true;
		while (normalOrdersRegionB.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
		{
			normalOrdersRegionB.removeFront(ord);
			ord->SetType(TYPE_VIP);
			ord->setPriority();
			totalWaitingOrders--;
			waitingNormalB--;
			addToVIPQueueRegionB(ord);
			
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region C
	if (normalOrdersRegionC.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
	{
		promotionExists = true;
		while (normalOrdersRegionC.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
		{
			normalOrdersRegionC.removeFront(ord);
			ord->SetType(TYPE_VIP);
			ord->setPriority();
			totalWaitingOrders--;
			waitingNormalC--;
			addToVIPQueueRegionC(ord);
			
		}

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////Region D
	if (normalOrdersRegionD.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
	{
		promotionExists = true;
		while (normalOrdersRegionD.peekFront(ord) && TS >= (ord->getArrTime() + autoS))
		{
			normalOrdersRegionD.removeFront(ord);
			ord->SetType(TYPE_VIP);
			ord->setPriority();
			totalWaitingOrders--;
			waitingNormalD--;
			addToVIPQueueRegionD(ord);
			
		}

	}

	return promotionExists;
}

void Restaurant::sortInfo(info* in, int size)
{
	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			//cout << "sort " << in[i].FT << " " << in[j].FT <<" i : "<<i<<" j : "<<j<<endl;
			if (in[i].FT > in[j].FT) {
				info temp = in[j];
				in[j] = in[i];
				in[i] = temp;
			}
			else if (in[i].FT == in[j].FT) {
				if (in[i].ST > in[j].ST) {
					info temp = in[j];
					in[j] = in[i];
					in[i] = temp;
				}
			}
		}
	}
	
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::promoteToVIP(int i, double extraMoney)
{
	
	Order* ord = getOrderById(i);
	if (ord == NULL) return false;

	if (ord->GetRegion() == A_REG) {
		ord->SetType(TYPE_VIP);
		ord->setMoney(ord->getMoney() + extraMoney);
		ord->setPriority();
		addToVIPQueueRegionA(ord);
		cancelOrder(ord->GetID());
	}
	else if (ord->GetRegion() == B_REG) 
	{
		ord->SetType(TYPE_VIP);
		ord->setMoney(ord->getMoney() + extraMoney);
		ord->setPriority();
		addToVIPQueueRegionB(ord);
		cancelOrder(ord->GetID());

	}
	else if (ord->GetRegion() == C_REG)
	{
		ord->SetType(TYPE_VIP);
		ord->setMoney(ord->getMoney() + extraMoney);
		ord->setPriority();
		addToVIPQueueRegionC(ord);
		cancelOrder(ord->GetID());

	}
	else
	{
		ord->SetType(TYPE_VIP);
		ord->setMoney(ord->getMoney() + extraMoney);
		ord->setPriority();
		addToVIPQueueRegionD(ord);
		cancelOrder(ord->GetID());
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::deleteOrdersEachTimeStep(int timeStep)
{

	// Check if any motorcycles returned
	ReturnMotors(timeStep);

	// Remove from VIP Orders
	while (dequeueFromOneQueue(VIPOrdersRegionA, n[0], v[0], f[0], timeStep)) {
		waitingVIPA--;
	}
	while (dequeueFromOneQueue(VIPOrdersRegionB, n[1], v[1], f[1], timeStep))
		waitingVIPB--;
	while (dequeueFromOneQueue(VIPOrdersRegionC, n[2], v[2], f[2], timeStep))
		waitingVIPC--;
	while (dequeueFromOneQueue(VIPOrdersRegionD, n[3], v[3], f[3], timeStep))
		waitingVIPD--;

	// Remove from Frozen Orders
	while (dequeueFromOneQueue(frozenOrdersRegionA, timeStep))
		waitingFrozenA--;
	while (dequeueFromOneQueue(frozenOrdersRegionB, timeStep))
		waitingFrozenB--;
	while (dequeueFromOneQueue(frozenOrdersRegionC, timeStep))
		waitingFrozenC--;
	while (dequeueFromOneQueue(frozenOrdersRegionD, timeStep))
		waitingFrozenD--;

	// Remove from Normal Orders
	while (dequeueFromOneQueue(normalOrdersRegionA, timeStep))
		waitingNormalA--;
	while (dequeueFromOneQueue(normalOrdersRegionB, timeStep))
		waitingNormalB--;
	while (dequeueFromOneQueue(normalOrdersRegionC, timeStep))
		waitingNormalC--;
	while (dequeueFromOneQueue(normalOrdersRegionD, timeStep))
		waitingNormalD--;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::setMCs()
{
	for (int i = 0; i < 4; i++) {
		Normal[i] = n[i];
		Frozen[i] = f[i];
		VIP[i] = v[i];
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < Normal[i]; j++) {

			REGION reg;

			if (i == 0)
				reg = A_REG;
			else if (i == 1)
				reg = B_REG;
			else if (i == 2)
				reg = C_REG;
			else
				reg = D_REG;

			Motorcycle* motor = new Motorcycle(-1, TYPE_NRM, sn, reg, IDLE, 100);

			if (i == 0)
				NormalMCA.enqueue(motor);
			else if (i == 1)
				NormalMCB.enqueue(motor);
			else if (i == 2)
				NormalMCC.enqueue(motor);
			else
				NormalMCD.enqueue(motor);
		}

		for (int j = 0; j < VIP[i]; j++) {

			REGION reg;

			if (i == 0)
				reg = A_REG;
			else if (i == 1)
				reg = B_REG;
			else if (i == 2)
				reg = C_REG;
			else
				reg = D_REG;

			Motorcycle* motor = new Motorcycle(-1, TYPE_VIP, sv, reg, IDLE, 100);

			if (i == 0)
				VIPMCA.enqueue(motor);
			else if (i == 1)
				VIPMCB.enqueue(motor);
			else if (i == 2)
				VIPMCC.enqueue(motor);
			else
				VIPMCD.enqueue(motor);
		}

		for (int j = 0; j < Frozen[i]; j++) {

			REGION reg;

			if (i == 0)
				reg = A_REG;
			else if (i == 1)
				reg = B_REG;
			else if (i == 2)
				reg = C_REG;
			else
				reg = D_REG;

			Motorcycle* motor = new Motorcycle(-1, TYPE_FROZ, sf, reg, IDLE, 100);

			if (i == 0)
				FrozenMCA.enqueue(motor);
			else if (i == 1)
				FrozenMCB.enqueue(motor);
			else if (i == 2)
				FrozenMCC.enqueue(motor);
			else
				FrozenMCD.enqueue(motor);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::dequeueFromOneQueue(Queue<Order*> & queue, int timeStep) {
	Order* pOrd;
	bool removed = queue.peekFront(pOrd);
	if (removed) {
		Motorcycle* m = nullptr;
		bool assigned = AssignOrder(pOrd, timeStep,m);
		if (assigned) {
			if (m) {
				cout <<"order : "<<pOrd->GetID()<< " order region " << pOrd->GetRegion() << " type " << pOrd->GetType() << endl;
				//cout << "order : " << pOrd->GetID() << " in region : " << pOrd->GetRegion() << " arrived at " << pOrd->getArrTime() << " assigned motor at " << timeStep << " " << " finished at " << m->getFT() << " serviced at " << m->getST() << endl;
				if (pOrd->GetRegion() == A_REG) {
					totalServA += m->getST();
					totalWaitingA += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersA++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersA++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersA++;
					}
				}
				else if (pOrd->GetRegion() == B_REG) {
					totalServB += m->getST();
					totalWaitingB += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersB++;
					}
				}
				else if (pOrd->GetRegion() == C_REG) {
					totalServC += m->getST();
					totalWaitingC += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersC++;
					}
				}
				else if (pOrd->GetRegion() == D_REG) {
					totalServD += m->getST();
					totalWaitingD += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersD++;
					}
				}
				info x;
				x.AT = pOrd->getArrTime();
				x.ID = pOrd->GetID();
				x.FT = m->getFT();
				x.ST = m->getST();
				x.WT = timeStep - pOrd->getArrTime();
				infoArr[curr] = x;
				
			
				curr+= 1;
			}
			queue.dequeue(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Restaurant::dequeueFromOneQueue(PriorityQueue<Order*> & queue, int noOFNormalAvailable, int noOFVIPAvailable, int noOfFrozenAvailable, int timeStep) {
	Order* pOrd;

	bool removed = queue.peekFront(pOrd);
	
	if (removed) {
		//cout << pOrd->getArrTime() << " from delete" << endl;
		Motorcycle* m = nullptr;
		bool assigned = AssignOrder(pOrd, timeStep,m);
		if (assigned) {
			if (m) {
				cout << "order : " << pOrd->GetID() << " order region " << pOrd->GetRegion() << " type " << pOrd->GetType() << endl;
			//	cout << "order : " << pOrd->GetID() << " in region : " << pOrd->GetRegion() << " arrived at " << pOrd->getArrTime() << " assigned motor at " << timeStep  << " " << " finished at " << m->getFT() << " serviced at " << m->getST() << endl;
				if (pOrd->GetRegion() == A_REG) {
					totalServA += m->getST();
					totalWaitingA += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersA++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersA++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersA++;
					}
				}
				else if (pOrd->GetRegion() == B_REG) {
					totalServB += m->getST();
					totalWaitingB += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersB++;
					}
				}
				else if (pOrd->GetRegion() == C_REG) {
					totalServC += m->getST();
					totalWaitingC += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersC++;
					}
				}
				else if (pOrd->GetRegion() == D_REG) {
					totalServD += m->getST();
					totalWaitingD += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersD++;
					}
				}
				info x;
				x.AT = pOrd->getArrTime();
				x.ID = pOrd->GetID();
				x.FT = m->getFT();
				x.ST = m->getST();
				x.WT = timeStep - pOrd->getArrTime();
				infoArr[curr] = x;
				//cout << "curr " << curr << " info X : " << infoArr[curr].FT << endl;
				curr+= 1;
			}
			queue.dequeue(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::dequeueFromOneQueue(LinkedList<Order*> & queue, int timeStep) {
	Order* pOrd;
	bool removed = queue.peekFront(pOrd);
	if (removed) {
		Motorcycle* m = nullptr;
		bool assigned = AssignOrder(pOrd, timeStep,m);
		if (assigned) {
			if (m) {
				cout << "order : " << pOrd->GetID() << " order region " << pOrd->GetRegion() << " type " << pOrd->GetType() << endl;
				//cout << "order : " << pOrd->GetID() << " in region : " << pOrd->GetRegion() << " arrived at " << pOrd->getArrTime() << " assigned motor at " << timeStep  << " " << " finished at " << m->getFT() << " serviced at " << m->getST() << endl;
				if (pOrd->GetRegion() == A_REG) {
					totalServA += m->getST();
					totalWaitingA += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersA++;
					}else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersA++;
					}else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersA++;
					}
				}
				else if (pOrd->GetRegion() == B_REG) {
					totalServB += m->getST();
					totalWaitingB += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersB++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersB++;
					}
				}
				else if (pOrd->GetRegion() == C_REG) {
					totalServC += m->getST();
					totalWaitingC += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersC++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersC++;
					}
				}
				else if (pOrd->GetRegion() == D_REG) {
					totalServD += m->getST();
					totalWaitingD += timeStep - pOrd->getArrTime();
					if (pOrd->GetType() == TYPE_NRM) {
						noOfNormOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_FROZ) {
						noOfFrozenOrdersD++;
					}
					else if (pOrd->GetType() == TYPE_VIP) {
						noOfVipOrdersD++;
					}
				}
				info x;
				x.AT = pOrd->getArrTime();
				x.ID = pOrd->GetID();
				x.FT = m->getFT();
				x.ST = m->getST();
				x.WT = timeStep - pOrd->getArrTime();
			//	cout << " X : " << x.FT << endl;
				infoArr[curr] = x;
			//	cout << "curr " << curr << " info X : " << infoArr[curr].FT << endl;
				curr+= 1;
			}
			queue.removeFront(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::AssignOrder(Order* & ord, int timeStep,Motorcycle* &m) {
	if (ord->GetType() == TYPE_VIP)
		return VIPAssign(ord, timeStep,m);
	else if (ord->GetType() == TYPE_FROZ)
		return FrozAssign(ord, timeStep,m);
	else
		return NormAssign(ord, timeStep,m);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::VIPAssign(Order* & ord, int timeStep, Motorcycle* &m) {
	Motorcycle* motor;

	if (ord->GetRegion() == A_REG) {
		if (VIPMCA.peekFront(motor)) {
			VIPMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[0]--;
			occupiedA.enqueue(motor);
			m = motor;
			return true;
		}
		else if (NormalMCA.peekFront(motor)) {
			NormalMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[0]--;
			occupiedA.enqueue(motor);
			m = motor;
			return true;
		}
		else if (FrozenMCA.peekFront(motor)) {
			FrozenMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[0]--;
			occupiedA.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == B_REG) {
		if (VIPMCB.peekFront(motor)) {
			VIPMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else if (NormalMCB.peekFront(motor)) {
			NormalMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else if (FrozenMCB.peekFront(motor)) {
			FrozenMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == C_REG) {
		if (VIPMCC.peekFront(motor)) {
			VIPMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else if (NormalMCC.peekFront(motor)) {
			NormalMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else if (FrozenMCC.peekFront(motor)) {
			FrozenMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else {
		if (VIPMCD.peekFront(motor)) {
			VIPMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else if (NormalMCD.peekFront(motor)) {
			NormalMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else if (FrozenMCD.peekFront(motor)) {
			FrozenMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::FrozAssign(Order* & ord, int timeStep, Motorcycle* &m) {
	Motorcycle* motor;

	if (ord->GetRegion() == A_REG) {
		if (FrozenMCA.peekFront(motor)) {
			FrozenMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[0]--;
			occupiedA.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == B_REG) {
		if (FrozenMCB.peekFront(motor)) {
			FrozenMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == C_REG) {
		if (FrozenMCC.peekFront(motor)) {
			FrozenMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else {
		if (FrozenMCD.peekFront(motor)) {
			FrozenMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			Frozen[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool Restaurant::NormAssign(Order* & ord, int timeStep, Motorcycle* &m) {
	Motorcycle* motor;

	if (ord->GetRegion() == A_REG) {
		if (NormalMCA.peekFront(motor)) {
			NormalMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[0]--;
			
			 occupiedA.enqueue(motor) ;
			 m = motor;
			return true;
		}
		else if (VIPMCA.peekFront(motor)) {
			VIPMCA.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[0]--;
			
			occupiedA.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == B_REG) {
		if (NormalMCB.peekFront(motor)) {
			NormalMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else if (VIPMCB.peekFront(motor)) {
			VIPMCB.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[1]--;
			occupiedB.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else if (ord->GetRegion() == C_REG) {
		if (NormalMCC.peekFront(motor)) {
			NormalMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else if (VIPMCC.peekFront(motor)) {
			VIPMCC.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[2]--;
			occupiedC.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}

	else {
		if (NormalMCD.peekFront(motor)) {
			NormalMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			Normal[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else if (VIPMCD.peekFront(motor)) {
			VIPMCD.dequeue(motor);
			motor->Assign(ord, timeStep);
			VIP[3]--;
			occupiedD.enqueue(motor);
			m = motor;
			return true;
		}
		else
			return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Restaurant::cancelFromCertainQueue(int id, LinkedList<Order*> & queue) {
	Order* pOrd;
	int stopPoint;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		stopPoint = pOrd->GetID();
		if (stopPoint == id) {
			queue.removeFront(pOrd);
			delete pOrd;
			totalWaitingOrders--;
			return true;
		}
		else {
			queue.removeFront(pOrd);
			queue.insertEnd(pOrd);
		}

		queue.peekFront(pOrd);

		while (pOrd->GetID() != stopPoint) {
			if (pOrd->GetID() == id) {
				queue.removeFront(pOrd);
				delete pOrd;
				totalWaitingOrders--;
				return true;
			}
			else {
				queue.removeFront(pOrd);
				queue.insertEnd(pOrd);
				queue.peekFront(pOrd);
			}
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::drawOneQueue(PriorityQueue<Order*> & queue) {
	Order* pOrd;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		Queue<Order*> tempQ;				//solves the problem of enqueuing in the same place in priority queue

											//The previous code:-
											/*int stopPoint = pOrd->GetID();
											pGUI->AddOrderForDrawing(pOrd);
											queue.dequeue(pOrd);
											tempQ.enqueue(pOrd);
											queue.peekFront(pOrd);*/
		while (!queue.isEmpty())			//if(stopPoint != pOrd->GetID()) --> this was the the previous condition
		{
			pGUI->AddOrderForDrawing(pOrd);
			queue.dequeue(pOrd);
			tempQ.enqueue(pOrd);
			queue.peekFront(pOrd);
		}
		while (!tempQ.isEmpty())
		{
			tempQ.dequeue(pOrd);
			queue.enqueue(pOrd);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::drawOneQueue(LinkedList<Order*> & queue) {
	Order* pOrd;
	bool exists = queue.peekFront(pOrd);
	if (exists) {
		int stopPoint = pOrd->GetID();
		pGUI->AddOrderForDrawing(pOrd);
		queue.removeFront(pOrd);
		queue.insertEnd(pOrd);
		queue.peekFront(pOrd);

		while (stopPoint != pOrd->GetID())
		{
			pGUI->AddOrderForDrawing(pOrd);
			queue.removeFront(pOrd);
			queue.insertEnd(pOrd);
			queue.peekFront(pOrd);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
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
	for (int i = 0; i < EventCnt; i++)
	{
		int O_id = i + 1;

		//Rendomize order type
		int OType;
		if (i < EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if (i < EventCnt*0.5)
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal


		int reg = rand() % REG_CNT;	//randomize region


		//Randomize event time
		EvTime += rand() % 4;
		pEv = new ArrivalEvent(EvTime, O_id, (ORD_TYPE)OType, (REGION)reg);
		AddEvent(pEv);

	}

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while (DEMO_Queue.dequeue(pOrd))
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToVIPQueueRegionA(Order * ord)
{
	VIPOrdersRegionA.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPA++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getVIPOrderRegionA()
{
	Order* pOrd;
	VIPOrdersRegionA.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToVIPQueueRegionB(Order * ord)
{
	VIPOrdersRegionB.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPB++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getVIPOrderRegionB()
{
	Order* pOrd;
	VIPOrdersRegionB.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToVIPQueueRegionC(Order * ord)
{
	VIPOrdersRegionC.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPC++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getVIPOrderRegionC()
{
	Order* pOrd;
	VIPOrdersRegionC.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToVIPQueueRegionD(Order * ord)
{
	VIPOrdersRegionD.enqueue(ord);
	totalWaitingOrders++;
	waitingVIPD++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getVIPOrderRegionD()
{
	Order* pOrd;
	VIPOrdersRegionD.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToFrozenQueueRegionA(Order * ord)
{
	frozenOrdersRegionA.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenA++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getFrozenOrderRegionA()
{
	Order* pOrd;
	frozenOrdersRegionA.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToFrozenQueueRegionB(Order * ord)
{
	frozenOrdersRegionB.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenB++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getFrozenOrderRegionB()
{
	Order* pOrd;
	frozenOrdersRegionB.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToFrozenQueueRegionC(Order * ord)
{
	frozenOrdersRegionC.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenC++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getFrozenOrderRegionC()
{
	Order* pOrd;
	frozenOrdersRegionC.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToFrozenQueueRegionD(Order * ord)
{
	frozenOrdersRegionD.enqueue(ord);
	totalWaitingOrders++;
	waitingFrozenD++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getFrozenOrderRegionD()
{
	Order* pOrd;
	frozenOrdersRegionD.dequeue(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToNormalQueueRegionA(Order * ord)
{
	normalOrdersRegionA.insertEnd(ord);
	totalWaitingOrders++;
	waitingNormalA++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getNormalOrderRegionA()
{
	Order* pOrd;
	normalOrdersRegionA.removeFront(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToNormalQueueRegionB(Order * ord)
{
	normalOrdersRegionB.insertEnd(ord);
	totalWaitingOrders++;
	waitingNormalB++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getNormalOrderRegionB()
{
	Order* pOrd;
	normalOrdersRegionB.removeFront(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToNormalQueueRegionC(Order * ord)
{
	normalOrdersRegionC.insertEnd(ord);
	totalWaitingOrders++;
	waitingNormalC++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getNormalOrderRegionC()
{
	Order* pOrd;
	normalOrdersRegionC.removeFront(pOrd);
	return pOrd;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Restaurant::addToNormalQueueRegionD(Order * ord)
{
	normalOrdersRegionD.insertEnd(ord);
	totalWaitingOrders++;
	waitingNormalD++;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Order * Restaurant::getNormalOrderRegionD()
{
	Order* pOrd;
	normalOrdersRegionD.removeFront(pOrd);
	return pOrd;
}