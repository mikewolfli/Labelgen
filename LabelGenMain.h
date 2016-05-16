/***************************************************************
 * Name:      LabelGenMain.h
 * Purpose:   Defines Application Frame
 * Author:    mikewolfli (mikewolfli@163.com)
 * Created:   2015-03-10
 * Copyright: mikewolfli (http://mikewolfli.blog.163.com/)
 * License:
 **************************************************************/

#ifndef LABELGENMAIN_H
#define LABELGENMAIN_H

//(*Headers(LabelGenFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include <wx/aui/aui.h>
#include "stdafx.h"
#include "treelistctrl.h"
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
//#include "label_gen.h"
#include <wx/textdlg.h>

extern   para gr_para;

class LabelGenFrame: public wxFrame
{
    public:

        LabelGenFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~LabelGenFrame();

        void set_clause(wxString str)
        {
            m_clause = str;
        }
        bool print_log(wxString s_wbs, wxString s_printer);
        void print_file(wxString s_file);
        wxString get_name(wxString s_id);

  //      wxArrayString array_print_file;

    private:

        //(*Handlers(LabelGenFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void Onmi_pdf_pathSelected(wxCommandEvent& event);
        void Onmi_pdf_previewSelected(wxCommandEvent& event);
        void Onmi_generate_pdfSelected(wxCommandEvent& event);
        void Onmi_previewSelected(wxCommandEvent& event);
        void Onmi_printSelected(wxCommandEvent& event);
        void OnMenuItem3Selected(wxCommandEvent& event);
        //*)

        //(*Identifiers(LabelGenFrame)
        static const long id_pass_word;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)
        static const long ID_TREELISTCTRL_PROJ_LIST;
        static const long ID_BUTTON_WBS_LIST;
		static const long ID_BUTTON_PROJ_NAME;
		static const long ID_BUTTON_CONTRACT;
		static const long ID_BUTTON_CLEAR;
		static const long ID_BUTTON_SYC;
		static const long ID_BUTTON_PDF;

		static const long ID_TEXTCTRL_WBS;
		static const long ID_TEXTCTRL_CAR_WEIGHT;
		static const long ID_TEXTCTRL_PRJ_NAME;
		static const long ID_TEXTCTRL_LIFT_NO;
		static const long ID_TEXTCTRL_CWT_WEIGHT;
		static const long ID_TEXTCTRL_DC_WEIGHT;
		static const long ID_TEXTCTRL_RATE;
		static const long ID_TEXTCTRL_BALANCE_QTY;
		static const long ID_TEXTCTRL_BALANCE0_QTY;
		static const long ID_TEXTCTRL_CWT_QTY_AFTER;
		static const long ID_TEXTCTRL_CWT_QTY_BEFOR;
		static const long ID_TEXTCTRL_CWT_BLOCK_MAT1;
		static const long ID_TEXTCTRL_CWT_BLOCK_MAT2;
		static const long ID_TEXTCTRL_TM_SPRING_LENGTH_L;
		static const long ID_TEXTCTRL_TM_SPRING_LENGTH_R;
		static const long ID_TEXTCTRL_BUFFER_NO_CAR;
		static const long ID_TEXTCTRL_BUFFER_NO_CWT;
		static const long ID_TEXTCTRL_GOVERN_NO_CAR;
		static const long ID_TEXTCTRL_SAFETY_NO_CAR;
		static const long ID_TEXTCTRL_GOVERN_NO_CWT;
		static const long ID_TEXTCTRL_SAFETY_NO_CWT;
		static const long ID_TEXTCTRL_MAINBOARD_NO;
		static const long ID_TEXTCTRL_TM_NO;
		static const long ID_BUTTON_GET_INFO;
		static const long ID_BUTTON_SYC_SINGLE;
		static const long ID_BUTTON_GEN_PDF_SINGLE;
		static const long ID_LOG_TEXT_CTRL;


        //(*Declarations(LabelGenFrame)
        wxMenuItem* MenuItem3;
        wxStatusBar* StatusBar1;
        //*)

		wxTextCtrl* tc_cwt_qty_dcbefore;
		wxTextCtrl* tc_cwt_qty_dcafter;
		wxTextCtrl* tc_car_weight;
		wxTextCtrl* tc_cwt_block_mat2;
		wxTextCtrl* tc_prj_name;
		wxTextCtrl* tc_cwt_weight;
	//	wxTextCtrl* tc_govern_no_cwt;
		wxTextCtrl* tc_rate;
	/*	wxTextCtrl* tc_safety_no_car;
		wxTextCtrl* tc_buffer_no_car;
		wxTextCtrl* tc_tm_spring_length_r;
		wxTextCtrl* tc_mainboard_no;
		wxTextCtrl* tc_tm_no;
		wxTextCtrl* tc_tm_spring_length_l;*/
		wxTextCtrl* tc_balance_qty;
		wxTextCtrl* tc_balance0_qty;
		wxTextCtrl* tc_wbs;
		wxTextCtrl* tc_dc_weight;
		wxTextCtrl* tc_lift_no;
		wxTextCtrl* tc_cwt_block_mat1;
		/*wxTextCtrl* tc_buffer_no_cwt;
		wxTextCtrl* tc_safety_no_cwt;
		wxTextCtrl* tc_govern_no_car;*/


	//	void OnIdle(wxIdleEvent &evt);
		void OnButtonWBS_SearchClick(wxCommandEvent& event);
        void OnButtonPrj_Name_SearchClick(wxCommandEvent& event);
        void OnButtonContract_Name_SearchClick(wxCommandEvent& event);
        void OnButtonClear_all(wxCommandEvent& event);
        void OnButtonPrintPdf(wxCommandEvent& event);
        void OnButtonPrintPreview(wxCommandEvent& event);
        void Clear_all();
        void refresh_treelist_level();

        void set_text_value(v_value_cell v_cell);

        wxAuiManager m_mgr;
        void Create_TreeList_Panel(wxWindow * parent);
        void Build_Treelist(wxWindow * parent);

        void TreeList_select(wxTreeEvent &event);

        void refresh_Treelist();
        void Create_Project_Info(wxWindow * parent);
        wxcode::wxTreeListCtrl* tlc_proj_list;
        int find_wbs(wxString s_wbs);
        wxTextCtrl * m_LOGTextCtrl;
        wxArrayValue array_result;

        wxPanel * m_treelist_Panel;
        wxPanel * m_proj_info_panel;

        wxString m_clause;


        DECLARE_EVENT_TABLE()
};



#endif // LABELGENMAIN_H
