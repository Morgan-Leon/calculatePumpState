//
//  LiBrPump.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/16.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "LiBrPump.hpp"



class LiBrPump{
private:
    //thermal load : 热负荷Q（KW）
    double thermalLoad = 5000;
    //tdr: Temperature difference ratio 温差比
    //吸收器与冷凝器的温差比
    double a_c_tdr = 1.3/1.1;
    
    //驱动热源温度 Twgi = 150˚C
    double Twgi = 150;
    
    //低品质热源温度：
    double Twei =45,Tweo = 30;
    //所制取热水温度：
    double Twco = 70,Twai = 50;
    
    Evaporator e;
    
    
    
    
public:
    

    
    
};