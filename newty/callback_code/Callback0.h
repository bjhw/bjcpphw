#ifndef CALLBACK_0_H
#define CALLBACK_0_H
//======================================================================
// Callback0.h
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

#include "Base_Callback0Body.h"
#include "Nil_Callback0Body.h"
#include "Function_Callback0Body.h"
#include "Member_Callback0Body.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

class Callback0
{
public:

  Callback0(Base_Callback0Body* body):
    body_(body) 
  {incBody();}

  Callback0(const Callback0& callback):
    body_(callback.body_) 
  {incBody();}

  Callback0(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback0() {decBody();}

  Callback0& operator=(const Callback0& callback);

  bool operator==(const Callback0& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback0& callback) const
  {return body_ < callback.body_;}
  
  void operator()() 
    { body_->operator()();} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback0Body* body_;

  static Callback0& nil_();
  static Nil_Callback0Body* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template < class Function>
Callback0 
make_callback(Callback0*, Function f)
{

  Function_Callback0Body<Function>* body = 
    new Function_Callback0Body<Function>(f);
  return Callback0(body);

} 

template < class Client, class Member>
Callback0 
make_callback(Callback0*,Client* client, Member member)
{

  Member_Callback0Body<Client,Member>* body = 
    new Member_Callback0Body<Client,Member>(client,member);
  return Callback0(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------










//======================================================================
#endif
