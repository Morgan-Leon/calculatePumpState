//
//  Evaporator.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Evaporator_hpp
#define Evaporator_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Formular.hpp"

using namespace std;

/*
 溴化锂吸收式热泵的蒸发器（Evaporator）。
 蒸发器:

 所求
 状态点    物质       位置          温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 1        水        蒸发器入口      T1i         P1i           H1i         X1i
 1`       水蒸气     蒸发器出口      T1o         P1o           H1o         X1o
 
 ∆: /'delta/
 
 */

class Evaporator{
    
private:
    double Twei;
    double Tweo;
    double deltaT_e;
    
    double T1i,T1o;
    double P1i,P1o;
    double H1i,H1o;
    double X1i,X1o;
    
    double calT1i();
    double calP1i(double T1i_C);

    
public:
    Evaporator();
    Evaporator(double Twei,double Tweo,double deltaT_e);
    double getT1i();
    double getT1o();
    double getTwei();
    double getTweo();
    double getP1i();
    double getP1o();
    double getX1i();
    double getX1o();
    
    void printEvaporator();


};

#endif /* Evaporator_hpp */
