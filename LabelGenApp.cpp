/***************************************************************
 * Name:      LabelGenApp.cpp
 * Purpose:   Code for Application Class
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2015-03-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com/)
 * License:
 **************************************************************/

#include "LabelGenApp.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include "wx/pdfdoc.h"
#include "wx/pdffontmanager.h"
#include "connect_para_dlg.h"
#include <wx/socket.h>
#include "pugixml.hpp"
#include "security/base64.h"
#include <wx/tokenzr.h>

//(*AppHeaders
#include "LabelGenMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(LabelGenApp);

para gr_para;
bool LabelGenApp::OnInit()
{
    wxFileName exePath = wxStandardPaths::Get().GetExecutablePath();
    wxString fontPath = exePath.GetPathWithSep() + wxT("./fonts");
    wxPdfFontManager::GetFontManager()->AddSearchPath(fontPath);

    if(!read_para()) return false;
    bool b_return;

    do
    {

        conn = new wxPostgreSQL(conn_str, wxConvUTF8);

//   int s_ver;
        if(conn->Status()==CONNECTION_OK)
        {
//        wxMessageBox(wxString(conn->GetHost()));
//      s_ver = conn->ServerVersion();
            b_return= true;
        }
        else
        {

            connect_para_dlg dlg;

            if(dlg.ShowModal() == wxID_OK)
            {
                if(conn)
                  delete conn;
                read_para();
                conn = new wxPostgreSQL(conn_str, wxConvUTF8);

                //   int s_ver;
                if(conn->Status()==CONNECTION_OK)
                {
//        wxMessageBox(wxString(conn->GetHost()));
//      s_ver = conn->ServerVersion();
                    b_return= true;
                }else b_return=false;
            }else
            {
              wxMessageBox(conn->ErrorMessage(),"Connect error:");
               return false;
            }

        }
    }
    while(!b_return);

    wxIPV4address addr;
    gr_para.local_pc_name = wxGetFullHostName();
    gr_para.local_user = wxGetUserId();
    gr_para.login_status = false;
    addr.Hostname(gr_para.local_pc_name);
    gr_para.local_ip = addr.IPAddress();
    gr_para.lang_info = wxT("zh_CN");


    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        LabelGenFrame* Frame = new LabelGenFrame(0);


        Frame->Show();
        SetTopWindow(Frame);
    }

    return wxsOK;

}

int LabelGenApp::OnExit()
{
    int i_way=check_status();
    if(i_way>=1)
        login_log(1);
    if(conn)
    {
        conn->Finish();
        delete conn;
    }

    return 0;
}



bool LabelGenApp::read_para()//read the parameter from the xml file
{

    wxString ldbusr,ldbpwd;
    pugi::xml_document ldoc;
    pugi::xml_node lnode;
    pugi::xml_parse_result result;

    result = ldoc.load_file("config.xml");
    if(result)
    {
        lnode =ldoc.child("connect");
        gr_para.server_host = wxString(lnode.child_value("host"));
        gr_para.server_port = wxString(lnode.child_value("port"));
        gr_para.server_dbname = wxString(lnode.child_value("dbname"));
        ldbusr = wxString(lnode.child_value("dbuser"));
        ldbpwd = wxString(lnode.child_value("dbpwd"));
        ldbpwd = Base64::Decode(ldbpwd);
//       ldbpwd = wxBase64Encode(ldbpwd,ldbpwd.Length());
//       wxMessageBox(ldbpwd);
        conn_str = wxT("host=")+gr_para.server_host +wxT(" port=")+gr_para.server_port+ wxT(" dbname=")+gr_para.server_dbname + wxT(" user=")+ldbusr + wxT(" password=")+ldbpwd;

        lnode = ldoc.child("environment");
        gr_para.threadgap = atoi(lnode.child_value("ThreadGap"));

        lnode = ldoc.child("printsetting");
        gr_para.s_printer = wxString (lnode.child_value("printer"));
        gr_para.s_printsetting = wxString(lnode.child_value("setting"));

        return true;
    }
    else return false;

}

