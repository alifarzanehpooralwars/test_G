#include "myglobals.h"
#include "G4SystemOfUnits.hh"

//const int MYGLOBALS::NUM_DETECTORS = 24;

//std::vector<G4double> MYGLOBALS::EdepsList = std::vector<G4double>(MYGLOBALS::NUM_DETECTORS);

//const std::vector<Specs> MYGLOBALS::DET_SPECS =
//{
//	{ 1 , 150 * deg, 180 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 2 , 150 * deg, 90  * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 3 , 150 * deg, 0   * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 4 , 150 * deg, 270 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 5 , 125 * deg, 135 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 6 , 125 * deg, 45  * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 7 , 125 * deg, 315 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 8 , 125 * deg, 225 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 9 , 110 * deg, 180 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 10, 110 * deg, 90  * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 11, 110 * deg, 0   * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
//	{ 12, 110 * deg, 270 * deg, 35 * cm, 0.5 * mm, 210  * mm, 175 * mm, 0.5 * cm, 0.5  * mm },
    //////////////////////////////////////////////////
//    { 13 , 30 * deg, 180 * deg, 17.97 * cm, 13.5 * mm, 80   * mm, 80 * mm, 65.5 * mm, 1    * mm },
//	{ 14 , 30 * deg, 90  * deg, 18.35 * cm, 13.5 * mm, 80   * mm, 80 * mm, 66   * mm, 0.5  * mm },
//	{ 15 , 30 * deg, 0   * deg, 19.75 * cm, 13   * mm, 79.5 * mm, 80 * mm, 66   * mm, 0.05 * mm },
//	{ 16 , 30 * deg, 270 * deg, 18.09 * cm, 13.5 * mm, 80   * mm, 80 * mm, 66   * mm, 0.5  * mm },
//	{ 17 , 55 * deg, 135 * deg, 19.13 * cm, 13.5 * mm, 80   * mm, 80 * mm, 68   * mm, 0.5  * mm },
//	{ 18 , 55 * deg, 45  * deg, 18.63 * cm, 17   * mm, 78.5 * mm, 80 * mm, 66   * mm, 0.5  * mm },
//	{ 19 , 55 * deg, 315 * deg, 18.00 * cm, 21   * mm, 79   * mm, 80 * mm, 67   * mm, 0.5  * mm },
//	{ 20 , 55 * deg, 225 * deg, 18.51 * cm, 13   * mm, 79   * mm, 80 * mm, 66   * mm, 0.5  * mm },
//	{ 21 , 70 * deg, 180 * deg, 19.95 * cm, 9    * mm, 87   * mm, 63 * mm, 44   * mm, 0.5  * mm },
//	{ 22 , 70 * deg, 90  * deg, 18.81 * cm, 20   * mm, 79   * mm, 79 * mm, 66   * mm, 0.5  * mm },
//	{ 23 , 70 * deg, 0   * deg, 18.97 * cm, 13   * mm, 79   * mm, 80 * mm, 66   * mm, 0.05 * mm },
//	{ 24 , 70 * deg, 270 * deg, 17.65 * cm, 12.5 * mm, 78   * mm, 80 * mm, 68   * mm, 0.5  * mm }
//};

//////Below HPGe////////
//
const int MYGLOBALS::NUM_DETECTORS = 12;

std::vector<G4double> MYGLOBALS::EdepsList = std::vector<G4double>(MYGLOBALS::NUM_DETECTORS);

const std::vector<Specs> MYGLOBALS::DET_SPECS = {
 	{ 1 , 30 * deg, 180 * deg, 17.97 * cm, 13.5 * mm, 80   * mm, 80 * mm, 65.5 * mm, 1    * mm },
 	{ 2 , 30 * deg, 90  * deg, 18.35 * cm, 13.5 * mm, 80   * mm, 80 * mm, 66   * mm, 0.5  * mm },
	{ 3 , 30 * deg, 0   * deg, 19.75 * cm, 13   * mm, 79.5 * mm, 80 * mm, 66   * mm, 0.05 * mm },
 	{ 4 , 30 * deg, 270 * deg, 18.09 * cm, 13.5 * mm, 80   * mm, 80 * mm, 66   * mm, 0.5  * mm },
 	{ 5 , 55 * deg, 135 * deg, 19.13 * cm, 13.5 * mm, 80   * mm, 80 * mm, 68   * mm, 0.5  * mm },
 	{ 6 , 55 * deg, 45  * deg, 18.63 * cm, 17   * mm, 78.5 * mm, 80 * mm, 66   * mm, 0.5  * mm },
 	{ 7 , 55 * deg, 315 * deg, 18.00 * cm, 21   * mm, 79   * mm, 80 * mm, 67   * mm, 0.5  * mm },
 	{ 8 , 55 * deg, 225 * deg, 18.51 * cm, 13   * mm, 79   * mm, 80 * mm, 66   * mm, 0.5  * mm },
 	{ 9 , 70 * deg, 180 * deg, 19.95 * cm, 9    * mm, 87   * mm, 63 * mm, 44   * mm, 0.5  * mm },
 	{ 10, 70 * deg, 90  * deg, 18.81 * cm, 20   * mm, 79   * mm, 79 * mm, 66   * mm, 0.5  * mm },
 	{ 11, 70 * deg, 0   * deg, 18.97 * cm, 13   * mm, 79   * mm, 80 * mm, 66   * mm, 0.05 * mm },
 	{ 12, 70 * deg, 270 * deg, 17.65 * cm, 12.5 * mm, 78   * mm, 80 * mm, 68   * mm, 0.5  * mm },
 };
//


