#ifndef CALLBACK_0_W_RET_H
#define CALLBACK_0_W_RET_H
//======================================================================
// Callback0wRet.h
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

#include "Base_Callback0wRetBody.h"
#include "Nil_Callback0wRetBody.h"
#include "Function_Callback0wRetBody.h"
#include "Member_Callback0wRetBody.h"








//==============================================================
// C a l l b a c k 2 w R e t
//--------------------------------------------------------------

template <class R>
class Callback0wRet
{
public:
  typedef R result_type;

  Callback0wRet(Base_Callback0wRetBody<R>* body):
    body_(body) 
  {incBody();}

  Callback0wRet(const Callback0wRet<R>& callback):
    body_(callback.body_) 
  {incBody();}

  Callback0wRet(): 
    body_(nil_().body_) 
  {incBody();}

  ~Callback0wRet() {decBody();}

  Callback0wRet<R>& operator=(const Callback0wRet<R>& callback);

  bool operator==(const Callback0wRet<R>& callback) const
  {return body_ == callback.body_;}

  bool operator<(const Callback0wRet<R>& callback) const
  {return body_ < callback.body_;}
  
  R operator()() 
    {return body_->operator()();} 
    // full name used instead of operator shorthand for Visual C++

private:
  Base_Callback0wRetBody<R>* body_;

  static Callback0wRet<R>& nil_();
  static Nil_Callback0wRetBody<R>* nilBody_();

  void incBody() {body_->incCount();}
  void decBody();
};








//==============================================================
// m a k e _ c a l l b a c k
//--------------------------------------------------------------

template <class R, class Function>
Callback0wRet<R> 
make_callback(Callback0wRet<R>*, Function f)
{

  Function_Callback0wRetBody<R,Function>* body = 
    new Function_Callback0wRetBody<R,Function>(f);
  return Callback0wRet<R>(body);

} 

template <class R, class Client, class Member>
Callback0wRet<R> 
make_callback(Callback0wRet<R>*,Client* client, Member member)
{

  Member_Callback0wRetBody<R,Client,Member>* body = 
    new Member_Callback0wRetBody<R,Client,Member>(client,member);
  return Callback0wRet<R>(body);

} 















//--------------------------------------
// template definitions
//--------------------------------------

#include "Callback0wRet.cpp"








//======================================================================
#endif
