//--------------------------------------------------------------------------------------------------
/**
 * @file sdefParser.h  Parser for .sdef files.
 *
 * Copyright (C) Sierra Wireless Inc.  Use of this work is subject to license.
 */
//--------------------------------------------------------------------------------------------------

#ifndef LEGATO_MKTOOLS_SDEF_PARSER_H_INCLUDE_GUARD
#define LEGATO_MKTOOLS_SDEF_PARSER_H_INCLUDE_GUARD


namespace sdef
{


//--------------------------------------------------------------------------------------------------
/**
 * Parses a .sdef file in version 1 format.
 *
 * @return Pointer to a fully populated SdefFile_t object.
 *
 * @throw mk::Exception_t if an error is encountered.
 */
//--------------------------------------------------------------------------------------------------
parseTree::SdefFile_t* Parse
(
    const std::string& filePath,    ///< Path to .sdef file to be parsed.
    bool beVerbose                  ///< true if progress messages should be printed.
);



} // namespace sdef

#endif // LEGATO_MKTOOLS_SDEF_PARSER_H_INCLUDE_GUARD
