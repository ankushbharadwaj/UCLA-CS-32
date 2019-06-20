//
//  testScoreList.cpp
//  hwk 1
//
//  Created by Ankush Bharadwaj on 4/15/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include <iostream>

#include "ScoreList.h"

using namespace std;

int main(){
    
    ScoreList f;
    
    assert(f.maximum() == NO_SCORE);
    assert(f.add(0));
    assert(f.add(5));
    assert(f.add(100));
    assert(f.add(6));
    assert(f.add(35));
    assert(f.add(3));
    
    assert(!f.add(101));
    assert(!f.add(-5));
    
    assert(f.maximum() == 100);
    assert(f.minimum() == 0);
    
    assert(f.remove(100));
    assert(!f.remove(7));
    assert(f.remove(0));
    
    assert(f.maximum() == 35);
    assert(f.minimum() == 3);
    assert(f.size() == 4);
    
    cout << "All tests succeed" << endl;
}

