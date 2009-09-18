#ifndef COUNTED_BODY_H
#define COUNTED_BODY_H
//======================================================================
// CountedBody.h
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





//
// C o u n t e d B o d y
//
//

class CountedBody
{
public:
  CountedBody(): count_(0) {}
  virtual ~CountedBody() {}
  void incCount() {count_++;}
  void decCount() {count_--;}
  int count() {return count_;}
  
private:
  int count_;
};








//======================================================================
#endif
