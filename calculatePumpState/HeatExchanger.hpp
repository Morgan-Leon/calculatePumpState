//
//  HeatExchanger.hpp
//  calculatePumpState
//
//  Created by Morgan on 16/3/7.
//  Copyright © 2016年 Morgan. All rights reserved.
//

#ifndef HeatExchanger_hpp
#define HeatExchanger_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Formular.hpp"

using namespace std;

/*
 溴化锂吸收式热泵的溶液热交换器（exchanger）
 降低发生器出口浓溶液温度，升高吸收器出口稀溶液温度，减轻吸收器负载以提高热能系数。
 
 已知：
    稀溶液浓度XL和浓溶液浓度XH，且： XL = X7o = X2o, XH = X8o = X4o
    T8o 与冷端(T2o)温差通常控制在5˚C以上（5-25˚C），即∆T_h = 17（5至25之间）
 
 溶液热交换器:
 
 所求
 状态点    物质       位置           温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 7       稀溶液    发生器方向出口      T7o         ----            H7o          X7o
 8       浓溶液    吸收器方向出口      T8o         ----            H8o          X8o
 
 ∆: /'delta/
 
 */

class HeatExchanger{
    
private:
    
    double XL,XH;
    double deltaT_h = 17;
    double T7o,P7o,H7o,X7o;
    double T8o,P8o,H8o,X8o;
    
public:
    HeatExchanger();
    HeatExchanger(double T2o, double X2o, double X4o, double H4o, double H2o);
    
    double calT8o(double);
    double calH8o(double,double);
    
    double calH7o(double h4, double h2);
    
    void setDeltaT_h(double);
    void setXL(double X2o);
    void setXH(double X4o);
    
    void printHeatExchanger();

    
};
#endif /* HeatExchanger_hpp */
