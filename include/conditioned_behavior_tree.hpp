//
//  cbt.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//


#ifndef conditioned_behavior_tree_hpp
#define conditioned_behavior_tree_hpp

#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <set>
#include <sstream>
#include <map>

#include "action.hpp"
#include "control_flow_node.hpp"
#include "execution_node.hpp"

namespace cbt{
    
    const std::string name_path_gen_req = "general_requirements.txt";
    const std::string name_path_bt_plans = "BTplans.txt";
    
    /** \brief Concrete class implemeting a Conditioned Behavior Tree. */
    class conditioned_behavior_tree{
    
    public:
        
        /**
         * Constructor.
         * Starts to build the root of the CBT.
         */
        conditioned_behavior_tree();
        
        /**
         * Destructor.
         * Destroys the tree from the root.
         */
        ~conditioned_behavior_tree();
        
        /**
         * Function returning the actions of the vocabulary.
         */
        std::set<action> get_actions();
        
        /**
         * Fuction returning the sequence length of the CBT.
         */
        int get_max_length_sequence();
        
        /**
         * Function inserting a new action of the vocabulary in the set of actions.
         * \param new_action action to be inserted
         */
        void insert_action(action const * const new_action);
        
        /**
         * Function to read the file.
         * \param path string containing the path to the .xml input file
         */
        void read_file(std::string const path);
        
        /**
         * Function to write the state graph to the output file.
         * \param path string containing the path to the output folder
         */
        void create_state_graph(std::string const path, std::string const req_path);
        
        /**
         * Function to write the plans of the CBT to the output file.
         * \param path string containing the path to the output folder
         */
        void create_CBT_plan(std::string const path);
        
        /**
         * Function computing for each node the associated length sequence.
         */
        void compute_length_sequences();

        /**
         * Function computing the execution time for each execution node.
         */
        void compute_ex_times();
      
        /**
         * Function handling the pipeline of function calls to compute the requirements.
         * \param input_path string containing the path to the input .xml file
         * \param req_path string containing the path to the input .txt file with the initial requirements
         * \param output_folder string containing the path to the output folder
         * \param limboole_path string containing the path to the limboole executable
         */
      void compute_initial_requirements(std::string const input_path,std::string const req_path, std::string const output_folder, std::string const limboole_path);



    private:
        
        //Functions to be used to read and check the XML file
        std::string get_next_line(std::ifstream * const);
        std::string read_action_label(std::string const);
        std::string read_condition_label(std::string const);
        void read_single_action(std::ifstream * const);
        void read_actions(std::ifstream * const);
        void read_BT(std::ifstream * const, std::string);
        std::string read_next_node(std::ifstream * const, control_flow_node * const);
        void read_execution_node(std::string, control_flow_node * const);
        void execute_program(std::string);
        
        
    private:
        
        /** Attribute representing the root of the CBT.*/
        control_flow_node* root_;
        /** Attribute representing the set of actions read in the vocabulary.*/
        std::set<action> actions_;
        /** Attribute representing the length of the longest sequence of actions of the entire CBT.*/
        int max_length_sequence_;

    };
    
}//namespace cbt

#endif /* conditioned_behavior_tree_hpp */
