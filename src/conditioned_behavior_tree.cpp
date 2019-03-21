//
//  cbt.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "conditioned_behavior_tree.hpp"

namespace cbt{
    
    conditioned_behavior_tree::conditioned_behavior_tree(){
        this->root_ = new control_flow_node(root);
        this->max_length_sequence_ = 0;
    };
    
    
    
    conditioned_behavior_tree::~conditioned_behavior_tree(){
        delete root_;
    }
  
    
    
    std::set<action> conditioned_behavior_tree::get_actions(){
        return this->actions_;
    };
    
    
    
    int conditioned_behavior_tree::get_max_length_sequence(){
        return this->max_length_sequence_;
    };
    
    
    
    void conditioned_behavior_tree::insert_action(action const * const new_action){
        
        if(!this->actions_.insert(*new_action).second){
            std::cerr << "Warning: action " << new_action->get_label() << " specified more than one time in the XML file." <<std::endl;
            std::cerr << "New pre and post conditions not memorized" << std::endl;
        }
    };
    
    
   
    //Function that ignores empty lines and whitespaces at the beginning of each
    //line. Takes as input the ifstream and returns the next full line.
    std::string conditioned_behavior_tree::get_next_line(std::ifstream * const file){
        std::string line = "";
        bool end_file = false;
        while(line.length() == 0 and !end_file){
            if(!file->eof()) {
                std::getline(*file >> std::ws,line);
            }
            else
                end_file = true;
        }
        return line;
    };
    
    
    
    //Function that, given a line, returns the cleaned action label.
    std::string conditioned_behavior_tree::read_action_label(std::string const line){
        unsigned long first_quotation_marks = line.find("\"");
        unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
        std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
        if (label.length()==0 || second_quotation_marks == std::string::npos)
            throw std::runtime_error("Input XML file bad format: YARPAction must have identifier surrounded by quotation marks");
        std::transform(label.begin(), label.end(), label.begin(), ::tolower);
        if(label.find(" ") != std::string::npos)
            throw std::runtime_error("Input XML file bad format: YARPAction cannot contain whitespaces");
        return label;
    };
    
    
    
    //Function that, given a line, returns the cleaned condition label.
    std::string conditioned_behavior_tree::read_condition_label(std::string const line){
        unsigned long first_quotation_marks = line.find("\"");
        unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
        std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
        if (label.length()==0 || second_quotation_marks == std::string::npos)
            throw std::runtime_error("Input XML file bad format: Pre and Post conditions must have identifier surrounded by quotation marks");
        std::transform(label.begin(), label.end(), label.begin(), ::tolower);
        if(label.substr(0,3).find("not")!=std::string::npos){
            if(label.substr(4).find(" ") != std::string::npos){
                throw std::runtime_error("Input XML file bad format: after \"not \" Pre and Post conditions cannot contain whitespaces");
            }
            label = "!" + label.substr(4);
        }else{
            if(label.find(" ") != std::string::npos)
                throw std::runtime_error("Input XML file bad format: positive Pre and Post conditions cannot contain whitespaces");
        }
        return label;
    };
    
    
    
