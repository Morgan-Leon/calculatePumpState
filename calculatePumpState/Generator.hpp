//
//  Generator.hpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#ifndef Generator_hpp
#define Generator_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Formular.hpp"

using namespace std;

/*
 溴化锂吸收式热泵的发生器（generator）
 已知Twgi = 150˚C, 一般要求T4o比Twgi低 10˚C 至 40˚C。
 T4o 由吸收器入口溶液浓度X6i和冷凝器中压力P3o决定。P3o由T3o求出。
 即再生器中浓溶液可加热温度，不能过高：高于165℃会使LiBr结晶;亦不能过低，影响加热功率。
 
 发生器:
 
 所求
 状态点    物质       位置           温度/˚C      压力/kPa       焓/(kJ/kg)   质量分数（LiBr）%
 4`      水蒸气    发生器水蒸气出口     T4wo        P4wo            H4wo         X4wo
 4       浓溶液    发生器溶液出口       T4o         P4o             H4o          X4o
 5       稀溶液    发生器入口          T5i         P5i             H5i          X5i
 
 ∆: /'delta/
 
 */

class Generator{
    
private:
    
    
    double T4wo,P4wo,H4wo,X4wo;
    double T4o,P4o,H4o,X4o;
    double T5i,P5i,H5i,X5i;
    
    double calT4o(double,double);
    double calT5i(double,double);
    
    double calH4o(double,double);
    double calH5i(double,double);
    
public:
    
    Generator();
    
    Generator(double T3o, double P3o, double X2o, double X6i);
    
    void printGenerator();
    
    
};

#endif /* Generator_hpp */
