/**
 * \file maracas.h
 * \brief Maracas (abbreviated MRC) is a basic C logger for debug purposes and colorful, bold prints
 *
 * Maracas define 6 categories of prints:
 * - PRINT: use the current block style (white by default), but can't be used as a block definer
 * - TRACE: in grey
 * - DEBUG: in blue
 * - INFO: in green
 * - WARN: in yellow
 * - ERROR: in red
 * - CRITIC: in dark red
 *
 * The main macros are:
 * - MRC_TYPE(...): that print anything as TYPE
 * - MRC_BLOCK_TYPE(x): that define a block of code where all prints whill be rendered as TYPE
 * - MRC_ASSERT(x,...): print a critical error and exit the code if x evaluate to false
 * - MRC_ASSERT_NOT(x,...): print a critical error and exit the code if x evaluate to true
 *
 * All these macros can be prefixed with an underscore to only compiled in DEBUG_MOD:
 * - _MRC_TYPE(...)
 * - _MRC_BLOCK_TYPE(x)
 * - _MRC_ASSERT(x,...)
 * - _MRC_ASSERT_NOT(x,...)
 *
 * Finally, MRC_DEBUG_ONLY(x) can be used to define a block of code that will only compile in DEBUG_MOD
 * \author Démolis Eloi
 */
#ifndef __MARACAS_H__
#define __MARACAS_H__

#include <stdlib.h>
#include <stdio.h>

//CONFIG
/**
 * \def MRC_DEBUG_MOD
 * \brief If defined, the code will be compiled in DEBUG_MOD
 */
#define MRC_DEBUG_MOD
/**
 * \def MRC_OUTPUT
 * \brief Define the standard output for Maracas (stderr by default)
 */
#define MRC_OUTPUT stderr

#ifdef MRC_DEBUG_MOD
	/**
	 * \def MRC_DEBUG_ONLY(x)
	 * \brief Define a block of code that will be compiled only in DEBUG_MOD
	 */
	#define MRC_DEBUG_ONLY(x)	x
	/**
	 * \def MRC_PROMPT
	 * \brief The prompt format used by Maracas (Contains the file and line of the print call if in DEBUG_MOD)
	 */
	#define MRC_PROMPT		"[%s(%d)]: "
	/**
	 * \def MRC_PROMPT_ARGS
	 * \brief The arguments taken by the #MRC_PROMPT
	 */
	#define MRC_PROMPT_ARGS		__FILE__, __LINE__,
	/**
	 * \def MRC_ASSERT_PROMPT
	 * \brief The additional prompt for failed assertion
	 */
	#define MRC_ASSERT_PROMPT(x)	"Assertion \"" #x "\" failed:\n\t"
#else
	/**
	 * \def MRC_DEBUG_ONLY(x)
	 * \brief Define a block of code that will be compiled only in DEBUG_MOD
	 */
	#define MRC_DEBUG_ONLY(x)
	/**
	 * \def MRC_PROMPT
	 * \brief The prompt format used by Maracas (Contains the file and line of the print call if in DEBUG_MOD)
	 */
	#define MRC_PROMPT
	/**
	 * \def MRC_PROMPT_ARGS
	 * \brief The arguments taken by the #MRC_PROMPT
	 */
	#define MRC_PROMPT_ARGS
	/**
	 * \def MRC_ASSERT_PROMPT
	 * \brief The additional prompt for failed assertion
	 */
	#define MRC_ASSERT_PROMPT(x)
#endif

//LOGGER

/**
 * \def MRC_END_SEQ
 * \brief Special character sequence needed to end colored prints
 */
#define MRC_END_SEQ "\033[0m"
/**
 * \def MRC_END
 * \brief End a Maracas block
 */
#define MRC_END fprintf(MRC_OUTPUT, MRC_END_SEQ"\n")
/**
 * \def MRC_BASE(color,x,...)
 * \brief Maracas print function with color and prompt
 */
