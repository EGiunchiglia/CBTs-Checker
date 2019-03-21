//
//  control_flow_node.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//


#ifndef control_flow_node_hpp
#define control_flow_node_hpp

#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>

#include "execution_node.hpp"
#include "task.hpp"

namespace cbt{
    
    /** \brief Concrete class implementing the behavior of a control flow node (internal node of the Behavior Tree). */
    class control_flow_node : public task {
      
    public:
        
        /**
         * Basic constructor.
         * Sets the sequence_length_ to 1 and the vector of children to the empty vector.
         */
        control_flow_node();
        
        /**
         * Constructor with node_type as input.
         * Sets the sequence_length_ to 1, the vector of children to the empty vector and the node type
         * to the type passed as input.
         * \param type specifies the type for the new node
         */
        control_flow_node(node_type type);
        
        /**
         * Destructor.
         * Deletes all its children.
         */
        ~control_flow_node();
    
        /**
         * Set the type of the node to the type passed as parameter.
         * \param type specifies the type for the calling node
         */
        void set_type(node_type type);
        
        /**
         * Returns the children of the node.
         */
        std::vector<task*> get_children();


        /**
         * Function returning the identifier_ attribute.
         */
        int get_identifier();
        
        /**
         * Adds a new child to the children of the node.
         * \param child specifies the new child to be added
         */
        void add(task * const child);

        /**
         * Checks if the node has children. If it has not throws an exception, otherwise it returns true.
         */
        bool has_children();
        
        /**
         * Function computing the length of the longest sequence of actions associated with the node and the identifier of the node.
         */
        std::tuple<int, int> compute_node_params(int id);

         /**
         * Function setting the execution time for execution nodes.
         */
        int set_ex_time(int current_time, task* parent);
        
        /**
         * Function returning the plan associated with the node.
         * \param current_time specifies the instant at which the node starts the execution of its plan
         * \param parent specifies the parent of the current node
         * \param file specifies the file in which we are writing the CBT plans
         * \param actions specifies the list of actions retrieven in the vocabulary
         */
        int get_plan(int current_time, task* parent, std::ofstream & file, std::set<action> * const actions);
        
   
    private:
        
        /** Attribute representing the children of the execution_node.*/
        std::vector<task*> children_;
        /**Unique identifier of the node**/ 
        int identifier_;

    };
    
}//namespace cbt

#endif /* control_flow_node_hpp */
