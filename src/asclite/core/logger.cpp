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
 * Logging methods
 */
 
#include "logger.h"

Logger* Logger::rootLogger = NULL;
ostream* Logger::where = &cerr;
int Logger::log_level = 1;

/** 
 * Set the logger to log in the path specified as an argument 
 */
void Logger::logInFile(string file)
{
    ofstream tmp;
    tmp.open(file.c_str());
    where = &tmp;
}

/** 
 * Log on stdout
 */
void Logger::logOnStdout()
{
    where = &cerr;
}

/** 
 * Change log level
 */
void Logger::setLogLevel(int level)
{
    log_level = level;
}

/**
 * Return the stream to output the loggin
 * level must be a int between 0 and 6
 * where :
 *   0 ===> Silence 
 *   1 ===> Quiet
 *   2 ===> Normal (default)
 *   3 ===> Verbose
 *   4 ===> Info
 *   5 ===> Debug
 *   6 ===> Alignment
 *   7 ===> Alignment only
 */ 
void Logger::log(int level, char* message)
{
	if( (level == 6) && (log_level == 7) )
		(*where) << LevelToString(level) << string(message) << endl;
    else if( (level <= log_level) && (log_level != 7) )
        (*where) << LevelToString(level) << string(message) << endl;
}

void Logger::log(int level, string message)
{
	if( (level == 6) && (log_level == 7) )
		(*where) << LevelToString(level) << message << endl;
    else if( (level <= log_level) && (log_level != 7) )
        (*where) << LevelToString(level) << message << endl;
}

string Logger::LevelToString(int level)
{
    if(level == 1)
        return string("[  FATAL  ] ");
    else if(level == 2)
        return string("[  ERROR  ] ");
    else if(level == 3)
        return string("[  WARN   ] ");
    else if(level == 4)
        return string("[  INFO   ] ");
    else if(level == 5)
        return string("[  DEBUG  ] ");
	else if(level == 6)
        return string("[ALIGNMENT] ");
    else
        return string("[  UNKWN  ] ");
}

Logger* Logger::getLogger()
{
    if (rootLogger == NULL)
        rootLogger = new Logger();

    return rootLogger;
}