//
//  mainprogram.hpp
//  LinePassword
//
//  Created by Saber on 2018/4/23.
//  Copyright © 2018年 Saber. All rights reserved.
//

#ifndef mainprogram_hpp
#define mainprogram_hpp
#include "comline.hpp"

class MainProgram {
protected:
	ComLine* cl ;
public:
	MainProgram() ;
	~MainProgram() ;
public:
	virtual int main(int argc, char* argv[]);
	virtual int main();
};

#endif /* mainprogram_hpp */
