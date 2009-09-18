#ifndef MEMBER_CB_0_BODY_H
#define MEMBER_CB_0_BODY_H
//======================================================================
// Callback0MemberBody.h
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
// include base class
//--------------------------------------

#include "Base_Callback0Body.h"





//==============================================================
// M e m b e r _ C a l l b a c k 2 w R e t B o d y
//
// Client - type of the client object that will be called by
//          the callback
// Member - type of the member function pointer, or data member
//          pointer where the data member is a function pointer
//          or function object -- this is what will be called
//          by the callback 
//--------------------------------------------------------------

template < class Client, class Member>
class Member_Callback0Body:
  public Base_Callback0Body
{
public:
  Member_Callback0Body(Client* client, Member member):
    client_(client), 
    member_(member)
  {}

  /*virtual*/ void operator()() 
    { (client_->*member_)();}

private:
  Client* client_;
  Member member_;
};





//======================================================================
#endif
