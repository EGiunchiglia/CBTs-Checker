//
//  task.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//




#include "task.hpp"


namespace cbt{
    
    
    
    int task::get_sequence_length(){
        return this->sequence_length_;
    };
    
    
    
    std::vector<task*> task::get_children(){
        return std::vector<task*>();
    };
    
    
    
    node_type task::get_type(){
        return this->type_;
    };
    


    bool task::has_children() {
        return false;
    };
    
    
    
    void task::add(task * const) {
        throw std::runtime_error("Only control flow nodes can have children");
    };
    
    
}//namespace cbt
