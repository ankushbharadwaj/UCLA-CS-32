//
//  ScoreList.cpp
//  hwk 1
//
//  Created by Ankush Bharadwaj on 4/15/19.
//  Copyright © 2019 Ankush Bharadwaj. All rights reserved.
//

#include "ScoreList.h"

ScoreList::ScoreList(): scores() {
    
}

int ScoreList::size() const {
    return scores.size();
}

bool ScoreList::add(unsigned long score){
    
    if(score > 100 || score < 0)
        return false;
    
    if(scores.size() >= DEFAULT_MAX_ITEMS)
        return false;
    
    scores.insert(score);
    
    return true;
}


bool ScoreList::remove(unsigned long score){
    
    if(scores.find(score) == -1)
        return false;
    
    
    return scores.erase(scores.find(score));
}

unsigned long ScoreList::minimum() const {
    
    unsigned long min_score = 100;
    
    if(scores.size() == 0)
        return NO_SCORE;
    
    for (int i = 0; i < scores.size(); i++) {
        unsigned long test = 0;
        scores.get(i,test);
        if (test < min_score)
            min_score = test;
        
    }
    
    return min_score;
}

unsigned long ScoreList::maximum() const{
    
    unsigned long max_score = 0;
    
    if(scores.size() == 0) {
        return NO_SCORE;
    }
    
    for (int i = 0; i < scores.size(); i++) {
        unsigned long test = 0;
        scores.get(i,test);
        if (test > max_score)
            max_score = test;
        
    }
    
    return max_score;
}

 
