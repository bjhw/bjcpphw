#ifndef NIL_CB_INVOKED
#define NIL_CB_INVOKED
//======================================================================
// NilCallbackInvoked
//
//
// Copyright (c) 1996 Paul Jakubik 
// 
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Paul Jakubik makes no representations 
// about the suitability of this software for any purpose.  It is 
// provided "as is" without express or implied warranty.
//----------------------------------------------------------------------





//
// N i l C a l l b a c k I n v o k e d
//
// This should actually inherit from runtime_error.  For the 
// sake of easy portability, this is currently a stand alone 
// class. Many compilers do not provide the exception base 
// classes.  Some do provide exception base classes, but provide
// base classes that don't quite conform with the standard.
//
// For now the easiest way to make this exception class work 
// with most compilers is for this class to not inherit from 
// anything.
//

class NilCallbackInvoked
{
 public:
  NilCallbackInvoked() {}
  NilCallbackInvoked(const NilCallbackInvoked&) {}
  NilCallbackInvoked& operator=(const NilCallbackInvoked&) 
    {return *this;}
  virtual ~NilCallbackInvoked() {}
  virtual const char* what() const {return "Nil callback invoked";}
};






//======================================================================
#endif
