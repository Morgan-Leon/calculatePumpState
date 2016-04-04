//
//  Condenser.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Condenser_hpp
#define Condenser_hpp

#include <stdio.h>
#include <iostream>
#include "Formular.hpp"

/*
 溴化锂吸收式热泵的冷凝器（Condenser）。
 冷凝器:
 已知量为二次水的出口温度Twco = 70˚C,以及∆T = 5
 所求
 状态点    物质       位置          温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 3        水        冷凝器出口      T3o         P3o           H3o          X3o
 
 */

class Condenser{
    
private:
    //冷凝器出口水温要略高于二次水出口，其大小由冷凝管决定（3-5˚C）
    double deltaT_c = 5;
    
    double Twco = 70;
    
    double T3o,P3o,H3o,X3o;
    
    double calT3o();
    
    double calX3o();
    
    double calH3o(double t);
    
    double calP3o(double t);

public:
    Condenser();
    
    Condenser(double Twco, double deltaT_c);
    
    double setDeltaT_C(double);
    
    double setTwco(double);
    
    double getT3o();
    
    double getP3o();
    
    double getH3o();
    
    
    void printCondenser();
};

#endif /* Condenser_hpp */