#define MRC_BASE(color,x,...) fprintf(MRC_OUTPUT, "\033[1m\033[38;5;" #color "m" MRC_PROMPT x "%s", MRC_PROMPT_ARGS __VA_ARGS__)

/**
 * \def MRC_BLOCK_TRACE(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_TRACE
 */
#define MRC_BLOCK_TRACE(x)	MRC_BASE(8, "", ""); x MRC_END;
/**
 * \def MRC_BLOCK_DEBUG(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_DEBUG
 */
#define MRC_BLOCK_DEBUG(x)	MRC_BASE(14, "", ""); x MRC_END;
/**
 * \def MRC_BLOCK_INFO(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_INFO
 */
#define MRC_BLOCK_INFO(x)	MRC_BASE(2, "", ""); x MRC_END;
/**
 * \def MRC_BLOCK_WARN(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_WARN
 */
#define MRC_BLOCK_WARN(x)	MRC_BASE(11, "", ""); x MRC_END;
/**
 * \def MRC_BLOCK_ERROR(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_ERROR
 */
#define MRC_BLOCK_ERROR(x)	MRC_BASE(1, "", ""); x MRC_END;
/**
 * \def MRC_BLOCK_CRITIC(x)
 * \brief Define a block of code where all prints will be rendered as #MRC_CRITIC
 */
#define MRC_BLOCK_CRITIC(x)	MRC_BASE(88, "", ""); x MRC_END;

/**
 * \def MRC_PRINT(...)
 * \brief print anything on the Maracas output
 */
#define MRC_PRINT(...)		fprintf(MRC_OUTPUT, __VA_ARGS__)
/**
 * \def MRC_TRACE(...)
 * \brief print anything in grey
 */
#define MRC_TRACE(...)		MRC_BASE(8, __VA_ARGS__, MRC_END_SEQ)
/**
 * \def MRC_DEBUG(...)
 * \brief print anything in blue
 */
#define MRC_DEBUG(...)		MRC_BASE(14, __VA_ARGS__, MRC_END_SEQ)
/**
 * \def MRC_INFO(...)
 * \brief print anything in green
 */
#define MRC_INFO(...)		MRC_BASE(2, __VA_ARGS__, MRC_END_SEQ)
/**
 * \def MRC_WARN(...)
 * \brief print anything in yellow
 */
#define MRC_WARN(...)		MRC_BASE(11, __VA_ARGS__, MRC_END_SEQ)
/**
 * \def MRC_ERROR(...)
 * \brief print anything in red
 */
#define MRC_ERROR(...)		MRC_BASE(1, __VA_ARGS__, MRC_END_SEQ)
/**
 * \def MRC_CRITIC(...)
 * \brief print anything in dark red
 */
#define MRC_CRITIC(...)		MRC_BASE(88, __VA_ARGS__, MRC_END_SEQ)

/**
 * \def MRC_ASSERT(x,...)
 * \brief print a critical error and exit the code if x evaluate to false
 */
#define MRC_ASSERT(x,...) 	{ if (!(x)) { MRC_CRITIC(MRC_ASSERT_PROMPT((x)) __VA_ARGS__); exit(-1); } }
/**
 * \def MRC_ASSERT_NOT(x,...)
 * \brief print a critical error and exit the code if x evaluate to true
 */
#define MRC_ASSERT_NOT(x,...) 	{ if (x) { MRC_CRITIC(MRC_ASSERT_PROMPT(!(x)) __VA_ARGS__); exit(-1); } }

//DEBUG ONLY

/**
 * \def _MRC_BLOCK_TRACE(x)
 * \brief Acts as #MRC_BLOCK_TRACE if in DEBUG_MOD
 */
#define _MRC_BLOCK_TRACE(x)	MRC_DEBUG_ONLY(MRC_BLOCK_TRACE(x))
/**
 * \def _MRC_BLOCK_DEBUG(x)
 * \brief Acts as #MRC_BLOCK_DEBUG if in DEBUG_MOD
 */
