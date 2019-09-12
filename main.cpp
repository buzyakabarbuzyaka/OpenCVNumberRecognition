#include <iostream>
#include <string>

#include "observer.hpp"

using namespace std;

int main(void)
{
	Observer obs("../../data/learn/");
	obs.StartObservation();
	return 0;
}