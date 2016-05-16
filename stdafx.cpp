#include "stdafx.h"
#include <wx/log.h>

void v_fixed_cell::init_data()
{
    s_project = _("项目名称:");
    s_head = _("项目基本信息表");
    s_sub_head1 = _("项目");
    s_sub_head2 = _("工厂配置(理论计算)");
    s_sub_head3 = _("实际安装");
    s_sub_head4 = _("调试员签字");
    s_sub_head5 = _("日期");
    s_sub_head6 = _("备注");
    s_sub_head7 = _("项目");
    s_sub_head8 = _("出厂设置");
    s_sub_head9 = _("调整后的测量值");
    s_sub_head10 = _("调试员签字");
    s_sub_head11 = _("日期");
    s_sub_head12 = _("缓冲器制造编号:");
    s_sub_head13 = _("限速器制造编号:");
    s_sub_head14 = _("安全钳制造编号:");
    s_sub_head15 = _("主板制造编号:");
    s_sub_head16 = _("曳引机制造编号:");
    s_balance_block_qty = _("轿厢配重块");
    s_balance_block0_qty = _("轿厢平衡块");
    s_sub_head17 = _("对重块数量");
    s_sub_head18 = _("装潢前");
    s_sub_head19 = _("装潢后");
    s_sub_head20 = _("装潢前");
    s_sub_head21 = _("装潢后");
    s_sub_head22 = _("曳引机制动弹簧");
    s_sub_head23 = _("左");
    s_sub_head24 = _("右");
    s_sub_head25 = _("长度(mm)");

    s_wbs = _("WBS号:");
    s_lift_no = _("梯号:");
    s_car_weight = _("空载轿厢重量(kg):");
    s_cwt_weight = _("对重架重量(kg):");
    s_dc_weight = _("预留装潢重量(kg):");
    s_rate = _("平衡系数");
    s_buffer_no_car = _("轿厢:");
    s_buffer_no_cwt = _("对重:");
    s_govern_no_car = _("轿厢:");
    s_govern_no_cwt = _("对重:");
    s_safe_guard_no_car = _("轿厢:");
    s_safe_guard_no_cwt = _("对重:");
    s_block_material1 = _("铸铁:");
    s_block_material2 = _("复合:");

}

v_value_cell& v_value_cell::operator=(const v_value_cell& other)
{
    if(&other != this)
    {
        s_project_name = other.s_project_name;
        s_balance_block_qty = other.s_balance_block_qty;
        s_balance_block0_qty  = other.s_balance_block0_qty;
        s_cwt_block_qty_dc_before = other.s_cwt_block_qty_dc_before;
        s_cwt_block_qty_dc_after = other.s_cwt_block_qty_dc_after;
        s_tm_spring_length_left = other.s_tm_spring_length_left;
        s_tm_spring_length_right = other.s_tm_spring_length_right;
        s_mainboard_no = other.s_mainboard_no;

        s_tm_no = other.s_tm_no;
        s_wbs = other.s_wbs;
        s_lift_no = other.s_lift_no;
        s_cwt_weight = other.s_cwt_weight;
        s_dc_weight = other.s_dc_weight;
        s_rate = other.s_rate;
        s_buffer_no_car = other.s_buffer_no_car;
        s_buffer_no_cwt = other.s_buffer_no_cwt;
        s_govern_no_car = other.s_govern_no_car;
        s_govern_no_cwt = other.s_govern_no_cwt;
        s_safe_guard_no_car = other.s_safe_guard_no_car;
        s_safe_guard_no_cwt = other.s_safe_guard_no_cwt;
        s_car_weight = other.s_car_weight;
        s_block_material1 = other.s_block_material1;
        s_block_material2 = other.s_block_material2;
    }

     return *this;
}