#define _MRC_BLOCK_DEBUG(x)	MRC_DEBUG_ONLY(MRC_BLOCK_DEBUG(x))
/**
 * \def _MRC_BLOCK_INFO(x)
 * \brief Acts as #MRC_BLOCK_INFO if in DEBUG_MOD
 */
#define _MRC_BLOCK_INFO(x)	MRC_DEBUG_ONLY(MRC_BLOCK_INFO(x))
/**
 * \def _MRC_BLOCK_WARN(x)
 * \brief Acts as #MRC_BLOCK_WARN if in DEBUG_MOD
 */
#define _MRC_BLOCK_WARN(x)	MRC_DEBUG_ONLY(MRC_BLOCK_WARN(x))
/**
 * \def _MRC_BLOCK_ERROR(x)
 * \brief Acts as #MRC_BLOCK_ERROR if in DEBUG_MOD
 */
#define _MRC_BLOCK_ERROR(x)	MRC_DEBUG_ONLY(MRC_BLOCK_ERROR(x))
/**
 * \def _MRC_BLOCK_CRITIC(x)
 * \brief Acts as #MRC_BLOCK_CRITIC if in DEBUG_MOD
 */
#define _MRC_BLOCK_CRITIC(x)	MRC_DEBUG_ONLY(MRC_BLOCK_CRITIC(x))

/**
 * \def _MRC_PRINT(...)
 * \brief Acts as #MRC_PRINT if in DEBUG_MOD
 */
#define _MRC_PRINT(...)		MRC_DEBUG_ONLY(MRC_PRINT(__VA_ARGS__))
/**
 * \def _MRC_TRACE(...)
 * \brief Acts as #MRC_TRACE if in DEBUG_MOD
 */
#define _MRC_TRACE(...)		MRC_DEBUG_ONLY(MRC_TRACE(__VA_ARGS__))
/**
 * \def _MRC_DEBUG(...)
 * \brief Acts as #MRC_DEBUG if in DEBUG_MOD
 */
#define _MRC_DEBUG(...)		MRC_DEBUG_ONLY(MRC_DEBUG(__VA_ARGS__))
/**
 * \def _MRC_INFO(...)
 * \brief Acts as #MRC_INFO if in DEBUG_MOD
 */
#define _MRC_INFO(...)		MRC_DEBUG_ONLY(MRC_INFO(__VA_ARGS__))
/**
 * \def _MRC_WARN(...)
 * \brief Acts as #MRC_WARN if in DEBUG_MOD
 */
#define _MRC_WARN(...)		MRC_DEBUG_ONLY(MRC_WARN(__VA_ARGS__))
/**
 * \def _MRC_ERROR(...)
 * \brief Acts as #MRC_ERROR if in DEBUG_MOD
 */
#define _MRC_ERROR(...)		MRC_DEBUG_ONLY(MRC_ERROR(__VA_ARGS__))
/**
 * \def _MRC_CRITIC(...)
 * \brief Acts as #MRC_CRITIC if in DEBUG_MOD
 */
#define _MRC_CRITIC(...)	MRC_DEBUG_ONLY(MRC_CRITIC(__VA_ARGS__))

/**
 * \def _MRC_ASSERT(...)
 * \brief Acts as #MRC_ASSERT if in DEBUG_MOD
 */
#define _MRC_ASSERT(...)	MRC_DEBUG_ONLY(MRC_ASSERT(__VA_ARGS__))
/**
 * \def _MRC_ASSERT_NOT(...)
 * \brief Acts as #MRC_ASSERT_NOT if in DEBUG_MOD
 */
#define _MRC_ASSERT_NOT(...)	MRC_DEBUG_ONLY(MRC_ASSERT_NOT(__VA_ARGS__))

#endif
