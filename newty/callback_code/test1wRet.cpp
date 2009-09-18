//======================================================================
// test1wRet.cpp
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

#include <test1wRet.h>

//
// f u n c t i o n
//
//

template <class T>
T function(T)
{
  cout << "function(T)" << endl;
  return T();

}








main()
{
  function(0);
  function((void*)0);
  function(Foo());

  Members<int> members(function);
  Members<void*> pvoid_members(function);
  Members<Foo> Foo_members(function);

  test<int> aTest(members,function);
  aTest();

  return 0;
}
