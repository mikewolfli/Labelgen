#ifndef MYTHREAD_H_INCLUDED
#define MYTHREAD_H_INCLUDED

#include <memory>
#include <wx/thread.h>

#include "LabelGenApp.h"
#include "label_gen.h"
#include "stdafx.h"
#include <windows.h>

class LabelGenFrame;



class CMyExec{

public:

   HANDLE hChildStdinRd, hChildStdinWr, hChildStdoutRd, hChildStdoutWr, hInputFile, hStdout;

   void Exec(char *command);
   LPWSTR ConvertCharToLPWSTR(char * szString);

};

class MyThread : public wxThread {
public:
    MyThread(LabelGenFrame* frame, wxArrayValue _value);
    ~MyThread();
    virtual ExitCode Entry();

private:
    std::unique_ptr<label_gen> thread_labels;

    wxArrayValue array_result;
    LabelGenFrame*  ThreadFrame;
};


#endif // MYTHREAD_H_INCLUDED
