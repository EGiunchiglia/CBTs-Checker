//
//
// Stage 1: read the XML file
//
//

#include <stdio.h>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("Test of the first stage of the pipeline: read file"){
    
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();

    //First read_file tries to open the file
    //Check the branch given by file not found
    WHEN("The XML file is not found"){
        REQUIRE_THROWS_WITH(cbtree->read_file("not_existing_path"), "Exception occurred while opening the file: input xml file not found.");
    }
    
    //If it manages it starts to read the actions
    //We have to check all the branches given by errors in the XML file
    WHEN("The XML file contains a bad formed action"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_no_ActionTemplate.xml"), "Input XML file bad format: object ActionTemplate must contain object YARPAction");
    }
    WHEN("The XML file contains actions with contrastant preconditions"){
         REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_contrastant_preconditions0.xml"), "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
    }
    WHEN("The XML file contains actions with contrastant preconditions"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_contrastant_preconditions1.xml"), "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
    }
    WHEN("The XML file contains actions with contrastant postconditions"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_contrastant_postconditions0.xml"), "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
    }
    WHEN("The XML file contains actions with contrastant postconditions"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_contrastant_postconditions1.xml"), "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
    }
    
    //Once completed the actions read_file starts to read the BT
    //We have to check all the branches given by errors in the XML file
    //CBT beginning
    WHEN("The XML file contains a BT not starting with the root"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_no_root.xml"), "Input XML file bad format: Behavior Tree must have a root");
    }
    WHEN("The XML file contains a BT without the tag <BehaviorTree> following the tag <root>"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_no_BehaviorTree.xml"), "Input XML file bad format: root must be followed by <BehaviorTree>");
    }
    //CBT internal
    WHEN("The XML file contains a BT with a not recognized CFN"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_not_recognized_CFN.xml"), "Input XML file bad format: Behavior Tree bad format");
    }
    WHEN("The XML file contains a BT with a not closed sequence tag"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_not_recognized_CFN.xml"), "Input XML file bad format: Behavior Tree bad format");
    }
    WHEN("The XML file contains a BT with a not closed fallback tag"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_not_recognized_CFN.xml"), "Input XML file bad format: Behavior Tree bad format");
    }
    WHEN("The XML file contains a BT with a not closed parallel tag"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_not_recognized_CFN.xml"), "Input XML file bad format: Behavior Tree bad format");
    }
    //CBT ending
    WHEN("The XML file contains a BT in which the tag <Behavior Tree> is not closed"){
         REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_no_closed_BehaviorTree.xml"), "Input XML file bad format: object <Behavior Tree> must be closed");
    }
    WHEN("The XML file contains a BT in which the tag <root> is not closed"){
        REQUIRE_THROWS_WITH(cbtree->read_file("./test/test_strutturali/stage_1/stage_1_no_closed_root.xml"), "Input XML file bad format: object <root> must be closed");
    }
    
    //Case of XML file with no errors --> we need to build a CBT that allows as to cover all the statements still uncovered
    WHEN("The XML file contains no errors"){
        REQUIRE_NOTHROW(cbtree->read_file("./test/test_strutturali/stage_1/complete_CBT.xml"));
        REQUIRE(cbtree->get_actions().size() == 4);
    }
}
