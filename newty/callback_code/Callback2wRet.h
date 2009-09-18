#ifndef CALLBACK_2_W_RET_H
#define CALLBACK_2_W_RET_H
//======================================================================
// Callback2wRet.h
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

#include "Base_Callback2wRetBody.h"
#include "Nil_Callback2wRetBody.h"
#include "Function_Callback2wRetBody.h"
#include "Member_Callback2wRetBody.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

template <class A1, class A2, class R>
class Callback2wRet
{
public:
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;
  typedef R result_type;

  Callback2wRet(Base_Callback2wRetBody<A1,A2,R>* body):
    body_(body) 
  {incBody();}

  Callback2wRet(const Callback2wRet<A1,A2,R>& callback):
    body_(callback.body_) 
  {incBody();}

  Callback2wRet(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback2wRet() {decBody();}

  Callback2wRet<A1,A2,R>& operator=(const Callback2wRet<A1,A2,R>& callback);

  bool operator==(const Callback2wRet<A1,A2,R>& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback2wRet<A1,A2,R>& callback) const
  {return body_ < callback.body_;}
  
  R operator()(A1 a1, A2 a2) 
    {return body_->operator()(a1,a2);} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback2wRetBody<A1,A2,R>* body_;

  static Callback2wRet<A1,A2,R>& nil_();
  static Nil_Callback2wRetBody<A1,A2,R>* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template <class A1, class A2, class R, class Function>
Callback2wRet<A1,A2,R> 
make_callback(Callback2wRet<A1,A2,R>*, Function f)
{

  Function_Callback2wRetBody<A1,A2,R,Function>* body = 
    new Function_Callback2wRetBody<A1,A2,R,Function>(f);
  return Callback2wRet<A1,A2,R>(body);

} 

template <class A1, class A2, class R, class Client, class Member>
Callback2wRet<A1,A2,R> 
make_callback(Callback2wRet<A1,A2,R>*,Client* client, Member member)
{

  Member_Callback2wRetBody<A1,A2,R,Client,Member>* body = 
    new Member_Callback2wRetBody<A1,A2,R,Client,Member>(client,member);
  return Callback2wRet<A1,A2,R>(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------

#include "Callback2wRet.cpp"








//======================================================================
#endif
