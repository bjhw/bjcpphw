#ifndef FUNCTION_CB_0_BODY_H
#define FUNCTION_CB_0_BODY_H
//======================================================================
// Function_Callback0Body.h
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
// include base class
//--------------------------------------

#include "Base_Callback0Body.h"





//==============================================================
// C a l l b a c k 2 w R e t F u n c t i o n B o d y
//
// Function - type of a function pointer, or function object
//            that will be called by the callback
//--------------------------------------------------------------

template < class Function>
class Function_Callback0Body:
  public Base_Callback0Body
{
public:
  Function_Callback0Body(const Function& f): f_(f) {}
  /*virtual*/ void operator()() 
    { f_();}

private:
  Function f_;
};





//======================================================================
#endif
