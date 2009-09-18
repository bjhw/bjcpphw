#ifndef TEST_0_H
#define TEST_0_H
//======================================================================
// test0.h
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





#include "Callback0.h"
#include <iostream.h>








//
// F u n c t i o n O b j e c t
//
//


class FunctionObject
{
public:
  void operator()()
  {
    cout << "FunctionObject::operator()()" << endl;
    
  }
};








//
// M e m b e r s
//
//


class Members
{
public:

  Members(void (*functionPtr)()):
    functionPtr_(functionPtr)
  {}
  
  void function()
  {
    cout << "Members::function()" << endl;
    
  }

  void (*functionPtr_)();
  FunctionObject functionObject_;

};








//
// F o o 
//
//

class Foo
{
public:
  Foo():
    val_(0)
  {}

  Foo(int val):
    val_(val)
  {}

  Foo(const Foo& rhs):
    val_(rhs.val_)
  {}

private:
  int val_;
};








//
// p r i n t _ e r r o r
//
//

void print_error()
{
  cerr << "*****  ****   ****    ***   **** " << endl;
  cerr << "*      *   *  *   *  *   *  *   *" << endl;
  cerr << "*****  ****   ****   *   *  **** " << endl;
  cerr << "*      *  *   *  *   *   *  *  * " << endl;
  cerr << "*****  *   *  *   *   ***   *   *" << endl;
}







//
// t e s t
//
//


class test
{
public:
  test(Members& members, void (functionPtr)()):
  nil_(),
  function_(make_callback((Callback0*)0, functionPtr)),
  functionObject_(
		  make_callback
		  (
		   (Callback0*)0, 
		   FunctionObject()
		   )
		  ),
  
  member_function_(
		   make_callback
		   (
		    (Callback0*)0, 
		    &members,
		    &Members::function
		    )
		   )

#ifndef __GNUG__
,
  member_functionPointer_(
			  make_callback
			  (
			   (Callback0*)0, 
			   &members,
			   &Members::functionPtr_
			   )
			  ),
  member_functionObject_(
			 make_callback
			 (
			  (Callback0*)0, 
			  &members,
			  &Members::functionObject_
			  )
			 )
#endif
  {}
    
  void operator()()
  {
    nil_test();
    invoke_test();
    equality_tests();
  }
  
  void nil_test()
  {
    Callback0 aNil;
    
    if (aNil == nil_)
      cout << "It worked" << endl;

    try
      {
        cout << "invoke aNil" << endl;
	aNil();
      }
    catch (const NilCallbackInvoked&)
      {
	cerr << "nil callback invoked" << endl;
      }
    return;
  }

  void invoke_test()
  {
    function_();
    functionObject_();
    member_function_();
#ifndef __GNUG__
    member_functionPointer_();
    member_functionObject_();
#endif
  }



  static void isEqual(const Callback0& cb1,
		 const Callback0& cb2)
  {
    if(cb1 == cb2)
      cout << ".";
    else
      {
	print_error();
	cout << "Tested not equal when should have tested equal" << endl;
      }
  }

  static void notEqual(const Callback0& cb1,
		 const Callback0& cb2)
  {
    if(cb1 == cb2)
      {
	print_error();
	cout << "Tested equal when should have tested not equal" << endl;
      }
    else
      cout << ".";
  }
    
  static void isEqual_lt(const Callback0& cb1,
		 const Callback0& cb2)
  {
    if((cb1 < cb2) || (cb2 < cb1))
      {
	print_error();
	cout << "Tested not equal when should have tested equal" << endl;
	cout << "used < for testing" << endl;
      }
    else
      cout << ".";
  }

  static void notEqual_lt(const Callback0& cb1,
		 const Callback0& cb2)
  {
    if((cb1 < cb2) || (cb2 < cb1))
      cout << ".";
    else
      {
	print_error();
	cout << "Tested equal when should have tested not equal" << endl;
	cout << "used < for testing" << endl;
      }
  }
    
  void equality_tests()
  {
    Callback0 nil_copy(nil_);
    Callback0 function_copy(function_);
    Callback0 functionObject_copy(functionObject_);
    Callback0 member_function_copy(member_function_);
#ifndef __GNUG__
    Callback0 
      member_functionPointer_copy(member_functionPointer_);
    Callback0 
      member_functionObject_copy(member_functionObject_);
#endif

    isEqual(nil_,nil_copy);
    isEqual(nil_copy,nil_);
    isEqual(function_,function_copy);
    isEqual(function_copy,function_);
    isEqual(functionObject_,functionObject_copy);
    isEqual(functionObject_copy,functionObject_);
    isEqual(member_function_,member_function_copy);
    isEqual(member_function_copy,member_function_);

#ifndef __GNUG__
    isEqual(member_functionPointer_,member_functionPointer_copy);
    isEqual(member_functionPointer_copy,member_functionPointer_);
    isEqual(member_functionObject_,member_functionObject_copy);
    isEqual(member_functionObject_copy,member_functionObject_);
#endif

    isEqual_lt(nil_,nil_copy);
    isEqual_lt(nil_copy,nil_);
    isEqual_lt(function_,function_copy);
    isEqual_lt(function_copy,function_);
    isEqual_lt(functionObject_,functionObject_copy);
    isEqual_lt(functionObject_copy,functionObject_);
    isEqual_lt(member_function_,member_function_copy);
    isEqual_lt(member_function_copy,member_function_);

#ifndef __GNUG__
    isEqual_lt(member_functionPointer_,member_functionPointer_copy);
    isEqual_lt(member_functionPointer_copy,member_functionPointer_);
    isEqual_lt(member_functionObject_,member_functionObject_copy);
    isEqual_lt(member_functionObject_copy,member_functionObject_);
#endif
  }
   
private:
  Callback0 nil_;
  Callback0 function_;
  Callback0 functionObject_;
  Callback0 member_function_;

#ifndef __GNUG__
  Callback0 member_functionPointer_;
  Callback0 member_functionObject_;
#endif
 
};






//======================================================================
#endif
