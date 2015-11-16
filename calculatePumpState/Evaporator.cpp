//
//  Evaporator.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Evaporator.hpp"

    Evaporator::Evaporator(){
        T1i = calT1i();
        P1i = calP1i(T1i);
        
    }
    
    Evaporator::Evaporator(double Twai,double Twao,double deltaT_a){
        this->Twai = Twai;
        this->Twao = Twao;
        this->deltaT_a = deltaT_a;
        T1i = calT1i();
        P1i = calP1i(T1i);
        
    }
    
    double Evaporator::calT1i(){
        return Twao - deltaT_a;
    }
    
    /*
     三步计算水的饱和蒸汽压力：
        1、将设施温度换算为开氏温度；
        2、计算lgp;(mmHg);
        3、将mmHg换算为kPa;
     */
    double Evaporator::calP1i(double T1i_C){
        double T1i_K = conversionT_C2K(T1i_C);
        double lgP1i = lgsvp(T1i_K);
        return conversion_P_lgmmHg2kPa(lgP1i);
        
    }

    double Evaporator::getTwai(){
        return Twai;
    }
    
    double Evaporator::getTwao(){
        return Twao;
    }
    
    double Evaporator::getT1i(){
        return T1i;
    }
    
    double Evaporator::getT1o(){
        return T1o;
    }
    
    double Evaporator::getP1i(){
        return P1i;
    }
    
    double Evaporator::getP1o(){
        return P1o;
    }
    
    double Evaporator::getX1i(){
        return X1i;
    }
    
    double Evaporator::getX1o(){
         return X1o;
    }
    
    void Evaporator::printEvaporator(){
        cout << "蒸发器状态参数如下所示:" <<endl;
        cout << "   Twai = "<<Twai<<"˚C"<<endl;
        cout << "   Twao = "<<Twao<<"˚C"<<endl;
        cout << "   ∆Te  = " <<deltaT_a<<"˚C"<<endl;
        cout << "   T1i  = " <<T1i <<"˚C"<<endl;
        cout << "   P1i  = " <<P1i <<"kPa"<<endl;
    }
