#ifndef CALLBACK_2_H
#define CALLBACK_2_H
//======================================================================
// Callback2.h
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

#include "Base_Callback2Body.h"
#include "Nil_Callback2Body.h"
#include "Function_Callback2Body.h"
#include "Member_Callback2Body.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

template <class A1, class A2>
class Callback2
{
public:
  typedef A1 first_argument_type;
  typedef A2 second_argument_type;

  Callback2(Base_Callback2Body<A1,A2>* body):
    body_(body) 
  {incBody();}

  Callback2(const Callback2<A1,A2>& callback):
    body_(callback.body_) 
  {incBody();}

  Callback2(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback2() {decBody();}

  Callback2<A1,A2>& operator=(const Callback2<A1,A2>& callback);

  bool operator==(const Callback2<A1,A2>& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback2<A1,A2>& callback) const
  {return body_ < callback.body_;}
  
  void operator()(A1 a1, A2 a2) 
    { body_->operator()(a1,a2);} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback2Body<A1,A2>* body_;

  static Callback2<A1,A2>& nil_();
  static Nil_Callback2Body<A1,A2>* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template <class A1, class A2, class Function>
Callback2<A1,A2> 
make_callback(Callback2<A1,A2>*, Function f)
{

  Function_Callback2Body<A1,A2,Function>* body = 
    new Function_Callback2Body<A1,A2,Function>(f);
  return Callback2<A1,A2>(body);

} 

template <class A1, class A2, class Client, class Member>
Callback2<A1,A2> 
make_callback(Callback2<A1,A2>*,Client* client, Member member)
{

  Member_Callback2Body<A1,A2,Client,Member>* body = 
    new Member_Callback2Body<A1,A2,Client,Member>(client,member);
  return Callback2<A1,A2>(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------

#include "Callback2.cpp"








//======================================================================
#endif