void v_value_cell::Clear()
{
        s_project_name.Clear();
         s_balance_block_qty.Clear();
         s_balance_block0_qty.Clear();
        s_cwt_block_qty_dc_before.Clear();
        s_cwt_block_qty_dc_after.Clear();
        s_tm_spring_length_left.Clear();
        s_tm_spring_length_right.Clear();
        s_mainboard_no.Clear();
        s_tm_no.Clear();

        s_wbs.Clear();
        s_lift_no.Clear();
        s_cwt_weight.Clear();
        s_dc_weight.Clear();
  //      s_rate.Clear();
        s_buffer_no_car.Clear();
        s_buffer_no_cwt.Clear();
        s_govern_no_car.Clear();
        s_govern_no_cwt.Clear();
        s_safe_guard_no_car.Clear();
        s_safe_guard_no_cwt.Clear();
        s_car_weight.Clear();
        s_block_material1.Clear();
        s_block_material2.Clear();
}

bool v_value_cell::check_info_finish(wxString &str)
{
    bool b_finish;
    str.Empty();


    if(s_car_weight.IsEmpty() || s_car_weight==wxT("0"))
    {
        str=str+wxT("轿厢空重;");
    }

    if(s_cwt_weight.IsEmpty() || s_cwt_weight==wxT("0"))
    {
        str=str+wxT("对重架重量;");
    }

    if(s_cwt_weight.IsEmpty() || s_cwt_weight==wxT("0"))
    {
        str=str+wxT("对重架重量;");
    }

    if(s_cwt_block_qty_dc_before.IsEmpty() || s_cwt_block_qty_dc_before==wxT("0"))
    {
        str=str+wxT("装潢前对重块数量;");
    }

    if(s_cwt_block_qty_dc_after.IsEmpty() || s_cwt_block_qty_dc_after==wxT("0"))
    {
        str=str+wxT("装潢后对重块数量;");
    }


        if((s_block_material1.IsEmpty()&&s_block_material2.IsEmpty())||(s_block_material1==wxT("0")&&s_block_material2==wxT("0"))||
        (s_block_material1.IsEmpty()&&s_block_material2==wxT("0"))||(s_block_material1==wxT("0")&&s_block_material2.IsEmpty()))
        {
            str=str+wxT("备注中对重块数量;");
        }


    if(str.IsEmpty())
        return true;
    else
        return false;
}

wxArrayString split_string(wxString src, wxString split_main_str, wxString serial_str, wxString individual_str, int unit_length, bool end_str)
{
    wxArrayString dest_str, src_str;
    wxString strtemp,strtemp1,strtemp2, strhead;
    int icount, itemp=0, ipos=0 ,ipos1,itemp1,itemp2,i,j;


    if(split_main_str == serial_str || split_main_str == individual_str && serial_str == individual_str)
    {
        wxLogMessage(_("分割字符不能相同,返回源字符串:")+src);
        dest_str.Add(src);
        return dest_str;
    }
//    src.Trim();

    if(end_str)
        src = src.RemoveLast(split_main_str.Length());

    if(!split_main_str.IsEmpty())
    {
        if(split_main_str.Contains(wxT("\\t")))
            split_main_str.Replace(wxT("\\t"),wxT("\t"));
        if(split_main_str.Contains(wxT("\\r")))
            split_main_str.Replace(wxT("\\r"),wxT("\r"));
        if(split_main_str.Contains(wxT("\\n")))
            split_main_str.Replace(wxT("\\n"),wxT("\n"));
        src_str = wxStringTokenize(src,split_main_str, wxTOKEN_RET_EMPTY_ALL );
    }
    else src_str.Add(src);

    if(unit_length<=0)
        dest_str = src_str;
    else
    {

        ipos=0;
        for(i =0; i< src_str.GetCount(); i++)
        {
            if(!src_str.Item(i).Contains(individual_str)&&!src_str.Item(i).Contains(serial_str))
            {
                if(src_str.Item(i).IsEmpty())
                    continue;
                dest_str.Add(src_str.Item(i));
                continue;
            }


            icount = getstrcount(src_str.Item(i),individual_str)+1;
            strhead=src_str.Item(i).Left(unit_length);

            itemp=unit_length;
            for (j=0; j<icount; j++)
            {
                ipos = src_str.Item(i).find(individual_str,ipos+1);
                if(ipos==wxNOT_FOUND)
                {
                    strtemp = src_str.Item(i).SubString(itemp+1,src_str.Item(i).Length()-1);
                }
                else
                    strtemp = src_str.Item(i).SubString(itemp+1,ipos-1);
                itemp=ipos;

                if(!strtemp.Contains(serial_str))
                {
                    strtemp = strhead + strtemp;
                    dest_str.Add(strtemp);
                }
                else
                {
                    ipos1 = strtemp.find(serial_str,0);
                    strtemp1=strtemp.Left(ipos1);
                    strtemp2=strtemp.Right(strtemp.Length()-ipos1-1);
                    itemp1 = wxAtoi(strtemp1);
                    itemp2 = wxAtoi(strtemp2);
                    for (int i=0; i<itemp2-itemp1+1; i++)
                    {
                        strtemp1=wxString::Format(wxT("%i"),itemp1+i);
                        if(strtemp1.Length()==1)
                            strtemp1=_T("00")+strtemp1;
                        else if(strtemp1.Length()==2)
                            strtemp1=_T("0")+strtemp1;

                        strtemp=strhead+strtemp1;

                        dest_str.Add(strtemp);
                    }

                }
            }

        }
    }
    return dest_str;


}


