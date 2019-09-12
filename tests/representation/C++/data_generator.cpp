#include <iostream>
#include <string>

#include "observer.hpp"

using namespace std;

int main(void)
{
	Observer obs("/home/ark/CLionProjects/number recognition/data/learn/");
	obs.StartSaving(100,"../../test_data/questions/");
	return 0;
}