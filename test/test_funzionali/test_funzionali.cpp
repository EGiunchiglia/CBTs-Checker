#include <stdio.h>
#include <string>

#include "catch.hpp"

#include "conditioned_behavior_tree.hpp"


SCENARIO("The user wants to compute the initial requirements of a CBT given an illegal input"){
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    
    std::string input_path = "";
    std::string output_folder = "./test/test_funzionali/sym_output/";
    std::string limboole_path = "../limboole1.1/limboole";

    
    WHEN("the input has no root"){
        std::string input_path = "./test/test_funzionali/illegal/req_f1_1.xml";
        THEN("it should rise an exception stating that the CBT must have a root"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: Behavior Tree must have a root");
        }
    }
    
    WHEN("the input has more than one external root"){
        std::string input_path = "./test/test_funzionali/illegal/req_f1_2.xml";
        THEN("it should rise an exception saying that <root> is followed by <Behavior Tree>"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: root must be followed by <BehaviorTree>");
        }
    }
    
    WHEN("the input presents also an internal root"){
        std::string input_path = "./test/test_funzionali/illegal/req_f1_3.xml";
        THEN("it should rise an exception stating that the CBT is badly formatted"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: Behavior Tree bad format");
        }
    }
    
    WHEN("the input presents a sequence node with no children"){
        std::string input_path = "./test/test_funzionali/illegal/req_f2_1.xml";
        THEN("it should rise an exception saying that a CFN must have children"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Exception occurred: control flow node without children");
        }
    }
    
    WHEN("the input presents a parallel node with no children"){
        std::string input_path = "./test/test_funzionali/illegal/req_f2_2.xml";
        THEN("it should rise an exception saying that a CFN must have children"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Exception occurred: control flow node without children");
        }
    }
    
    WHEN("the input presents a fallback node with no children"){
        std::string input_path = "./test/test_funzionali/illegal/req_f2_3.xml";
        THEN("it should rise an exception saying that a CFN must have children"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Exception occurred: control flow node without children");
        }
    }
    
    WHEN("the input presents a bad formed precondition"){
        std::string input_path = "./test/test_funzionali/illegal/req_f3_1.xml";
        THEN("it should rise an exception saying that Pre and Post conditions should either contain no whitespaces or contain \"not \""){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: after \"not \" Pre and Post conditions cannot contain whitespaces");
        }
    }
    
    WHEN("the input presents a bad formed postcondition"){
        std::string input_path = "./test/test_funzionali/illegal/req_f3_2.xml";
        THEN("it should rise an exception saying that Pre and Post conditions should either contain no whitespaces or contain \"not \""){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: positive Pre and Post conditions cannot contain whitespaces");
        }
    }
    
    WHEN("the input presents an action in the CBT which is not defined in the vocabulary"){
        std::string input_path = "./test/test_funzionali/illegal/req_f4_1.xml";
        THEN("it should rise an exception stating that an action is not in the vocabulary"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Action not defined in the vocabulary");
        }
    }
    
    WHEN("the input presents an action in the CBT which is not defined in the vocabulary"){
        std::string input_path = "./test/test_funzionali/illegal/req_f4_2.xml";
        THEN("it should rise an exception stating that an action is not in the vocabulary"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Action not defined in the vocabulary");
        }
    }
    
    WHEN("the input presents a parallel node with CFN as children"){
        std::string input_path = "./test/test_funzionali/illegal/req_f5.xml";
        THEN("it should rise an exception stating that a parallel node can have only EN as children"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: parallel node children must be execution nodes");
        }
    }
    
    WHEN("the input presents an action having as preconditions both c and not c"){
        std::string input_path = "./test/test_funzionali/illegal/req_f6.xml";
        THEN("it should rise an exception stating that an action cannot have both c and not c as preconditions"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: action cannot have 'c' and 'not c' as pre-conditions");
        }
    }
    
    WHEN("the input presents an action having as postconditions both c and not c"){
        std::string input_path = "./test/test_funzionali/illegal/req_f7.xml";
        THEN("it should rise an exception stating that an action cannot have both c and not c as postconditions"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: action cannot have 'c' and 'not c' as post-conditions");
        }
    }
    
    WHEN("the input presents an parallel node having children with contrastant post-conditions"){
        std::string input_path = "./test/test_funzionali/illegal/req_f8.xml";
        THEN("it should rise an exception stating that a parallel node cannot have children with contrastant post-conditions"){
            REQUIRE_THROWS_WITH(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path), "Input XML file bad format: children of parallel node cannot have contrastant post-conditions");
        }
    }
    
    WHEN("the input presents two or more actions with the same label"){
        std::string input_path = "./test/test_funzionali/illegal/req_f9.xml";
        THEN("only one must be memorized"){
            REQUIRE(typeid(cbtree->get_actions())==typeid(std::set<cbt::action>));
        }
    }
}


SCENARIO("The user wants to compute the initial requirements of a CBT given a legal input"){
    
    cbt::conditioned_behavior_tree* cbtree = new cbt::conditioned_behavior_tree();
    
    std::string input_path = "";
    std::string output_folder = "./test/test_funzionali/sym_output/";
    std::string limboole_path = "../limboole1.1/limboole";
    
    WHEN("the input CBT contains only a action node"){
        input_path = "./test/test_funzionali/legal/action_node.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::string line;
        
        getline(CBT_plans, line);
        REQUIRE(line == "(action1_0 -> (precondition11_0 & precondition12_0)) & ");
        getline(CBT_plans, line);
        REQUIRE(line =="(action1_0 -> (postcondition1_1)) & ");
        getline(CBT_plans, line);
        REQUIRE(line == "(!postcondition1_0 & postcondition1_1 -> (action1_0)) &");
        getline(CBT_plans, line);
        REQUIRE(line =="((action1_0))");
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }
    
    WHEN("the input CBT contains only a condition node"){
        input_path = "./test/test_funzionali/legal/condition_node.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::string line;
        
        getline(CBT_plans, line);
        REQUIRE(line =="((condition1_0))");
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }

    WHEN("the input CBT contains only a fallback node"){
        input_path = "./test/test_funzionali/legal/fallback_node.xml";
        THEN("no exception should be raised"){
                REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }
    
    WHEN("the input CBT contains only a sequence node"){
        input_path = "./test/test_funzionali/legal/sequence_node.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }
    
    WHEN("the input CBT contains only a parallel node containing all actions as children"){
        input_path = "./test/test_funzionali/legal/parallel_node_all_vocab.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }

    WHEN("the input CBT contains only a parallel node not containing all actions as children"){
        input_path = "./test/test_funzionali/legal/parallel_node_not_all_vocab.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }
    
    WHEN("the input CBT contains has 2 layers"){
        input_path = "./test/test_funzionali/legal/2_layer_CBT.xml";
        THEN("no exception should be raised"){
            REQUIRE_NOTHROW(cbtree->compute_initial_requirements(input_path, output_folder, limboole_path));
        }
        std::ifstream CBT_plans("./test/test_funzionali/sym_output/BTplans.txt");
        REQUIRE(CBT_plans.good());
        
        std::ifstream general_req("./test/test_funzionali/sym_output/general_requirements.txt");
        REQUIRE(general_req.good());
        
        std::ifstream initial_req("./test/test_funzionali/sym_output/initial_requirements.txt");
        REQUIRE(initial_req.good());
    }
}
