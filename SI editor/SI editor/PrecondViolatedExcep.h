#pragma once
#ifndef PRECOND_VIOLATED_EXCEP_
#define PRECOND_VIOLATED_EXCEP_

#include <stdexcept>
#include <string>

class PrecondViolatedExcep : public std::logic_error
{
public:
	PrecondViolatedExcep(const std::string& message = "");
}; // end PrecondViolatedExcep 
#endif