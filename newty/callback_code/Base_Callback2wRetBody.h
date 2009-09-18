#ifndef BASE_CB_2_W_RET_BODY_H
#define BASE_CB_2_W_RET_BODY_H
//======================================================================
// Base_Callback2wRetBody.h
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
// local include
//--------------------------------------

#include "CountedBody.h" // for CountedBody class





template <class A1, class A2, class R>
class Base_Callback2wRetBody:
  public CountedBody
{

public:

  virtual R operator()(A1 a1, A2 a2) = 0;

};





//======================================================================
#endif