void LabelGenApp::login_log(int i_way)//log the login
{
    wxString lquery;
    switch(i_way)
    {
    case 0:
        lquery = "INSERT INTO l_login_log(employee_id, log_status, login_time, login_ip, login_user, login_pc_name,version_id) VALUES ('"+gr_para.login_user+"', TRUE,'"+ gr_para.login_datetime.Format("%Y-%m-%d %H:%M:%S")+"','"+ gr_para.local_ip +"','"+gr_para.local_user+"','"+gr_para.local_pc_name+"','LabelGen');";
        conn->ExecuteVoid(lquery);
        break;
    case 1:
        lquery = "UPDATE l_login_log SET log_status=false, logoff_time='"+ wxDateTime::Now().Format("%Y-%m-%d %H:%M:%S")+"' where employee_id = '"+gr_para.login_user+"' and login_time = '"+gr_para.login_datetime.Format("%Y-%m-%d %H:%M:%S")+"' AND login_pc_name='"+gr_para.local_pc_name+"'";
        conn->ExecuteVoid(lquery);
        break;
    case 2:
           lquery = "UPDATE l_login_log SET log_status=false where employee_id = '"+gr_para.login_user+"' and login_pc_name ='"+gr_para.local_pc_name+"' and log_status = true;";
            conn->ExecuteVoid(lquery);
            break;
    default:
        break;
    }

}

int LabelGenApp::check_status() //check the conn connect status
{
    if(gr_para.login_user.IsEmpty())
        return 0;

    if(conn->Status()==CONNECTION_BAD)
        return -1;

    if(!conn->IsAlive())
        return -1;

    wxPostgreSQLresult *res;
    wxString lquery= "select * from l_login_log where employee_id = '"+gr_para.login_user+"' and log_status = true and login_pc_name = '"+gr_para.local_pc_name+"'";
    res = conn->Execute(lquery);
    if(res->Status()!=PGRES_TUPLES_OK)
    {
        wxMessageBox(res->ErrorMessage(),_("SELECT failed:"));
        res->Clear();
        return -1;
    }

    int irow = res->GetRowsNumber();
    res->Clear();
    return irow;
}


bool LabelGenApp::is_have(wxString lquery)
{
    wxPostgreSQLresult * l_res = conn->Execute(lquery);
    if(l_res->Status() == PGRES_TUPLES_OK)
    {
        int irow = l_res->GetRowsNumber();

        l_res->Clear();
        if(irow >=1)
            return true;
        else
            return false;

    }else
            l_res->Clear();

    return false;
}

void LabelGenApp::clear_login()
{
    gr_para.login_user.Empty();
    gr_para.login_role.Empty();
    gr_para.login_status = false;
    gr_para.login_user_name.Empty();
    gr_para.login_datetime = wxDateTime::Now();
    gr_para.plant.Empty();
}


wxString LabelGenApp::get_ser_no(wxString _table_str, wxString _para_str)
{
    if(!gr_para.login_status|| conn->Status()!= CONNECTION_OK)
        return wxEmptyString;

    wxString result;
    long l_counter;
    int i_step,i_len;
    wxString pre_c,fol_c;

    wxString lquery = wxT("select current_counter, counter_step, pre_char, fol_char, id_len from s_number_counter where table_str = '")+_table_str+wxT("' and table_para_str ='")+_para_str+wxT("'");
    wxPostgreSQLresult * l_res = conn->Execute(lquery);


    if(l_res->Status()!= PGRES_TUPLES_OK)
        return wxEmptyString;

    int irow = l_res->NumRows();
    if(irow<1)
        return wxEmptyString;

    if(irow>1)
    {
        wxLogMessage(_("数据库表中存在重复数据,请核查!"));
        return wxEmptyString;
    }

    l_counter = l_res->GetLong(wxT("current_counter"));
    i_step = l_res->GetInt(wxT("counter_step"));
    i_len = l_res->GetInt(wxT("id_len"));
    pre_c = l_res->GetVal(wxT("pre_char"));
    fol_c = l_res->GetVal(wxT("fol_char"));

    if(!fol_c.IsEmpty())
        result = pre_c + zero_begin(l_counter,i_len) + wxT("-")+ fol_c;
    else
        result = pre_c + zero_begin(l_counter,i_len);

    l_res->Clear();

    bool b_run = true;

    l_counter = l_counter + i_step;


    lquery = wxT("UPDATE s_number_counter SET current_counter = '")+NumToStr(l_counter)+wxT("' WHERE table_str = '")+_table_str+wxT("' and table_para_str ='")+_para_str+wxT("'");

    do
    {
        l_res = conn->Execute(lquery);

        if(l_res->Status() == PGRES_FATAL_ERROR)
            b_run = false;

        l_res->Clear();

    }
    while(!b_run);


    return result;
}

