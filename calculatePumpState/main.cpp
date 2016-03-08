//
//  main.cpp
//  calculatePumpState
//
//  Created by Morgan on 15/11/15.
//  Copyright © 2015年 Morgan. All rights reserved.
//

#include <iostream>
#include "LiBrPump.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    
    LiBrPump p1;
    
//    double x[] = {55.1, 62.4, 96.9, 50.8, 3.000, 1.3/2.4, 1.1/2.4, 25, 0.04,5,17};
    
    cout << "<<-----------------------------------------\n";
    
    LiBrPump p2 = LiBrPump(55.1, 62.4, 96.9, 50.8, 3.000,
                           1.3/2.4, 1.1/2.4, 6.0000,
                           25, 0.04, 5, 1);
    
    return 0;
}
