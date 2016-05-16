#ifndef STDAFX_H_INCLUDED
#define STDAFX_H_INCLUDED
#include <wx/wx.h>
#include <wx/string.h>
#include <wx/tokenzr.h>
#include <wx/dynarray.h>

#include "interface/wxPostgreSQL.h"
#include "interface/wxpg_utils.h"

#ifdef __WXMSW__
#define END_OF_LINE wxT("\r\n")
#else
#define END_OF_LINE wxT("\n")
#endif

#define table_width 180
#define table_height 100
#define head_height 9
#define cell_height 6.5
#define table_edge_h 2
#define table_edge_v 2
#define blank_ch wxT(" ")
#define font_height1 8
#define font_height2 11
#define font_height3 9
#define font_height4 7

#define LABEL_PDF_PRINT_MAX_PAGES 99999

// table has 70 cells
class v_fixed_cell
{
public:
    v_fixed_cell()
    {
    }
    ~v_fixed_cell()
    {

    }
    // template
    wxString s_head;
    wxString s_sub_head1;
    wxString s_sub_head2;
    wxString s_sub_head3;
    wxString s_sub_head4;
    wxString s_sub_head5;
    wxString s_sub_head6;
    wxString s_sub_head7;
    wxString s_sub_head8;
    wxString s_sub_head9;
    wxString s_sub_head10;
    wxString s_sub_head11;
    wxString s_sub_head12;
    wxString s_sub_head13;
    wxString s_sub_head14;
    wxString s_sub_head15;
    wxString s_sub_head16;
    wxString s_sub_head17;
    wxString s_sub_head18;
    wxString s_sub_head19;
    wxString s_sub_head20;
    wxString s_sub_head21;
    wxString s_sub_head22;
    wxString s_sub_head23;
    wxString s_sub_head24;
    wxString s_balance_block_qty;
    wxString s_balance_block0_qty;
    wxString s_project;
    wxString s_sub_head25;

    wxString s_wbs;
    wxString s_lift_no;
    wxString s_car_weight;
    wxString s_cwt_weight;
    wxString s_dc_weight;
    wxString  s_rate;
    wxString s_buffer_no_car;
    wxString s_buffer_no_cwt;
    wxString s_govern_no_car;
    wxString s_govern_no_cwt;
    wxString s_safe_guard_no_car;
    wxString s_safe_guard_no_cwt;
    wxString s_block_material1;
    wxString s_block_material2;

    void init_data();

};

class v_value_cell
{
public:
    v_value_cell()
    {

    }
    ~v_value_cell()
    {

    }

    wxString s_wbs;
    wxString s_lift_no;
    wxString s_car_weight;
    wxString s_cwt_weight;
    wxString s_dc_weight;
    wxString s_block_material1;
    wxString s_block_material2;
    wxString s_rate = wxT("0.48");
    wxString s_project_name;
    wxString s_balance_block_qty;
    wxString s_balance_block0_qty;
    wxString s_cwt_block_qty_dc_before;
    wxString s_cwt_block_qty_dc_after;

    wxString s_tm_spring_length_left;
    wxString s_tm_spring_length_right;
    wxString s_mainboard_no;
    wxString s_tm_no;
    wxString s_buffer_no_car;
    wxString s_buffer_no_cwt;
    wxString s_govern_no_car;
    wxString s_govern_no_cwt;
    wxString s_safe_guard_no_car;
    wxString s_safe_guard_no_cwt;
    bool check_info_finish(wxString &str);
    v_value_cell& operator=(const v_value_cell& other);
    void Clear();
};

WX_DECLARE_OBJARRAY(v_value_cell, wxArrayValue);
//WX_DEFINE_ARRAY_PTR(v_value_cell *, wxArrayValue);

template < class T >
int ArrayCmp(T *a, T *b)
{
    if (*a == *b)
        return 0;

    if (*a > *b)
        return 1;
    else
        return -1;
}

//
// Table cell value formats
//
enum {
	wxStringFormat = 1,
	wxIntFormat,//2
	wxDoubleFormat,//3
	wxMoneyFormat,//4
	wxBoolFormat,//5
	wxDateTimeFormat,//6
	wxChoicesFormat,//7
	wxBitmapFormat,//8
	wxLastFormat//9
};

typedef struct prog_para
{
    wxString login_user;
    wxString login_role;
    wxString login_user_name;
    wxString plant;
    wxString lang_info;
    bool login_status;
    wxDateTime login_datetime;
    wxString server_host;
    wxString server_port;
    wxString server_dbname;
    wxString local_user;
    wxString local_ip;
    wxString local_pc_name;
    int threadgap;
    wxString s_printer;
    wxString s_printsetting;
} para;
extern para gr_para;