wxString LabelGenApp::get_ser_id(wxString _table_str, wxString _para_str)
{
    if(!gr_para.login_status||conn->Status()!= CONNECTION_OK)
        return wxEmptyString;

    wxString result;
    long l_counter;
    int i_step;
    wxString pre_c,fol_c;

    wxString lquery = wxT("select current_counter, counter_step, pre_char, fol_char from s_number_counter where table_str = '")+_table_str+wxT("' and table_para_str ='")+_para_str+wxT("'");
    wxPostgreSQLresult * l_res = conn->Execute(lquery);


    if(l_res->Status()!= PGRES_TUPLES_OK)
        return wxEmptyString;

    int irow = l_res->NumRows();
    if(irow<1)
        return wxEmptyString;

    if(irow>1)
    {
        wxLogMessage(_("数据库表中存在重复数据,请核查!"));
        return wxEmptyString;
    }

    l_counter = l_res->GetLong(wxT("current_counter"));
    i_step = l_res->GetInt(wxT("counter_step"));
    pre_c = l_res->GetVal(wxT("pre_char"));
    fol_c = l_res->GetVal(wxT("fol_char"));

    if(!fol_c.IsEmpty())
         result = pre_c + NumToStr(l_counter) + wxT("-") + fol_c;
    else
        result = pre_c + NumToStr(l_counter);

    l_res->Clear();

    bool b_run = true;

    l_counter = l_counter + i_step;


    lquery = wxT("UPDATE s_number_counter SET current_counter = '")+NumToStr(l_counter)+wxT("' WHERE table_str = '")+_table_str+wxT("' and table_para_str ='")+_para_str+wxT("'");

    do
    {
        l_res = conn->Execute(lquery);

        if(l_res->Status() == PGRES_FATAL_ERROR)
            b_run = false;

        l_res->Clear();

    }
    while(!b_run);


    return result;

}

wxArrayString LabelGenApp::Get_header(wxString _table_str, wxArrayString &_para_str)
{
    wxArrayString str_header;
    wxString lquery;

     str_header.Clear();
    if(!gr_para.login_status|| conn->Status()!= CONNECTION_OK)
        return str_header;

    lquery = wxT("SELECT table_para_str, item_name FROM v_table_parameter WHERE lang_info = '")+gr_para.lang_info+wxT("' AND  table_str = '")+_table_str+wxT("'");

    wxPostgreSQLresult * l_res = conn->Execute(lquery);

    if(l_res->Status()!= PGRES_TUPLES_OK)
    {
        return str_header;
    }

    int irow = l_res->NumRows();

    if(irow <= 0)
        return str_header;

    int icol = _para_str.GetCount();



    for (int i=0;i<icol;i++)
      for(int j=0;j<irow;j++)
      {
          if(_para_str.Item(i)== wxString(l_res->GetValue(j,0),wxConvUTF8))
            str_header.Add(wxString(l_res->GetValue(j,1),wxConvUTF8));
          else
            str_header.Add(wxEmptyString);
      }
    l_res->Clear();
    return str_header;
}

bool LabelGenApp::app_sql_update(wxString &_query)
{
    return conn->ExecuteVoid(_query);
}

wxPostgreSQLresult * LabelGenApp::app_sql_select(wxString & _query)
{
    return conn->Execute(_query);
}

bool LabelGenApp::update_desc(wxString str_id, wxString str_desc, bool b_update)
{
    wxString str_query;

    if(b_update)
    {
        str_query = wxT("UPDATE s_doc SET doc_desc='")+str_desc+wxT("' WHERE doc_id='")+str_id+wxT("';");

    }else
    {
        str_query = wxT("INSERT INTO s_doc (doc_id, doc_desc) VALUES ('")+str_id+wxT("','")+str_desc+wxT("');");
    }


    return conn->ExecuteVoid(str_query);

}

wxString LabelGenApp::get_leader(wxString s_group)
{
    wxString l_query;

    l_query = wxT("SELECT employee_id FROM s_group_member WHERE group_id = '")+s_group+wxT("' AND is_leader = true and status = true;");

    return conn->ExecuteScalar(l_query);

}

wxArrayString LabelGenApp::get_group()
{
    wxPostgreSQLresult *t_res;
    wxArrayString str_groups;
    wxString l_query, str_temp;
    l_query = wxT("SELECT group_id FROM s_group_member WHERE employee_id = '")+gr_para.login_user +wxT("' and status = true;");

    t_res = conn->Execute(l_query);


    if(t_res->Status()!= PGRES_TUPLES_OK)
    {
        return str_groups;
    }

    int icount = t_res->GetRowsNumber();

    t_res->MoveFirst();
    for(int i=0;i<icount;i++)
    {
        str_temp = t_res->GetVal(0);
        str_groups.Add(str_temp);
        t_res->MoveNext();
    }
    t_res->Clear();

    return str_groups;

}

