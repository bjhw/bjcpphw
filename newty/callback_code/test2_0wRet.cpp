//======================================================================
// test2_0wRet.cpp
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

#include <test0wRet.h>

//
// f u n c t i o n
//
//


int function()
{
  cout << "function()" << endl;
  return 0;

}








main()
{
  function();
  function();
  function();

  Members int_members(function);
  Members pvoid_members(function);
  Members Foo_members(function);

  test int_test(int_members,function);
  int_test();

  test pvoid_test(pvoid_members,function);
  pvoid_test();

  test Foo_test(Foo_members,function);
  Foo_test();

  return 0;
}
