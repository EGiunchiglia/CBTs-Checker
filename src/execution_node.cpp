//
//  execution_node.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "execution_node.hpp"


namespace cbt{
    
   
    execution_node::execution_node(std::string label){
        action_label_ = label;
        sequence_length_ = 1;
        type_ = execution;
    };
    
    
    
    std::string execution_node::get_action_label(){
        return this->action_label_;
    };



    int execution_node::get_identifier(){
        return this->identifier_;
    };

  int execution_node::get_ex_time(){
        return this->ex_time_;
    };
    
    std::tuple<int, int> execution_node::compute_node_params(int id){
        this->identifier_ = id; 
        return  std::make_tuple(this->sequence_length_, this->identifier_);
    };


    int execution_node::set_ex_time(int current_time, task* parent){
        
	this->ex_time_ = current_time;
        return current_time+1;

    };
    
    
    int execution_node::get_plan(int current_time, task* parent, std::ofstream &file, std::set<action> * const actions){

        file << " & (eta_succ_" << this->get_identifier() << " -> " << "eta_try_" << this->get_identifier() << ")";
        file << " & (eta_succ_"<< this->get_identifier() << " <-> " << this->get_action_label() << "_" << this->get_ex_time() << ")";

	if (parent->get_type() != parallel){
	  file << " & (";
	  unsigned int j = 0;
	  for(auto& a : *actions){
            if(a.get_label()!= this->get_action_label()){
	      if (j < actions->size()-1)
                file << "!" << a.get_label() << "_" << this->get_ex_time() << " & ";
	      else
		file << "!" << a.get_label() << "_" << this->get_ex_time();
            }
	    j++;
	  }
        
	  file << ")";
	}  
        
        return current_time+1;
    };
    
    
    
}//namespace cbt
