#pragma once

struct maps {

	int x = 0;
	int y = 0;
	int floor = 0;
};

int mapping[3][30][30] = {
	{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,-1},
		{-1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,-1},//10
		{-1,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,1,1,0,1,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,0,0,0,1,1,1,1,0,-1},
		{-1,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,-1},
		{-1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,100,1,0,-1},
		{-1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,-1},
		{-1,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,0,-1},
		{-1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2,2,2,0,-1},
		{-1,0,0,0,0,0,0,2,2,0,2,2,2,0,2,2,2,2,2,2,2,2,2,2,0,2,2,2,0,-1},
		{-1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,2,0,0,2,2,2,2,2,2,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,2,0,0,2,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,2,0,0,2,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,2,2,2,2,2,2,2,0,0,2,0,0,0,2,2,2,2,2,0,2,2,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,2,0,0,2,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,-1},//10
		{-1,0,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,0,0,2,2,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,2,0,0,0,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,2,2,2,2,0,2,2,2,2,0,2,2,2,2,2,2,2,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,0,2,2,0,0,0,2,0,0,0,0,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,2,2,0,2,2,100,2,2,0,0,0,0,2,0,0,0,0,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,0,2,2,0,0,0,2,0,0,0,0,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,0,0,0,2,0,0,0,0,0,-1},
		{-1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,-1},
		{-1,0,2,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,-1},
		{-1,0,2,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,0,0,2,0,0,2,101,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,2,0,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,0,0,0,2,0,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,0,0,0,2,2,2,2,0,2,0,0,0,0,0,0,0,2,2,2,2,0,-1},
		{-1,0,2,2,2,2,2,2,0,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
	},{
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},//10
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
}
};