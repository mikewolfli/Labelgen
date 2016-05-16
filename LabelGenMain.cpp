/***************************************************************
 * Name:      LabelGenMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2015-03-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com/)
 * License:
 **************************************************************/

#include "LabelGenMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(LabelGenFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)
#include <wx/gbsizer.h>
#include <wx/sizer.h>
#include <wx/display.h>
#include "LabelGenApp.h"
#include "login_dlg.h"
#include <wx/printdlg.h>
#include "search_case.h"
#include "thread/mythread.h"
#include <wx/filefn.h>
#include "reset_pwd.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(LabelGenFrame)
const long LabelGenFrame::id_pass_word = wxNewId();
const long LabelGenFrame::idMenuQuit = wxNewId();
const long LabelGenFrame::idMenuAbout = wxNewId();
const long LabelGenFrame::ID_STATUSBAR1 = wxNewId();
//*)
const long LabelGenFrame::ID_TREELISTCTRL_PROJ_LIST = wxNewId();
const long LabelGenFrame::ID_BUTTON_WBS_LIST = wxNewId();
const long LabelGenFrame::ID_BUTTON_PROJ_NAME = wxNewId();
const long LabelGenFrame::ID_BUTTON_CONTRACT = wxNewId();
const long LabelGenFrame::ID_BUTTON_CLEAR = wxNewId();
const long LabelGenFrame::ID_BUTTON_SYC = wxNewId();
const long LabelGenFrame::ID_BUTTON_PDF = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_WBS = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CAR_WEIGHT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_PRJ_NAME = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_LIFT_NO = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CWT_WEIGHT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_DC_WEIGHT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_RATE = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_BALANCE_QTY = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_BALANCE0_QTY = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CWT_QTY_AFTER = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CWT_QTY_BEFOR = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CWT_BLOCK_MAT1 = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_CWT_BLOCK_MAT2 = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_TM_SPRING_LENGTH_L = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_TM_SPRING_LENGTH_R = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_BUFFER_NO_CAR = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_BUFFER_NO_CWT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_GOVERN_NO_CAR = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_SAFETY_NO_CAR = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_GOVERN_NO_CWT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_SAFETY_NO_CWT = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_MAINBOARD_NO = wxNewId();
const long LabelGenFrame::ID_TEXTCTRL_TM_NO = wxNewId();
const long LabelGenFrame::ID_BUTTON_GET_INFO = wxNewId();
const long LabelGenFrame::ID_BUTTON_SYC_SINGLE = wxNewId();
const long LabelGenFrame::ID_BUTTON_GEN_PDF_SINGLE = wxNewId();
const long LabelGenFrame::ID_LOG_TEXT_CTRL = wxNewId();

BEGIN_EVENT_TABLE(LabelGenFrame,wxFrame)
    //(*EventTable(LabelGenFrame)
    //*)
END_EVENT_TABLE()


LabelGenFrame::LabelGenFrame(wxWindow* parent,wxWindowID id)
{
    m_mgr.SetManagedWindow(this);

 //   this->Maximize(true);
    this->SetMinSize(wxSize(900,600));
    wxDisplay Screen;
    wxRect ClientRect = Screen.GetClientArea();

    //(*Initialize(LabelGenFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, id_pass_word, _("修改登录密码(&P)"), _("修改登录密码"), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -5, -10, -10 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(id_pass_word,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&LabelGenFrame::OnMenuItem3Selected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&LabelGenFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&LabelGenFrame::OnAbout);
    //*)
 //   Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(LabelGenFrame::OnIdle));

    m_LOGTextCtrl = new wxTextCtrl(this, ID_LOG_TEXT_CTRL, _("LOG Messages:\r\n"), wxDefaultPosition, wxSize(ClientRect.width,ClientRect.height/10),
		wxTE_READONLY|wxTE_MULTILINE);

#if wxUSE_LOG
#ifdef __WXMOTIF__
    // For some reason, we get a memcpy crash in wxLogStream::DoLogStream
    // on gcc/wxMotif, if we use wxLogTextCtl. Maybe it's just gcc?
    delete wxLog::SetActiveTarget(new wxLogStderr);
#else
    // set our text control as the log target
    wxLogTextCtrl *logWindow = new wxLogTextCtrl(m_LOGTextCtrl);
    delete wxLog::SetActiveTarget(logWindow);
#endif
#endif // wxUSE_LOG

    SetIcon(wxICON(aaaa));

    login_dlg dlg;
    if(dlg.ShowModal()==wxID_OK)
    {
        wxGetApp().login_log(2);
        gr_para.login_status = true;
        wxLogMessage(gr_para.login_user+_("登录 server:")+gr_para.server_host+";port:"+gr_para.server_port+"; database:"+gr_para.server_dbname);
        SetStatusText(gr_para.login_user+_(" 已登录\t")+gr_para.local_ip+"\t"+gr_para.local_pc_name,2);
    }
    else
    {
        gr_para.login_status = false;
        SetStatusText(_("未登录\t")+gr_para.local_ip+"\t"+gr_para.local_pc_name,2);
    }


    wxBoxSizer * size_treelist_panel = new wxBoxSizer(wxVERTICAL);

    m_treelist_Panel = new wxPanel(this, -1, wxDefaultPosition, wxSize(ClientRect.width/4,ClientRect.height*9/10), wxNO_BORDER);
    m_treelist_Panel->SetSizer(size_treelist_panel);
    Create_TreeList_Panel(m_treelist_Panel);
    size_treelist_panel->Fit(m_treelist_Panel);


    wxBoxSizer * size_proj_info_panel = new wxBoxSizer(wxVERTICAL);
    m_proj_info_panel = new wxPanel(this, -1, wxDefaultPosition, wxSize(ClientRect.width*3/4,ClientRect.height*9/10), wxNO_BORDER);
    m_proj_info_panel->SetSizer(size_proj_info_panel);
    Create_Project_Info(m_proj_info_panel);
    size_proj_info_panel->Fit(m_proj_info_panel);


	m_mgr.AddPane(m_treelist_Panel, wxAuiPaneInfo().
                  Name(wxT("Project_List")).Caption(wxT("项目列表")).Left().
				  Layer(1).Position(1));
	m_mgr.AddPane(m_LOGTextCtrl, wxAuiPaneInfo().
                  Name(wxT("Event LOG")).Caption(wxT("Event LOG")).Bottom().
				  Layer(1).Position(1));
	m_mgr.AddPane(m_proj_info_panel, wxAuiPaneInfo().Name(wxT("Center Pane")).CenterPane());
	m_mgr.Update();
	Layout();

}

