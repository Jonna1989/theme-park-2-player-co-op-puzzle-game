#pragma once

#include <vector>
namespace std;
class Board
{
public:
	Board();
	~Board();


	void Initialize();
	void Update();
	void Cleanup();

private:
	vector<vector<int> > m_Board2dVector;

};

