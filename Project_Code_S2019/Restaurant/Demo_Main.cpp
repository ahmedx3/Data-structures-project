//#include "Drawing.h"
#include "Rest\Restaurant.h"
#include "GUI\GUI.h"
#include <windows.h>
int main()
{
	PlaySound(TEXT("hamadayel3ab.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	Restaurant* pRest = new Restaurant;
	pRest->RunSimulation();
	
	delete pRest;
	
	

	
	return 0;
}
