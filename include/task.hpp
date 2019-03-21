//
//  task.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 30/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.



#ifndef task_hpp
#define task_hpp

#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <set>
#include <string>
#include <vector>

#include "action.hpp"

namespace cbt{
    
    
    enum node_type {root, sequence, fallback, parallel, execution};

    /** \brief Abstract class representing a general node in the Conditioned Behavior Tree. */
    class task{
        
    public:
        
        /** Virtual destructor of the class task. */
        virtual ~task() {};
        
        /**
         * Virtual function to get the sequence length of a node.
         * Implements the default behavior for both cbt::execution_node and cbt::control_flow_node.
         */
        virtual int get_sequence_length();

        /**
         * Virtual function to get the children of a node.
         * Task implements the deafult behavior: returns an empty vector.
         */
        virtual std::vector<task*> get_children();
        
        /**
         * Virtual function to get the type of the current node.
         */
        virtual node_type get_type();
        
        /**
         * Virtual function to add a new child.
         * Task implements the default behavior: throws an exception.
         * \param new_child the new child to be added
         */
        virtual void add(task * const new_child);
        
        /**
         * Virtual function to acknowledge if a node has children.
         * Task implements the default behavior: returns false.
         */
        virtual bool has_children();


      virtual int get_identifier() = 0;
        
        /**
         * Pure virtual function.
         */
        virtual std::tuple<int, int> compute_node_params(int id) = 0;


        /**
         * Pure virtual function to set the execution time.
         * Implements the default behavior for both cbt::execution_node and cbt::control_flow_node.
         */
        virtual int set_ex_time(int current_time, task* parent) = 0;
        
        
        /**
         * Pure virtual function.
         * \param current_time specifies the instant at which the node starts the execution of its plan
         * \param parent specifies the parent of the current node
         * \param file specifies the file in which we are writing the CBT plans
         * \param actions specifies the list of actions retrieven in the vocabulary
         */
        virtual int get_plan(int current_time, task* parent, std::ofstream & file, std::set<action> * const actions) = 0;
        
    protected:
        
        /** Attribute representing the length of the longest sequence of actions defined by the children of the node itself.*/
        int sequence_length_;
        /** Attribute representing the type of the node itself.*/
        node_type type_;
        /** Attribute representing the execution of the node itself.*/
        int ex_time_;
    };
    
}//namespace cbt
#endif /* task_hpp */
