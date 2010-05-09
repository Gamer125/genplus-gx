/****************************************************************************
 *  menu.c
 *
 *  Genesis Plus GX menus
 *
 *  Eke-Eke (2009)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ***************************************************************************/

#include "shared.h"
#include "menu.h"
#include "font.h"
#include "gui.h"
#include "dvd.h"
#include "file_dvd.h"
#include "file_fat.h"
#include "file_slot.h"
#include "filesel.h"

/*****************************************************************************/
/*  Specific Menu Callbacks                                                  */
/*****************************************************************************/
static void ctrlmenu_cb(void);
static void savemenu_cb(void);

/*****************************************************************************/
/*  Generic Buttons data                                                     */
/*****************************************************************************/
static butn_data arrow_up_data =
{
  {NULL,NULL},
  {Button_up_png,Button_up_over_png}
};

static butn_data arrow_down_data =
{
  {NULL,NULL},
  {Button_down_png,Button_down_over_png}
};

static butn_data button_text_data =
{
  {NULL,NULL},
  {Button_text_png,Button_text_over_png}
};

static butn_data button_icon_data =
{
  {NULL,NULL},
  {Button_icon_png,Button_icon_over_png}
};

static butn_data button_icon_sm_data =
{
  {NULL,NULL},
  {Button_icon_sm_png,Button_icon_sm_over_png}
};

static butn_data button_player_data =
{
  {NULL,NULL},
  {Ctrl_player_png,Ctrl_player_over_png}
};

static butn_data button_player_none_data =
{
  {NULL,NULL},
  {Ctrl_player_none_png,NULL}
};

static butn_data button_load_data =
{
  {NULL,NULL},
  {Button_load_png,Button_load_over_png}
};

static butn_data button_save_data =
{
  {NULL,NULL},
  {Button_save_png,Button_save_over_png}
};

static butn_data button_special_data =
{
  {NULL,NULL},
  {Button_special_png,Button_special_over_png}
};

static butn_data button_delete_data =
{
  {NULL,NULL},
  {Button_delete_png,Button_delete_over_png}
};

/*****************************************************************************/
/*  Generic GUI items                                                         */
/*****************************************************************************/
static gui_item action_cancel =
{
  NULL,Key_B_png,"","Back",10,422,28,28
};

static gui_item action_select =
{
  NULL,Key_A_png,"","",602,422,28,28
};


/*****************************************************************************/
/*  Generic GUI backgrounds                                                  */
/*****************************************************************************/
static gui_image bg_main[4] =
{
  {NULL,Bg_main_png,IMAGE_VISIBLE,178,28,284,288,255},
  {NULL,Bg_overlay_png,IMAGE_VISIBLE|IMAGE_REPEAT,0,0,640,480,255},
  {NULL,Banner_main_png,IMAGE_VISIBLE|IMAGE_SLIDE_BOTTOM,0,340,640,140,255},
  {NULL,Main_logo_png,IMAGE_VISIBLE|IMAGE_SLIDE_BOTTOM,202,362,232,56,255}
};

static gui_image bg_misc[5] =
{
  {NULL,Bg_main_png,IMAGE_VISIBLE,178,96,284,288,255},
  {NULL,Bg_overlay_png,IMAGE_VISIBLE|IMAGE_REPEAT,0,0,640,480,255},
  {NULL,Banner_top_png,IMAGE_VISIBLE|IMAGE_SLIDE_TOP,0,0,640,108,255},
  {NULL,Banner_bottom_png,IMAGE_VISIBLE|IMAGE_SLIDE_BOTTOM,0,380,640,100,255},
  {NULL,Main_logo_png,IMAGE_VISIBLE|IMAGE_SLIDE_TOP,466,40,152,44,255}
};

static gui_image bg_ctrls[8] =
{
  {NULL,Bg_main_png,IMAGE_VISIBLE,374,140,284,288,255},
  {NULL,Bg_overlay_png,IMAGE_VISIBLE|IMAGE_REPEAT,0,0,640,480,255},
  {NULL,Banner_top_png,IMAGE_VISIBLE,0,0,640,108,255},
  {NULL,Banner_bottom_png,IMAGE_VISIBLE,0,380,640,100,255},
  {NULL,Main_logo_png,IMAGE_VISIBLE,466,40,152,44,255},
  {NULL,Frame_s4_png,IMAGE_VISIBLE,38,72,316,168,128},
  {NULL,Frame_s4_png,IMAGE_VISIBLE,38,242,316,168,128},
  {NULL,Frame_s3_png,IMAGE_SLIDE_RIGHT,400,134,292,248,128}
};

static gui_image bg_list[6] =
{
  {NULL,Bg_main_png,IMAGE_VISIBLE,374,140,284,288,255},
  {NULL,Bg_overlay_png,IMAGE_VISIBLE|IMAGE_REPEAT,0,0,640,480,255},
  {NULL,Banner_top_png,IMAGE_VISIBLE,0,0,640,108,255},
  {NULL,Banner_bottom_png,IMAGE_VISIBLE,0,380,640,100,255},
  {NULL,Main_logo_png,IMAGE_VISIBLE,466,40,152,44,255},
  {NULL,Frame_s1_png,IMAGE_VISIBLE,8,70,372,336,64}
};

static gui_image bg_saves[8] =
{
  {NULL,NULL,0,0,0,0,0,255},
  {NULL,Bg_main_png,IMAGE_VISIBLE,374,140,284,288,255},
  {NULL,Bg_overlay_png,IMAGE_VISIBLE|IMAGE_REPEAT,0,0,640,480,255},
  {NULL,Banner_top_png,IMAGE_VISIBLE|IMAGE_SLIDE_TOP,0,0,640,108,255},
  {NULL,Banner_bottom_png,IMAGE_VISIBLE|IMAGE_SLIDE_BOTTOM,0,380,640,100,255},
  {NULL,Main_logo_png,IMAGE_VISIBLE|IMAGE_SLIDE_TOP,466,40,152,44,255},
  {NULL,Frame_s1_png,IMAGE_VISIBLE,8,70,372,336,64},
  {NULL,Frame_s1_png,IMAGE_SLIDE_RIGHT,468,110,372,296,64}
};

/*****************************************************************************/
/*  Menu Items description                                                   */
/*****************************************************************************/

static gui_item items_main[9] =
{
  {NULL,Main_load_png    ,"","",114, 72,80,92},
  {NULL,Main_options_png ,"","",290, 76,60,88},
  {NULL,Main_quit_png    ,"","",460, 80,52,84},
  {NULL,Main_file_png    ,"","",114,216,80,92},
  {NULL,Main_reset_png   ,"","",282,224,76,84},
  {NULL,Main_ggenie_png  ,"","",450,224,72,84},
#ifdef HW_RVL
  {NULL,Main_play_wii_png,"","", 10,372,84,32},
#else
  {NULL,Main_play_gcn_png,"","", 10,372,84,32},
#endif
  {NULL,Main_takeshot_png,"","",546,334,84,32},
  {NULL,Main_showinfo_png,"","",546,372,84,32}
};

static gui_item items_ctrls[13] =
{
  {NULL,NULL,"","",  0,  0,  0,  0},
  {NULL,NULL,"","",  0,  0,  0,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",304,  0, 24,  0},
  {NULL,NULL,"","",  0,  0,  0,  0},
  {NULL,NULL,"","",  0,  0,  0,  0},
  {NULL,Ctrl_config_png,"Keys\nConfig","Configure Controller Keys",530,306,32,32}
};

static gui_item items_load[4] =
{
  {NULL,Load_recent_png,"","Load recent ROM files (USB/SD)" ,276,120,88,96},
  {NULL,Load_sd_png    ,"","Load ROM files from SDCARD"     ,110,266,88,96},
#ifdef HW_RVL
  {NULL,Load_usb_png   ,"","Load ROM files from USB device" ,276,266,88,96},
#endif
  {NULL,Load_dvd_png   ,"","Load ROM files from DVD"        ,442,266,88,96}
};

static gui_item items_options[5] =
{
  {NULL,Option_system_png,"","System settings", 114,142,80,92},
  {NULL,Option_video_png ,"","Video settings",  288,150,64,84},
  {NULL,Option_sound_png ,"","Audio settings",  464,154,44,80},
  {NULL,Option_ctrl_png  ,"","Input settings",  192,286,88,92},
  {NULL,Option_menu_png  ,"","Menu settings",   370,286,60,92}
};

/* Audio options */
static gui_item items_audio[12] =
{
  {NULL,NULL,"High-Quality FM: ON",   "Enable/disable YM2612 resampling", 52,132,276,48},
  {NULL,NULL,"FM Roll-off: 0.999",    "Adjust FIR low-pass filtering",    52,132,276,48},
  {NULL,NULL,"FM Resolution: MAX",    "Adjust YM2612 DAC precision",      52,132,276,48},
  {NULL,NULL,"FM Volume: 1.00",       "Adjust YM2612 output level",       52,132,276,48},
  {NULL,NULL,"PSG Volume: 2.50",      "Adjust SN76489 output level",      52,132,276,48},
  {NULL,NULL,"PSG Noise Boost: OFF",  "Boost SN76489 Noise Channel",      52,132,276,48},
  {NULL,NULL,"Filtering: 3-BAND EQ",  "Setup Audio filtering",            52,132,276,48},
  {NULL,NULL,"Low Gain: 1.00",        "Adjust EQ Low Band Gain",          52,132,276,48},
  {NULL,NULL,"Mid Gain: 1.00",        "Adjust EQ Mid Band Gain",          52,132,276,48},
  {NULL,NULL,"High Gain: 1.00",       "Adjust EQ High BandGain",          52,132,276,48},
  {NULL,NULL,"Low Freq: 200 Hz",      "Adjust EQ Lowest Frequency",       52,132,276,48},
  {NULL,NULL,"High Freq: 20000 Hz",   "Adjust EQ Highest Frequency",      52,132,276,48}
};

/* System options */
static gui_item items_system[7] =
{
  {NULL,NULL,"Console Region: AUTO",  "Select system region",                     52,132,276,48},
  {NULL,NULL,"System Lockups: OFF",   "Enable/disable original system lock-ups",  52,132,276,48},
  {NULL,NULL,"68k Address Error: ON", "Enable/disable 68k Address Error",         52,132,276,48},
  {NULL,NULL,"System BIOS: OFF",      "Enable/disable TMSS BIOS support",         52,132,276,48},
  {NULL,NULL,"Lock-on: OFF",          "Select Lock-On cartridge type",            52,132,276,48},
  {NULL,NULL,"Cartridge Swap: OFF",   "Enable/disable cartridge hot swap",        52,132,276,48},
  {NULL,NULL,"SVP Cycles: 1500",      "Adjust SVP chip emulation speed",          52,132,276,48}
};

/* Video options */
#ifdef HW_RVL
static gui_item items_video[10] =
#else
static gui_item items_video[8] =
#endif
{
  {NULL,NULL,"Display: PROGRESSIVE",    "Select video signal type",                   52,132,276,48},
  {NULL,NULL,"TV mode: 50/60Hz",        "Select video signal frequency",              52,132,276,48},
  {NULL,NULL,"GX Bilinear Filter: OFF", "Enable/disable texture hardware filtering",  52,132,276,48},
#ifdef HW_RVL
  {NULL,NULL,"VI Trap Filter: ON",      "Enable/disable video hardware filtering",    52,132,276,48},
  {NULL,NULL,"VI Gamma Correction: 1.0","Adjust video hardware gamma correction",     52,132,276,48},
#endif
  {NULL,NULL,"NTSC Filter: COMPOSITE",  "Enable/disable NTSC software filtering",     52,132,276,48},
  {NULL,NULL,"Borders: OFF",            "Enable/disable overscan emulation",          52,132,276,48},
  {NULL,NULL,"Aspect: ORIGINAL (4:3)",  "Select display aspect ratio",                52,132,276,48},
  {NULL,NULL,"Screen Position (+0,+0)", "Adjust display position",                    52,132,276,48},
  {NULL,NULL,"Screen Scaling (+0,+0)",  "Adjust display scaling",                     52,132,276,48}
};

/* Menu options */
static gui_item items_prefs[8] =
{
  {NULL,NULL,"Load ROM Auto: OFF","Enable/Disable automatic ROM loading on startup",  52,132,276,48},
  {NULL,NULL,"Auto Saves: OFF",   "Enable/Disable automatic saves",                   52,132,276,48},
  {NULL,NULL,"Saves Device: FAT", "Configure default device for saves",               52,132,276,48},
  {NULL,NULL,"SFX Volume: 100",   "Adjust sound effects volume",                      52,132,276,48},
  {NULL,NULL,"BGM Volume: 100",   "Adjust background music volume",                   52,132,276,48},
  {NULL,NULL,"BG Color: DEFAULT", "Select background color",                          52,132,276,48},
  {NULL,NULL,"BG Overlay: ON",    "Enable/disable background overlay",                52,132,276,48},
  {NULL,NULL,"Screen Width: 658", "Adjust menu screen width in pixels",               52,132,276,48},
};

/* Save Manager */
static gui_item items_saves[9] =
{
  {NULL,NULL,"",""                   ,0,0,0,0},
  {NULL,NULL,"",""                   ,0,0,0,0},
  {NULL,NULL,"",""                   ,0,0,0,0},
  {NULL,NULL,"",""                   ,0,0,0,0},
  {NULL,NULL,"",""                   ,0,0,0,0},
  {NULL,NULL,"","Load file"          ,0,0,0,0},
  {NULL,NULL,"","Set as default file",0,0,0,0},
  {NULL,NULL,"","Delete file"        ,0,0,0,0},
  {NULL,NULL,"","Save file"          ,0,0,0,0}
};

/*****************************************************************************/
/*  Menu Buttons description                                                 */
/*****************************************************************************/

/* Generic Buttons for list menu */
static gui_butn arrow_up = {&arrow_up_data,BUTTON_ACTIVE|BUTTON_OVER_SFX,{0,0,0,0},14,76,360,32};
static gui_butn arrow_down = {&arrow_down_data,BUTTON_ACTIVE|BUTTON_OVER_SFX,{0,0,0,0},14,368,360,32};

/* Generic list menu */
static gui_butn buttons_list[4] =
{
  {&button_text_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0},56,132,276,48},
  {&button_text_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0},56,188,276,48},
  {&button_text_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0},56,244,276,48},
  {&button_text_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0},56,300,276,48}
};