#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxArrayValue);
//WX_DEFINE_EXPORTED_OBJARRAY(wxArrayValue);
int arraycompare(v_value_cell** arg1, v_value_cell** arg2)
{
    wxString s_arg1 = (*arg1)->s_wbs;
    wxString s_arg2 = (*arg2)->s_wbs;
    s_arg1.Replace(wxT("E/"),wxT(""));
    s_arg2.Replace(wxT("E/"),wxT(""));
    s_arg1.Replace(wxT("."),wxT(""));
    s_arg2.Replace(wxT("."),wxT(""));

    return (wxAtol(s_arg1)< wxAtol(s_arg2));
}

int nstd_action_to_status(wxString s_action_id)
{
   s_action_id.Remove(0,2);
   int i_action = wxAtoi(s_action_id);

   switch(i_action)
   {
   case 9:
   case 12:
   case 16:
       return 0;
   case 10:
   case 13:
   case 14:
   case 17:
       return 1;
   case 11:
   case 15:
   case 18:
       return 2;
   case 22:
   case 24:
       return 3;
   case 23:
       return 4;
   case 19:
   case 20:
       return 5;
   default:
       break;
   }

   return -1;
}


int getstrcount(wxString str, wxString cf)
{
    int icount= str.Length();
    int istep = cf.Length();
    int istr=0;
    for (int i=0; i<icount-istep+2; i++)
    {
        if(cf==str.Mid(i,istep))
        {
            istr+=1;
        }
    }

    return istr;
}

wxArrayString combine_str(wxArrayString & array_str,wxString split_main_str, wxString serial_str, wxString individual_str, bool ck_sort,bool one_str)
{
    wxArrayString strhead,strresult;
    wxString str1,str2,strtemp;
    strhead = sort_array_string(array_str, ck_sort);
    int i,j,icount,icount_head,k;
    icount = array_str.GetCount();
    icount_head=strhead.GetCount();

    for(i=0; i<icount_head; i++)
    {
        k=0;
        for (j=0; j<icount; j++)
        {
            if(array_str.Item(j).Left(10)==strhead.Item(i))
            {
                if(k==0)
                {
                    str1=array_str.Item(j).Right(3);
                    k++;
                    continue;
                }

                if(serial_str.IsEmpty())
                {
                    //str1=str1+individual_str+array_str.Item(j).Right(3);
                    str1=str1+individual_str+array_str.Item(j);
                    k++;
                    continue;
                }

                k++;
                str2 = array_str.Item(j).Right(3);
                if(wxAtoi(str2)-wxAtoi(str1.Right(3))>1)
                {
                    str1=str1+individual_str+str2;
                    continue;
                }

                strtemp=str1.Right(serial_str.length()+3);
                if(strtemp.Contains(serial_str))
                {
                    str1.RemoveLast(3);
                    str1=str1+str2;
                }
                else
                    str1 = str1+serial_str+str2;

            }

        }

        str1 = strhead.Item(i) + wxT(".") +str1;
        strresult.Add(str1);
    }

    if(one_str)
    {
        strhead.Clear();
        str1 = strresult.Item(0);
        for(i=1; i<icount_head; i++)
        {
            str1=str1+split_main_str+strresult.Item(i);
        }
        strhead.Add(str1);
        return strhead;
    }

    return strresult;
}


