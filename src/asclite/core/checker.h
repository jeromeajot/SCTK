/*
 * asclite
 * Author: Jerome Ajot, Nicolas Radde, Chris Laprun
 *
 * This software was developed at the National Institute of Standards and Technology by
 * employees of the Federal Government in the course of their official duties.  Pursuant to
 * Title 17 Section 105 of the United States Code this software is not subject to copyright
 * protection within the United States and is in the public domain. asclite is
 * an experimental system.  NIST assumes no responsibility whatsoever for its use by any party.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS."  With regard to this software, NIST MAKES NO EXPRESS
 * OR IMPLIED WARRANTY AS TO ANY MATTER WHATSOEVER, INCLUDING MERCHANTABILITY,
 * OR FITNESS FOR A PARTICULAR PURPOSE.
 */
 
#ifndef CHECKER_H
#define CHECKER_H

#include "filter.h" // inheriting class's header file

/**
 * Implement a validator on a speech object and his content.
 */
class Checker : public Filter
{
	public:
		// class constructor
		Checker();
		// class destructor
		~Checker();
		/**
		 * Launch the check process on the specified speech.
		 */
		virtual unsigned long int Process(Speech* speech)=0;
};

#endif // CHECKER_H