/* Main menu */
static gui_butn buttons_main[9] =
{
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,3,0,1}, 80, 50,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,3,1,1},246, 50,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,3,1,1},412, 50,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX                  ,{3,0,1,1}, 80,194,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX                  ,{3,0,1,1},246,194,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX                  ,{3,0,1,0},412,194,148,132},
  {NULL             ,                             BUTTON_OVER_SFX                  ,{3,0,1,1}, 10,372, 84, 32},
  {NULL             ,                             BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{2,1,1,1},546,334, 84, 32},
  {NULL             ,                             BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,0,1,0},546,372, 84, 32}
};

/* Controllers Menu */
static gui_butn buttons_ctrls[13] =
{
  {&button_icon_data    ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX                  ,{0,1,0,2}, 60, 88,148,132},
  {&button_icon_data    ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX                  ,{1,0,0,5}, 60,258,148,132},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,1,2,0},250, 79, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,3,0},250,117, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,4,0},250,155, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,5,0},250,193, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,5,0},250,249, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,6,0},250,287, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,1,7,0},250,325, 84, 32},
  {NULL                 ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,0,8,0},250,363, 84, 32},
  {&button_icon_sm_data ,BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX                            ,{0,1,1,0},436,168,160, 52},
  {&button_icon_sm_data ,BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX                            ,{1,1,0,0},436,232,160, 52},
  {&button_icon_sm_data ,BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX|BUTTON_SELECT_SFX          ,{1,0,0,0},436,296,160, 52}
};

/* Load Game menu */
static gui_butn buttons_load[4] =
{
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,2,0,1},246,102,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{1,0,1,1}, 80,248,148,132},
#ifdef HW_RVL
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{2,0,1,1},246,248,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{3,0,1,0},412,248,148,132}
#else
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{2,0,1,0},412,248,148,132}
#endif
};

/* Options menu */
static gui_butn buttons_options[5] =
{
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,3,0,1}, 80,120,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,3,1,1},246,120,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{0,2,1,1},412,120,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{3,0,1,1},162,264,148,132},
  {&button_icon_data,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX|BUTTON_SELECT_SFX,{2,0,1,0},330,264,148,132}
};

/* Save Manager Menu */
static gui_butn buttons_saves[9] =
{
  {&button_text_data   ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{0,1,0,0}, 56,102,276,48},
  {&button_text_data   ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0}, 56,158,276,48},
  {&button_text_data   ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0}, 56,214,276,48},
  {&button_text_data   ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,1,0,0}, 56,270,276,48},
  {&button_text_data   ,BUTTON_VISIBLE|BUTTON_ACTIVE|BUTTON_OVER_SFX,{1,0,0,0}, 56,326,276,48},
  {&button_load_data   ,BUTTON_ACTIVE|BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX,{0,1,0,0},530,130, 56,56},
  {&button_special_data,BUTTON_ACTIVE|BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX,{1,1,0,0},530,196, 56,56},
  {&button_delete_data ,BUTTON_ACTIVE|BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX,{1,1,0,0},530,262, 56,56},
  {&button_save_data   ,BUTTON_ACTIVE|BUTTON_SLIDE_RIGHT|BUTTON_OVER_SFX,{1,0,0,0},530,328, 56,56}
};

/*****************************************************************************/
/*  Menu descriptions                                                        */
/*****************************************************************************/

/* Main menu */
static gui_menu menu_main =
{
  "",
  0,0,
  9,9,4,0,
  items_main,
  buttons_main,
  bg_main,
  {NULL,NULL},
  {NULL,NULL},
  NULL
};

/* Main menu */
gui_menu menu_ctrls =
{
  "Controller Settings",
  0,0,
  13,13,8,0,
  items_ctrls,
  buttons_ctrls,
  bg_ctrls,
  {&action_cancel, &action_select},
  {NULL,NULL},
  ctrlmenu_cb
};

/* Load Game menu */
static gui_menu menu_load =
{
  "Load Game",
  0,0,
#ifdef HW_RVL
  4,4,5,0,
#else
  3,3,5,0,
#endif
  items_load,
  buttons_load,
  bg_misc,
  {&action_cancel, &action_select},
  {NULL,NULL},
  NULL
};

/* Options menu */
static gui_menu menu_options =
{
  "Settings",
  0,0,
  5,5,5,0,
  items_options,
  buttons_options,
  bg_misc,
  {&action_cancel, &action_select},
  {NULL,NULL},
  NULL
};

/* System Options menu */
static gui_menu menu_system =
{
  "System Settings",
  0,0,
  6,4,6,0,
  items_system,
  buttons_list,
  bg_list,
  {&action_cancel, &action_select},
  {&arrow_up,&arrow_down},
  NULL
};

/* Video Options menu */
static gui_menu menu_video =
{
  "Video Settings",
  0,0,
  8,4,6,0,
  items_video,
  buttons_list,
  bg_list,
  {&action_cancel, &action_select},
  {&arrow_up,&arrow_down},
  NULL
};

/* Sound Options menu */
static gui_menu menu_audio =
{
  "Audio Settings",
  0,0,
  8,4,6,0,
  items_audio,
  buttons_list,
  bg_list,
  {&action_cancel, &action_select},
  {&arrow_up,&arrow_down},
  NULL
};

/* Sound Options menu */
static gui_menu menu_prefs =
{
  "Menu Settings",
  0,0,
  8,4,6,0,
  items_prefs,
  buttons_list,
  bg_list,
  {&action_cancel, &action_select},
  {&arrow_up,&arrow_down},
  NULL
};


/* Save Manager menu */
static gui_menu menu_saves =
{
  "Save Manager",
  0,0,
  9,9,8,0,
  items_saves,
  buttons_saves,
  bg_saves,
  {&action_cancel, &action_select},
  {NULL,NULL},
  savemenu_cb
};

/****************************************************************************
 * GUI Settings menu
 *
 ****************************************************************************/
static void update_screen_w(void)
{
  vmode->viWidth    = config.screen_w;
  vmode->viXOrigin  = (VI_MAX_WIDTH_NTSC -config.screen_w)/2;
  VIDEO_Configure(vmode);
  VIDEO_Flush();
}

static void update_bgm(void)
{
  SetVolumeOgg(((int)config.bgm_volume * 255) / 100);
}

static void prefmenu ()
{
  int ret, quit = 0;
  gui_menu *m = &menu_prefs;
  gui_item *items = m->items;
  
  sprintf (items[0].text, "Load ROM Auto: %s", config.autoload ? "ON":"OFF");
  if (config.s_auto == 3)
    sprintf (items[1].text, "Auto Saves: ALL");
  else if (config.s_auto == 2)
    sprintf (items[1].text, "Auto Saves: STATE ONLY");
  else if (config.s_auto == 1)
    sprintf (items[1].text, "Auto Saves: SRAM ONLY");
  else
    sprintf (items[1].text, "Auto Saves: NONE");
  if (config.s_device == 1)
    sprintf (items[2].text, "Saves Device: MCARD A");
  else if (config.s_device == 2)
    sprintf (items[2].text, "Saves Device: MCARD B");
  else
    sprintf (items[2].text, "Saves Device: FAT");
  sprintf (items[3].text, "SFX Volume: %1.1f", config.sfx_volume);
  sprintf (items[4].text, "BGM Volume: %1.1f", config.bgm_volume);
  if (config.bg_color)
    sprintf (items[5].text, "BG Color: TYPE %d", config.bg_color);
  else
    sprintf (items[5].text, "BG Color: DEFAULT");
  sprintf (items[6].text, "BG Overlay: %s", config.bg_overlay ? "ON":"OFF");
  sprintf (items[7].text, "Screen Width: %d", config.screen_w);

  GUI_InitMenu(m);
  GUI_SlideMenuTitle(m,strlen("Menu "));

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      case 0:   /* Auto load last ROM file */
        config.autoload ^= 1;
        sprintf (items[ret].text, "Load ROM Auto: %s", config.autoload ? "ON":"OFF");
        break;

      case 1:  /*** Auto load/save STATE & SRAM files ***/
        config.s_auto = (config.s_auto + 1) % 4;
        if (config.s_auto == 3)
          sprintf (items[ret].text, "Auto Saves: ALL");
        else if (config.s_auto == 2)
          sprintf (items[ret].text, "Auto Saves: STATE ONLY");
        else if (config.s_auto == 1)
          sprintf (items[ret].text, "Auto Saves: SRAM ONLY");
        else
          sprintf (items[ret].text, "Auto Saves: NONE");
        break;

      case 2:   /*** Default saves device ***/
        config.s_device = (config.s_device + 1) % 3;
        if (config.s_device == 1)
          sprintf (items[ret].text, "Saves Device: MCARD A");
        else if (config.s_device == 2)
          sprintf (items[ret].text, "Saves Device: MCARD B");
        else
          sprintf (items[ret].text, "Saves Device: FAT");
        break;

      case 3:   /*** Sound effects volume ***/
        GUI_OptionBox(m,0,"SFX Volume",(void *)&config.sfx_volume,10.0,0.0,100.0,0);
        sprintf (items[ret].text, "SFX Volume: %1.1f", config.sfx_volume);
        break;

      case 4:   /*** Background music volume ***/
        GUI_OptionBox(m,update_bgm,"BGM Volume",(void *)&config.bgm_volume,10.0,0.0,100.0,0);
        sprintf (items[ret].text, "BGM Volume: %1.1f", config.bgm_volume);
        break;

      case 5:   /*** Background color ***/
        if (ret < 0)
          config.bg_color --;
        else
          config.bg_color ++;
        if (config.bg_color < 0)
          config.bg_color = BG_COLOR_MAX - 1;
        else if (config.bg_color >= BG_COLOR_MAX)
          config.bg_color = 0;
        if (config.bg_color)
          sprintf (items[ret].text, "BG Color: TYPE %d", config.bg_color);
        else
          sprintf (items[ret].text, "BG Color: DEFAULT");
        GUI_SetBgColor((u8)config.bg_color);
        GUI_DeleteMenu(m);
        if (config.bg_color == 0)
        {
          bg_main[0].data = Bg_main_2_png;
          bg_misc[0].data = Bg_main_2_png;
          bg_ctrls[0].data = Bg_main_2_png;
          bg_list[0].data = Bg_main_2_png;
          bg_saves[1].data = Bg_main_2_png;
        }
        else
        {
          bg_main[0].data = Bg_main_png;
          bg_misc[0].data = Bg_main_png;
          bg_ctrls[0].data = Bg_main_png;
          bg_list[0].data = Bg_main_png;
          bg_saves[1].data = Bg_main_png;
        }
        GUI_InitMenu(m);
        break;

      case 6:   /*** Background items ***/
        config.bg_overlay ^= 1;
        if (config.bg_overlay)
        {
          bg_main[1].state |= IMAGE_VISIBLE;
          bg_misc[1].state |= IMAGE_VISIBLE;
          bg_ctrls[1].state |= IMAGE_VISIBLE;
          bg_list[1].state |= IMAGE_VISIBLE;
          bg_saves[2].state |= IMAGE_VISIBLE;
        }
        else
        {
          bg_main[1].state &= ~IMAGE_VISIBLE;
          bg_misc[1].state &= ~IMAGE_VISIBLE;
          bg_ctrls[1].state &= ~IMAGE_VISIBLE;
          bg_list[1].state &= ~IMAGE_VISIBLE;
          bg_saves[2].state &= ~IMAGE_VISIBLE;
        }
        sprintf (items[ret].text, "BG Overlay: %s", config.bg_overlay ? "ON":"OFF");
        break;

      case 7:   /*** Screen Width ***/
        GUI_OptionBox(m,update_screen_w,"Screen Width",(void *)&config.screen_w,2,640,VI_MAX_WIDTH_NTSC,1);
        sprintf (items[ret].text, "Screen Width: %d", config.screen_w);
        break;

      case -1:
        quit = 1;
        break;
    }
  }

  GUI_DeleteMenu(m);
}

