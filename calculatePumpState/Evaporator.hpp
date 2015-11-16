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
 溴化锂吸收式热泵的吸收器（Evaporator）。
 吸收器:
 已知量为二次水的入口温度 Twai = 45˚C、二次水的出口温度 Twao = ˚C,以及∆T
 所求
 状态点    物质       位置          温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 2        稀溶液      吸收器入口      T2i         P2i           H2i         X2i
 6`       浓溶液      吸收器出口      T2o         P2o           H2o         X1o
 
 ∆: /'delta/
 
 */

class Evaporator{
    
private:
    double Twai = 50.0000;
    double Twao;
    double deltaT_a = 3.0000;
    
    double T1i,T1o;
    double P1i,P1o;
    double H1i,H1o;
    double X1i,X1o;
    
public:
    Evaporator();
    Evaporator(double Twai,double Twao,double deltaT_a);
    double calT1i();
    double calP1i(double T1i_C);
    double getT1i();
    double getT1o();
    double getTwai();
    double getTwao();
    double getP1i();
    double getP1o();
    double getX1i();
    double getX1o();
    
    void printEvaporator();

};

#endif /* Evaporator_hpp */
