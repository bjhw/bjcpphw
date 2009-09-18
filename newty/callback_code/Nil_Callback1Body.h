#ifndef NIL_CB_1_BODY_H
#define NIL_CB_1_BODY_H
//======================================================================
// Nil_Callback1Body.h
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





//--------------------------------------
// local includes
//--------------------------------------

#include "Base_Callback1Body.h" // base class
#include "NilCallbackInvoked.h" // exception thrown





//==============================================================
// N i l _ C a l l b a c k 2 w R e t B o d y
//
// Used to implement a Nil callback.  If this callback is 
// invoked, it throws an exception.  All Nil callbacks share the 
// same body.
//--------------------------------------------------------------

template <class A1>
class Nil_Callback1Body:
  public Base_Callback1Body<A1>
{
public:

  /*virtual*/ void operator()(A1) 
  {
    throw NilCallbackInvoked();
  }

};





//======================================================================
#endif