/****************************************************************************
 * Audio Settings menu
 *
 ****************************************************************************/
static int update_snd_items(void)
{
  gui_menu *m = &menu_audio;
  gui_item *items = m->items;
  int offset;
  float fm_volume = (float)config.fm_preamp/100.0;
  float psg_volume = (float)config.psg_preamp/100.0;
  float rolloff = config.rolloff * 100.0;
  
  if (config.hq_fm)
  {
    sprintf (items[0].text, "High-Quality FM: ON");
    sprintf (items[1].text, "FM Roll-off: %1.2f %%",rolloff);
    strcpy  (items[1].comment, "Adjust FIR low-pass filtering");
    offset = 2;
  }
  else
  {
    sprintf (items[0].text, "High-Quality FM: OFF");
    offset = 1;
  }
 
  strcpy(items[offset].comment, "Adjust YM2612 DAC precision");
  strcpy(items[offset+1].comment, "Adjust YM2612 output level");
  strcpy(items[offset+2].comment, "Adjust SN76489 output level");
  strcpy(items[offset+3].comment, "Boost SN76489 Noise Channel");
  strcpy(items[offset+4].comment, "Configure Audio filtering");

  if (config.dac_bits < 14)
    sprintf (items[offset].text, "FM Resolution: %d bits", config.dac_bits);
  else 
    sprintf (items[offset].text, "FM Resolution: MAX");

  sprintf (items[offset+1].text, "FM Volume: %1.2f", fm_volume);
  sprintf (items[offset+2].text, "PSG Volume: %1.2f", psg_volume);
  sprintf (items[offset+3].text, "PSG Noise Boost: %s", config.psgBoostNoise ? "ON":"OFF");

  if (config.filter == 2)
  {
    sprintf (items[offset+4].text, "Filtering: 3-BAND EQ");
    sprintf (items[offset+5].text, "Low Gain: %1.2f", config.lg);
    sprintf (items[offset+6].text, "Middle Gain: %1.2f", config.mg);
    sprintf (items[offset+7].text, "High Gain: %1.2f", config.hg);
    sprintf (items[offset+8].text, "Low Freq: %d", config.low_freq);
    sprintf (items[offset+9].text, "High Freq: %d", config.high_freq);
    strcpy  (items[offset+5].comment, "Adjust EQ Low Band Gain");
    strcpy  (items[offset+6].comment, "Adjust EQ Mid Band Gain");
    strcpy  (items[offset+7].comment, "Adjust EQ High Band Gain");
    strcpy  (items[offset+8].comment, "Adjust EQ Lowest Frequency");
    strcpy  (items[offset+9].comment, "Adjust EQ Highest Frequency");
    m->max_items  = offset + 10;
  }
  else if (config.filter == 1)
  {
    sprintf (items[offset+4].text, "Filtering: LOW-PASS");
    sprintf (items[offset+5].text, "Low-Pass Rate: %d %%", config.lp_range);
    strcpy (items[offset+5].comment, "Adjust Low Pass filter");
    m->max_items  = offset + 6;
  }
  else
  {
    sprintf (items[offset+4].text, "Filtering: OFF");
    m->max_items  = offset + 5;
  }

  sprintf (items[offset+6].text, "Middle Gain: %1.2f", config.mg);
  sprintf (items[offset+7].text, "High Gain: %1.2f", config.hg);
  sprintf (items[offset+8].text, "Low Freq: %d", config.low_freq);
  sprintf (items[offset+9].text, "High Freq: %d", config.high_freq);
  strcpy  (items[offset+5].comment, "Adjust EQ Low Band Gain");
  strcpy  (items[offset+6].comment, "Adjust EQ Mid Band Gain");
  strcpy  (items[offset+7].comment, "Adjust EQ High Band Gain");
  strcpy  (items[offset+8].comment, "Adjust EQ Lowest Frequency");
  strcpy  (items[offset+9].comment, "Adjust EQ Highest Frequency");

  return offset;
}

static void soundmenu ()
{
  int ret, quit = 0;
  u8 *temp;
  gui_menu *m = &menu_audio;
  gui_item *items = m->items;
  float fm_volume = (float)config.fm_preamp/100.0;
  float psg_volume = (float)config.psg_preamp/100.0;
  float rolloff = config.rolloff * 100.0;
  int offset = update_snd_items();
  GUI_InitMenu(m);
  GUI_SlideMenuTitle(m,strlen("Audio "));

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    /* special case */
    if (config.hq_fm)
    {
      if (ret == 1)
      {
        GUI_OptionBox(m,0,"FM Roll-off",(void *)&rolloff,0.1,95.0,99.9,0);
        sprintf (items[1].text, "FM Roll-off: %1.2f %%",rolloff);
        config.rolloff = rolloff / 100.0;
        ret = 255;
        if (cart.romsize) 
        {
          /* save YM2612 context */
          temp = memalign(32,YM2612GetContextSize());
          if (temp)
          {
            /* save YM2612 context */
            memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());

            /* reinitialize audio timings */
            audio_init(snd.sample_rate,snd.frame_rate);
            sound_init();

            /* restore YM2612 context */
            YM2612Restore(temp);
            free(temp);
          }
        }
      }
      else if (ret > 1)
      {
        ret--;
      }
    }

    switch (ret)
    {
      case 0:
        config.hq_fm ^= 1;
        offset = update_snd_items();

        if (cart.romsize) 
        {
          /* save YM2612 context */
          temp = memalign(32,YM2612GetContextSize());
          if (temp)
          {
            memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());
          }

          /* reinitialize audio timings */
          audio_init(snd.sample_rate,snd.frame_rate);
          sound_init();

          /* restore YM2612 context */
          if (temp)
          {
            YM2612Restore(temp);
            free(temp);
          }
        }
        break;

      case 1:
        config.dac_bits++;
        if (config.dac_bits > 14)
          config.dac_bits = 7;
        if (config.dac_bits < 14)
          sprintf (items[offset].text, "FM Resolution: %d bits", config.dac_bits);
        else 
          sprintf (items[offset].text, "FM Resolution: MAX");

        if (cart.romsize) 
        {
          /* save YM2612 context */
          temp = memalign(32,YM2612GetContextSize());
          if (temp)
          {
            memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());
          }

          /* reinitialize audio timings */
          audio_init(snd.sample_rate,snd.frame_rate);
          sound_init();

          /* restore YM2612 context */
          if (temp)
          {
            YM2612Restore(temp);
            free(temp);
          }
        }
        break;

      case 2:
        GUI_OptionBox(m,0,"FM Volume",(void *)&fm_volume,0.01,0.0,5.0,0);
        sprintf (items[offset+1].text, "FM Volume: %1.2f", fm_volume);
        config.fm_preamp = (int)(fm_volume * 100.0);
        break;

      case 3:
        GUI_OptionBox(m,0,"PSG Volume",(void *)&psg_volume,0.01,0.0,5.0,0);
        sprintf (items[offset+2].text, "PSG Volume: %1.2f", psg_volume);
        config.psg_preamp = (int)(psg_volume * 100.0);
        break;

      case 4:
        config.psgBoostNoise ^= 1;
        sprintf (items[offset+3].text, "PSG Noise Boost: %s", config.psgBoostNoise ? "ON":"OFF");
        SN76489_BoostNoise(config.psgBoostNoise);
        break;

      case 5:
        config.filter = (config.filter + 1) % 3;
        if (config.filter == 2)
        {
          sprintf (items[offset+4].text, "Filtering: 3-BAND EQ");
          sprintf (items[offset+5].text, "Low Gain: %1.2f", config.lg);
          strcpy (items[offset+5].comment, "Adjust EQ Low Band Gain");
          m->max_items = offset + 10;
          audio_set_equalizer();
        }
        else if (config.filter == 1)
        {
          sprintf (items[offset+4].text, "Filtering: LOW-PASS");
          sprintf (items[offset+5].text, "Low-Pass Rate: %d %%", config.lp_range);
          strcpy (items[offset+5].comment, "Adjust Low Pass filter");
          m->max_items = offset + 6;
        }
        else
        {
          sprintf (items[offset+4].text, "Filtering: OFF");
          m->max_items = offset + 5;
        }

        while ((m->offset + 4) > m->max_items)
        {
          m->offset --;
          m->selected++;
        }
        break;

      case 6:
        if (config.filter == 1)
        {
          GUI_OptionBox(m,0,"Low-Pass Rate",(void *)&config.lp_range,1,0,100,1);
          sprintf (items[offset+5].text, "Low-Pass Rate: %d %%", config.lp_range);
        }
        else
        {
          GUI_OptionBox(m,0,"Low Gain",(void *)&config.lg,0.01,0.0,2.0,0);
          sprintf (items[offset+5].text, "Low Gain: %1.2f", config.lg);
          audio_set_equalizer();
        }
        break;

      case 7:
        GUI_OptionBox(m,0,"Middle Gain",(void *)&config.mg,0.01,0.0,2.0,0);
        sprintf (items[offset+6].text, "Middle Gain: %1.2f", config.mg);
        audio_set_equalizer();
        break;

      case 8:
        GUI_OptionBox(m,0,"High Gain",(void *)&config.hg,0.01,0.0,2.0,0);
        sprintf (items[offset+7].text, "High Gain: %1.2f", config.hg);
        audio_set_equalizer();
        break;

      case 9:
        GUI_OptionBox(m,0,"Low Frequency",(void *)&config.low_freq,10,0,config.high_freq,1);
        sprintf (items[offset+8].text, "Low Freq: %d", config.low_freq);
        audio_set_equalizer();
        break;

      case 10:
        GUI_OptionBox(m,0,"High Frequency",(void *)&config.high_freq,100,config.low_freq,30000,1);
        sprintf (items[offset+9].text, "High Freq: %d", config.high_freq);
        audio_set_equalizer();
        break;

      case -1:
        quit = 1;
        break;
    }
  }

  GUI_DeleteMenu(m);
}

/****************************************************************************
 * System Settings menu
 *
 ****************************************************************************/
static void systemmenu ()
{
  int ret, quit = 0;
  float framerate;
  u8 *temp;
  gui_menu *m = &menu_system;
  gui_item *items = m->items;

  if (config.region_detect == 0)
    sprintf (items[0].text, "Console Region: AUTO");
  else if (config.region_detect == 1)
    sprintf (items[0].text, "Console Region:  USA");
  else if (config.region_detect == 2)
    sprintf (items[0].text, "Console Region:  EUR");
  else if (config.region_detect == 3)
    sprintf (items[0].text, "Console Region:  JAP");

  sprintf (items[1].text, "System Lockups: %s", config.force_dtack ? "OFF" : "ON");
  sprintf (items[2].text, "68k Address Error: %s", config.addr_error ? "ON" : "OFF");
  sprintf (items[3].text, "System BIOS: %s", (config.bios_enabled & 1) ? "ON":"OFF");

  if (config.lock_on == TYPE_GG)
    sprintf (items[4].text, "Lock-On: GAME GENIE");
  else if (config.lock_on == TYPE_AR)
    sprintf (items[4].text, "Lock-On: ACTION REPLAY");
  else if (config.lock_on == TYPE_SK)
    sprintf (items[4].text, "Lock-On: SONIC & KNUCKLES");
  else
    sprintf (items[4].text, "Lock-On: OFF");

  sprintf (items[5].text, "Cartridge Swap: %s", config.hot_swap ? "ON":"OFF");

  if (svp)
  {
    sprintf (items[6].text, "SVP Cycles: %d", SVP_cycles);
    m->max_items = 7;
  }
  else
  {
    m->max_items = 6;
  }

  GUI_InitMenu(m);
  GUI_SlideMenuTitle(m,strlen("System "));

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      case 0:  /*** Region Force ***/
        config.region_detect = (config.region_detect + 1) % 4;
        if (config.region_detect == 0)
          sprintf (items[0].text, "Console Region: AUTO");
        else if (config.region_detect == 1)
          sprintf (items[0].text, "Console Region:  USA");
        else if (config.region_detect == 2)
          sprintf (items[0].text, "Console Region:  EUR");
        else if (config.region_detect == 3)
          sprintf (items[0].text, "Console Region:  JAP");

        if (cart.romsize)
        {
          /* force region & cpu mode */
          set_region();

          /* update framerate */
          if (vdp_pal)
            framerate = 50.0;
          else
            framerate = ((config.tv_mode == 0) || (config.tv_mode == 2)) ? (1000000.0/16715.0) : 60.0;

          /* save YM2612 context */
          temp = memalign(32,YM2612GetContextSize());
          if (temp)
            memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());

          /* reinitialize all timings */
          audio_init(snd.sample_rate, framerate);
          system_init();

          /* restore SRAM */
          if (config.s_auto & 1)
            slot_autoload(0,config.s_device);

          /* restore YM2612 context */
          if (temp)
          {
            YM2612Restore(temp);
            free(temp);
          }

          /* reinitialize HVC tables */
          vctab = vdp_pal ? ((reg[1] & 8) ? vc_pal_240 : vc_pal_224) : vc_ntsc_224;
          hctab = (reg[12] & 1) ? cycle2hc40 : cycle2hc32;

          /* reinitialize overscan area */
          bitmap.viewport.x = config.overscan ? 14 : 0;
          bitmap.viewport.y = config.overscan ? (((reg[1] & 8) ? 0 : 8) + (vdp_pal ? 24 : 0)) : 0;
        }
        break;

      case 1:  /*** force DTACK ***/
        config.force_dtack ^= 1;
        sprintf (items[1].text, "System Lockups: %s", config.force_dtack ? "OFF" : "ON");
        break;

      case 2:  /*** 68k Address Error ***/
        config.addr_error ^= 1;
        cart_hw_init ();
        sprintf (items[2].text, "68k Address Error: %s", config.addr_error ? "ON" : "OFF");
        break;


      case 3:  /*** BIOS support ***/
        config.bios_enabled ^= 1;
        sprintf (items[3].text, "System BIOS: %s", (config.bios_enabled & 1) ? "ON":"OFF");
        if (cart.romsize) 
        {
          system_init();
          system_reset();
          if (config.s_auto & 1)
            slot_autoload(0,config.s_device);
        }
        break;

      case 4:  /*** Cart Lock-On ***/
        config.lock_on++;
        if (config.lock_on > TYPE_SK)
          config.lock_on = 0;
        if (config.lock_on == TYPE_GG)
          sprintf (items[4].text, "Lock-On: GAME GENIE");
        else if (config.lock_on == TYPE_AR)
          sprintf (items[4].text, "Lock-On: ACTION REPLAY");
        else if (config.lock_on == TYPE_SK)
          sprintf (items[4].text, "Lock-On: SONIC & KNUCKLES");
        else
          sprintf (items[4].text, "Lock-On: OFF");
        if (cart.romsize) 
        {
          system_reset(); /* clear any patches first */
          system_init();
          system_reset();
          if (config.s_auto & 1)
            slot_autoload(0,config.s_device);
        }
        break;

      case 5:  /*** Cartridge Hot Swap ***/
        config.hot_swap ^= 1;
        sprintf (items[5].text, "Cartridge Swap: %s", config.hot_swap ? "ON":"OFF");
        break;

      case 6:  /*** SVP cycles per line ***/
        GUI_OptionBox(m,0,"SVP Cycles",(void *)&SVP_cycles,1,1,1500,1);
        sprintf (items[6].text, "SVP Cycles: %d", SVP_cycles);
        break;

      case -1:
        quit = 1;
        break;
    }
  }

  GUI_DeleteMenu(m);
}

