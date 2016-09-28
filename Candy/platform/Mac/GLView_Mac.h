//
//  GLView_Mac.h
//  Candy
//
//  Created by Dongyang.Cai on 28/09/2016.
//
//

#ifndef GLView_Mac_h
#define GLView_Mac_h

#include <stdio.h>
#include <string>

class GLView {
public:
    
    static GLView *create(const std::string& viewName);
};

#endif /* GLView_Mac_h */
