#pragma once
#include "../Includes.hpp"

class Feature
{
public:
	Feature() {};

	virtual void Render() = 0;

	virtual void Create() = 0;
	
	virtual void Destroy() = 0;
};