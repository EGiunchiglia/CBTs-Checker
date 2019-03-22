//
//  control_flow_node.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "control_flow_node.hpp"

namespace cbt{
    
    
    
    control_flow_node :: control_flow_node(){
        this->sequence_length_=1;
        this->children_= std::vector<task*>();
    };
    
    

    control_flow_node :: control_flow_node(node_type type){
        this->sequence_length_=1;
        this->children_= std::vector<task*>();
        this->type_ = type;
    };
    
    
    
    control_flow_node :: ~control_flow_node(){
        for (auto& c : this->children_){
            delete c;
        }
        
    }
    
    
    void control_flow_node::set_type(node_type type){
        this->type_ = type;
    };
    
    
    
    std::vector<task*> control_flow_node::get_children(){
        return children_;
    };


   int control_flow_node::get_identifier(){
        return this->identifier_;
    };
    
    
    
    void control_flow_node :: add(task * const child){
        this->children_.push_back(child);
    };
    
    
    
    bool control_flow_node :: has_children(){
        if(this->children_.size() == 0){
            throw std::runtime_error("Exception occurred: control flow node without children");
        }
        return true;
    };
    
    
    
  std::tuple<int, int> control_flow_node :: compute_node_params(int id){
    
        int sequence_length = 0;
	this->identifier_ = id;

        
        if(this->get_type()==sequence){
            for(auto& child: this->get_children()){
	        std::tuple <int, int> dummy = child->compute_node_params(id+1);
                sequence_length += std::get<0>(dummy);
		id = std::get<1>(dummy);
            }
        }
        else{
            int current_sequence_length = 0;
            for (auto& child: this->get_children()){
	        std::tuple <int, int> dummy = child->compute_node_params(id+1);
                current_sequence_length += std::get<0>(dummy);
		id = std::get<1>(dummy);
                if(current_sequence_length > sequence_length)
                    sequence_length = current_sequence_length;
            }
        }
        this->sequence_length_ = sequence_length;
        return  std::make_tuple(sequence_length, id);
    };


  int control_flow_node:: set_ex_time(int current_time, task* parent){
        this->has_children();
        /*if (parent->get_type() == fallback){
            unsigned int no_ops_time = parent->get_sequence_length() - this->get_sequence_length();
            current_time += no_ops_time;
	    }*/
        
        if(this->get_type() == root){
	   for(auto& c : this->get_children()){
	       current_time = c->set_ex_time(current_time, this);
	    }
	   return current_time;
        }
        
        if (this->get_type() == sequence){
            for(auto& c : this->get_children()){
                current_time = c->set_ex_time(current_time, this);
            }
            return current_time;
        }
        
        if (this->get_type() == fallback){
            for(auto& c : this->get_children()){
                 current_time = c->set_ex_time(current_time, this);
            }
            return current_time;/*+this->get_sequence_length();*/
        }
        
        if (this->get_type() == parallel){
	    for(auto& c : this->get_children()){
                c->set_ex_time(current_time, this);
            }
            return current_time+1;
        }
        else
            throw std::runtime_error("Input XML file bad format.");
  
   };
    