int function_sort(wxString str)
{
    return wxAtoi(str.Right(3));
}

wxArrayString sort_array_string(wxArrayString &array_str, bool ck_sort)
{
    wxArrayString strhead;

    if(!ck_sort)
        array_str.Sort(function_sort);

    int icount = array_str.GetCount();

    strhead.Add(array_str.Item(0).Left(10));
    for(int i = 1; i<icount; i++)
    {
        if(strhead.Index(array_str.Item(i).Left(10),false,false)== wxNOT_FOUND)
            strhead.Add(array_str.Item(i).Left(10));
    }
    return strhead;
}


wxString qtIdent(const wxString &value, bool b_needquote)
{
    if (value.Length() == 0)
        return value;

    wxString result = value;

    if (b_needquote)
    {
        result.Replace(wxT("\""), wxT("\"\""));
        return wxT("\"") + result + wxT("\"");
    }
    else
        return result;
}


wxString zero_begin(long current_int, int length)
{
    wxString result;

    result= NumToStr(current_int);

    int len = result.Length();

    for(int i=0; i<length-len; i++)
    {
        result=wxT("0")+result;
    }

    return result;
}


wxString get_str_val(wxString str,wxArrayString &_header, wxArrayString &_value)
{
    int ifound = _header.Index(str);
    if(ifound == wxNOT_FOUND)
        return wxEmptyString;

    return _value.Item(ifound);
}

int find_in_array(wxString _str, wxArrayString &_array )
{
      return _array.Index(_str);
}


wxString nstd_status_to_str(int i_status)
{
    wxString str;
    switch(i_status)
    {
       case -1 :
         str =  wxT("DEL");
         break;
       case 0:
         str =  wxT("CRTD");
         break;
       case 1:
          str =  wxT("SUBMIT");
          break;
       case 2:
         str =  wxT("APPROVE");
         break;
       case 3:
         str =  wxT("PROC");
         break;
       case 4:
         str =  wxT("FEEDBACK");
         break;
       case 5:
         str = wxT("PDM-READY");
         break;
       case 6:
         str = wxT("SAP-READY");
         break;
       case 7:
          str = wxT("DOC-READY");
          break;
       case 8:
          str = wxT("ALL-READY");
          break;
       case 10:
         str =  wxT("CLOSED");
         break;
       default:
           str.Empty();
         break;
    }
    return str;
}

int nstd_str_to_status(wxString str_status)
{
    if(str_status == wxT("DEL"))
       return -1;

    if(str_status == wxT("CRTD"))
        return 0;


    if(str_status == wxT("SUBMIT"))
        return 1;

    if(str_status == wxT("APPROVE"))
        return 2;


    if(str_status == wxT("PROC"))
        return 3;

    if(str_status == wxT("FEEDBACK"))
        return 4;

    if(str_status == wxT("PDM-READY"))
        return 5;

    if(str_status == wxT("SAP-READY"))
        return 6;

    if(str_status == wxT("DOC-READY"))
        return 7;

    if(str_status == wxT("ALL-READY"))
        return 8;

    if(str_status == wxT("CLOSED"))
        return 10;

    return -2;
}

