/***************************************************************
 * Name:      LabelGenApp.h
 * Purpose:   Defines Application Class
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2015-03-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com/)
 * License:
 **************************************************************/

#ifndef LABELGENAPP_H
#define LABELGENAPP_H

#include <wx/app.h>
#include "stdafx.h"
#include "interface/wxPostgreSQL.h"
#include "stdafx.h"

WX_DEFINE_ARRAY_PTR(wxThread *, wxArrayThread);
extern para gr_para;

class LabelGenApp : public wxApp
{
public:
    LabelGenApp() : AppShutdown(false) {}
    virtual bool OnInit();
    virtual int OnExit();

    bool read_para();
    wxPostgreSQL* conn;

    void login_log(int i_way);
    int check_status();
    void clear_login();
    wxString get_ser_no(wxString _table_str, wxString _para_str);
    wxString get_ser_id(wxString _table_str, wxString _para_str);
    bool is_have(wxString lquery);
    wxArrayString Get_header(wxString _table_str, wxArrayString & _para_str);
    bool app_sql_update(wxString &_query);//include insert and update)
    wxPostgreSQLresult * app_sql_select(wxString & _query);
    bool update_desc(wxString str_id, wxString str_desc, bool b_update);
    wxString get_leader(wxString s_group);
    wxArrayString get_group();
    wxString get_only_group();
    wxArrayString get_member_in_group(wxString str_group, bool with_leader = false);
    wxArrayString get_member_in_group(wxArrayString str_group, bool with_leader =false);
    bool is_leader(wxString s_group);

    bool change_log(wxString s_table, wxString s_keyword, wxString source_char,wxString source_value, wxString result_value, wxString change_way=wxT("hand"));
    bool update_data_in_database(wxString change_key, wxString change_value, wxString table_name, wxString pri_key, wxString pri_value);

    // Critical Section for multi-thread background

    wxCriticalSection   AppCritSection;
    wxSemaphore         AppSemaphoreDone;
    bool                AppShutdown;

    wxArrayThread       AppThreads;

private:
    wxString conn_str;


};

DECLARE_APP(LabelGenApp)
#endif // LABELGENAPP_H
