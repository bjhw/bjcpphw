#ifndef CALLBACK_0_CPP
#define CALLBACK_0_CPP
//======================================================================
// Callback0.cpp
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








#include "Callback0.h"








//
// n i l B o d y _
//
// Returns a Nil body.  GCC and G++ do not support templated 
// static data members, so a templated static member function 
// must be used for portability.
//
//

Nil_Callback0Body* 
Callback0::nilBody_()
{

  static Nil_Callback0Body* body = 
    new Nil_Callback0Body;
  return body;

}








//
// n i l _
//
// Returns a Nil callback.  GCC and G++ do not support templated 
// static data members, so a templated static member function 
// must be used for portability.
//
//

Callback0& 
Callback0::nil_()
{

  static Callback0 callback(nilBody_());
  return callback;

}








//
// o p e r a t o r =
//
//

Callback0& 
Callback0::operator=(const Callback0& rhs)
{

  if (body_ != rhs.body_)
  {
    decBody();
    body_ = rhs.body_;
    incBody();
  }
  return *this;

}








//
// d e c B o d y
//
//

void 
Callback0::decBody()
{
  
  body_->decCount();
  if(!body_->count())
    delete body_;

}








//======================================================================
#endif
