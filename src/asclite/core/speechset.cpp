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

/**
 * A speech set represent all the data from one source (reference, participant)
 * it's a collection of Speech(Speaker) from one source.
 */
 
#include "speechset.h" // class's header file

Logger* SpeechSet::logger = Logger::getLogger();

// class constructor
SpeechSet::SpeechSet(string sourceFileName)
{
	ref = false;
	hyp = false;
	UpdatePropertiesIfNeeded(true);
	fileName = sourceFileName;
}

void SpeechSet::UpdatePropertiesIfNeeded(bool force)
{
	if(force || Properties::IsDirty())
    {
		case_sensitive = (Properties::GetProperty("align.case_sensitive") == "true");
		fragments_are_correct = (Properties::GetProperty("align.fragment_are_correct") == "true");
		string optionally = Properties::GetProperty("align.optionally");
		optionally_deletable = (optionally == "both");
        
		if(!optionally_deletable)
        {
			optionally_deletable = ( (IsRef()) ? optionally == "ref" : optionally == "hyp" );
		}
	}
}

bool SpeechSet::PerformCaseSensitiveAlignment()
{
	UpdatePropertiesIfNeeded(false);
	return case_sensitive;
}

bool SpeechSet::AreFragmentsCorrect()
{
	UpdatePropertiesIfNeeded(false);
	return fragments_are_correct;
}

bool SpeechSet::UseOptionallyDeletable()
{
	UpdatePropertiesIfNeeded(false);
	return optionally_deletable;
}


// class destructor
SpeechSet::~SpeechSet()
{
	vector<Speech*>::iterator i, ei;

	i = speeches.begin();
	ei = speeches.end();
	
	while(i != ei)
	{
		Speech* ptr_elt = *i;
		
		if(ptr_elt)
			delete ptr_elt;
		
		++i;
	}
	
	speeches.clear();
}

/**
 * Set the hyp/ref status of this set
 */
void SpeechSet::SetOrigin(string status)
{
    if (status == "ref")
    {
        ref = true;
		hyp = false;
    }
    else if (status == "hyp")
    {
        hyp = true;
		ref= false;
    }
    else
    {
        LOG_WARN(logger, "The status of the SpeechSet dont exist (must be 'ref' or 'hyp') and was: "+status);
    }
	
    UpdatePropertiesIfNeeded(true);
}