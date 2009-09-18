#ifndef CALLBACK_1_H
#define CALLBACK_1_H
//======================================================================
// Callback1.h
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

#include "Base_Callback1Body.h"
#include "Nil_Callback1Body.h"
#include "Function_Callback1Body.h"
#include "Member_Callback1Body.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

template <class A1>
class Callback1
{
public:
  typedef A1 first_argument_type;

  Callback1(Base_Callback1Body<A1>* body):
    body_(body) 
  {incBody();}

  Callback1(const Callback1<A1>& callback):
    body_(callback.body_) 
  {incBody();}

  Callback1(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback1() {decBody();}

  Callback1<A1>& operator=(const Callback1<A1>& callback);

  bool operator==(const Callback1<A1>& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback1<A1>& callback) const
  {return body_ < callback.body_;}
  
  void operator()(A1 a1) 
    { body_->operator()(a1);} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback1Body<A1>* body_;

  static Callback1<A1>& nil_();
  static Nil_Callback1Body<A1>* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template <class A1, class Function>
Callback1<A1> 
make_callback(Callback1<A1>*, Function f)
{

  Function_Callback1Body<A1,Function>* body = 
    new Function_Callback1Body<A1,Function>(f);
  return Callback1<A1>(body);

} 

template <class A1, class Client, class Member>
Callback1<A1> 
make_callback(Callback1<A1>*,Client* client, Member member)
{

  Member_Callback1Body<A1,Client,Member>* body = 
    new Member_Callback1Body<A1,Client,Member>(client,member);
  return Callback1<A1>(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------

#include "Callback1.cpp"








//======================================================================
#endif
