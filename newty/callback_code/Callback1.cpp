#ifndef CALLBACK_1_CPP
#define CALLBACK_1_CPP
//======================================================================
// Callback1.cpp
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








#include "Callback1.h"








//
// n i l B o d y _
//
// Returns a Nil body.  GCC and G++ do not support templated 
// static data members, so a templated static member function 
// must be used for portability.
//
//

template <class A1>
Nil_Callback1Body<A1>* 
Callback1<A1>::nilBody_()
{

  static Nil_Callback1Body<A1>* body = 
    new Nil_Callback1Body<A1>;
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

template <class A1> 
Callback1<A1>& 
Callback1<A1>::nil_()
{

  static Callback1<A1> callback(nilBody_());
  return callback;

}








//
// o p e r a t o r =
//
//

template <class A1> 
Callback1<A1>& 
Callback1<A1>::operator=(const Callback1<A1>& rhs)
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

template <class A1> 
void 
Callback1<A1>::decBody()
{
  
  body_->decCount();
  if(!body_->count())
    delete body_;

}








//======================================================================
#endif
