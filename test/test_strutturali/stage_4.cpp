//
//
//  Stage 4: create the CBT plans representation
//
//

#include <stdio.h>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the fourth stage of the pipeline: write on output file the representation of the CBT plans"){
    
    
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();

    
    //First the function tries to open the file
    //We have to test that it raises an exception if it does not manage
    WHEN("The function cannot open the file"){
        REQUIRE_THROWS(cbtree->create_CBT_plan("./not_existing_folder/"));
    }
    
    
    //If it is called by a CFN then it tests if the CFN has children
    //We have to test the raise of the exception
    WHEN("The function can open the file and creates the representation of a CBT with CFN with no children"){
        
        //Suppose the XML file has been read
        cbtree->read_file("./test/test_strutturali/stage_4/complete_CBT_CFN_no_children.xml");
        //that the sence lengths have been computed
        cbtree->compute_length_sequences();
        //and the state graph representation has been written on the file
        cbtree->create_state_graph("./test/test_strutturali/stage_4/sym_output/");
        
        REQUIRE_THROWS_WITH(cbtree->create_CBT_plan("./test/test_strutturali/stage_4/sym_output/"), "Exception occurred: control flow node without children");
        
    }


    
     //In order to test the raise of the exception of the parallel node, we need a CBT with a parallel node with CFN as children
    WHEN("The function can open the file and creates the representation of a CBT with parallel CFN as children"){

        //Suppose the XML file has been read
        cbtree->read_file("./test/test_strutturali/stage_4/complete_CBT_parallel_CFN_children.xml");
        //that the sence lengths have been computed
        cbtree->compute_length_sequences();
        //and the state graph representation has been written on the file
        cbtree->create_state_graph("./test/test_strutturali/stage_4/sym_output/");
        
        REQUIRE_THROWS_WITH(cbtree->create_CBT_plan("./test/test_strutturali/stage_4/sym_output/"), "Input XML file bad format: parallel node children must be execution nodes");

    }
    
    //If the function manages to open the file then, in order to test all the branches,
    //we need a CBT with the follow characteristics:
    //1. A CFN node must be child of a fallback node and must have a sequence length inferior than the parent's one
    //2. There must be a parallel, a fallback and a sequence node
    //3. A EN must be child of a fallback node and define a sequence shorter thant the parent
    WHEN("The function can open the file and creates the representation of the CBT plan"){
        //Suppose the XML file has been read
        cbtree->read_file("./test/test_strutturali/stage_4/complete_CBT.xml");
        //that the sence lengths have been computed
        cbtree->compute_length_sequences();
        //and the state graph representation has been written on the file
        cbtree->create_state_graph("./test/test_strutturali/stage_4/sym_output/");
        
        REQUIRE_NOTHROW(cbtree->create_CBT_plan("./test/test_strutturali/stage_4/sym_output/"));
        
        std::ifstream CBT_plans("./test/test_strutturali/stage_4/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        int num_of_lines = 17;
        std::string line;
        
        while(num_of_lines > 0){
            REQUIRE(!CBT_plans.eof());
            getline(CBT_plans, line);
            num_of_lines--;
        }
        
        REQUIRE(line == "((((((condition1_0 & !action1_0 & !action2_0 & !condition2_0) & (action1_1 & !action2_1 & !condition1_1 & !condition2_1))) | ((!action1_0 & !action2_0 & !condition1_0 & !condition2_0) & (action1_1 & action2_1 & !condition1_1 & !condition2_1)) | (!action1_0 & !action2_0 & !condition1_0 & !condition2_0 & condition2_1 & !action1_1 & !action2_1 & !condition1_1))))");
    }
   
    
}
