//
//  Formular.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Formular_hpp
#define Formular_hpp

#include <iostream>
#include <math.h>
using namespace std;

double conversionT_C2K(double temperature_C);

double conversionT_K2C(double temperature_K);

double conversion_P_lgmmHg2kPa(double lgp);

double lgsvp(double satsaturationTemperatureH2O);

double dewTLiBr(double satsaturationTemperatureH2O_C, double concentrationOfLiBrSolution);

double enthalpyLiBrSolution(double solutionTemperatureLiBr_C,double concentrationOfLiBrSolution);

#endif /* Formular_hpp */