/****************************************************************************
 * Video Settings menu
 *
 ****************************************************************************/
#ifdef HW_RVL
#define VI_OFFSET 5
static void update_gamma(void)
{
  VIDEO_SetGamma((int)(config.gamma * 10.0));
  VIDEO_Flush();
}
#else
#define VI_OFFSET 3
#endif

static void videomenu ()
{
  u16 state[2];
  int ret, quit = 0;
  float framerate;
  u8 *temp;
  gui_menu *m = &menu_video;
  gui_item *items = m->items;

  if (config.render == 1)
    sprintf (items[0].text,"Display: INTERLACED");
  else if (config.render == 2)
    sprintf (items[0].text, "Display: PROGRESSIVE");
  else
    sprintf (items[0].text, "Display: ORIGINAL");

  if (config.tv_mode == 0)
    sprintf (items[1].text, "TV Mode: 60HZ");
  else if (config.tv_mode == 1)
    sprintf (items[1].text, "TV Mode: 50HZ");
  else
    sprintf (items[1].text, "TV Mode: 50/60HZ");

  sprintf (items[2].text, "GX Bilinear Filter: %s", config.bilinear ? " ON" : "OFF");

#ifdef HW_RVL
  sprintf (items[3].text, "VI Trap Filter: %s", config.trap ? " ON" : "OFF");
  sprintf (items[4].text, "VI Gamma Correction: %1.1f", config.gamma);
#endif

  if (config.ntsc == 1)
    sprintf (items[VI_OFFSET].text, "NTSC Filter: COMPOSITE");
  else if (config.ntsc == 2)
    sprintf (items[VI_OFFSET].text, "NTSC Filter: S-VIDEO");
  else if (config.ntsc == 3)
    sprintf (items[VI_OFFSET].text, "NTSC Filter: RGB");
  else
    sprintf (items[VI_OFFSET].text, "NTSC Filter: OFF");

  sprintf (items[VI_OFFSET+1].text, "Borders: %s", config.overscan ? "ON" : "OFF");

  if (config.aspect == 1)
    sprintf (items[VI_OFFSET+2].text,"Aspect: ORIGINAL (4:3)");
  else if (config.aspect == 2)
    sprintf (items[VI_OFFSET+2].text, "Aspect: ORIGINAL (16:9)");
  else
    sprintf (items[VI_OFFSET+2].text, "Aspect: MANUAL SCALE");

  sprintf (items[VI_OFFSET+3].text, "Screen Position: (%s%02d,%s%02d)",
    (config.xshift < 0) ? "":"+", config.xshift,
    (config.yshift < 0) ? "":"+", config.yshift);

  sprintf (items[VI_OFFSET+4].text, "Screen Scaling: (%s%02d,%s%02d)",
    (config.xscale < 0) ? "":"+", config.xscale,
    (config.yscale < 0) ? "":"+", config.yscale);

  if (config.aspect)
    m->max_items  = VI_OFFSET+4;
  else
    m->max_items  = VI_OFFSET+5;

  GUI_InitMenu(m);
  GUI_SlideMenuTitle(m,strlen("Video "));

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      case 0:  /*** rendering ***/
        config.render = (config.render + 1) % 3;
        if (config.render == 2)
        {
          if (VIDEO_HaveComponentCable())
          {
            /* progressive mode (60hz only) */
            config.tv_mode = 0;
            sprintf (items[1].text, "TV Mode: 60HZ");
          }
          else
          {
            /* do nothing if component cable is not detected */
            config.render = 0;
          }
        }
        if (config.render == 1)
          sprintf (items[0].text,"Display: INTERLACED");
        else if (config.render == 2)
          sprintf (items[0].text, "Display: PROGRESSIVE");
        else
          sprintf (items[0].text, "Display: ORIGINAL");
        break;

      case 1: /*** tv mode ***/
        if (config.render != 2)
        {
          config.tv_mode = (config.tv_mode + 1) % 3;

          /* update framerate */
          if (vdp_pal)
            framerate = 50.0;
          else
            framerate = ((config.tv_mode == 0) || (config.tv_mode == 2)) ? (1000000.0/16715.0) : 60.0;

          /* save YM2612 context */
          temp = memalign(32,YM2612GetContextSize());
          if (temp)
            memcpy(temp, YM2612GetContextPtr(), YM2612GetContextSize());

          /* reinitialize audio timings */
          audio_init(snd.sample_rate, framerate);
          sound_init();

          /* restore YM2612 context */
          if (temp)
          {
            YM2612Restore(temp);
            free(temp);
          }

          if (config.tv_mode == 0)
            sprintf (items[1].text, "TV Mode: 60HZ");
          else if (config.tv_mode == 1)
            sprintf (items[1].text, "TV Mode: 50HZ");
          else
            sprintf (items[1].text, "TV Mode: 50/60HZ");
        }
        else
        {
          GUI_WaitPrompt("Error","Progressive Mode is 60hz only !\n");
        }
        break;
    
      case 2: /*** GX Texture filtering ***/
        config.bilinear ^= 1;
        sprintf (items[2].text, "GX Bilinear Filter: %s", config.bilinear ? " ON" : "OFF");
        break;

#ifdef HW_RVL
      case 3: /*** VIDEO Trap filtering ***/
        config.trap ^= 1;
        sprintf (items[3].text, "VI Trap Filter: %s", config.trap ? " ON" : "OFF");
        break;

      case 4: /*** VIDEO Gamma correction ***/
        if (cart.romsize) 
        {
          update_gamma();
          state[0] = m->arrows[0]->state;
          state[1] = m->arrows[1]->state;
          m->max_buttons = 0;
          m->max_images = 0;
          m->arrows[0]->state = 0;
          m->arrows[1]->state = 0;
          m->screenshot = 255;
          strcpy(m->title,"");
          GUI_OptionBox(m,update_gamma,"VI Gamma Correction",(void *)&config.gamma,0.1,0.1,3.0,0);
          m->max_buttons = 4;
          m->max_images = 6;
          m->arrows[0]->state = state[0];
          m->arrows[1]->state = state[1];
          m->screenshot = 0;
          strcpy(m->title,"Video Settings");
          sprintf (items[4].text, "VI Gamma Correction: %1.1f", config.gamma);
          VIDEO_SetGamma(VI_GM_1_0);
          VIDEO_Flush();
        }
        else
        {
          GUI_WaitPrompt("Error","Please load a game first !\n");
        }
        break;
#endif

      case VI_OFFSET: /*** NTSC filter ***/
        config.ntsc = (config.ntsc + 1) % 4;
        if (config.ntsc == 1)
          sprintf (items[VI_OFFSET].text, "NTSC Filter: COMPOSITE");
        else if (config.ntsc == 2)
          sprintf (items[VI_OFFSET].text, "NTSC Filter: S-VIDEO");
        else if (config.ntsc == 3)
          sprintf (items[VI_OFFSET].text, "NTSC Filter: RGB");
        else
          sprintf (items[VI_OFFSET].text, "NTSC Filter: OFF");
        break;

      case VI_OFFSET+1: /*** overscan emulation ***/
        config.overscan ^= 1;
        sprintf (items[VI_OFFSET+1].text, "Borders: %s", config.overscan ? "ON" : "OFF");
        break;

      case VI_OFFSET+2: /*** aspect ratio ***/
        config.aspect = (config.aspect + 1) % 3;
        if (config.aspect == 1)
          sprintf (items[VI_OFFSET+2].text,"Aspect: ORIGINAL (4:3)");
        else if (config.aspect == 2)
          sprintf (items[VI_OFFSET+2].text, "Aspect: ORIGINAL (16:9)");
        else
          sprintf (items[VI_OFFSET+2].text, "Aspect: MANUAL SCALE");

        if (config.aspect)
        {
          /* disable items */
          m->max_items  = VI_OFFSET+4;

          /* reset menu selection */
          if (m->offset > VI_OFFSET)
          {
            m->offset  = VI_OFFSET;
            m->selected = 2;
          }
        }
        else
        {
          /* enable items */
          m->max_items  = VI_OFFSET+5;
        }

        break;

      case VI_OFFSET+3: /*** screen position ***/
        if (cart.romsize) 
        {
          state[0] = m->arrows[0]->state;
          state[1] = m->arrows[1]->state;
          m->max_buttons = 0;
          m->max_images = 0;
          m->arrows[0]->state = 0;
          m->arrows[1]->state = 0;
          m->screenshot = 255;
          strcpy(m->title,"");
          GUI_OptionBox2(m,"X Offset","Y Offset",&config.xshift,&config.yshift,1,-99,99);
          m->max_buttons = 4;
          m->max_images = 6;
          m->arrows[0]->state = state[0];
          m->arrows[1]->state = state[1];
          m->screenshot = 0;
          strcpy(m->title,"Video Settings");
          sprintf (items[VI_OFFSET+3].text, "Screen Position: (%s%02d,%s%02d)",
            (config.xshift < 0) ? "":"+", config.xshift,
            (config.yshift < 0) ? "":"+", config.yshift);
        }
        else
        {
          GUI_WaitPrompt("Error","Please load a game first !\n");
        }
        break;

      case VI_OFFSET+4: /*** screen scaling ***/
        if (cart.romsize) 
        {
          state[0] = m->arrows[0]->state;
          state[1] = m->arrows[1]->state;
          m->max_buttons = 0;
          m->max_images = 0;
          m->arrows[0]->state = 0;
          m->arrows[1]->state = 0;
          m->screenshot = 255;
          strcpy(m->title,"");
          GUI_OptionBox2(m,"X Scale","Y Scale",&config.xscale,&config.yscale,1,-99,99);
          m->max_buttons = 4;
          m->max_images = 6;
          m->arrows[0]->state = state[0];
          m->arrows[1]->state = state[1];
          m->screenshot = 0;
          strcpy(m->title,"Video Settings");
          sprintf (items[VI_OFFSET+4].text, "Screen Scaling: (%s%02d,%s%02d)",
            (config.xscale < 0) ? "":"+", config.xscale,
            (config.yscale < 0) ? "":"+", config.yscale);
        }
        else
        {
          GUI_WaitPrompt("Error","Please load a game first !\n");
        }
        break;

      case -1:
        quit = 1;
        break;
    }
  }

  GUI_DeleteMenu(m);
}

/****************************************************************************
 * Controllers Settings menu
 ****************************************************************************/
static int player = 0;
static void ctrlmenu_cb(void)
{
  char msg[16];
  gui_menu *m = &menu_ctrls;

  /* draw device port number */
  if (m->bg_images[7].state & IMAGE_VISIBLE)
  {
    if (config.input[player].device != -1)
    {
      sprintf(msg,"%d",config.input[player].port + 1);
      if (m->selected == 11)
        FONT_write(msg,16,m->items[11].x+m->items[11].w+4,m->items[11].y+m->items[11].h+4,640,(GXColor)DARK_GREY);
      else
        FONT_write(msg,14,m->items[11].x+m->items[11].w,m->items[11].y+m->items[11].h,640,(GXColor)DARK_GREY);
    }
  }
}

