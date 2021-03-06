/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Status Window
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2010 by David S. Register   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.             *
 ***************************************************************************
 */


#ifndef __statwin_H__
#define __statwin_H__

#include "chart1.h"

//----------------------------------------------------------------------------
//   constants
//----------------------------------------------------------------------------
#define KEY_REGIONS_MAX       100

#define NSIGBARS              4

// Class declarations

class MyFrame;
//----------------------------------------------------------------------------
// TStatWin
//----------------------------------------------------------------------------
class TStatWin: public wxWindow
{
public:
      TStatWin(wxFrame *frame);
      ~TStatWin();

      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void TextDraw(const wxString& text);

      wxString *pText;
      bool  bTextSet;

DECLARE_EVENT_TABLE()
};


//----------------------------------------------------------------------------
// PianoWin
//----------------------------------------------------------------------------
class PianoWin: public wxWindow
{
public:
      PianoWin(wxFrame *frame);
      ~PianoWin();

      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void FormatKeys(void);
      void MouseEvent(wxMouseEvent& event);
      void SetColorScheme(ColorScheme cs);
      void SetKeyArray(ArrayOfInts piano_chart_index_array);
      void SetActiveKey(int iactive) { m_iactive = iactive; }
      void SetActiveKeyArray(ArrayOfInts array);
      void SetNoshowIndexArray(ArrayOfInts array);
      void SetSubliteIndexArray(ArrayOfInts array);
      void SetSkewIndexArray(ArrayOfInts array);
      void SetTmercIndexArray(ArrayOfInts array);
      void SetPolyIndexArray(ArrayOfInts array);

      void SetVizIcon(wxBitmap *picon_bmp){ if( m_pVizIconBmp ) delete m_pVizIconBmp; m_pVizIconBmp = picon_bmp; }
      void SetInVizIcon(wxBitmap *picon_bmp){ if( m_pInVizIconBmp ) delete m_pInVizIconBmp; m_pInVizIconBmp = picon_bmp; }
      void SetSkewIcon(wxBitmap *picon_bmp){ if( m_pSkewIconBmp ) delete m_pSkewIconBmp; m_pSkewIconBmp = picon_bmp; }
      void SetTMercIcon(wxBitmap *picon_bmp){ if( m_pTmercIconBmp ) delete m_pTmercIconBmp; m_pTmercIconBmp = picon_bmp; }
      void SetPolyIcon(wxBitmap *picon_bmp){ if( m_pPolyIconBmp ) delete m_pPolyIconBmp; m_pPolyIconBmp = picon_bmp; }

      wxPoint GetKeyOrigin(int key_index);
      void ResetRollover(void);
      void SetRoundedRectangles(bool val){ m_brounded = val; }


      int         Size_X, Size_Y, Pos_X, Pos_Y;

      wxRegion    KeyRegion[KEY_REGIONS_MAX];

private:
      int         m_nRegions;
      int         m_index_last;
      int         m_hover_icon_last;
      int         m_hover_last;

      wxBrush     m_backBrush;
      wxBrush     m_tBrush;
      wxBrush     m_vBrush;
      wxBrush     m_svBrush;
      wxBrush     m_uvBrush;
      wxBrush     m_slBrush;

      wxBrush     m_cBrush;
      wxBrush     m_scBrush;

      ArrayOfInts m_key_array;
      ArrayOfInts m_noshow_index_array;
      ArrayOfInts m_active_index_array;
      ArrayOfInts m_sublite_index_array;
      ArrayOfInts m_skew_index_array;
      ArrayOfInts m_tmerc_index_array;
      ArrayOfInts m_poly_index_array;


      wxBitmap    *m_pVizIconBmp;
      wxBitmap    *m_pInVizIconBmp;
      wxBitmap    *m_pTmercIconBmp;
      wxBitmap    *m_pSkewIconBmp;
      wxBitmap    *m_pPolyIconBmp;

      int         m_iactive;
      bool        m_brounded;

DECLARE_EVENT_TABLE()
};

#ifdef USE_WIFI_CLIENT
//----------------------------------------------------------------------------
// WiFiStatWin
//----------------------------------------------------------------------------
class WiFiStatWin: public wxWindow
{
    public:
        WiFiStatWin(wxFrame *frame);
        ~WiFiStatWin();

        void OnSize(wxSizeEvent& event);
        void OnPaint(wxPaintEvent& event);
        void TextDraw(const char * text);
        void SetNumberStations(int n);
        void SetStationQuality(int istation, int quality);
        void SetStationSecureFlag(int istation, int flag);
        void SetStationAge(int istation, int age);
        void SetServerStatus(bool stat) { m_bserverstat = stat; }
        void DrawBars(wxDC &dc, int x, int y, int box_width, int box_height, int val, int val_max);
        void SetColorScheme(ColorScheme cs);


        wxBrush     qual_hiBrush;
        wxBrush     secureBrush;

        wxBrush     qual_hiNewBrush;
        wxBrush     secureNewBrush;

        wxBrush     backBrush;

        int         m_nstations;
        int         m_quality[NSIGBARS];
        int         m_secure[NSIGBARS];
        int         m_age[NSIGBARS];
        bool        m_bserverstat;

        DECLARE_EVENT_TABLE()
};
#endif


//----------------------------------------------------------------------------
// StatWin
//----------------------------------------------------------------------------
class StatWin: public wxDialog
{
public:
      StatWin(wxWindow *frame);
      ~StatWin();
      void OnSize(wxSizeEvent& event);
      void OnPaint(wxPaintEvent& event);
      void MouseEvent(wxMouseEvent& event);
      int  GetFontHeight();
      int  GetRows(){ return(m_rows);}
      void SetColorScheme(ColorScheme cs);
      void RePosition();

      void FormatStat(void);

      PianoWin    *pPiano;
      TStatWin    *pTStat1;
      TStatWin    *pTStat2;
#ifdef USE_WIFI_CLIENT
      WiFiStatWin *pWiFi;
#endif

private:
      wxBrush     m_backBrush;
      int         m_rows;


DECLARE_EVENT_TABLE()
};

#endif
