//
//  Formular.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include "Formular.hpp"


/*
 摄氏度转开尔文温度
 */
double conversionT_C2K(double temperature_C){
    return temperature_C + 273.15;
}

/*
 开尔文温度转摄氏度
 */
double conversionT_K2C(double temperature_K){
    return temperature_K - 273.15;
}

/*
 mmHg与kPa换算
 */
double conversion_P_lgmmHg2kPa(double lgp){
    return  pow(10, lgp)*0.1333224;
}

/*计算水的饱和蒸汽压力
 Calculate saturated vapor pressure(svp) of H2O.
 lgsvp，lg为以10为底的对数
 */
double lgsvp(double satsaturationTemperatureH2O_K){
    double lgsvp;
    double t = satsaturationTemperatureH2O_K;
    double lgT = log10(t);
    lgsvp = 31.46559 - 8.2*lgT - 3142.305/t + 0.0024804*t;
    return lgsvp;
}


/*计算溴化锂的露点温度(Calculate dew temperature of LiBr)
 
 satsaturationTemperatureH2O_C:水的饱和温度（摄氏度）
 concentrationOfLiBrSolution :100kg 溴化锂水溶液中含有溴化锂的千克数
 此方程试用范围：
 0℃ < satsaturationTemperatureH2O_C < 100℃
 45% < concentrationOfLiBrSolution < 65%
 */

double dewTLiBr(double satsaturationTemperatureH2O_C, double concentrationOfLiBrSolution){
    
    double a[]={0.770033,1.45455e-2,-2.63906e-4,2.27609e-6};
    double b[]={140.877,-8.55749,0.16709,-8.82641e-4};
    
    double t= satsaturationTemperatureH2O_C;
    double x = concentrationOfLiBrSolution;
    
    double sum1 =0.000000 ,sum2=0.000000;
    
    //循环语句用于求和
    for (int i =0; i<4; i++) {
        sum1+=t*a[i]*pow(x, i);
        sum2+=b[i]*pow(x, i);
    }
    
    double dewTLiBr = sum1 + sum2;
    
    return dewTLiBr;
}

/*计算溴化锂水溶液的焓值（Calculate the enthalpy of LiBr solution）单位：kcal/kg;
 
 solutionTemperatureLiBr_C: 溴化锂溶液的温度，˚C
 concentrationOfLiBrSolution :100kg 溴化锂水溶液中含有溴化锂的千克数
 
 
    solutionTemperatureLiBr_C ≤ 200 ˚C
 30% < concentrationOfLiBrSolution < 75%
 
 1千卡(kcal)=1大卡=4.184千焦(kJ)
 */
double enthalpyLiBrSolution(double solutionTemperatureLiBr_C,double concentrationOfLiBrSolution){
    double a[] = {3.22313e2,3.83413e2,-2.65438e3,2.87262e3};
    double b[] = {4.19928,-9.39005,1.60770e1,-1.36171e1};
    double c[] = {1.00479e-3,-1.41857e-3,-2.06186e-3,5.92438e-3};
    double sum1 = 0.00000000 , sum2 = 0.0000000 , sum3 = 0.0000000;
    double t = solutionTemperatureLiBr_C;
    double x = concentrationOfLiBrSolution/100;
    double h;
    /*
     sum1 = ∑ax^n
     */
    for (int i=0; i<4; i++) {
        sum1 += a[i]*pow(x,i);
        sum2 += b[i]*pow(x, i);
        if (i<3) {
            sum3 += c[i]*pow(x,i);
        }
    }
    
    h = sum1 + sum2*t  + (sum3 + pow(c[3],3)*x)*t*t;
    
    return  h;
    
}