int nstd_str_to_level(wxString str_status)
{
    if(str_status == wxT("Target STD"))
       return 1;

    if(str_status == wxT("Option STD"))
        return 2;


    if(str_status == wxT("Simple Non-STD"))
        return 3;

    if(str_status == wxT("Complex Non-STD"))
        return 4;


    if(str_status == wxT("Comp-Standard"))
        return 5;

    if(str_status == wxT("Comp-Measurement"))
        return 6;

    if(str_status == wxT("Comp-Configurable"))
        return 7;

    if(str_status == wxT("Design Fault-Qty."))
        return 11;

    if(str_status == wxT("Design Fault-Spec."))
        return 12;

    if(str_status == wxT("Sales Order Fault-Qt"))
        return 13;

    if(str_status == wxT("Sales Order Fault-Sp"))
        return 14;

    if(str_status == wxT("Matl Pick Fault-Qty."))
        return 15;

    if(str_status == wxT("Matl Pick Fault-Spec"))
        return 16;

    if(str_status == wxT("Packing Fault-Qty."))
        return 17;

    if(str_status == wxT("Packing Fault-Spec."))
        return 18;

    if(str_status == wxT("Logistic Fault."))
        return 19;

    if(str_status == wxT("Abnormal in logistic"))
        return  21;

    if(str_status == wxT("ATI or ECR."))
        return 22;

    if(str_status == wxT("Others"))
        return 23;

    return 0;
}

wxString nstd_level_to_str(int i_status)
{
    wxString str;
    switch(i_status)
    {

    case 1:
        str = wxT("Target STD");
        break;
    case 2:
        str = wxT("Option STD");
        break;
    case 3:
        str = wxT("Simple Non-STD");
        break;
    case 4:
        str = wxT("Complex Non-STD");
        break;
    case 5:
        str = wxT("Comp-Standard");
        break;
    case 6:
        str = wxT("Comp-Measurement");
        break;
    case 7:
        str = wxT("Comp-Configurable");
        break;
    case 11:
        str = wxT("Design Fault-Qty.");
        break;
    case 12:
        str = wxT("Design Fault-Spec.");
        break;
    case 13:
        str = wxT("Sales Order Fault-Qt");
        break;
    case 14:
        str = wxT("Sales Order Fault-Sp");
        break;
    case 15:
        str = wxT("Matl Pick Fault-Qty.");
        break;
    case 16:
        str = wxT("Matl Pick Fault-Spec");
        break;
    case 17:
        str = wxT("Packing Fault-Qty.");
        break;
    case 18:
        str = wxT("Packing Fault-Spec.");
        break;
    case 19:
        str = wxT("Logistic Fault.");
        break;
    case 21:
        str = wxT("Abnormal in logistic");
        break;
    case 22:
        str = wxT("ATI or ECR.");
        break;
    case 23:
        str = wxT("Others");
        break;
    default:
        str.Empty();
        break;
    }

    return str;
}

wxString prj_catalog_to_str(int i_prj)
{
    wxString str;
    switch(i_prj)
    {

    case 1:
        str = wxT("Common Project");
        break;
    case 2:
        str = wxT("High-Speed Project");
        break;
    case 3:
        str = wxT("Special Project");
        break;
    case 4:
        str = wxT("Major Project");
        break;
    case 5:
        str = wxT("Pre_engineering");
        break;
    case 6:
        str = wxT("Lean Project");
        break;
    default:
        str.Empty();
        break;
    }

    return str;
}

int prj_str_to_catalog(wxString str_catalog)
{
    if(str_catalog == wxT("Common Project"))
       return 1;

    if(str_catalog == wxT("High-Speed Project"))
       return 2;

    if(str_catalog == wxT("Special Project"))
       return 3;


    if(str_catalog == wxT("Major Project"))
       return 4;

    if(str_catalog == wxT("Pre_engineering"))
       return 5;

    if(str_catalog == wxT("Lean Project"))
       return 6;

    return -1;
}