    //Function processing and storing a single action
    void conditioned_behavior_tree::read_single_action(std::ifstream * const file){
        action* new_action = new action();
        
        //Get the label of the action and check the input format
        std::string line;
        line = get_next_line(file);
        if (line.substr(0,11).find("YARPAction") == std::string::npos)
            throw std::runtime_error("Input XML file bad format: object ActionTemplate must contain object YARPAction");
        
        std::string action_label = read_action_label(line);
        new_action->set_label(action_label);
        
        //Get the Pre-conditions of the action and check the input format
        std::string pre_label;
        line = get_next_line(file);
        while(line.substr(0,13).find("Precondition") != std::string::npos){
            pre_label = read_condition_label(line);

            if(pre_label[0] == '!' && std::find(new_action->get_pre().begin(), new_action->get_pre().end(), pre_label.substr(1)) != new_action->get_pre().end()){
                throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
            }
            
            else if(pre_label[0] != '!' && (std::find(new_action->get_pre().cbegin(), new_action->get_pre().cend(), "!" + pre_label) != new_action->get_pre().cend())) {
                throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
            }
            new_action->insert_pre(pre_label);
            
            line = get_next_line(file);
        };
        
        
        //Get the Post-conditions of the action and check the input format
        std::string post_label;
        while(line.substr(0,14).find("Postcondition") != std::string::npos){
            post_label = read_condition_label(line);
            if(post_label[0] == '!' && std::find(new_action->get_post().begin(), new_action->get_post().end(), post_label.substr(1)) != new_action->get_post().end()){
                throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
            }
            else if(post_label[0] != '!' && std::find(new_action->get_post().begin(), new_action->get_post().end(), ("!" + post_label)) != new_action->get_post().end()) {
                throw std::runtime_error("Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
            }
            new_action->insert_post(post_label);
            line = get_next_line(file);
        };
        
        //Check end of the function
        if (line.compare("</ActionTemplate>") != 0)
            throw std::runtime_error("Input XML file bad format: object ActionTemplate must end with </ActionTemplate>");
        
        //Insert the new action in the list of actions
        this->insert_action(new_action);
    };
    
    
    
    void conditioned_behavior_tree::read_execution_node(std::string line, control_flow_node * const parent){
        unsigned long first_quotation_marks = line.find("\"");
        unsigned long second_quotation_marks = line.find("\"", first_quotation_marks+1);
        std::string label = line.substr(first_quotation_marks+1, second_quotation_marks-first_quotation_marks-1);
        std::transform(label.begin(), label.end(), label.begin(), ::tolower);
        action* dummy_action = new action();
        dummy_action->set_label(label);
        
        if(line.find("YARPAction") != std::string::npos){
            if(this->actions_.find(*dummy_action) == this->actions_.end())
                throw std::runtime_error("Action not defined in the vocabulary");
        }
        if(line.find("YARPCondition") != std::string::npos){
            this->insert_action(dummy_action);
        }
        execution_node* node = new execution_node(label);
        parent->add(node);
    };
    
    
    
    std::string conditioned_behavior_tree::read_next_node(std::ifstream *const file, control_flow_node * const parent){
        std::string line = get_next_line(file);
        if(line.find("YARP") != std::string::npos){
            read_execution_node(line, parent);
            if (parent->get_type() == root)
                line = get_next_line(file);
            return line;
        }
        else if(line.find("</") != std::string::npos){
            return line;
        }
        else {
            control_flow_node* node = new control_flow_node();
            if(line.find("<Sequence>")!= std::string::npos)
                node->set_type(sequence);
            else if(line.find("<Fallback>")!= std::string::npos)
                node->set_type(fallback);
            else if(line.find("<Parallel>")!= std::string::npos)
                node->set_type(parallel);
            else
                throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
            parent->add(node);
            
            do{
                line = read_next_node(file, node);
            }while(line.find("YARP") != std::string::npos);
            
            //Check that the node is closed
            if (node->get_type() == sequence && line.find("</Sequence>")== std::string::npos)
                    throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
            else if (node->get_type() == fallback && line.find("</Fallback>") == std::string::npos)
                    throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
            else if (node->get_type() == parallel && line.find("</Parallel>") == std::string::npos)
                    throw std::runtime_error("Input XML file bad format: Behavior Tree bad format");
            
            do{
                line = read_next_node(file, parent);
            }while(line.find("YARP") != std::string::npos);
            
            return line;
        }
    }
    
    
    
    void conditioned_behavior_tree::read_BT(std::ifstream *const file, std::string line){
        //Check that the tree starts
        if (line.substr(0, 6).compare("<root>") != 0){
            throw std::runtime_error("Input XML file bad format: Behavior Tree must have a root");
        }
        
        std::string bt_line =get_next_line(file);
        if (bt_line.substr(0, 14).compare("<BehaviorTree>") != 0){
            throw std::runtime_error("Input XML file bad format: root must be followed by <BehaviorTree>");
        }
        line = read_next_node(file, root_);
        if (line.substr(0, 15).compare("</BehaviorTree>") != 0){            
            throw std::runtime_error("Input XML file bad format: object <Behavior Tree> must be closed");
        }
        line = get_next_line(file);
        if (line.substr(0, 7).compare("</root>") != 0){
            throw std::runtime_error("Input XML file bad format: object <root> must be closed");
        }

    };
    
    
    
    //Function handling the pipeline necessary to read and check the input XML file.
    void conditioned_behavior_tree::read_file(std::string const path){
        
        std::ifstream file;
        file.open(path);
        if (!file.good())
            throw std::runtime_error("Exception occurred while opening the file: input xml file not found.");
 
        //Read the vocabulary of actions
        std::string line = get_next_line(&file);
        while(line == "<ActionTemplate>"){
            read_single_action(&file);
            line = get_next_line(&file);
        }
        //Read the BT
        read_BT(&file, line);
        
    };
    
    
    
    void conditioned_behavior_tree::compute_length_sequences(){
        this->root_->compute_node_params(0);
        this->max_length_sequence_ = this->root_->get_sequence_length();
    };
    

    void conditioned_behavior_tree::compute_ex_times(){
        this->root_->set_ex_time(0, this->root_);
     };
  
    
    void conditioned_behavior_tree::create_state_graph(std::string const output_folder){
        std::ofstream file;
        file.exceptions (std::ofstream::failbit | std::ofstream::badbit );

        std::string output_path_bt_plans = output_folder + name_path_bt_plans;
        
 
        file.open(output_path_bt_plans, std::ios::out);
        if (!file.good())
            throw std::runtime_error("Exception occurred while creating output file for BT plans.");
        
        
        //Write all the formulas of the state graph of the type:
        // a_i --> \big_wedge {c_i | c \in Pre}
        // a_i --> \bigwedge {c_{i+1} | c \in Post}
        for(auto& a: this->actions_){
            for(int i=0; i < this->max_length_sequence_; i++){
                
                if(a.get_pre().size()>0){
                    unsigned int k = 0;
                    file << "(" << a.get_label() << "_" << i << " & (";
                    for(auto& pre: a.get_pre()){
                        if(k < a.get_pre().size()-1)
			    file << "!" <<  pre << "_" << i << " | ";
                        else
                            file << "!" <<  pre << "_" << i;
                        k++;
                    }
                    file << ")) | \n";
                }
	     }
	 }
	
        for(auto& a: this->actions_){
            for(int i=0; i < this->max_length_sequence_; i++){                   
                if(a.get_post().size()>0){
                    unsigned int k=0;
                    file  << "(" << a.get_label() << "_" << i << " -> (";
                    for(auto& post: a.get_post()){
                        if(k < a.get_post().size()-1)
                            file <<  post << "_" << (i+1) << " & ";
                        else
                            file <<  post << "_" << (i+1);
                        k++;
                    }
                    file << ")) & \n";
                }
            }
        }
        //Write all formulas of the state graph of the type
        // (c_i \wedge \neg c_{i+1}) --> \big_vee {a_i | \neg c \in Post}
        // (\neg c_i \wedge c_{i+1}) --> \big_vee {a_i | c \in Post}
        
        //First we create a map from each condition to all the actions that generete that postcondition
        std::map<std::string, std::vector<std::string>> formulas;
        for(auto& a: this->actions_){
            std::string action = a.get_label();
            for(auto& post : a.get_post()){
                std::vector<std::string> actions;
                actions.insert(actions.begin(), action);
                std::pair<std::map<std::string,std::vector<std::string>>::iterator,bool> ret;
                ret = formulas.insert(std::pair<std::string, std::vector<std::string>> (post, actions));
                if (!ret.second){ //it means that the pair with that condition already existed in the map, in that case nothing is inserted
                    ret.first->second.insert(ret.first->second.begin(), action);
                }
            }
        }
        
        //Given the map we can write all the formulas
        for (auto& pair: formulas){
            for (int i=0; i < max_length_sequence_; i++){
                file << "(";
                if (pair.first.substr(0,1).compare("!") == 0)
                    file << pair.first.substr(1) << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
                else
                    file << "!" << pair.first << "_" << i << " & " << pair.first << "_" << i+1 << " -> (";
                unsigned int j=0;
                for (auto& a : pair.second){
                    if(j < pair.second.size()-1)
                        file << a << "_" << i << " | ";
                    else
                        file << a << "_" << i;
                    j++;
                }
                
                file << ")) &\n";
            }
        }
        
        file.flush();
        file.close();
    };
    
    
    //Function that creates the CBT plan
    void conditioned_behavior_tree::create_CBT_plan(std::string const output_folder){
        std::ofstream file;
        file.exceptions (std::ofstream::failbit | std::ofstream::badbit );
        
        std::string output_path_bt_plans = output_folder + name_path_bt_plans;
        
       
        file.open(output_path_bt_plans, std::ios::app);
        this->root_->get_plan(0, this->root_, file, &this->actions_);
        
        file.close();
        
    };
    
    
    void conditioned_behavior_tree::execute_program(std::string c){
        
        
        std::string command(c);
        
        std::array<char, 128> buffer;
        std::string result;
        
        FILE* pipe = popen(command.c_str(), "r");
        
        while (fgets(buffer.data(), 128, pipe) != NULL) {
            result += buffer.data();
        }
        pclose(pipe);
        
    }
    
    //Function handling the pipeline of the functions to call
    void conditioned_behavior_tree::compute_initial_requirements(std::string const input_path, std::string const output_folder, std::string const limboole_path){
        this->read_file(input_path);
        this->compute_length_sequences();
	this->compute_ex_times();
        this->create_state_graph(output_folder);
        this->create_CBT_plan(output_folder);
        
        std::string output_path_bt_plans = output_folder + name_path_bt_plans;
        std::string output_path_gen_req = output_folder + name_path_gen_req;
        
        std::string init_req_path = output_folder + "initial_requirements.txt";
        std::string command_string = limboole_path + " -s " + output_path_bt_plans + ">> " + output_path_gen_req;
        
        //If file already exixts remove such file
        remove(output_path_gen_req.c_str());
        
        //system(command_string.c_str());
        execute_program(command_string);
        
        std::ifstream general_requirements;
        std::ofstream initial_requirements;
     
        general_requirements.open(output_path_gen_req);
        initial_requirements.open(init_req_path, std::ios::out);
        

        std::string line;
        while(getline(general_requirements, line)){
            if (line[line.size()-5] == '0'){
                initial_requirements << line << std::endl;
            }
        }

        general_requirements.close();
        initial_requirements.close();
        
    };
    
    
    
}//namespace cbt
    
    
