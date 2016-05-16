#include "mythread.h"
#include "LabelGenMain.h"


void CMyExec::Exec(char *command){
   SECURITY_ATTRIBUTES saAttr;
   BOOL fSuccess;

// Set the bInheritHandle flag so pipe handles are inherited.

   saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
   saAttr.bInheritHandle = TRUE;
   saAttr.lpSecurityDescriptor = NULL;

// Get the handle to the current STDOUT.

   hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

// Create a pipe for the child process's STDOUT.

   if (! CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0))
      return;

// Ensure the read handle to the pipe for STDOUT is not inherited.

   SetHandleInformation( hChildStdoutRd, HANDLE_FLAG_INHERIT, 0);

// Create a pipe for the child process's STDIN.

   if (! CreatePipe(&hChildStdinRd, &hChildStdinWr, &saAttr, 0))
     return;

// Ensure the write handle to the pipe for STDIN is not inherited.

   SetHandleInformation( hChildStdinWr, HANDLE_FLAG_INHERIT, 0);

   PROCESS_INFORMATION piProcInfo;
   STARTUPINFO siStartInfo;
   BOOL bFuncRetn = FALSE;

// Set up members of the PROCESS_INFORMATION structure.

   ZeroMemory( &piProcInfo, sizeof(PROCESS_INFORMATION) );

// Set up members of the STARTUPINFO structure.

   ZeroMemory( &siStartInfo, sizeof(STARTUPINFO) );
   siStartInfo.cb = sizeof(STARTUPINFO);
   siStartInfo.hStdError = hChildStdoutWr;
   siStartInfo.hStdOutput = hChildStdoutWr;
   siStartInfo.hStdInput = hChildStdinRd;
   siStartInfo.dwFlags |= STARTF_USESHOWWINDOW;
   siStartInfo.wShowWindow = SW_HIDE;

// Create the child process.

   bFuncRetn = CreateProcess(NULL,
      ConvertCharToLPWSTR(command),     // command line
      NULL,          // process security attributes
      NULL,          // primary thread security attributes
      TRUE,          // handles are inherited
      0,             // creation flags
      NULL,          // use parent's environment
      NULL,          // use parent's current directory
      &siStartInfo,  // STARTUPINFO pointer
      &piProcInfo);  // receives PROCESS_INFORMATION

}

LPWSTR CMyExec::ConvertCharToLPWSTR(char * szString)
{
 int dwLen = strlen(szString) + 1;
 int nwLen = MultiByteToWideChar(CP_ACP, 0, szString, dwLen, NULL, 0);//算出合适的长度
 LPWSTR lpszPath = new WCHAR[dwLen];
 MultiByteToWideChar(CP_ACP, 0, szString, dwLen, lpszPath, nwLen);
 return lpszPath;
}


MyThread::MyThread(LabelGenFrame* frame, wxArrayValue _value) : wxThread(),thread_labels(new label_gen)
{
     ThreadFrame = frame;
     array_result = _value;
}

MyThread::~MyThread() {
    wxCriticalSectionLocker locker(wxGetApp().AppCritSection);

    wxArrayThread& threads = wxGetApp().AppThreads;
    threads.Remove(this);

    if ( threads.IsEmpty() ) {
        // signal that no threads is waiting

        if ( wxGetApp().AppShutdown ) {
            wxGetApp().AppShutdown = false;

            wxGetApp().AppSemaphoreDone.Post();
        }
    }
}

// Thread entry
wxThread::ExitCode MyThread::Entry() {


    int i_count = array_result.GetCount();

   // wxString s_now=wxDateTime::Now().Format("%Y%m%d%H%M%S")+wxT(".pdf");
    wxArrayString array_error;
    wxString str;
    v_value_cell value;

    if(i_count ==0)
    {
        wxLogMessage(_("清单中没有打印项目,进程终止!"));
        return NULL;
    }


    wxLogMessage(_("正在生成表单:")+str);
    for(int i=0;i<i_count;i++)
    {
        value = array_result.Item(i);
        {
            wxCriticalSectionLocker locker(wxGetApp().AppCritSection);

            // If stop button pressed then return immediately
            if ( wxGetApp().AppShutdown )
            {
                return NULL;
            }
        }

        if(!value.check_info_finish(str))
        {
            array_error.Add(str);
            wxLogMessage(str);
            continue;
        }


        thread_labels->get_value(value);
        thread_labels->generate_table();
        ThreadFrame->print_log(value.s_wbs, gr_para.s_printer);

    }
    int i_row = array_error.GetCount();


    if(i_row==i_count)
    {
        return NULL;
    }

    wxString str_file= thread_labels->save_pdf_file();

    ThreadFrame->print_file(str_file);

  //  wxRemoveFile(str_file);

    if(i_row ==0 )
        return NULL;

    str.Empty();

    for(int j=0;j<i_row;j++)
    {
        str = str+array_error.Item(j)+wxT("\n");
    }

    wxMessageBox(str,_("错误提示"));

    return NULL;
}


