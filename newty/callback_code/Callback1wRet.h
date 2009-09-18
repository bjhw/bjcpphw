#ifndef CALLBACK_1_W_RET_H
#define CALLBACK_1_W_RET_H
//======================================================================
// Callback1wRet.h
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
// from HP's STL
//--------------------------------------

#include <bool.h> // for bool typedefs








//--------------------------------------
// local
//--------------------------------------

#include "Base_Callback1wRetBody.h"
#include "Nil_Callback1wRetBody.h"
#include "Function_Callback1wRetBody.h"
#include "Member_Callback1wRetBody.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

template <class A1, class R>
class Callback1wRet
{
public:
  typedef A1 first_argument_type;
  typedef R result_type;

  Callback1wRet(Base_Callback1wRetBody<A1,R>* body):
    body_(body) 
  {incBody();}

  Callback1wRet(const Callback1wRet<A1,R>& callback):
    body_(callback.body_) 
  {incBody();}

  Callback1wRet(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback1wRet() {decBody();}

  Callback1wRet<A1,R>& operator=(const Callback1wRet<A1,R>& callback);

  bool operator==(const Callback1wRet<A1,R>& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback1wRet<A1,R>& callback) const
  {return body_ < callback.body_;}
  
  R operator()(A1 a1) 
    {return body_->operator()(a1);} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback1wRetBody<A1,R>* body_;

  static Callback1wRet<A1,R>& nil_();
  static Nil_Callback1wRetBody<A1,R>* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template <class A1, class R, class Function>
Callback1wRet<A1,R> 
make_callback(Callback1wRet<A1,R>*, Function f)
{

  Function_Callback1wRetBody<A1,R,Function>* body = 
    new Function_Callback1wRetBody<A1,R,Function>(f);
  return Callback1wRet<A1,R>(body);

} 

template <class A1, class R, class Client, class Member>
Callback1wRet<A1,R> 
make_callback(Callback1wRet<A1,R>*,Client* client, Member member)
{

  Member_Callback1wRetBody<A1,R,Client,Member>* body = 
    new Member_Callback1wRetBody<A1,R,Client,Member>(client,member);
  return Callback1wRet<A1,R>(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------

#include "Callback1wRet.cpp"








//======================================================================
#endif
