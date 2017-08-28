// DemoProfCpp3rd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "chap19\chap19.h"
#include "chap11\chap11Template.h"
#include "chap12\chap12OutputStreams.h"

int main(int argc, char* argv[])
{
  printf("------------------------------------\n");
  printf("Professional C++ 3rd!\n");
  printf("LZA 520 2017\n");
  printf("------------------------------------\n");
  chap19StdFunction();
  chap19StdFunctionLambda();
  chap11DemoGrid();
  chap11DemoGridNonTypeParam();
  chap11FunctionTemplatesSyntax();
  chap11FunctionTemplateSpecialization1();
  chap11FunctionTemplateSpecialization2();
  chap12TestStreams();
  chap12TestManipulators();
  //chap12TestInputGet();
  //chap12TestInputUnget();
  //chap12TestInputPeek();
  //chap12TestInputGetline();
  //chap12TestInputErrorCheck();
  //chap12TestMuffin();
  //chap12TestStringStream();
  chap12TestOutputFileStream(argc, argv);
  chap12TestJumpingWithSeekTell();
  chap12TestLinkStream();
  chap12TestBidirectionalIO();

  return 0;
}

