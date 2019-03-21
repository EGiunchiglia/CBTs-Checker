//
//  Action.hpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//


#ifndef action_hpp
#define action_hpp

#include <stdio.h>
#include <string>
#include <vector>


namespace cbt{
    
    
    /** \brief Concrete class used to memorize an action and its pre-conditions and post-conditions. */
    class action{
      
        
    public:
        
        /**
         * Constructor.
         * Sets the label to the empty string, and pre and post to the empty vector.
         */
        action();
        
        /**
         * Function returning the action label.
         */
        std::string get_label() const;
        
        /**
         * Function returning the pre-conditions of the action.
         */
        const std::vector<std::string>& get_pre() const;
        
        /**
         * Function returning the post-conditions of the action.
         */
        const std::vector<std::string>& get_post() const;
        
        /**
         * Function setting the label of the action equal to the string in new_label.
         * \param new_label string containing the label for the action.
         */
        void set_label(std::string new_label);
        
        /**
         * Function inserting a new pre-condition.
         * \param new_pre string containing the pre-condition to be inserted.
         */
        void insert_pre(std::string new_pre);
        
        /**
         * Function setting a new post-condition.
         * \param new_post string containing the post-condition to be inserted.
         */
        void insert_post(std::string new_post);
        
        
        //Overloaded operators
        friend bool operator< (action const& a, action const& b){
            return a.label_.compare(b.label_) < 0;
        };
        
    private:
        
        /** Attribute representing the label of the action.*/
        std::string label_;
        /**Attribute representing the set of pre-conditions associated to the action.*/
        std::vector<std::string> pre_;
        /** Attribute representing the set of post-conditions associated to the action.*/
        std::vector<std::string> post_;

    };
}//namespace cbt

#endif /* action_hpp */
