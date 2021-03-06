#ifndef _SSF_CAMERAS_DEFS_HPP_
#define _SSF_CAMERAS_DEFS_HPP_

namespace ssf{

#if (defined WIN32 || defined _WIN32 || defined __CYGWIN__)
	#if defined CAMERAS_API_EXPORTS
		#define  CAMERAS_EXPORT __declspec(dllexport)
	#else
		#define  CAMERAS_EXPORT __declspec(dllimport)
	#endif
#else
		#define CAMERAS_EXPORT
#endif

}

#endif // !_SSF_CONFIGURATION_DEFS_HPP_