/* Set menu elements depending on current system configuration */
static void ctrlmenu_raz(void)
{
  int i,max = 0;
  gui_menu *m = &menu_ctrls;

  /* update players buttons */
  for (i=0; i<MAX_DEVICES; i++)
  {
    if (input.dev[i] == NO_DEVICE)
    {
      m->buttons[i+2].data  = &button_player_none_data;
      m->buttons[i+2].state &= ~BUTTON_ACTIVE;
      strcpy(m->items[i+2].text,"");
      strcpy(m->items[i+2].comment,"");
    }
    else
    {
      m->buttons[i+2].data  = &button_player_data;
      m->buttons[i+2].state |= BUTTON_ACTIVE;
      sprintf(m->items[i+2].text,"%d",max + 1);
      if (cart.hw.jcart && (i > 4))
        sprintf(m->items[i+2].comment,"Configure Player %d (J-CART) settings", max + 1);
      else
        sprintf(m->items[i+2].comment,"Configure Player %d settings", max + 1);
      max++;
    }
  }

  /* update buttons navigation */
  if (input.dev[0] != NO_DEVICE)
    m->buttons[0].shift[3] = 2;
  else if (input.dev[4] != NO_DEVICE)
    m->buttons[0].shift[3] = 6;
  else
    m->buttons[0].shift[3] = 0;
  if (input.dev[4] != NO_DEVICE)
    m->buttons[1].shift[3] = 5;
  else if (input.dev[0] != NO_DEVICE)
    m->buttons[1].shift[3] = 1;
  else
    m->buttons[1].shift[3] = 0;
  if (input.dev[1] != NO_DEVICE)
    m->buttons[2].shift[1] = 1;
  else if (input.dev[4] != NO_DEVICE)
    m->buttons[2].shift[1] = 4;
  else
    m->buttons[2].shift[1] = 0;
  if (input.dev[3] != NO_DEVICE)
    m->buttons[6].shift[0] = 1;
  else if (input.dev[0] != NO_DEVICE)
    m->buttons[6].shift[0] = 4;
  else
    m->buttons[6].shift[0] = 0;
  if (input.dev[4] != NO_DEVICE)
    m->buttons[5].shift[1] = 1;
  else
    m->buttons[5].shift[1] = 0;

  if (input.dev[5] != NO_DEVICE)
  {
    m->buttons[6].shift[1] = 1;
    if (input.dev[6] != NO_DEVICE)
    {
      m->buttons[7].shift[1] = 1;
      if (input.dev[7] != NO_DEVICE) m->buttons[8].shift[1] = 1;
      else m->buttons[8].shift[1] = 0;
    }
    else
    {
      m->buttons[7].shift[1] = 0;
    }
  }
  else
  {
    m->buttons[6].shift[1] = 0;
  }
}

