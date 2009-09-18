#ifndef CALLBACK_2_CPP
#define CALLBACK_2_CPP
//======================================================================
// Callback2.cpp
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








#include "Callback2.h"








//
// n i l B o d y _
//
// Returns a Nil body.  GCC and G++ do not support templated 
// static data members, so a templated static member function 
// must be used for portability.
//
//

template <class A1, class A2>
Nil_Callback2Body<A1,A2>* 
Callback2<A1,A2>::nilBody_()
{

  static Nil_Callback2Body<A1,A2>* body = 
    new Nil_Callback2Body<A1,A2>;
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

template <class A1, class A2> 
Callback2<A1,A2>& 
Callback2<A1,A2>::nil_()
{

  static Callback2<A1,A2> callback(nilBody_());
  return callback;

}








//
// o p e r a t o r =
//
//

template <class A1, class A2> 
Callback2<A1,A2>& 
Callback2<A1,A2>::operator=(const Callback2<A1,A2>& rhs)
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

template <class A1, class A2> 
void 
Callback2<A1,A2>::decBody()
{
  
  body_->decCount();
  if(!body_->count())
    delete body_;

}








//======================================================================
#endif
