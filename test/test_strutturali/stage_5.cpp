//
//
//  Stage 5: compute a model of the representation and derive the initial requirements
//
//

#include <stdio.h>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the fifth stage of the pipeline: call limboole and write model on file"){

    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    
    //Here there is a unique branch
    REQUIRE_NOTHROW(cbtree->compute_initial_requirements("./test/test_strutturali/stage_5/complete_CBT.xml", "./test/test_strutturali/stage_5/sym_output/", "../limboole1.1/limboole"));
    
    std::ifstream CBT_plans("./test/test_strutturali/stage_5/sym_output/BTplans.txt");
    REQUIRE(CBT_plans.good());
    
    std::ifstream general_req("./test/test_strutturali/stage_5/sym_output/general_requirements.txt");
    REQUIRE(general_req.good());
    
    std::ifstream initial_req("./test/test_strutturali/stage_5/sym_output/initial_requirements.txt");
    REQUIRE(initial_req.good());
}