static void ctrlmenu(void)
{
  int old_player = -1;
  int i = 0;
  int update = 0;
  gui_item *items = NULL;
  u8 *special = NULL;
  u32 exp;

  /* System devices */
  gui_item items_sys[2][7] =
  {
    {
      {NULL,Ctrl_none_png       ,"","Select Port 1 device",110,130,48,72},
      {NULL,Ctrl_gamepad_png    ,"","Select Port 1 device", 87,117,96,84},
      {NULL,Ctrl_mouse_png      ,"","Select Port 1 device", 97,113,64,88},
      {NULL,Ctrl_menacer_png    ,"","Select Port 1 device", 94,113,80,88},
      {NULL,Ctrl_justifiers_png ,"","Select Port 1 device", 88,117,80,84},
      {NULL,Ctrl_teamplayer_png ,"","Select Port 1 device", 94,109,80,92},
      {NULL,Ctrl_4wayplay_png   ,"","Select Port 1 device", 98,110,72,92}
    },
    {
      {NULL,Ctrl_none_png       ,"","Select Port 2 device",110,300,48,72},
      {NULL,Ctrl_gamepad_png    ,"","Select Port 2 device", 87,287,96,84},
      {NULL,Ctrl_mouse_png      ,"","Select Port 2 device", 97,283,64,88},
      {NULL,Ctrl_menacer_png    ,"","Select Port 2 device", 94,283,80,88},
      {NULL,Ctrl_justifiers_png ,"","Select Port 2 device", 88,287,80,84},
      {NULL,Ctrl_teamplayer_png ,"","Select Port 2 device", 94,279,80,92},
      {NULL,Ctrl_4wayplay_png   ,"","Select Port 2 device", 98,280,72,92}
    }
  };

  /* Player Configuration special items */
  gui_item items_special[3][2] =
  {
    {
      /* Gamepad options */
      {NULL,Ctrl_pad3b_png,"Pad\nType","Use 3-buttons Pad",528,180,44,28},
      {NULL,Ctrl_pad6b_png,"Pad\nType","Use 6-buttons Pad",528,180,44,28}
    },
    {
      /* Mouse options */
      {NULL,ctrl_option_off_png,"Invert\nMouse","Enable/Disable Mouse Y-Axis inversion",534,180,24,24},
      {NULL,ctrl_option_on_png ,"Invert\nMouse","Enable/Disable Mouse Y-Axis inversion",534,180,24,24},
    },
    {
      /* Gun options */
      {NULL,ctrl_option_off_png,"Show\nCursor","Enable/Disable Lightgun cursor",534,180,24,24},
      {NULL,ctrl_option_on_png ,"Show\nCursor","Enable/Disable Lightgun cursor",534,180,24,24},
    }
  };

  /* Player Configuration device items */
#ifdef HW_RVL
  gui_item items_device[5] =
  {
    {NULL,ctrl_option_off_png ,"Input\nDevice","Select Input Controller",534,244,24,24},
    {NULL,ctrl_gamecube_png   ,"Input\nDevice","Select Input Controller",530,246,36,24},
    {NULL,ctrl_wiimote_png    ,"Input\nDevice","Select Input Controller",526,250,40,12},
    {NULL,ctrl_nunchuk_png    ,"Input\nDevice","Select Input Controller",532,242,32,32},
    {NULL,ctrl_classic_png    ,"Input\nDevice","Select Input Controller",526,242,40,32},
  };
#else
  gui_item items_device[2] =
  {
    {NULL,ctrl_option_off_png ,"Input\nDevice","Select Input Controller",534,244,24,24},
    {NULL,ctrl_gamecube_png   ,"Input\nDevice","Select Input Controller",530,246,36,24}
  };
#endif

  /* initialize menu */
  gui_menu *m = &menu_ctrls;
  GUI_InitMenu(m);

  /* initialize custom buttons */
  button_player_data.texture[0]      = gxTextureOpenPNG(button_player_data.image[0],0);
  button_player_data.texture[1]      = gxTextureOpenPNG(button_player_data.image[1],0);
  button_player_none_data.texture[0] = gxTextureOpenPNG(button_player_none_data.image[0],0);

  /* initialize custom images */
  items_sys[1][0].texture = items_sys[0][0].texture = gxTextureOpenPNG(items_sys[0][0].data,0);
  items_sys[1][1].texture = items_sys[0][1].texture = gxTextureOpenPNG(items_sys[0][1].data,0);
  items_sys[1][2].texture = items_sys[0][2].texture = gxTextureOpenPNG(items_sys[0][2].data,0);
  items_sys[1][3].texture = items_sys[0][3].texture = gxTextureOpenPNG(items_sys[0][3].data,0);
  items_sys[1][4].texture = items_sys[0][4].texture = gxTextureOpenPNG(items_sys[0][4].data,0);
  items_sys[1][5].texture = items_sys[0][5].texture = gxTextureOpenPNG(items_sys[0][5].data,0);
  items_sys[1][6].texture = items_sys[0][6].texture = gxTextureOpenPNG(items_sys[0][6].data,0);
  items_special[0][0].texture = gxTextureOpenPNG(items_special[0][0].data,0);
  items_special[0][1].texture = gxTextureOpenPNG(items_special[0][1].data,0);
  items_special[2][0].texture = items_special[1][0].texture = gxTextureOpenPNG(items_special[1][0].data,0);
  items_special[2][1].texture = items_special[1][1].texture = gxTextureOpenPNG(items_special[1][1].data,0);
  items_device[0].texture = items_special[1][0].texture;
  items_device[1].texture = gxTextureOpenPNG(items_device[1].data,0);
#ifdef HW_RVL
  items_device[2].texture = gxTextureOpenPNG(items_device[2].data,0);
  items_device[3].texture = gxTextureOpenPNG(items_device[3].data,0);
  items_device[4].texture = gxTextureOpenPNG(items_device[4].data,0);
#endif

  /* restore current menu elements */
  player = 0;
  ctrlmenu_raz();
  memcpy(&m->items[0],&items_sys[0][input.system[0]],sizeof(gui_item));
  memcpy(&m->items[1],&items_sys[1][input.system[1]],sizeof(gui_item));

  /* menu title slide effect */
  m->selected = 0;
  GUI_SlideMenuTitle(m,strlen("Controller "));

  while (update != -1)
  {
    /* draw menu */
    GUI_DrawMenu(m);

    /* update menu */
    update = GUI_UpdateMenu(m);

    if (update > 0)
    {
      switch (m->selected)
      {
        case 0:   /* update port 1 system */
          if (cart.hw.jcart) break;
          if (input.system[0] == SYSTEM_MOUSE)
            input.system[0] +=3; /* lightguns are never used on Port 1 */
          else
            input.system[0]++;
          if ((input.system[0] == SYSTEM_MOUSE) && (input.system[1] == SYSTEM_MOUSE))
            input.system[0] +=3;
          if (input.system[0] == SYSTEM_WAYPLAY)
            input.system[1] = SYSTEM_WAYPLAY;
          if (input.system[0] > SYSTEM_WAYPLAY)
          {
            input.system[0] = NO_SYSTEM;
            input.system[1] = SYSTEM_GAMEPAD;
          }
          old_system[0] = -1;
          old_system[1] = -1;
          io_init();
          io_reset();
          old_system[0] = input.system[0];
          old_system[1] = input.system[1];

          /* update menu elements */
          ctrlmenu_raz();
          memcpy(&m->items[0],&items_sys[0][input.system[0]],sizeof(gui_item));
          memcpy(&m->items[1],&items_sys[1][input.system[1]],sizeof(gui_item));

          if (m->bg_images[7].state & IMAGE_VISIBLE)
          {
            /* slide out configuration window */
            GUI_DrawMenuFX(m, 20, 1);

            /* remove configuration window */
            m->bg_images[7].state &= ~IMAGE_VISIBLE;

            /* disable configuration buttons */
            m->buttons[10].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
            m->buttons[11].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
            m->buttons[12].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);

            /* update directions */
            m->buttons[2].shift[3] = 0;
            m->buttons[3].shift[3] = 0;
            m->buttons[4].shift[3] = 0;
            m->buttons[5].shift[3] = 0;
            m->buttons[6].shift[3] = 0;
            m->buttons[7].shift[3] = 0;
            m->buttons[8].shift[3] = 0;
            m->buttons[9].shift[3] = 0;

            /* update title */
            sprintf(m->title,"Controller Settings");
          }
          break;

        case 1:   /* update port 2 system */
          if (cart.hw.jcart) break;
          input.system[1] ++;
          if ((input.system[0] == SYSTEM_MOUSE) && (input.system[1] == SYSTEM_MOUSE))
            input.system[1] ++;
          if (input.system[1] == SYSTEM_WAYPLAY)
            input.system[0] = SYSTEM_WAYPLAY;
          if (input.system[1] > SYSTEM_WAYPLAY)
          {
            input.system[1] = NO_SYSTEM;
            input.system[0] = SYSTEM_GAMEPAD;
          }
          old_system[0] = -1;
          old_system[1] = -1;
          io_init();
          io_reset();
          old_system[0] = input.system[0];
          old_system[1] = input.system[1];

          /* update menu elements */
          ctrlmenu_raz();
          memcpy(&m->items[0],&items_sys[0][input.system[0]],sizeof(gui_item));
          memcpy(&m->items[1],&items_sys[1][input.system[1]],sizeof(gui_item));

          if (m->bg_images[7].state & IMAGE_VISIBLE)
          {
            /* slide out configuration window */
            GUI_DrawMenuFX(m, 20, 1);

            /* remove configuration window */
            m->bg_images[7].state &= ~IMAGE_VISIBLE;

            /* disable configuration buttons */
            m->buttons[10].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
            m->buttons[11].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
            m->buttons[12].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);

            /* update directions */
            m->buttons[2].shift[3] = 0;
            m->buttons[3].shift[3] = 0;
            m->buttons[4].shift[3] = 0;
            m->buttons[5].shift[3] = 0;
            m->buttons[6].shift[3] = 0;
            m->buttons[7].shift[3] = 0;
            m->buttons[8].shift[3] = 0;
            m->buttons[9].shift[3] = 0;

            /* update title */
            sprintf(m->title,"Controller Settings");
          }

          break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
          /* remove duplicate assigned inputs */
          for (i=0; i<MAX_INPUTS; i++)
          {
            if ((i!=player) && (config.input[i].device == config.input[player].device) && (config.input[i].port == config.input[player].port))
            {
              config.input[i].device = -1;
              config.input[i].port = i%4;
            }
          }

          /* update player index */
          old_player = player;
          player = 0;
          for (i=0; i<(m->selected-2); i++)
            if (input.dev[i] != NO_DEVICE) player ++;

          if (m->bg_images[7].state & IMAGE_VISIBLE)
          {
            if (old_player == player) break;
            
            /* slide out configuration window */
            GUI_DrawMenuFX(m, 20, 1);
          }
          else
          {
            /* append configuration window */
            m->bg_images[7].state |= IMAGE_VISIBLE;

            /* enable configuration buttons */
            m->buttons[10].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
            m->buttons[11].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
            m->buttons[12].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);

            /* update directions */
            m->buttons[2].shift[3] = 8;
            m->buttons[3].shift[3] = 7;
            m->buttons[4].shift[3] = 6;
            m->buttons[5].shift[3] = 5;
            m->buttons[6].shift[3] = 4;
            m->buttons[7].shift[3] = 3;
            m->buttons[8].shift[3] = 2;
            m->buttons[9].shift[3] = 1;
          }

          /* retrieve current player informations */
          if (input.dev[m->selected-2] == DEVICE_LIGHTGUN)
          {
            items = items_special[2];
            special = &config.gun_cursor[m->selected & 1];
          }
          else if (input.dev[m->selected-2] == DEVICE_MOUSE)
          {
            items = items_special[1];
            special = &config.invert_mouse;
          }
          else
          {
            items = items_special[0];
            special = &config.input[player].padtype;
          }

          memcpy(&m->items[10],&items[*special],sizeof(gui_item));
          memcpy(&m->items[11],&items_device[config.input[player].device + 1],sizeof(gui_item));

          /* slide in configuration window */
          m->buttons[10].shift[2] = 10 - m->selected;
          m->buttons[11].shift[2] = 11 - m->selected;
          m->buttons[12].shift[2] = 12 - m->selected;
          m->selected = 10;
          GUI_DrawMenuFX(m, 20, 0);

          /* update title */
          if (cart.hw.jcart && (player > 1))
            sprintf(m->title,"Controller Settings (Player %d) (J-CART)",player+1);
          else
            sprintf(m->title,"Controller Settings (Player %d)",player+1);
          break;

        case 10: /* specific option */
          if (special == &config.input[player].padtype)
          {
            if (config.input[player].device == 1) break;
            config.input[player].padtype ^= 1;
            input_init();
            input_reset();
          }
          else
          {
            *special ^= 1;
          }

          /* update menu items */
          memcpy(&m->items[10],&items[*special],sizeof(gui_item));
          break;

        case 11:  /* input controller selection */

          /* no input device */
          if (config.input[player].device < 0)
          {
            /* try gamecube controllers */
            config.input[player].device = 0;
            config.input[player].port = 0;
          }
          else
          {
            /* try next port */
            config.input[player].port ++;
          }

          /* autodetect connected gamecube controllers */
          if (config.input[player].device == 0)
          {
            exp = 0;
            while ((config.input[player].port<4) && !exp)
            {
              exp = PAD_ScanPads() & (1<<config.input[player].port);
              if (!exp) config.input[player].port ++;
            }

            if (config.input[player].port >= 4)
            {
#ifdef HW_RVL
              /* no gamecube controller found, try wiimote */
              config.input[player].port = 0;
              config.input[player].device = 1;
#else
              /* no input controller left */
              config.input[player].device = -1;
              config.input[player].port = player%4;
#endif
            }
          }

#ifdef HW_RVL
          /* autodetect connected wiimotes (without nunchuk) */
          if (config.input[player].device == 1)
          {
            exp = 4;
            if (config.input[player].port<4)
            {
              WPAD_Probe(config.input[player].port,&exp);
              if (exp == WPAD_EXP_NUNCHUK) exp = 4;
            }

            while ((config.input[player].port<4) && (exp == 4))
            {
              /* try next port */
              config.input[player].port ++;
              if (config.input[player].port<4)
              {
                exp = 4;
                WPAD_Probe(config.input[player].port,&exp);
                if (exp == WPAD_EXP_NUNCHUK) exp = 4;
              }
            }

            if (config.input[player].port >= 4)
            {
              /* no wiimote (without nunchuk)  found, try wiimote+nunchuks */
              config.input[player].port = 0;
              config.input[player].device = 2;
            }
          }

          /* autodetect connected wiimote+nunchuks */
          if (config.input[player].device == 2)
          {
            exp = 4;
            if (config.input[player].port<4)
            {
              WPAD_Probe(config.input[player].port,&exp);
            }

            while ((config.input[player].port<4) && (exp != WPAD_EXP_NUNCHUK))
            {
              /* try next port */
              config.input[player].port ++;
              if (config.input[player].port<4)
              {
                exp = 4;
                WPAD_Probe(config.input[player].port,&exp);
              }
            }

            if (config.input[player].port >= 4)
            {
              /* no wiimote+nunchuk found, try classic controllers */
              config.input[player].port = 0;
              config.input[player].device = 3;
            }
          }

          /* autodetect connected classic controllers */
          if (config.input[player].device == 3)
          {
            exp = 4;
            if (config.input[player].port<4)
            {
              WPAD_Probe(config.input[player].port,&exp);
            }

            while ((config.input[player].port<4) && (exp != WPAD_EXP_CLASSIC))
            {
              /* try next port */
              config.input[player].port ++;
              if (config.input[player].port<4)
              {
                exp = 4;
                WPAD_Probe(config.input[player].port,&exp);
              }
            }

            if (config.input[player].port >= 4)
            {
              /* no input controller left */
              config.input[player].device = -1;
              config.input[player].port = player%4;
            }
          }

          /* force 3-buttons gamepad when using Wiimote */
          if (config.input[player].device == 1)
          {
            config.input[player].padtype = DEVICE_3BUTTON;
            memcpy(&m->items[10],&items[*special],sizeof(gui_item));
          }
#endif

          /* update menu items */
          memcpy(&m->items[11],&items_device[config.input[player].device + 1],sizeof(gui_item));
          break;

        case 12:  /* Controller Keys Configuration */
          if (config.input[player].device < 0) break;
          GUI_MsgBoxOpen("Keys Configuration", "",0);
          if (config.input[player].padtype == DEVICE_6BUTTON)
          {
            /* 6-buttons gamepad */
            if (config.input[player].device == 0)
            {
              /* Gamecube PAD: 6-buttons w/o MODE */
              gx_input_Config(config.input[player].port, config.input[player].device, 7);
            }
            else
            {
              gx_input_Config(config.input[player].port, config.input[player].device, 8);
            }
          }
          else
          {
            /* 3-Buttons gamepad, mouse, lightgun */
            gx_input_Config(config.input[player].port, config.input[player].device, 4);
          }
          GUI_MsgBoxClose();
          break;
      }
    }

    /* Close Window */
    else if (update < 0)
    {
      if (m->bg_images[7].state & IMAGE_VISIBLE)
      {
        /* slide out configuration window */
        GUI_DrawMenuFX(m, 20, 1);

        /* disable configuration window */
        m->bg_images[7].state &= ~IMAGE_VISIBLE;

        /* disable configuration buttons */
        m->buttons[10].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
        m->buttons[11].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
        m->buttons[12].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);

        /* clear directions */
        m->buttons[2].shift[3] = 0;
        m->buttons[3].shift[3] = 0;
        m->buttons[4].shift[3] = 0;
        m->buttons[5].shift[3] = 0;
        m->buttons[6].shift[3] = 0;
        m->buttons[7].shift[3] = 0;
        m->buttons[8].shift[3] = 0;
        m->buttons[9].shift[3] = 0;

        /* update selector */
        m->selected -= m->buttons[m->selected].shift[2];

        /* restore title */
        sprintf(m->title,"Controller Settings");

        /* stay in menu */
        update = 0;
      }
      else
      {
        /* check we have at least one connected input before leaving */
        old_player = player;
        player = 0;
        for (i=0; i<MAX_DEVICES; i++)
        {
          /* check inputs */
          if (input.dev[i] != NO_DEVICE)
          {
            if (config.input[player].device != -1)
              break;
            player++;
          }
        }
        player = old_player;

        /* no input connected */
        if (i == MAX_DEVICES) 
        {
          /* stay in menu */
          GUI_WaitPrompt("Error","No input connected !");
          update = 0;
        }
      }
    }
  }

  /* remove duplicate assigned inputs before leaving */
  for (i=0; i<8; i++)
  {
    if ((i!=player) && (config.input[i].device == config.input[player].device) && (config.input[i].port == config.input[player].port))
    {
      config.input[i].device = -1;
      config.input[i].port = i%4;
    }
  }

  /* disable configuration window */
  m->bg_images[7].state &= ~IMAGE_VISIBLE;

  /* disable configuration buttons */
  m->buttons[10].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
  m->buttons[11].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);
  m->buttons[12].state &= (~BUTTON_VISIBLE & ~BUTTON_ACTIVE);

  /* clear directions */
  m->buttons[2].shift[3] = 0;
  m->buttons[3].shift[3] = 0;
  m->buttons[4].shift[3] = 0;
  m->buttons[5].shift[3] = 0;
  m->buttons[6].shift[3] = 0;
  m->buttons[7].shift[3] = 0;
  m->buttons[8].shift[3] = 0;
  m->buttons[9].shift[3] = 0;

  /* clear menu items */
  memset(&m->items[0],0,sizeof(gui_item));
  memset(&m->items[1],0,sizeof(gui_item));
  memset(&m->items[10],0,sizeof(gui_item));
  memset(&m->items[11],0,sizeof(gui_item));

  /* clear player buttons */
  m->buttons[2].data    = NULL;
  m->buttons[3].data    = NULL;
  m->buttons[4].data    = NULL;
  m->buttons[5].data    = NULL;
  m->buttons[6].data    = NULL;
  m->buttons[7].data    = NULL;
  m->buttons[8].data    = NULL;
  m->buttons[9].data    = NULL;

  /* delete menu */
  GUI_DeleteMenu(m);

  /* delete custom buttons */
  gxTextureClose(&button_player_data.texture[0]);
  gxTextureClose(&button_player_data.texture[1]);
  gxTextureClose(&button_player_none_data.texture[0]);

  /* delete custom images */
  gxTextureClose(&items_sys[0][0].texture);
  gxTextureClose(&items_sys[0][1].texture);
  gxTextureClose(&items_sys[0][2].texture);
  gxTextureClose(&items_sys[0][3].texture);
  gxTextureClose(&items_sys[0][4].texture);
  gxTextureClose(&items_sys[0][5].texture);
  gxTextureClose(&items_sys[0][6].texture);
  gxTextureClose(&items_special[0][0].texture);
  gxTextureClose(&items_special[0][1].texture);
  gxTextureClose(&items_special[1][0].texture);
  gxTextureClose(&items_special[1][1].texture);
  gxTextureClose(&items_device[1].texture);
#ifdef HW_RVL
  gxTextureClose(&items_device[2].texture);
  gxTextureClose(&items_device[3].texture);
  gxTextureClose(&items_device[4].texture);
#endif
}

/****************************************************************************
 * Main Option menu
 *
 ****************************************************************************/
static void optionmenu(void)
{
  int ret, quit = 0;
  gui_menu *m = &menu_options;

  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,30,0);

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      case 0:
        GUI_DeleteMenu(m);
        systemmenu();
        GUI_InitMenu(m);
        break;
      case 1:
        GUI_DeleteMenu(m);
        videomenu();
        GUI_InitMenu(m);
        break;
      case 2:
        GUI_DeleteMenu(m);
        soundmenu();
        GUI_InitMenu(m);
        break;
      case 3:
        GUI_DeleteMenu(m);
        ctrlmenu();
        GUI_InitMenu(m);
        break;
      case 4:
        GUI_DeleteMenu(m);
        prefmenu();
        GUI_InitMenu(m);
        break;
      case -1:
        quit = 1;
        break;
    }
  }

  GUI_DrawMenuFX(m,30,1);
  GUI_DeleteMenu(m);
}

