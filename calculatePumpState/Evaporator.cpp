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
        this->Twei = Twai;
        this->Tweo = Twao;
        this->deltaT_e = deltaT_a;
        T1i = calT1i();
        P1i = calP1i(T1i);
        P1o = P1i;
        T1o = T1i;
        
    }
    
    double Evaporator::calT1i(){
        return Tweo - deltaT_e;
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

    double Evaporator::getTwei(){
        return Twei;
    }
    
    double Evaporator::getTweo(){
        return Tweo;
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
        cout << "\t蒸发器状态参数如下所示:" <<endl;
        
        cout << "\t  已知:" <<endl;
        cout << "\t    Twei = "<<Twei<<"˚C"<<endl;
        cout << "\t    Tweo = "<<Tweo<<"˚C"<<endl;
        
        cout << "\t  假定:" <<endl;
        cout << "\t    ∆Te  = " <<deltaT_e<<"˚C"<<endl;
        
        cout << "\t  求得:" <<endl;
        cout << "\t    T1i  = " <<T1i <<"˚C"<<endl;
        cout << "\t    P1i  = " <<P1i <<"kPa"<<endl;
        cout << "\t    T1o  = " <<T1o <<"˚C"<<endl;
        cout << "\t    P1o  = " <<P1o <<"kPa"<<endl;
    }
