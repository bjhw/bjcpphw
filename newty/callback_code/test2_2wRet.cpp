//======================================================================
// test2_2wRet.cpp
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

#include <test2wRet.h>

//
// f u n c t i o n
//
//

template <class T>
T function(T,T)
{
  cout << "function(T,T)" << endl;
  return T();

}








main()
{
  function(0,0);
  function((void*)0,(void*)0);
  function(Foo(),Foo());

  Members<int> int_members(function);
  Members<void*> pvoid_members(function);
  Members<Foo> Foo_members(function);

  test<int> int_test(int_members,function);
  int_test();

  test<void*> pvoid_test(pvoid_members,function);
  pvoid_test();

  test<Foo> Foo_test(Foo_members,function);
  Foo_test();

  return 0;
}