wxString LabelGenApp::get_only_group()
{
    wxArrayString array_group = get_group();
    if(array_group.GetCount() == 1)
    {
        return array_group.Item(0);
    }

    if(array_group.GetCount() == 0)
    {
        return wxEmptyString;
    }

    return NumToStr(array_group.GetCount());
}

bool LabelGenApp::is_leader(wxString s_group)
{

    wxPostgreSQLresult *t_res;
    wxString l_query;
    l_query = wxT("SELECT count(1) as row_num FROM s_group_member WHERE group_id = '")+s_group+wxT("' AND is_leader = true AND employee_id = '")+gr_para.login_user+wxT("' and status = true;");
    t_res = conn->Execute(l_query);


    if(t_res->Status()!= PGRES_TUPLES_OK)
    {
        return false;
    }

    int icount = t_res->GetInt(wxT("row_num"));

    if(icount >=1)
    {
        t_res->Clear();
        return true;
    }
    else
    {
        t_res->Clear();
        return false;
    }
    return false;
}

wxArrayString LabelGenApp::get_member_in_group(wxString str_group, bool with_leader)
{
    wxPostgreSQLresult *t_res;
    wxArrayString str_members;
    wxString l_query, str_temp;
    l_query = wxT("SELECT concat(employee_id,'-',name), is_leader FROM v_group_member WHERE group_id = '")+str_group+wxT("' AND plant = '")+gr_para.plant+wxT("' and status=true;");

    t_res = conn->Execute(l_query);


    if(t_res->Status()!= PGRES_TUPLES_OK)
    {
        return str_members;
    }

    int icount = t_res->GetRowsNumber();

    t_res->MoveFirst();
    for(int i=0;i<icount;i++)
    {
        str_temp = t_res->GetVal(0);

        if(!with_leader && t_res->GetBool(1))
        {
            t_res->MoveNext();
            continue;
        }

        str_members.Add(str_temp);
        t_res->MoveNext();
    }
    t_res->Clear();

    return str_members;

}

wxArrayString LabelGenApp::get_member_in_group(wxArrayString str_group, bool with_leader)
{
    int i_count = str_group.GetCount();

    wxPostgreSQLresult *t_res;
    wxArrayString str_members;
    wxString l_query, str_temp;
    l_query = wxT("SELECT concat(employee_id,'-',name)as employee , is_leader FROM v_group_member WHERE plant = '")+gr_para.plant+wxT("'AND group_id = '")+str_group.Item(0)+ wxT("' and status =true  ");
    for(int i =1;i<i_count;i++)
    {
        l_query = l_query + wxT(" OR group_id = '")+str_group.Item(i)+wxT("' ");
    }

    l_query = l_query+wxT(";");


    t_res = conn->Execute(l_query);


    if(t_res->Status()!= PGRES_TUPLES_OK)
    {
        return str_members;
    }

    int icount = t_res->GetRowsNumber();

    t_res->MoveFirst();
    for(int i=0;i<icount;i++)
    {
        str_temp = t_res->GetVal(0);

        if(!with_leader && t_res->GetBool(1))
        {
            t_res->MoveNext();
            continue;
        }

        str_members.Add(str_temp);
        t_res->MoveNext();
    }
    t_res->Clear();

    return str_members;
}

bool LabelGenApp::change_log(wxString s_table, wxString s_keyword, wxString source_char,wxString source_value, wxString result_value, wxString change_way)
{
    wxString str_query;

    str_query = wxT("INSERT INTO l_change_log(table_str, key_word, source_char, source_value, result_value, \
            modify_person, modify_date, change_way) VALUES ('")+s_table+wxT("','")+s_keyword+wxT("','")+source_char+wxT("','")
            +source_value+wxT("','")+result_value+wxT("','")+gr_para.login_user+wxT("','")+DateToAnsiStr(wxDateTime::Now())+wxT("','")+change_way+wxT("');");


    return conn->ExecuteVoid(str_query);

}

bool LabelGenApp::update_data_in_database(wxString change_key, wxString change_value, wxString table_name, wxString pri_key, wxString pri_value)
{
    wxString str_query;
    str_query = wxT("UPDATE  ")+table_name+ wxT(" SET ")+change_key+wxT("='")+change_value+wxT("' , modify_date='")+DateToAnsiStr(wxDateTime::Now())+
                           wxT("', modify_emp_id='")+gr_para.login_user+wxT("' WHERE ")+pri_key+wxT("='")+pri_value+wxT("';");
    str_query.Replace(wxT("''"),wxT("NULL"));
    return conn->ExecuteVoid(str_query);
}
