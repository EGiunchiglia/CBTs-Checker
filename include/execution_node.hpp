//
//  execution_node.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.


#ifndef execution_node_hpp
#define execution_node_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include <set>
#include <tuple>

#include "task.hpp"

namespace cbt{
    
    /** \brief Concrete class implementing the behavior of an execution node (leaf node of the Behavior Tree). */

    class execution_node : public task {        
        
    public:
        
        /**
         * Constructor.
         * Sets the action_label_ atribute equal to the std::string passed as parameter, the sequence_lenght equal to 1
         * and the node_type_ equal to execution.
         * \param label specifies the label of the new node
         */
        execution_node(std::string label);
        
        /**
         * Function returning the action_label_ attribute.
         */
        std::string get_action_label();


        /**
         * Function returning the identifier_ attribute.
         */
        int get_identifier();



        /**
         * Function returning the identifier_ attribute.
         */
        int get_ex_time();

      

        /**
         * Function returning the sequence_length_ associated to the execution_node (hence 1) and settinf the identifier.
         */
        std::tuple<int, int> compute_node_params(int id);


        /**
         * Function computing the execution time for the execution node.
         */
        int set_ex_time(int current_time, task* parent);
	  
        
        /**
         * Function writing the plan associated to the cbt::execution_node on the file passed as std::ofstream& in input.
         * \param current_time specifies the instant at which the node starts the execution of its plan
         * \param parent specifies the parent of the current node
         * \param file specifies the file in which we are writing the CBT plans
         * \param actions specifies the list of actions retrieven in the vocabulary
         */
        int get_plan(int current_time, task* parent, std::ofstream& file, std::set<action> * const actions);
        
    private:
        
        /**Attribute representing the action label associated to the execution node */
        std::string action_label_;
        /**Unique identifier of the node**/ 
        int identifier_;
        /** Excecution time of the node**/
        int ex_time_;
    };
    
}//namespace cbt

#endif /* execution_node_hpp */