wxString prj_status_to_str(int i_prj)
{
    wxString str;
    switch(i_prj)
    {
       case -2:
          str = wxT("DEL");
          break;
       case -1 :
         str =  wxT("CANCEL");
         break;
       case 0:
         str =  wxT("CRTD");
         break;
       case 1:
         str =  wxT("ACTIVE");
         break;
       case 2:
          str =  wxT("FININISH");
          break;
       case 3:
         str =  wxT("RESTART");
         break;
       case 4:
         str =  wxT("FREEZED");
         break;
       case 5:
         str = wxT("CLOSED");
         break;
       case 6:
         str = wxT("RELEASED");
         break;
       case 7:
         str = wxT("PART FINISH");
         break;
       case 8:
         str = wxT("DELIVERIED");
         break;
       default:
           str.Empty();
         break;
    }
    return str;

}

int prj_str_to_status(wxString str_status)
{

    if(str_status == wxT("DEL"))
        return -2;

    if(str_status == wxT("CANCEL"))
       return -1;

    if(str_status == wxT("CRTD"))
        return 0;

    if(str_status == wxT("ACTIVE"))
        return 1;

    if(str_status == wxT("FININISH"))
        return 2;

    if(str_status == wxT("RESTART"))
        return 3;

    if(str_status == wxT("FREEZED"))
        return 4;

    if(str_status == wxT("CLOSED"))
        return 5;

    if(str_status == wxT("RELEASED"))
        return 6;

    if(str_status == wxT("PART FINISH"));
        return 7;

    if(str_status == wxT("DELIVERIED"));
       return 8;

    return -2;

}

wxString communication_status_to_str(int i_status)
{
    wxString str;
    switch(i_status)
    {
       case -1 :
         str =  _("已删除");
         break;
     case 0:
         str =  wxT("关闭");
          break;
       case 1:
         str =  _("等待分公司答复");
         break;
       case 2:
         str =  _("分公司已答复");
         break;

       default:
           str.Empty();
         break;
    }
    return str;

}

int communication_str_to_status(wxString str_status)
{
    if(str_status == _("已删除"))
       return -1;

    if(str_status == _("等待分公司答复"))
        return 1;


    if(str_status == _("分公司已答复"))
        return 2;

    if(str_status == _("关闭"))
        return 0;

    return -1;
}

int prj_str_to_nstd_level(wxString str_level)
{

    if(str_level == wxT("Complete Standard"))
        return 1;

    if(str_level == wxT("Option Standard"))
        return 2;

    if(str_level == wxT("Standard Configuration Without PC"))
        return 3;

    if(str_level == wxT("Simple Non-Standard"))
        return 4;

    if(str_level == wxT("Complex Non-Standard"))
        return 5;

    return 0;

}

wxString get_english_char(wxString str, int i_step,bool is_front, bool is_upper)
{
    wxString char_table = wxT("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    wxString str_resutl;

    int i_pos = char_table.Find(str);

    if(i_pos == wxNOT_FOUND)
        return wxEmptyString;

    if(is_front)
    {
        if(i_pos + i_step >=26)
            return wxEmptyString;

        str_resutl =  char_table.Mid(i_pos+i_step, 1);
    }else
     {
         if(i_pos - i_step <0)
            return wxEmptyString;

         str_resutl = char_table.Mid(i_pos-i_step, 1);
     }

     if(is_upper)
        str_resutl.Upper();
     else
        str_resutl.Lower();

     return str_resutl;
}

int task_status_to_int(wxString s_task_status)
{
    if(s_task_status == wxT("CRTD"))
        return 0;

    if(s_task_status == wxT("Approved"))
        return 2;

    if(s_task_status == wxT("Need Approve"))
        return 1;

    if(s_task_status == wxT("DEL"))
        return -1;

    return 0;
}

wxString task_int_to_status(int i_status)
{
   switch(i_status)
   {
   case 0:
       return wxT("CRTD");
   case 1:
       return wxT("Need Approve");
   case 2:
       return wxT("Approved");
   case -1:
       return wxT("DEL");
   default:
       return wxEmptyString;
   }

}
