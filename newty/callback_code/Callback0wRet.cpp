#ifndef CALLBACK_0_W_RET_CPP
#define CALLBACK_0_W_RET_CPP
//======================================================================
// Callback0wRet.cpp
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








#include "Callback0wRet.h"








//
// n i l B o d y _
//
// Returns a Nil body.  GCC and G++ do not support templated 
// static data members, so a templated static member function 
// must be used for portability.
//
//

template <class R>
Nil_Callback0wRetBody<R>* 
Callback0wRet<R>::nilBody_()
{

  static Nil_Callback0wRetBody<R>* body = 
    new Nil_Callback0wRetBody<R>;
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

template <class R> 
Callback0wRet<R>& 
Callback0wRet<R>::nil_()
{

  static Callback0wRet<R> callback(nilBody_());
  return callback;

}








//
// o p e r a t o r =
//
//

template <class R> 
Callback0wRet<R>& 
Callback0wRet<R>::operator=(const Callback0wRet<R>& rhs)
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

template <class R> 
void 
Callback0wRet<R>::decBody()
{
  
  body_->decCount();
  if(!body_->count())
    delete body_;

}








//======================================================================
#endif