   int control_flow_node::get_plan(int current_time, task* parent, std::ofstream &file, std::set<action> * const actions){
        this->has_children();
        if(this->get_type() == root){
	    file << "(eta_try_" << this->get_identifier() << " <-> " <<  "eta_succ_" << this->get_identifier() << ") & " << "eta_try_" << this->get_identifier();
            this->get_children().front()->get_plan(current_time, this, file, actions);
            return 0;
        }
        
        if (this->get_type() == sequence){

	    file << " & (eta_succ_" << this->get_identifier() << " -> " << "eta_try_" << this->get_identifier() << ")";
	    file << " & (eta_succ_" << this->get_identifier() << " <-> (";
	    unsigned int j = 0;
            for(auto& c : this->get_children()){
		file << "eta_succ_" << c->get_identifier();
                if(j<this->get_children().size()-1)
                    file << " & ";
		j++;
            }
            file << "))";
	    
	    file << " & (";
	    j = 0;
	    for (auto c = this->get_children().rbegin(); c != this->get_children().rend(); ++c){
	      file << "(eta_try_" << (*c)->get_identifier() << " -> " << "eta_succ_" << (*(c+1))->get_identifier() << ")";
	      if(j < this->get_children().size()-2){
		file << " & ";
	      }
              if(j == this->get_children().size()-2){
        	   break;
	      }
	      j++;
            }
            file << ")";
	    
	    for(auto& c : this->get_children()){
                c->get_plan(current_time, this, file, actions);
	    } 
            return current_time;
        }
        
        if (this->get_type() == fallback){

	    file << " & (eta_succ_" << this->get_identifier() << " -> " << "eta_try_" << this->get_identifier() << ")";
	    file << " & (eta_succ_" << this->get_identifier() << " <-> (";
	    unsigned int i = 0;
            for(auto& c : this->get_children()){
	      	file << "(eta_succ_" << c->get_identifier();
		unsigned int j = 0;
	        for(auto& c1 : this->get_children()){
		  if (c1 != c){
		    if(j<this->get_children().size()-1)
		      file << " & ";
		    file << "!eta_succ_" << c1->get_identifier();
		    j++;
		  }
		}
		if(i < this->get_children().size()-1)
                    file << ") | ";
		i++;
	     }
	    file << "))) & (";

	    unsigned int j = 0;
	    for (auto c = this->get_children().rbegin(); c != this->get_children().rend(); ++c){
	      file << "(eta_try_" << (*c)->get_identifier() << " -> " << "!eta_succ_" << (*(c+1))->get_identifier() << ")";
	      if(j < this->get_children().size()-2){
		file << " & ";
	      }
              if(j == this->get_children().size()-2){
        	   break;
	      }
	      j++;
            }
            file << ")";
	    
            for(auto& c : this->get_children()){
                c->get_plan(current_time, this, file, actions);
            }
            return 0;
        }
        
        if (this->get_type() == parallel){
          file << " & (eta_succ_" << this->get_identifier() << " -> " << "eta_try_" << this->get_identifier() << ")";
	  file << " & (eta_succ_"<< this->get_identifier() << " <-> (";
	  unsigned int j = 0;
	  for(auto& c : this->get_children()){
	    file << "eta_succ_"<< c->get_identifier();
	    if(j<this->get_children().size()-1)
                file << " & ";
	    j++;
          }
	  file << ")) & (eta_try_"<< this->get_identifier() << " <-> (";

	  j = 0;
	  for(auto& c : this->get_children()){
	    file << "eta_try_"<< c->get_identifier();
	    if(j<this->get_children().size()-1)
                file << " | ";
	    j++;
          }
	  file << "))";

	  std::set<std::string> in_parallel_actions;
          for(auto& c : this->get_children()){
                execution_node* ex_node = dynamic_cast<execution_node*>(c);
                if(ex_node == NULL)
                    throw std::runtime_error("Input XML file bad format: parallel node children must be execution nodes");
		in_parallel_actions.insert(ex_node->get_action_label());
          }
	  file << " & (";
	  for(auto& a : *actions){
                if(in_parallel_actions.find(a.get_label()) == in_parallel_actions.end()){
		    execution_node* ex_node = dynamic_cast<execution_node*>(*this->get_children().begin());
                    if (j < actions->size()-1){
		        file << "!" << a.get_label() << "_" << ex_node->get_ex_time() << " & ";
		    }
                    else{
                        file << "!" << a.get_label() << "_" << ex_node->get_ex_time();
                    }
                    j++;
                }
	  }
	  file << ")";
	  
	  for(auto& c : this->get_children()){
                c->get_plan(current_time, this, file, actions);
          }
	  return 0;
	  
        }
        else
            throw std::runtime_error("Input XML file bad format.");
    };
    
}//namespace cbt
