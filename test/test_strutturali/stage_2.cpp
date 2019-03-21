//
//
// Stage 2: compute the sequence length of each node
//
//

#include <stdio.h>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"

SCENARIO("Test of the second stage of the pipeline: compute sequence length for each node"){
    
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    //In this case if we take the CBT with every type of node
    WHEN("completed the computations"){
        cbtree->read_file("./test/test_strutturali/stage_2/complete_CBT.xml");
        REQUIRE_NOTHROW(cbtree->compute_length_sequences());
        REQUIRE(cbtree->get_max_length_sequence() == 2);
    }
    
}