/****************************************************************************
* Save Manager menu
*
****************************************************************************/
static t_slot slots[5];
static void savemenu_cb(void)
{
  int i;
  char msg[16];
  gx_texture *star = gxTextureOpenPNG(Star_full_png,0);
  
  if (sram.on)
  {
    FONT_write("Backup Memory",16,buttons_saves[0].x+16,buttons_saves[0].y+(buttons_saves[0].h-16)/2+16,buttons_saves[0].x+buttons_saves[0].w,(GXColor)DARK_GREY);
    if (slots[0].valid)
    {
      sprintf(msg,"%d/%02d/%02d",slots[0].day,slots[0].month,slots[0].year);
      FONT_alignRight(msg,12,buttons_saves[0].x+buttons_saves[0].w-16,buttons_saves[0].y+(buttons_saves[0].h-28)/2+12,(GXColor)DARK_GREY);
      sprintf(msg,"%02d:%02d",slots[0].hour,slots[0].min);
      FONT_alignRight(msg,12,buttons_saves[0].x+buttons_saves[0].w-16,buttons_saves[0].y+(buttons_saves[0].h-28)/2+28,(GXColor)DARK_GREY);
    }

    if (sram.crc != crc32(0, &sram.sram[0], 0x10000))
      gxDrawTexture(star,22,buttons_saves[0].y+(buttons_saves[0].h-star->height)/2,star->width,star->height,255);
  }
  else
  {
    FONT_writeCenter("Backup Memory disabled",16,buttons_saves[0].x,buttons_saves[0].x+buttons_saves[0].w,buttons_saves[0].y+(buttons_saves[0].h-16)/2+16,(GXColor)DARK_GREY);
  }

  for (i=1; i<5; i++)
  {
    if (slots[i].valid)
    {
      sprintf(msg,"Slot %d",i);
      FONT_write(msg,16,buttons_saves[i].x+16,buttons_saves[i].y+(buttons_saves[i].h-16)/2+16,buttons_saves[i].x+buttons_saves[i].w,(GXColor)DARK_GREY);
      sprintf(msg,"%d/%02d/%02d",slots[i].day,slots[i].month,slots[i].year);
      FONT_alignRight(msg,12,buttons_saves[i].x+buttons_saves[i].w-16,buttons_saves[i].y+(buttons_saves[i].h-28)/2+12,(GXColor)DARK_GREY);
      sprintf(msg,"%02d:%02d",slots[i].hour,slots[i].min);
      FONT_alignRight(msg,12,buttons_saves[i].x+buttons_saves[i].w-16,buttons_saves[i].y+(buttons_saves[i].h-28)/2+28,(GXColor)DARK_GREY);
    }
    else
    {
      FONT_write("Empty Slot",16,buttons_saves[i].x+16,buttons_saves[i].y+(buttons_saves[i].h-16)/2+16,buttons_saves[i].x+buttons_saves[i].h,(GXColor)DARK_GREY);
    }

    if (i == config.s_default)
      gxDrawTexture(star,22,buttons_saves[i].y+(buttons_saves[i].h-star->height)/2,star->width,star->height,255);
  }
  gxTextureClose(&star);
}

static int savemenu(void)
{
  int i, update = 0;
  int ret = 0;
  int slot = -1;
  char filename[MAXPATHLEN];
  gui_menu *m = &menu_saves;
  FILE *snap;

  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,30,0);
  m->bg_images[3].state &= ~IMAGE_SLIDE_TOP;
  m->bg_images[4].state &= ~IMAGE_SLIDE_BOTTOM;
  m->bg_images[5].state &= ~IMAGE_SLIDE_TOP;

  /* detect existing files */
  for (i=0; i<5; i++)
    slot_autodetect(i, config.s_device, &slots[i]);

  /* SRAM disabled */
  if (sram.on)
  {
    m->buttons[0].state |= BUTTON_ACTIVE;
    m->buttons[1].shift[0] = 1;
  }
  else
  {
    m->buttons[0].state &= ~BUTTON_ACTIVE;
    m->buttons[1].shift[0] = 0;
    if (m->selected == 0)
      m->selected = 1;
  }

  while (update != -1)
  {
    /* slot selection */
    if ((m->selected < 5) && (slot != m->selected))
    {
      /* update slot */
      slot = m->selected;

      /* delete previous texture if any */
      gxTextureClose(&bg_saves[0].texture);
      bg_saves[0].state &= ~IMAGE_VISIBLE;
      bg_saves[1].state |= IMAGE_VISIBLE;

      /* state slot */
      if (!config.s_device && slot && slots[slot].valid)
      {
        /* open screenshot file */
        sprintf (filename, "%s/saves/%s__%d.png", DEFAULT_PATH, rom_filename, slot - 1);
        snap = fopen(filename, "rb");
        if (snap)
        {
          /* load texture from file */
          bg_saves[0].texture = gxTextureOpenPNG(0,snap);
          if (bg_saves[0].texture)
          {
            /* set menu background */
            bg_saves[0].w = bg_saves[0].texture->width * 2;
            bg_saves[0].h = bg_saves[0].texture->height * 2;
            bg_saves[0].x = (vmode->fbWidth - bg_saves[0].w) / 2;
            bg_saves[0].y = (vmode->efbHeight - bg_saves[0].h) / 2;
            bg_saves[0].state |= IMAGE_VISIBLE;
            bg_saves[1].state &= ~IMAGE_VISIBLE;
          }
          fclose(snap);
        }
      }
    }

    /* draw menu */
    GUI_DrawMenu(m);

    /* update menu */
    update = GUI_UpdateMenu(m);

    if (update > 0)
    {
      switch (m->selected)
      {
        case 5: /* load file */
        {
          if (slots[slot].valid)
          {
            ret = slot_load(slot,config.s_device);
         
            /* force exit */
            if (ret > 0)
            {
              GUI_DrawMenuFX(m, 20, 1);
              m->buttons[slot].state &= ~BUTTON_SELECTED;
              m->bg_images[7].state &= ~IMAGE_VISIBLE;
              if (sram.on)
                m->buttons[0].state |= BUTTON_ACTIVE;
              m->buttons[1].state |= BUTTON_ACTIVE;
              m->buttons[2].state |= BUTTON_ACTIVE;
              m->buttons[3].state |= BUTTON_ACTIVE;
              m->buttons[4].state |= BUTTON_ACTIVE;
              m->buttons[5].state &= ~BUTTON_VISIBLE;
              m->buttons[6].state &= ~BUTTON_VISIBLE;
              m->buttons[7].state &= ~BUTTON_VISIBLE;
              m->buttons[8].state &= ~BUTTON_VISIBLE;
              m->selected = slot;
              update = -1;
            }
          }
          break;
        }

        case 6: /* set default slot */
        {
          config.s_default = slot;
          break;
        }

        case 7: /* delete file */
        {
          if (slots[slot].valid)
          {
            if (slot_delete(slot,config.s_device) >= 0)
            {
              /* hide screenshot */
              gxTextureClose(&bg_saves[0].texture);
              bg_saves[0].state &= ~IMAGE_VISIBLE;
              slots[slot].valid = 0;
              update = -1;
            }
          }
          break;
        }

        case 8: /* save file */
        {
          ret = slot_save(slot,config.s_device);

          /* force exit */
          if (ret > 0)
          {
            GUI_DrawMenuFX(m, 20, 1);
            m->buttons[slot].state &= ~BUTTON_SELECTED;
            m->bg_images[7].state &= ~IMAGE_VISIBLE;
            if (sram.on)
              m->buttons[0].state |= BUTTON_ACTIVE;
            m->buttons[1].state |= BUTTON_ACTIVE;
            m->buttons[2].state |= BUTTON_ACTIVE;
            m->buttons[3].state |= BUTTON_ACTIVE;
            m->buttons[4].state |= BUTTON_ACTIVE;
            m->buttons[5].state &= ~BUTTON_VISIBLE;
            m->buttons[6].state &= ~BUTTON_VISIBLE;
            m->buttons[7].state &= ~BUTTON_VISIBLE;
            m->buttons[8].state &= ~BUTTON_VISIBLE;
            m->selected = slot;
            update = -1;
          }
          break;
        }

        default: /* slot selection */
        {
          /* enable right window */
          m->bg_images[7].state |= IMAGE_VISIBLE;
          m->buttons[5].state |= BUTTON_VISIBLE;
          m->buttons[6].state |= BUTTON_VISIBLE;
          m->buttons[7].state |= BUTTON_VISIBLE;
          m->buttons[8].state |= BUTTON_VISIBLE;

          /* only enable valid options */
          if (slots[slot].valid)
          {
            m->buttons[5].state |= BUTTON_ACTIVE;
            m->buttons[7].state |= BUTTON_ACTIVE;
            m->buttons[6].shift[0] = 1;
            m->buttons[6].shift[1] = 1;
            m->buttons[8].shift[0] = 1;
            m->selected = 5;
          }
          else
          {
            m->buttons[5].state &= ~BUTTON_ACTIVE;
            m->buttons[7].state &= ~BUTTON_ACTIVE;
            m->buttons[6].shift[0] = 0;
            m->buttons[6].shift[1] = 2;
            m->buttons[8].shift[0] = (slot > 0) ? 2 : 0;
            m->selected = 8;
          }

          /* state slot 'only' button */
          if (slot > 0)
          {
            m->buttons[6].state |= BUTTON_ACTIVE;
            m->buttons[5].shift[1] = 1;
            m->buttons[7].shift[0] = 1;
          }
          else
          {
            m->buttons[6].state &= ~BUTTON_ACTIVE;
            m->buttons[5].shift[1] = 2;
            m->buttons[7].shift[0] = 2;
          }

          /* disable left buttons */
          m->buttons[0].state &= ~BUTTON_ACTIVE;
          m->buttons[1].state &= ~BUTTON_ACTIVE;
          m->buttons[2].state &= ~BUTTON_ACTIVE;
          m->buttons[3].state &= ~BUTTON_ACTIVE;
          m->buttons[4].state &= ~BUTTON_ACTIVE;

          /* keep current selection highlighted */
          m->buttons[slot].state |= BUTTON_SELECTED;

          /* slide in window */
          GUI_DrawMenuFX(m, 20, 0);

          break;
        }
      }
    }

    if (update < 0)
    {
      /* close right window */
      if (m->bg_images[7].state & IMAGE_VISIBLE)
      {
        /* slide out window */
        GUI_DrawMenuFX(m, 20, 1);

        /* clear current selection */
        m->buttons[slot].state &= ~BUTTON_SELECTED;

        /* enable left buttons */
        if (sram.on)
          m->buttons[0].state |= BUTTON_ACTIVE;
        m->buttons[1].state |= BUTTON_ACTIVE;
        m->buttons[2].state |= BUTTON_ACTIVE;
        m->buttons[3].state |= BUTTON_ACTIVE;
        m->buttons[4].state |= BUTTON_ACTIVE;

        /* disable right window */
        m->bg_images[7].state &= ~IMAGE_VISIBLE;
        m->buttons[5].state &= ~BUTTON_VISIBLE;
        m->buttons[6].state &= ~BUTTON_VISIBLE;
        m->buttons[7].state &= ~BUTTON_VISIBLE;
        m->buttons[8].state &= ~BUTTON_VISIBLE;

        /* stay in menu */
        m->selected = slot;
        update = 0;
      }
    }
  }

  /* leave menu */
  m->bg_images[3].state |= IMAGE_SLIDE_TOP;
  m->bg_images[4].state |= IMAGE_SLIDE_BOTTOM;
  m->bg_images[5].state |= IMAGE_SLIDE_TOP;
  GUI_DrawMenuFX(m,30,1);
  GUI_DeleteMenu(m);
  return ret;
}

/****************************************************************************
 * Load Game menu
 *
 ****************************************************************************/
static int loadgamemenu ()
{
  int ret;
  gui_menu *m = &menu_load;
  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,30,0);

  while (1)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      /*** Button B ***/
      case -1: 
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        return 0;

      /*** Load from DVD ***/
  #ifdef HW_RVL
      case 3:
  #else
      case 2:
  #endif
        if (DVD_Open())
        {
          GUI_DeleteMenu(m);
          if (FileSelector(cart.rom,0))
            return 1;
          GUI_InitMenu(m);
        }
        break;

      /*** Load from FAT device ***/
      default:
        if (FAT_Open(ret))
        {
          GUI_DeleteMenu(m);
          if (FileSelector(cart.rom,1))
            return 1;
          GUI_InitMenu(m);
        }
        break;
    }
  }

  return 0;
}

/***************************************************************************
  * Show rom info screen
 ***************************************************************************/
