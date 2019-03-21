//
//  main.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 02/06/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include <stdio.h>
#include <string>

#include "conditioned_behavior_tree.hpp"

int main(int argc, const char * argv[]) {
 
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    
    if (argc < 3){
        std::cerr << "Input Error: expected 3 inputs to the program\n";
        return 1;
    }
    
    std::string input_path = argv[1];//"./input/example-file-prepost.xml"; //
    std::string output_folder = argv[2]; //"./output/";//
    std::string limboole_path = argv[3];//"./bin/limboole";//
    
    try{
        cbtree->compute_initial_requirements(input_path, output_folder, limboole_path);
    }
    catch(const std::exception &e){
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    delete cbtree;
    std::cout << "Computation of requirements completed" << std::endl;
    return 0;
}
