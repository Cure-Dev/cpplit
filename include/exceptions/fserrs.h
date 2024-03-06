#include "exceptions/exception.h"

#ifndef _FSERRS_H_
#define _FSERRS_H_

class file_err/* : public exception*/ {}; // fserr

class file_not_exists : public file_err {
public:
	file_not_exists(std::string filepath) /*: FILEPATH(filepath)*/ {};
	std::string FILEPATH;
};

#endif