static void showrominfo (void)
{
  char items[15][64];

  /* fill ROM infos */
  sprintf (items[0], "Console Type: %s", rominfo.consoletype);
  sprintf (items[1], "Copyright: %s", rominfo.copyright);
  sprintf (items[2], "Company Name: %s", companyinfo[getcompany ()].company);
  sprintf (items[3], "Domestic Name:");
  sprintf (items[4], "%s",rominfo.domestic);
  sprintf (items[5], "International Name:");
  sprintf (items[6], "%s",rominfo.international);
  sprintf (items[7], "Type: %s (%s)",rominfo.ROMType, strcmp(rominfo.ROMType, "AI") ? "Game" : "Educational");
  sprintf (items[8], "Product ID: %s", rominfo.product);
  sprintf (items[9], "Checksum: %04x (%04x) (%s)", rominfo.checksum, realchecksum, (rominfo.checksum == realchecksum) ? "GOOD" : "BAD");
  
  sprintf (items[10], "Supports: ");
  if (peripherals & (1 << 1))
  {
    strcat(items[10],peripheralinfo[1].pName);
    strcat(items[10],", ");
  }
  else if (peripherals & (1 << 0))
  {
    strcat(items[10],peripheralinfo[0].pName);
    strcat(items[10],", ");
  }
  if (peripherals & (1 << 7))
  {
    strcat(items[10],peripheralinfo[7].pName);
    strcat(items[10],", ");
  }
  if (peripherals & (1 << 8))
  {
    strcat(items[10],peripheralinfo[8].pName);
    strcat(items[10],", ");
  }
  if (peripherals & (1 << 11))
  {
    strcat(items[10],peripheralinfo[11].pName);
    strcat(items[10],", ");
  }
  if (peripherals & (1 << 13))
  {
    strcat(items[10],peripheralinfo[13].pName);
    strcat(items[10],", ");
  }
  if (strlen(items[10]) > 10)
    items[10][strlen(items[10]) - 2] = 0;

  sprintf (items[11], "ROM end: $%06X", rominfo.romend);

  if (sram.custom)
    sprintf (items[12], "EEPROM(%dK): $%06X", ((eeprom.type.size_mask+1)* 8) /1024, (unsigned int)eeprom.type.sda_out_bit);
  else if (sram.detected)
    sprintf (items[12], "SRAM Start: $%06X", sram.start);
  else
    sprintf (items[12], "No Backup Memory specified");

  if (sram.custom) 
    sprintf (items[13], "EEPROM(%dK): $%06X", ((eeprom.type.size_mask+1)* 8) /1024, (unsigned int)eeprom.type.scl_bit);
  else if (sram.detected)
    sprintf (items[13], "SRAM End: $%06X", sram.end);
  else if (sram.on)
    sprintf (items[13], "SRAM enabled by default");
  else
    sprintf (items[13], "SRAM disabled by default");
  
  if (region_code == REGION_USA)
    sprintf (items[14], "Region: %s (USA)", rominfo.country);
  else if (region_code == REGION_EUROPE)
    sprintf (items[14], "Region: %s (EUR)", rominfo.country);
  else if (region_code == REGION_JAPAN_NTSC)
    sprintf (items[14], "Region: %s (JAP)", rominfo.country);
  else if (region_code == REGION_JAPAN_PAL)
    sprintf (items[14], "Region: %s (JAP 50Hz)", rominfo.country);

  GUI_TextWindow(&menu_main, "ROM Header Infos", items, 15, 15);
}

/***************************************************************************
  * Show credits
 ***************************************************************************/
static void showcredits(void)
{
  int offset = 0;
  
  gx_texture *texture = gxTextureOpenPNG(Bg_credits_png,0);
  s16 p = 0;

  while (!p)
  {
    gxClearScreen ((GXColor)BLACK);
    gxDrawTexture(texture, (640-texture->width)/2, (480-texture->height)/2, texture->width, texture->height,255);

    FONT_writeCenter("Genesis Plus Core", 24, 0, 640, 480 - offset, (GXColor)LIGHT_BLUE);
    FONT_writeCenter("original 1.2a version by Charles MacDonald", 18, 0, 640, 516 - offset, (GXColor)WHITE);
    FONT_writeCenter("improved emulation core & additional features by Eke-Eke", 18, 0, 640, 534 - offset, (GXColor)WHITE);
    FONT_writeCenter("original Z80 core by Juergen Buchmueller", 18, 0, 640, 552 - offset, (GXColor)WHITE);
    FONT_writeCenter("original 68k core by Karl Stenerud (Musashi)", 18, 0, 640, 570 - offset, (GXColor)WHITE);
    FONT_writeCenter("original YM2612 core by Jarek Burczynski & Tatsuyuki Satoh", 18, 0, 640, 588 - offset, (GXColor)WHITE);
    FONT_writeCenter("SN76489 core by Maxim", 18, 0, 640, 606 - offset, (GXColor)WHITE);
    FONT_writeCenter("SVP core by Gravydas Ignotas (Notaz)", 18, 0, 640, 624 - offset, (GXColor)WHITE);
    FONT_writeCenter("FIR Resampler & NTSC Video Filter by Shay Green (Blargg)", 18, 0, 640, 642 - offset, (GXColor)WHITE);
    FONT_writeCenter("3-Band EQ implementation by Neil C", 18, 0, 640, 660 - offset, (GXColor)WHITE);

    FONT_writeCenter("Additional thanks to ...", 20, 0, 640, 700 - offset, (GXColor)LIGHT_GREEN);
    FONT_writeCenter("Nemesis, Tasco Deluxe, Bart Trzynadlowski, Jorge Cwik, Haze,", 18, 0, 640, 736 - offset, (GXColor)WHITE);
    FONT_writeCenter("Stef Dallongeville, AamirM, Steve Snake, Charles MacDonald", 18, 0, 640, 754 - offset, (GXColor)WHITE);
    FONT_writeCenter("Spritesmind & SMS Power members for their technical help", 18, 0, 640, 772 - offset, (GXColor)WHITE);

    FONT_writeCenter("Gamecube & Wii port", 24, 0, 640, 830 - offset, (GXColor)LIGHT_BLUE);
    FONT_writeCenter("original Gamecube port by Softdev, Honkeykong & Markcube", 18, 0, 640, 866 - offset, (GXColor)WHITE);
    FONT_writeCenter("current porting code, GUI engine & design by Eke-Eke", 18, 0, 640, 884 - offset, (GXColor)WHITE);
    FONT_writeCenter("original icons, logo & button design by Low Lines", 18, 0, 640, 906 - offset, (GXColor)WHITE);
    FONT_writeCenter("memory card icon design by Brakken", 18, 0, 640, 924 - offset, (GXColor)WHITE);
    FONT_writeCenter("libogc by Shagkur & many others", 18, 0, 640, 942 - offset, (GXColor)WHITE);
    FONT_writeCenter("libfat by Chism", 18, 0, 640, 960 - offset, (GXColor)WHITE);
    FONT_writeCenter("wiiuse by Michael Laforest (Para)", 18, 0, 640, 978 - offset, (GXColor)WHITE);
    FONT_writeCenter("EHCI module, asndlib & OGG player by Francisco Mu�oz (Hermes)", 18, 0, 640, 996 - offset, (GXColor)WHITE);
    FONT_writeCenter("USB2 storage support by Kwiirk, Rodries & Tantric", 18, 0, 640, 1014 - offset, (GXColor)WHITE);
    FONT_writeCenter("zlib, libpng & libtremor by their respective authors", 18, 0, 640, 1032 - offset, (GXColor)WHITE);
    FONT_writeCenter("devkitPPC by Wintermute", 18, 0, 640, 1050 - offset, (GXColor)WHITE);

    FONT_writeCenter("Additional thanks to ...", 20, 0, 640, 1090 - offset, (GXColor)LIGHT_GREEN);
    FONT_writeCenter("Softdev, Tmbinc, Costis, Emukiddid, Team Twiizer", 18, 0, 640, 1126 - offset, (GXColor)WHITE);
    FONT_writeCenter("Brakken & Tehskeen members for their support", 18, 0, 640, 1144 - offset, (GXColor)WHITE);

    gxSetScreen();
    p = m_input.keys;
    VIDEO_WaitVSync();
    p |= m_input.keys;
    offset ++;
    if (offset > 1144)
      offset = 0;
  }

  gxTextureClose(&texture);
}


/****************************************************************************
 * Main Menu
 *
 ****************************************************************************/
void MainMenu (void)
{
  static int rom_loaded = 0;
  int ret, quit = 0;

  char *items[3] =
  {
    "View Credits",
    "Return to Loader",
#ifdef HW_RVL
    "Exit to System Menu"
#else
    "Reset System"
#endif
  };

  /* autosave SRAM */
  if (config.s_auto & 1)
    slot_autosave(0,config.s_device);

#ifdef HW_RVL
  /* Wiimote shutdown */
  if (Shutdown)
  {
    GUI_FadeOut();
    shutdown();
    SYS_ResetSystem(SYS_POWEROFF, 0, 0);
  }

  /* wiimote pointer */
  w_pointer = gxTextureOpenPNG(generic_point_png,0);
#endif

  gui_menu *m = &menu_main;

  if (!rom_loaded)
  {
    /* check if a game is running */
    if (cart.romsize)
    {
      m->screenshot = 128;
      m->bg_images[0].state &= ~IMAGE_VISIBLE;
      m->buttons[3].state |= BUTTON_SELECT_SFX;
      m->buttons[5].state |= BUTTON_SELECT_SFX;
      m->buttons[6].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[7].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[8].state |= (BUTTON_VISIBLE | BUTTON_ACTIVE);
      m->buttons[3].shift[1] = 3;
      m->buttons[4].shift[1] = 3;
      m->buttons[5].shift[1] = 2;
      m->buttons[5].shift[3] = 1;
      rom_loaded = 1;
    }
  }

  /* Background Settings */
  GUI_SetBgColor((u8)config.bg_color);
  if (config.bg_color == 0)
  {
    bg_main[0].data = Bg_main_2_png;
    bg_misc[0].data = Bg_main_2_png;
    bg_ctrls[0].data = Bg_main_2_png;
    bg_list[0].data = Bg_main_2_png;
    bg_saves[1].data = Bg_main_2_png;
  }
  else
  {
    bg_main[0].data = Bg_main_png;
    bg_misc[0].data = Bg_main_png;
    bg_ctrls[0].data = Bg_main_png;
    bg_list[0].data = Bg_main_png;
    bg_saves[1].data = Bg_main_png;
  }
  if (config.bg_overlay)
  {
    bg_main[1].state |= IMAGE_VISIBLE;
    bg_misc[1].state |= IMAGE_VISIBLE;
    bg_ctrls[1].state |= IMAGE_VISIBLE;
    bg_list[1].state |= IMAGE_VISIBLE;
    bg_saves[2].state |= IMAGE_VISIBLE;
  }
  else
  {
    bg_main[1].state &= ~IMAGE_VISIBLE;
    bg_misc[1].state &= ~IMAGE_VISIBLE;
    bg_ctrls[1].state &= ~IMAGE_VISIBLE;
    bg_list[1].state &= ~IMAGE_VISIBLE;
    bg_saves[2].state &= ~IMAGE_VISIBLE;
  }

  GUI_InitMenu(m);
  GUI_DrawMenuFX(m,10,0);

  while (quit == 0)
  {
    ret = GUI_RunMenu(m);

    switch (ret)
    {
      /*** Load Game Menu ***/
      case 0:
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        quit = loadgamemenu();
        if (quit)
          break;
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;

      /*** Options Menu */
      case 1:
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        optionmenu();
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;

      /*** Exit Menu ***/
      case 2:
      {
        switch (GUI_OptionWindow(m, VERSION, items,3))
        {
          case 0: /* credits */
            showcredits();
            break;

          case 1: /* return to loader */
#ifdef HW_RVL
            gxTextureClose(&w_pointer);
#endif
            GUI_DeleteMenu(m);
            GUI_FadeOut();
            shutdown();
            exit(0);
            break;

          case 2: /* soft reset */
#ifdef HW_RVL
            gxTextureClose(&w_pointer);
#endif
            GUI_DeleteMenu(m);
            GUI_FadeOut();
            shutdown();
#ifdef HW_RVL
            SYS_ResetSystem(SYS_RETURNTOMENU, 0, 0);
#else
            SYS_ResetSystem(SYS_HOTRESET,0,0);
#endif
            break;
          
          default:
            break;
        }
        break;
      }

      /*** Save Manager ***/
      case 3:
        if (!cart.romsize)
          break;
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        quit = savemenu();
        if (quit)
          break;
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;

      /*** Virtual system  hard reset ***/
      case 4:
        if (!cart.romsize)
          break;
        GUI_DrawMenuFX(m,10,1);
        GUI_DeleteMenu(m);
        gxClearScreen((GXColor)BLACK);
        gxSetScreen();
        audio_init(snd.sample_rate,snd.frame_rate);
        system_init();
        system_reset();
        if (config.s_auto & 1)
          slot_autoload(0,config.s_device);
        quit = 1;
        break;

      /*** Game Genie menu (TODO !!!) ***/
      case 5:
        if (!cart.romsize)
          break;
        GUI_DrawMenuFX(m,30,1);
        GUI_DeleteMenu(m);
        GetGGEntries();
        GUI_InitMenu(m);
        GUI_DrawMenuFX(m,30,0);
        break;

      /*** Return to Game ***/
      case 6:
      case -1:
        if (!cart.romsize)
          break;
        GUI_DrawMenuFX(m,10,1);
        GUI_DeleteMenu(m);
        quit = 1;
        break;

      /*** Game Capture ***/
      case 7:
        if (!cart.romsize)
          break;
        char filename[MAXPATHLEN];
        sprintf(filename,"%s/snaps/%s.png", DEFAULT_PATH, rom_filename);
        gxSaveScreenshot(filename);
        break;

      /*** ROM information screen ***/
      case 8:
        if (!cart.romsize)
          break;
        showrominfo();
        break;
    }
  }

  /*** Remove any still held buttons ***/
  while (PAD_ButtonsHeld(0))
    PAD_ScanPads();
#ifdef HW_RVL
  while (WPAD_ButtonsHeld(0))
    WPAD_ScanPads();

  /* free wiimote pointer data */
  gxTextureClose(&w_pointer);
#endif

#ifndef HW_RVL
  /*** Stop the DVD from causing clicks while playing ***/
  uselessinquiry ();
#endif
}