typedef enum
{
    COMMON_PROJECT = 1,
    HIGH_SPEED_PROJECT,
    SPECIAL_PROJECT,
    MAJOR_PROJECT,
    PRE_ENGINEERING,
    LEAN_PROJECT
} prj_type;

typedef enum
{
    IS_DELETED = -2,
    IS_CANCEL = -1,//删除
    IS_CREATED,//创建0
    IS_ACTIVE,//激活1
    IS_FINISHED,//完成2
    IS_RESTART,//重排产3
    IS_FREEZED,//暂停4
    IS_CLOSED,//关闭5
    IS_RELEASE, // release 6
    IS_PART_FINISHED, // 部分完成7
    IS_DELIVERY // 已发运 8
} _status;

typedef enum
{
    IS_DEL = -1 , //删除
    IS_CRTD, //新建0
    IS_SUBMIT, //提交1
    IS_APPROVE, //批准2
    IS_PROC,//任务已分配 3
    IS_RETURN, //返回状态 4
    IS_PROC_PDM, //任务已分配，已上传PDM 5
    IS_PROC_SAP,//任务已分配, 已上传SAP 6
    IS_PROC_DOC, //任务已分配， 已完成图纸 7
    IS_ALL_READY,//所有条件均具备 8
    IS_CLS //结束10
} nstd_status;

typedef enum
{
    IS_COM_CANCEL = -1 , //取消
    IS_COM_CLS,//结束
    IS_ISSUE, //提交ISSUE
    IS_FEEDBACK //反馈
}com_status;

typedef enum
{
    YA1 = 1,//Target STD
    YA2,//Option STD
    YA3, //Simple Non-STD
    YA4, //Complex Non-STD
    YA5, //Comp-Standard
    YA6,//Comp-Measurement
    YA7, //Comp-Configurable
    RA1=11,//Design Fault-Qty
    RA2,//Design Fault-Spec  12
    RA3,//Sales Order Fault-Qt 13
    RA4,//Sales Order Fault-Sp 14
    RA5,//Matl Pick Fault-Qty 15
    RA6,//Matl Pick Fault-Spec 16
    RA7,//Packing Fault-Qty 17
    RA8,//Packing Fault-Spec 18
    RA9,//Logistic Fault 19
    RB1=21,//Abnormal in logistic
    RB2,//TI or ECR 22
    RB3 //Others 23
} non_std_level;

/* split_string
   This function is used to split the unit (combine wbs no to separated units. Such as:
   E/30017758.001~003,005,008 to E/30017758.001, E/30017758.002, E/30017758.003, E/30017758.005, E/30017758.008
   also ,it can separate the some other string according to the parameters:
    1 src is the long-term string to be separated
    2 split_main_str - the main split string can separate the string to several be-separated strings,
    3 serial str - the two linked strings are the serial string;
    4 individual - the two linked strings are the individual string;
    5 unit_length - the project string length . if 0, not for unit split,
    6 end_str - bool type , is to check if the end of string contains the split character.

  case 1 : when unit_length <= 0, the serial_str and individual_str are invalided, only use the split_main_str to split the src)

*/

wxArrayString split_string(wxString src, wxString split_main_str, wxString serial_str, wxString individual_str, int unit_length, bool end_str);

//return the count of the sub-string in one string;
int getstrcount(wxString str, wxString cf);

//combine several unit wbs to one string;
wxArrayString combine_str(wxArrayString & array_str,wxString split_main_str, wxString serial_str, wxString individual_str, bool ck_sort,bool one_str);

//return head string;
wxArrayString sort_array_string(wxArrayString & array_str, bool ck_sort=true);
int function_sort(wxString str);

wxString qtIdent(const wxString &value, bool b_needquote);

wxString zero_begin(long current_int, int length);

wxString get_str_val(wxString str,wxArrayString &_header, wxArrayString &_value);

int find_in_array(wxString _str, wxArrayString &_array );


wxString nstd_status_to_str(int i_status);
int nstd_str_to_status(wxString str_status);

wxString nstd_level_to_str(int i_status);
int nstd_str_to_level(wxString str_status);

wxString communication_status_to_str(int i_status);
int communication_str_to_status(wxString str_status);

wxString prj_catalog_to_str(int i_prj);
int prj_str_to_catalog(wxString str_catalog);

wxString prj_status_to_str(int i_prj);
int prj_str_to_status(wxString str_status);

int prj_str_to_nstd_level(wxString str_level);

wxString get_english_char(wxString str, int i_step,bool is_front = true, bool is_upper=true);

int nstd_action_to_status(wxString s_action_id);

int task_status_to_int(wxString s_task_status);

wxString task_int_to_status(int i_status);

#endif // STDAFX_H_INCLUDED
