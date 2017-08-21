#pragma once
void rawWrite(const char* data, size_t dataSize);
void rawPutChar(const char* data, size_t charIndex);

// demo testing
void chap12TestStreams();
void chap12TestManipulators();
void chap12TestInputGet();
void chap12TestInputUnget();
void chap12TestInputPeek();
void chap12TestInputGetline();
void chap12TestInputErrorCheck();
void chap12TestMuffin();