LabelGenFrame::~LabelGenFrame()
{
    //(*Destroy(LabelGenFrame)
    //*)
    m_mgr.UnInit();

    wxThread *thread;

    wxGetApp().AppCritSection.Enter();

    // check if we have any threads running first
    const wxArrayThread& threads = wxGetApp().AppThreads;
    size_t count = threads.GetCount();

    if ( count )
    {
        // set the flag for MyThread::OnExit()
        wxGetApp().AppShutdown = true;

        // stop all threads
        while ( ! threads.IsEmpty() )
        {
            thread = threads.Last();

            wxGetApp().AppCritSection.Leave();

            thread->Delete();

            wxGetApp().AppCritSection.Enter();
        }
    }

    wxGetApp().AppCritSection.Leave();

    if ( count )
    {
        // now wait for them to really terminate
        wxGetApp().AppSemaphoreDone.Wait();
    }
    //else: no threads to terminate, no condition to wait for

#if wxUSE_LOG
    delete wxLog::SetActiveTarget(NULL);
#endif // wxUSE_LOG


}
/*
void LabelGenFrame::OnIdle(wxIdleEvent &evt)
{
    wxString str_file;
    while(!array_print_file.IsEmpty())
    {
        int i=0;
         str_file = array_print_file.Item(0);

         if(print_file(str_file)==-1)
            continue;

         wxSleep(3);

         array_print_file.Remove(str_file);

         while(!wxRemoveFile(str_file)&& i<=3)
         {
             i++;
             wxSleep(3);
         }

    }

    evt.Skip();
}
*/

void LabelGenFrame::OnQuit(wxCommandEvent& event)
{
 //   Close();
    wxCriticalSectionLocker enter(wxGetApp().AppCritSection);

    // AppThreads should always be empty...
    if (wxGetApp().AppThreads.IsEmpty()) {
        Close(true);
    }
    // ... so this check is a little bit superfluously
    else {
        wxGetApp().AppThreads.Empty();
        Close(true);
    }

    event.Skip();
}

void LabelGenFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void LabelGenFrame::Create_TreeList_Panel(wxWindow * parent)
{

	wxGridSizer* GridSizer1;
	wxBoxSizer* size_boxsizer = (wxBoxSizer *)parent->GetSizer();
	wxStaticBoxSizer* StaticBoxSizer1;

	GridSizer1 = new wxGridSizer(2, 2, 0, 0);
	wxButton* Button_WBS = new wxButton(parent, ID_BUTTON_WBS_LIST, _("按WBS NO搜索"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_WBS_LIST"));
	GridSizer1->Add(Button_WBS, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	wxButton* Button_Proj_name = new wxButton(parent, ID_BUTTON_PROJ_NAME, _("按项目名称搜索"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PROJ_NAME"));
	GridSizer1->Add(Button_Proj_name, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	wxButton* Button_Contract = new wxButton(parent, ID_BUTTON_CONTRACT, _("按合同号搜索"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CONTRACT"));
	GridSizer1->Add(Button_Contract, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	wxButton* Button_Clear = new wxButton(parent, ID_BUTTON_CLEAR, _("清除结果"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_CLEAR"));
	GridSizer1->Add(Button_Clear, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	//wxButton* Button_Syc = new wxButton(parent, ID_BUTTON_SYC, _("同步质量数据库"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SYC"));
	//GridSizer1->Add(Button_Syc, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	//wxButton* Button_PDF = new wxButton(parent, ID_BUTTON_PDF, _("生成PDF"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_PDF"));
	//GridSizer1->Add(Button_PDF, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	size_boxsizer->Add(GridSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, parent, _("项目清单"));
	size_boxsizer->Add(StaticBoxSizer1, 5, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);

	Build_Treelist(parent);
    StaticBoxSizer1->Add(tlc_proj_list, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0 );

    Connect(ID_BUTTON_WBS_LIST,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonWBS_SearchClick);
    Connect(ID_BUTTON_PROJ_NAME,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonPrj_Name_SearchClick);
    Connect(ID_BUTTON_CONTRACT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonContract_Name_SearchClick);
    Connect(ID_BUTTON_CLEAR,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonClear_all);

}

void LabelGenFrame::Clear_all()
{
    tc_wbs->Clear();
    tc_prj_name->Clear();
    tc_lift_no->Clear();
    tc_car_weight->Clear();
    tc_cwt_block_mat1->Clear();
    tc_cwt_block_mat2->Clear();
    tc_balance_qty->Clear();
    tc_rate->Clear();
    tc_cwt_qty_dcbefore->Clear();
    tc_cwt_qty_dcafter->Clear();
    tc_dc_weight->Clear();
    tc_cwt_weight->Clear();
    tc_balance0_qty->Clear();
}

void LabelGenFrame::set_text_value(v_value_cell v_cell)
{
    tc_wbs->SetValue(v_cell.s_wbs);
    tc_prj_name->SetValue(v_cell.s_project_name);
    tc_lift_no->SetValue(v_cell.s_lift_no);
    tc_car_weight->SetValue(v_cell.s_car_weight);
    tc_cwt_weight->SetValue(v_cell.s_cwt_weight);
    tc_cwt_block_mat1->SetValue(v_cell.s_block_material1);
    tc_cwt_block_mat2->SetValue(v_cell.s_block_material2);
    tc_balance_qty->SetValue(v_cell.s_balance_block_qty);
    tc_balance0_qty->SetValue(v_cell.s_balance_block0_qty);
    tc_rate->SetValue(v_cell.s_rate);
    tc_cwt_qty_dcbefore->SetValue(v_cell.s_cwt_block_qty_dc_before);
    tc_cwt_qty_dcafter->SetValue(v_cell.s_cwt_block_qty_dc_after);
    tc_dc_weight->SetValue(v_cell.s_dc_weight);
}

void LabelGenFrame::OnButtonClear_all(wxCommandEvent& event)
{
    wxTreeItemId root = tlc_proj_list->GetRootItem();
    tlc_proj_list->DeleteChildren (root);
    array_result.Clear();
    Clear_all();
}

void LabelGenFrame::OnButtonContract_Name_SearchClick(wxCommandEvent& event)
{
    if (!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,不能进行任何操作!"));
        return;
    }

    wxTextEntryDialog tdlg(this, _("请输入合同号"), _("合同号"), wxT(""), wxTextEntryDialogStyle, wxDefaultPosition);
    tdlg.SetTextValidator(wxFILTER_NONE);
    if (tdlg.ShowModal() == wxID_CANCEL)
        return;

    wxString s_sql = wxT(" contract_id = '")+tdlg.GetValue()+wxT("' and status >=5 ");
    set_clause(s_sql);

    refresh_Treelist();
}

void LabelGenFrame::OnButtonPrj_Name_SearchClick(wxCommandEvent& event)
{
    if (!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,不能进行任何操作!"));
        return;
    }

    wxTextEntryDialog tdlg(this, _("请输入项目名称"), _("项目名称"), wxT(""), wxTextEntryDialogStyle, wxDefaultPosition);
    tdlg.SetTextValidator(wxFILTER_NONE);
    if (tdlg.ShowModal() == wxID_CANCEL)
        return;

    wxString s_sql = wxT(" project_name like '%")+tdlg.GetValue()+wxT("%' and status >=5 ");
    set_clause(s_sql);

    refresh_Treelist();
}

void LabelGenFrame::OnButtonWBS_SearchClick(wxCommandEvent& event)
{

    if (!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,不能进行任何操作!"));
        return;
    }

    search_case tdlg;
    tdlg.set_wbs_check(true);
    wxArrayString array_wbs;

    if(tdlg.ShowModal()==wxID_OK)
    {
        array_wbs = tdlg.GetValue();

    }else
       return;

    if(array_wbs.IsEmpty())
        return;

    wxString s_sql;

    int i_count = array_wbs.GetCount();

    for (int i = 0; i < i_count; i++)
    {
        if (i == 0)
           s_sql = wxT(" (wbs_no = '") + array_wbs.Item(i) + wxT("' ");
        else
            s_sql = s_sql + wxT(" OR wbs_no = '") + array_wbs.Item(i) + wxT("' ");
    }
    s_sql  = s_sql + wxT(")  and status >=5 ");

    set_clause(s_sql);

    refresh_Treelist();
}

void LabelGenFrame::Build_Treelist(wxWindow * parent)
{
    tlc_proj_list = new wxcode::wxTreeListCtrl(parent, ID_TREELISTCTRL_PROJ_LIST ,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxTR_DEFAULT_STYLE| wxTR_COLUMN_LINES|wxTR_HIDE_ROOT|wxTR_ROW_LINES|wxTR_MULTIPLE | wxTR_FULL_ROW_HIGHLIGHT);

    tlc_proj_list->AddColumn(_("项目信息"),200,wxALIGN_LEFT,-1,true,false);//0
    tlc_proj_list->AddColumn(_("索引"),0,wxALIGN_LEFT,-1,false,false);//1
    tlc_proj_list->AddColumn(_("梯号"),50,wxALIGN_LEFT, -1,true,false );//2
    tlc_proj_list->AddColumn(_("梯型"),100,wxALIGN_LEFT, -1,true,false );//3
    tlc_proj_list->AddColumn(_("载重"),50,wxALIGN_LEFT,-1,true,false);//4
    tlc_proj_list->AddColumn(_("速度"),50,wxALIGN_LEFT,-1,true,false);//5
    tlc_proj_list->AddColumn(_("信息是否完整"),50,wxALIGN_LEFT,-1,true,false);//6
    tlc_proj_list->AddColumn(_("说明"),50,wxALIGN_LEFT,-1,true,false);//7
    tlc_proj_list->AddColumn(_("配置工程师"),100,wxALIGN_LEFT, -1,true,false);//8


    Connect(ID_TREELISTCTRL_PROJ_LIST,wxEVT_COMMAND_TREE_ITEM_ACTIVATED,(wxObjectEventFunction)&LabelGenFrame::TreeList_select);

    tlc_proj_list->AddRoot (_("项目列表"));
}

void LabelGenFrame::refresh_treelist_level()
{


    wxTreeItemId root = tlc_proj_list->GetRootItem();
    wxString s_status;

    wxTreeItemIdValue cookie;
    wxTreeItemId item = tlc_proj_list->GetFirstChild(root,cookie);

    while(item.IsOk())
    {
        wxTreeItemIdValue cookie_child;
        wxTreeItemId child_item = tlc_proj_list->GetFirstChild(item,cookie_child);
        tlc_proj_list->Expand(item);

        while(child_item.IsOk())
        {

            s_status = tlc_proj_list->GetItemText(child_item, 6);
            if(s_status.IsEmpty())
                tlc_proj_list->SetItemBackgroundColour(child_item, *wxRED);

            child_item = tlc_proj_list->GetNextSibling(child_item);

        }
        item = tlc_proj_list->GetNextSibling(item);

    }
}

void LabelGenFrame::TreeList_select(wxTreeEvent &event)
{
    if(!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,无法做任何操作!"));
        return;
    }

    wxTreeItemId root = tlc_proj_list->GetRootItem();
    wxTreeItemId sel_id = event.GetItem();

    if(tlc_proj_list->GetItemParent(sel_id) == root)
    {
        wxLogMessage(_("请选择树枝节点"));
        return;
    }

    wxString s_wbs = tlc_proj_list->GetItemText(sel_id, 0);

    int i_pos = find_wbs(s_wbs);

    if(i_pos !=-1)
        set_text_value(array_result.Item(i_pos));
    else
        Clear_all();

}

int LabelGenFrame::find_wbs(wxString s_wbs)
{

    int i_count = array_result.GetCount();

    if(i_count==0)
        return -1;

    for(int i=0;i<i_count;i++)
    {
        if(array_result.Item(i).s_wbs == s_wbs)
            return i;
    }
    return -1;
}

bool LabelGenFrame::print_log(wxString s_wbs, wxString s_printer)
{
    wxString s_sql= wxT("INSERT INTO s_unit_info_attach_print_log(wbs_no, printed_date, printer, printed_by) VALUES ('")+s_wbs+wxT("','")+
                    DateToAnsiStr(wxDateTime::Now())+wxT("','")+s_printer+wxT("','")+gr_para.login_user+wxT("');");
    return wxGetApp().app_sql_update(s_sql);
}

void LabelGenFrame::Create_Project_Info(wxWindow * parent)
{
	wxGridBagSizer* GridBagSizer1;
	wxBoxSizer* BoxSizer2;
	wxBoxSizer* size_boxsizer = (wxBoxSizer *)parent->GetSizer();


	GridBagSizer1 = new wxGridBagSizer(0, 0);
	wxStaticText* StaticText1 = new wxStaticText(parent, wxID_ANY, _("WBS号"));
	GridBagSizer1->Add(StaticText1, wxGBPosition(0, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_wbs = new wxTextCtrl(parent, ID_TEXTCTRL_WBS, wxEmptyString, wxDefaultPosition, wxSize(98,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_WBS"));
	GridBagSizer1->Add(tc_wbs, wxGBPosition(0, 1), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText2 = new wxStaticText(parent, wxID_ANY, _("项目名称"));
	GridBagSizer1->Add(StaticText2, wxGBPosition(0, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText4 = new wxStaticText(parent, wxID_ANY, _("空载轿厢\n重量 (kg)"));
	GridBagSizer1->Add(StaticText4, wxGBPosition(1, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_car_weight = new wxTextCtrl(parent, ID_TEXTCTRL_CAR_WEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CAR_WEIGHT"));
	GridBagSizer1->Add(tc_car_weight, wxGBPosition(1, 1), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_prj_name = new wxTextCtrl(parent, ID_TEXTCTRL_PRJ_NAME, wxEmptyString, wxDefaultPosition, wxSize(249,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_PRJ_NAME"));
	GridBagSizer1->Add(tc_prj_name, wxGBPosition(0, 6), wxGBSpan(1, 4), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText3 = new wxStaticText(parent, wxID_ANY, _("梯号"));
	GridBagSizer1->Add(StaticText3, wxGBPosition(0, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_lift_no = new wxTextCtrl(parent, ID_TEXTCTRL_LIFT_NO, wxEmptyString, wxDefaultPosition, wxSize(49,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_LIFT_NO"));
	GridBagSizer1->Add(tc_lift_no, wxGBPosition(0, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText5 = new wxStaticText(parent, wxID_ANY, _("对重架重量(kg)"));
	GridBagSizer1->Add(StaticText5, wxGBPosition(1, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_cwt_weight = new wxTextCtrl(parent, ID_TEXTCTRL_CWT_WEIGHT, wxEmptyString, wxDefaultPosition, wxSize(51,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CWT_WEIGHT"));
	GridBagSizer1->Add(tc_cwt_weight, wxGBPosition(1, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText6 = new wxStaticText(parent, wxID_ANY, _("预留装潢重量(kg)"));
	GridBagSizer1->Add(StaticText6, wxGBPosition(1, 5), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_dc_weight = new wxTextCtrl(parent, ID_TEXTCTRL_DC_WEIGHT, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_DC_WEIGHT"));
	GridBagSizer1->Add(tc_dc_weight, wxGBPosition(1, 7), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText7 = new wxStaticText(parent, wxID_ANY, _("平衡系数"));
	GridBagSizer1->Add(StaticText7, wxGBPosition(1, 8), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	tc_rate = new wxTextCtrl(parent, ID_TEXTCTRL_RATE, wxEmptyString, wxDefaultPosition, wxSize(40,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_RATE"));
	GridBagSizer1->Add(tc_rate, wxGBPosition(1, 9), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);


    wxStaticText* StaticText30 = new wxStaticText(parent, wxID_ANY, _("工厂配置\n平衡块数量"));
	GridBagSizer1->Add(StaticText30, wxGBPosition(2, 0), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    tc_balance0_qty = new wxTextCtrl(parent, ID_TEXTCTRL_BALANCE0_QTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_BALANCE_QTY"));
	GridBagSizer1->Add(tc_balance0_qty, wxGBPosition(2, 1), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	wxStaticText* StaticText8 = new wxStaticText(parent, wxID_ANY, _("工厂配置\n配重块数量"));
	GridBagSizer1->Add(StaticText8, wxGBPosition(2, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_balance_qty = new wxTextCtrl(parent, ID_TEXTCTRL_BALANCE_QTY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_BALANCE_QTY"));
	GridBagSizer1->Add(tc_balance_qty, wxGBPosition(2, 4), wxGBSpan(1, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);

	wxStaticText* StaticText9 = new wxStaticText(parent, wxID_ANY, _("对重块数量"));
	GridBagSizer1->Add(StaticText9, wxGBPosition(3, 0), wxGBSpan(2, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText11 = new wxStaticText(parent, wxID_ANY, _("装潢后"));
	GridBagSizer1->Add(StaticText11, wxGBPosition(4, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_cwt_qty_dcafter = new wxTextCtrl(parent, ID_TEXTCTRL_CWT_QTY_AFTER, wxEmptyString, wxDefaultPosition, wxSize(51,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CWT_QTY_AFTER"));
	GridBagSizer1->Add(tc_cwt_qty_dcafter, wxGBPosition(4, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText10 = new wxStaticText(parent, wxID_ANY, _("装潢前"));
	GridBagSizer1->Add(StaticText10, wxGBPosition(3, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_cwt_qty_dcbefore = new wxTextCtrl(parent, ID_TEXTCTRL_CWT_QTY_BEFOR, wxEmptyString, wxDefaultPosition, wxSize(52,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CWT_QTY_BEFOR"));
	GridBagSizer1->Add(tc_cwt_qty_dcbefore, wxGBPosition(3, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText12 = new wxStaticText(parent, wxID_ANY, _("铸铁"));
	GridBagSizer1->Add(StaticText12, wxGBPosition(3, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_cwt_block_mat1 = new wxTextCtrl(parent, ID_TEXTCTRL_CWT_BLOCK_MAT1, wxEmptyString, wxDefaultPosition, wxSize(50,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CWT_BLOCK_MAT1"));
	GridBagSizer1->Add(tc_cwt_block_mat1, wxGBPosition(3, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText13 = new wxStaticText(parent, wxID_ANY, _("复合"));
	GridBagSizer1->Add(StaticText13, wxGBPosition(4, 3), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_cwt_block_mat2 = new wxTextCtrl(parent, ID_TEXTCTRL_CWT_BLOCK_MAT2, wxEmptyString, wxDefaultPosition, wxSize(49,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_CWT_BLOCK_MAT2"));
	GridBagSizer1->Add(tc_cwt_block_mat2, wxGBPosition(4, 4), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	/*wxStaticText* StaticText14 = new wxStaticText(parent, wxID_ANY, _("*曳引机制动\n弹簧长度(mm)"));
	GridBagSizer1->Add(StaticText14, wxGBPosition(5, 0), wxGBSpan(2, 1), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText15 = new wxStaticText(parent, wxID_ANY, _("左*"));
	GridBagSizer1->Add(StaticText15, wxGBPosition(5, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_tm_spring_length_l = new wxTextCtrl(parent, ID_TEXTCTRL_TM_SPRING_LENGTH_L, wxEmptyString, wxDefaultPosition, wxSize(49,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_TM_SPRING_LENGTH_L"));
	GridBagSizer1->Add(tc_tm_spring_length_l, wxGBPosition(5, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText16 = new wxStaticText(parent, wxID_ANY, _("右*"));
	GridBagSizer1->Add(StaticText16, wxGBPosition(6, 1), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_tm_spring_length_r = new wxTextCtrl(parent, ID_TEXTCTRL_TM_SPRING_LENGTH_R, wxEmptyString, wxDefaultPosition, wxSize(48,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_TM_SPRING_LENGTH_R"));
	GridBagSizer1->Add(tc_tm_spring_length_r, wxGBPosition(6, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText17 = new wxStaticText(parent, wxID_ANY, _("*缓冲器制造编号"));
	GridBagSizer1->Add(StaticText17, wxGBPosition(7, 0), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText18 = new wxStaticText(parent, wxID_ANY, _("轿厢*"));
	GridBagSizer1->Add(StaticText18, wxGBPosition(7, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_buffer_no_car = new wxTextCtrl(parent, ID_TEXTCTRL_BUFFER_NO_CAR, wxEmptyString, wxDefaultPosition, wxSize(132,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_BUFFER_NO_CAR"));
	GridBagSizer1->Add(tc_buffer_no_car, wxGBPosition(7, 3), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText19 = new wxStaticText(parent, wxID_ANY, _("对重*"));
	GridBagSizer1->Add(StaticText19, wxGBPosition(7, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_buffer_no_cwt = new wxTextCtrl(parent, ID_TEXTCTRL_BUFFER_NO_CWT, wxEmptyString, wxDefaultPosition, wxSize(138,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_BUFFER_NO_CWT"));
	GridBagSizer1->Add(tc_buffer_no_cwt, wxGBPosition(7, 6), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText20 = new wxStaticText(parent, wxID_ANY, _("*限速器制造编号"));
	GridBagSizer1->Add(StaticText20, wxGBPosition(8, 0), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText21 = new wxStaticText(parent, wxID_ANY, _("轿厢*"));
	GridBagSizer1->Add(StaticText21, wxGBPosition(8, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_govern_no_car = new wxTextCtrl(parent, ID_TEXTCTRL_GOVERN_NO_CAR, wxEmptyString, wxDefaultPosition, wxSize(132,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_GOVERN_NO_CAR"));
	GridBagSizer1->Add(tc_govern_no_car, wxGBPosition(8, 3), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_safety_no_car = new wxTextCtrl(parent, ID_TEXTCTRL_SAFETY_NO_CAR, wxEmptyString, wxDefaultPosition, wxSize(132,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_SAFETY_NO_CAR"));
	GridBagSizer1->Add(tc_safety_no_car, wxGBPosition(9, 3), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText22 = new wxStaticText(parent, wxID_ANY, _("对重*"));
	GridBagSizer1->Add(StaticText22, wxGBPosition(8, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_govern_no_cwt = new wxTextCtrl(parent, ID_TEXTCTRL_GOVERN_NO_CWT, wxEmptyString, wxDefaultPosition, wxSize(135,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_GOVERN_NO_CWT"));
	GridBagSizer1->Add(tc_govern_no_cwt, wxGBPosition(8, 6), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText23 = new wxStaticText(parent, wxID_ANY, _("*安全钳制造编号"));
	GridBagSizer1->Add(StaticText23, wxGBPosition(9, 0), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText24 = new wxStaticText(parent, wxID_ANY, _("轿厢*"));
	GridBagSizer1->Add(StaticText24, wxGBPosition(9, 2), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText25 = new wxStaticText(parent, wxID_ANY, _("对重*"));
	GridBagSizer1->Add(StaticText25, wxGBPosition(9, 5), wxDefaultSpan, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_safety_no_cwt = new wxTextCtrl(parent, ID_TEXTCTRL_SAFETY_NO_CWT, wxEmptyString, wxDefaultPosition, wxSize(134,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_SAFETY_NO_CWT"));
	GridBagSizer1->Add(tc_safety_no_cwt, wxGBPosition(9, 6), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText26 = new wxStaticText(parent, wxID_ANY, _("*主板制造编号"));
	GridBagSizer1->Add(StaticText26, wxGBPosition(10, 0), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_mainboard_no = new wxTextCtrl(parent, ID_TEXTCTRL_MAINBOARD_NO, wxEmptyString, wxDefaultPosition, wxSize(406,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_MAINBOARD_NO"));
	GridBagSizer1->Add(tc_mainboard_no, wxGBPosition(10, 2), wxGBSpan(1, 6), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	wxStaticText* StaticText27 = new wxStaticText(parent, wxID_ANY, _("*曳引机制造编号"));
	GridBagSizer1->Add(StaticText27, wxGBPosition(11, 0), wxGBSpan(1, 2), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	tc_tm_no = new wxTextCtrl(parent, ID_TEXTCTRL_TM_NO, wxEmptyString, wxDefaultPosition, wxSize(406,21), wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL_TM_NO"));
	GridBagSizer1->Add(tc_tm_no, wxGBPosition(11, 2), wxGBSpan(1, 6), wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);*/
	size_boxsizer->Add(GridBagSizer1, 8, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	wxButton* Button_Get_info = new wxButton(parent, ID_BUTTON_GET_INFO, _("预览前次生成表单"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_GET_INFO"));
	BoxSizer2->Add(Button_Get_info, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
   //wxButton* Button_Syc = new wxButton(parent, ID_BUTTON_SYC_SINGLE, _("打印预览"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_SYC_SINGLE"));
	//BoxSizer2->Add(Button_Syc, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxButton* Button_Gen_pdf = new wxButton(parent, ID_BUTTON_GEN_PDF_SINGLE, _("打印"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON_GEN_PDF"));
	BoxSizer2->Add(Button_Gen_pdf, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	size_boxsizer->Add(BoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_BOTTOM, 0);


    Connect(ID_BUTTON_GEN_PDF_SINGLE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonPrintPdf);
    Connect(ID_BUTTON_GET_INFO,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LabelGenFrame::OnButtonPrintPreview);


}

void LabelGenFrame::OnButtonPrintPreview(wxCommandEvent& event)
{

    wxString s_exe =wxGetCwd()+wxT("\\plugins\\SumatraPDF.exe ");
    wxString s_file = wxGetCwd() +wxT("\\temp\\temp.pdf");

    if(!wxFileExists(s_file))
    {
        wxLogMessage(s_file+_("文件不存在!"));
        return;
    }

    wxExecute(s_exe+s_file, wxEXEC_SYNC);
}

void LabelGenFrame::OnButtonPrintPdf(wxCommandEvent& event)
{
    if(!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,无法做任何操作!"));
        return;
    }

    if(!wxGetApp().conn->IsAlive())
    {
        wxLogMessage(_("系统连接已断开,请重新连接!"));
        wxGetApp().clear_login();
        return;
    }

    wxArrayValue array_print;

    wxArrayTreeItemIds items;
    wxTreeItemId root = tlc_proj_list->GetRootItem();

    wxArrayTreeItemIds::iterator iter;
    tlc_proj_list->GetSelections( items );
    wxString s_wbs;
    int i_pos;
    wxTreeItemId sel_item, child_item;
    wxTreeItemIdValue cookie;

    if(items.IsEmpty())
    {
        wxLogMessage(_("未选择打印项次，默认全部打印!"));
        array_print = array_result;
    }
    else
    {
        for( iter = items.begin(); iter<items.end(); iter++)
        {
            sel_item = *iter;
            if(tlc_proj_list->GetItemParent(sel_item)==root)
            {
                child_item = tlc_proj_list->GetFirstChild(sel_item,cookie);
                while(child_item.IsOk())
                {

                    s_wbs = tlc_proj_list->GetItemText(child_item, 0);

                    i_pos = find_wbs(s_wbs);
                    array_print.Add(array_result.Item(i_pos));
                    child_item = tlc_proj_list->GetNextSibling(child_item);
                }
            }
            else
            {
                s_wbs = tlc_proj_list->GetItemText(sel_item,0);
                              i_pos = find_wbs(s_wbs);
                array_print.Add(array_result.Item(i_pos));

            }
        }
    }


    MyThread* print_thread = new MyThread(this,array_print);

    if ( print_thread->Create() != wxTHREAD_NO_ERROR )
    {
        wxLogError(wxT("无法创建打印线程"));
        return;
    }

    wxCriticalSectionLocker enter(wxGetApp().AppCritSection);
    wxGetApp().AppThreads.Add(print_thread);


    if ( print_thread->Run() != wxTHREAD_NO_ERROR )
    {
         wxLogMessage(_("打印线程启动失败!"));
         return;
    }
    wxString s_id = wxString::Format("0x%lx",print_thread->GetId());
    wxLogMessage(_("打印线程已经启动,请耐心等待,线程ID:")+s_id);
}

void LabelGenFrame::refresh_Treelist()
{
    if(!gr_para.login_status)
    {
        wxLogMessage(_("尚未登陆,无法做任何操作!"));
        return;
    }

    if(!wxGetApp().conn->IsAlive())
    {
        wxLogMessage(_("系统连接已断开,请重新连接!"));
        wxGetApp().clear_login();
        return;
    }


    array_result.Clear();
    Clear_all();
    wxTreeItemId root = tlc_proj_list->GetRootItem();
    tlc_proj_list->DeleteChildren (root);


    wxString str_sql = wxT("select contract_id, project_name, plant, branch_name, res_emp_id, wbs_no, \
       project_id, elevator_id,(select elevator_type FROM s_elevator_type_define where elevator_type_id = \
       elevator_id) as elevator_type,lift_no, status, wf_status, is_urgent, \
       project_catalog, nonstd_level, is_batch, unit_doc_id, batch_id, \
       car_weight, cwt_frame_weight, reserve_decoration_weight, balance_rate, \
       conf_balance_block_qty, conf_balance_block0_qty, cwt_block_qty_before_dc, cwt_block_qty_after_dc, \
       cwt_block_qty_mat1, cwt_block_qty_mat2, tm_spring_length_left, \
       (select load from s_unit_parameter where wbs_no = v_unit_info_attach.wbs_no) as load, \
        (select speed from s_unit_parameter where wbs_no = v_unit_info_attach.wbs_no) as speed, \
       tm_spring_length_right, buffer_man_no_car, buffer_man_no_cwt, \
       govern_man_no_car, govern_man_no_cwt, safty_guard_man_no_car, \
       safty_guard_man_no_cwt, mainboard_man_no, traction_man_no, (select operator_id from l_proc_act where instance_id=wbs_no and action_id='AT00000004') as conf_operator_id from \
       v_unit_info_attach where ")+m_clause+wxT("  order by wbs_no ASC;");

  //     wxMessageBox(str_sql, _(""));

   wxPostgreSQLresult* _res= wxGetApp().app_sql_select(str_sql);

    if(_res->Status()!= PGRES_TUPLES_OK)
    {
        return;
    }

    int i_count = _res->GetRowsNumber();

     wxTreeItemId branch_item,leaf_item;
     wxString s_wbs, s_project_id, s_project_name, str, s_employee_id;
     int i_temp;
     v_value_cell v_cell;
    for(int i=0;i<i_count;i++)
    {
       if(s_project_id != _res->GetVal(wxT("project_id")))
       {
           s_project_id = _res->GetVal(wxT("project_id"));
           s_project_name = _res->GetVal(wxT("project_name"));
           str = _res->GetVal(wxT("contract_id"))+wxT(" ")+s_project_name+wxT(" ")+s_project_id;
           branch_item = tlc_proj_list->AppendItem(root, str);
           tlc_proj_list->SetItemText(branch_item,1, s_project_id);

       }

       str = _res->GetVal(wxT("wbs_no"));

       v_cell.s_wbs = str;
       v_cell.s_project_name = s_project_name;
       leaf_item = tlc_proj_list->AppendItem(branch_item,str,-1,-1);

       tlc_proj_list->SetItemText(leaf_item, 1, s_project_id);

       str = _res->GetVal(wxT("lift_no"));
       if(str.Right(1)==wxT("*"))
         str.RemoveLast(1);
       v_cell.s_lift_no = str;
       tlc_proj_list->SetItemText(leaf_item, 2, str);

       str =_res->GetVal(wxT("elevator_type"));
       tlc_proj_list->SetItemText(leaf_item, 3, str);

       str = _res->GetVal(wxT("load"));
       tlc_proj_list->SetItemText(leaf_item, 4, str);

       str = _res->GetVal(wxT("speed"));
       tlc_proj_list->SetItemText(leaf_item, 5, str);

       s_employee_id = _res->GetVal(wxT("conf_operator_id"));
       str = get_name( s_employee_id);
       tlc_proj_list->SetItemText(leaf_item, 8, str);

       i_temp = _res->GetInt(wxT("car_weight"));
       v_cell.s_car_weight = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("cwt_frame_weight"));
       v_cell.s_cwt_weight = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("reserve_decoration_weight"));
       v_cell.s_dc_weight = NumToStr(i_temp);

       str = _res->GetVal(wxT("balance_rate"));
       v_cell.s_rate = str;

       i_temp = _res->GetInt(wxT("conf_balance_block_qty"));
       v_cell.s_balance_block_qty = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("conf_balance_block0_qty"));
       v_cell.s_balance_block0_qty = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("cwt_block_qty_before_dc"));

          v_cell.s_cwt_block_qty_dc_before = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("cwt_block_qty_after_dc"));

          v_cell.s_cwt_block_qty_dc_after = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("cwt_block_qty_mat1"));
       v_cell.s_block_material1 = NumToStr(i_temp);

       i_temp = _res->GetInt(wxT("cwt_block_qty_mat2"));

          v_cell.s_block_material2 = NumToStr(i_temp);


       bool b_show= v_cell.check_info_finish(str);

       tlc_proj_list->SetItemText(leaf_item,6, BoolToY(b_show));
       tlc_proj_list->SetItemText(leaf_item, 7,str);

       array_result.Add(v_cell);
       _res->MoveNext();

    }

    _res->Clear();

    refresh_treelist_level();
}

wxString LabelGenFrame::get_name(wxString s_id)
{
    if(s_id.IsEmpty())
        return wxEmptyString;
    wxString s_sql = wxT("select name from s_employee where employee_id = '")+s_id+wxT("';");
    wxPostgreSQLresult* _res= wxGetApp().app_sql_select(s_sql);

    if(_res->Status()!= PGRES_TUPLES_OK)
    {
        return wxEmptyString;
    }

    int i_count = _res->GetRowsNumber();
    if(i_count==0)
    {
        _res->Clear();
        return wxEmptyString;
    }

    wxString str = _res->GetVal(wxT("name"));

    _res->Clear();

    return str;
}

void LabelGenFrame::print_file(wxString s_file)
{

    if(s_file.IsEmpty())
        return;

    wxString s_exe,s_para;

    s_exe = wxGetCwd()+wxT("\\plugins\\SumatraPDF.exe");
    if(gr_para.s_printer.IsEmpty())
    {
        s_para =wxT(" -print-to-default -print-settings \"")+
                gr_para.s_printsetting+wxT("\" ")+s_file;

    }
    else
    {
        s_para =  wxT(" -print-to \"")+gr_para.s_printer+wxT("\" -print-settings \"")+
                gr_para.s_printsetting+wxT("\" ")+s_file;
    }

    wxLogMessage(_("正在将文档输出到打印机..."));
    wxLogMessage(_("文档:")+s_file);

    wxString s_command = s_exe+s_para;
   // wxLogMessage(s_command);

    char c1[1024];
    strncpy(c1, s_command.mb_str(wxConvUTF8), 1023);


    CMyExec exec;
    exec.Exec(c1);

  //  wxRemoveFile(s_file);

}

void LabelGenFrame::Onmi_pdf_pathSelected(wxCommandEvent& event)
{
}

void LabelGenFrame::Onmi_pdf_previewSelected(wxCommandEvent& event)
{
}

void LabelGenFrame::Onmi_generate_pdfSelected(wxCommandEvent& event)
{/*
    v_value_cell l_value;
    l_value.s_project_name = _("拱墅区康桥单元FG08-R21-16地块");
    l_value.s_lift_no = _("L20");
    l_value.s_wbs = _("E/30028661.020");
    l_value.s_car_weight = _("1500");
    l_value.s_cwt_weight = _("600");
    l_value.s_dc_weight = _("300");
    l_value.s_balance_block_qty = _("10");
    l_value.s_cwt_block_qty_dc_before = _("24");
    l_value.s_cwt_block_qty_dc_after = _("30");
    l_value.s_block_material1=_("0");
    l_value.s_block_material2 = _("30");
    m_label_pdf->get_value(l_value);
    m_label_pdf->generate_table();
    m_label_pdf->save_pdf_file();*/

}

void LabelGenFrame::Onmi_previewSelected(wxCommandEvent& event)
{
}

void LabelGenFrame::Onmi_printSelected(wxCommandEvent& event)
{
}

void LabelGenFrame::OnMenuItem3Selected(wxCommandEvent& event)
{
    reset_pwd pwd_dlg;
    pwd_dlg.ShowModal();
}
