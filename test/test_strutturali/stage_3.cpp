//
//
//  Stage 3: create the state graph
//
//

#include <stdio.h>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the third stage of the pipeline: write on output file the representation of the state graph"){
    
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    
    //Suppose the XML file has been read
    cbtree->read_file("./test/test_strutturali/stage_3/complete_CBT.xml");
    //and that the sence lengths have been computed
    cbtree->compute_length_sequences();
    
    //First the function tries to open the output file
    //If it is not possible than it raises an exceptio
    WHEN("It is not possibile to open the output file"){
        REQUIRE_THROWS(cbtree->create_state_graph("./not_existing_folder/"));
    }
    
    //In the case it manages to open the file, in order to cover all branches we need:
    //1. a CBT with two actions sharing the same pre or post condition
    //2. a CBT containing both positive and negative pre and post conditions
    WHEN("We have a CBT with actions sharing pre and post conditions and containing positive and negative conditions"){
        REQUIRE_NOTHROW(cbtree->create_state_graph("./test/test_strutturali/stage_3/sym_output/"));
        std::ifstream CBT_plans("./test/test_strutturali/stage_3/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::string line;
        int num_of_lines = 0;
        
        getline(CBT_plans, line);
        REQUIRE(line == "(action1_0 -> (precondition_0 & precondition1_0)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action1_0 -> (post_1 & !postcondition_1 & postcondition1_1)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action1_1 -> (precondition_1 & precondition1_1)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action1_1 -> (post_2 & !postcondition_2 & postcondition1_2)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action2_0 -> (precondition_0 & precondition2_0)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action2_0 -> (!post_1 & !postcondition_1 & postcondition2_1)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action2_1 -> (precondition_1 & precondition2_1)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(action2_1 -> (!post_2 & !postcondition_2 & postcondition2_2)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(post_0 & !post_1 -> (action2_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(post_1 & !post_2 -> (action2_1)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(postcondition_0 & !postcondition_1 -> (action2_0 | action1_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(postcondition_1 & !postcondition_2 -> (action2_1 | action1_1)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!post_0 & post_1 -> (action1_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!post_1 & post_2 -> (action1_1)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!postcondition1_0 & postcondition1_1 -> (action1_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!postcondition1_1 & postcondition1_2 -> (action1_1)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!postcondition2_0 & postcondition2_1 -> (action2_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line == "(!postcondition2_1 & postcondition2_2 -> (action2_1)) &");
        
        CBT_plans.close();
    }
}
