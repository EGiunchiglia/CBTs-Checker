//
//  Action.cpp
//  CBT_Requirements_Calculator
//
//  Created by E.Giunchiglia on 29/05/18.
//  Copyright © 2018 Eleonora Giunchiglia. All rights reserved.
//

#include "action.hpp"

namespace cbt{
    
    
    
    action::action(){
        label_= "";
        pre_ = std::vector<std::string>();
        post_ = std::vector<std::string>();
    }
    

    
    std::string action::get_label() const{
        return this->label_;
    };
    
    
    
    const std::vector<std::string>& action::get_pre() const{
        return (this->pre_);
    };
    
    
    
    const std::vector<std::string>& action::get_post() const{
        return this->post_;
    };
    
    
    
    void action::set_label(std::string new_label){
        this->label_ = new_label;
    };
    
    
    
    void action::insert_pre(std::string new_pre){
        (this->pre_).push_back(new_pre);
    };
    
    
    
    void action::insert_post(std::string new_post){
        this->post_.push_back(new_post);
    };
    
    
}//namespace cbt
