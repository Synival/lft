// common.hpp
// ----------
// Definitions, macros, etc. to be included in all other public headers

#ifndef LFT_COMMON_HPP_INCLUDED
#define LFT_COMMON_HPP_INCLUDED

// (Windows DLL stuff)
// -------------------
// Define "LFT_EXPORT" to export to a DLL
#ifdef LFT_EXPORT
    #define LFT_API __declspec(dllexport)
// Define "LFT_INTEGRATED" if the lft code should be included directly in another project.
#elif LFT_INTEGRATED
    #define LFT_API
// Otherwise, assume the lft project is dynamically-linked from a DLL.
#else
    #define LFT_API __declspec(dllimport)
#endif

// Superfluous macros to delete things C++ makes by default.
#define LFT_DELETE_DEFAULT_CONSTRUCTOR(t) \
    t() = delete

#define LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS(t) \
    t(const t &) = delete; \
    t (t &&) = delete

#define LFT_DELETE_ALL_IMPLICIT_ASSIGNMENT_OPERATORS(t) \
    t &operator=(const t &) = delete; \
    t &operator=(t &&) = delete

#define LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(t) \
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS(t); \
    LFT_DELETE_ALL_IMPLICIT_ASSIGNMENT_OPERATORS(t)

#define LFT_DELETE_ALL_IMPLICIT_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(t) \
    LFT_DELETE_DEFAULT_CONSTRUCTOR(t); \
    LFT_DELETE_ALL_IMPLICIT_COPY_CONSTRUCTORS_AND_ASSIGNMENT_OPERATORS(t)

#endif // LFT_COMMON_HPP_INCLUDED
