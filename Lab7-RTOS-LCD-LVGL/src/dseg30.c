/*******************************************************************************
 * Size: 30 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef DSEG30
#define DSEG30 1
#endif

#if DSEG30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002D "-" */
    0x7f, 0xfd, 0xff, 0xff, 0xff, 0x80,

    /* U+002E "." */
    0x5f, 0xf0,

    /* U+0030 "0" */
    0xff, 0xff, 0xa7, 0xff, 0xf7, 0x7f, 0xfd, 0xf0,
    0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xc0,
    0x0, 0xf0, 0x0, 0x12, 0x0, 0x3, 0xc0, 0x0,
    0xfc, 0x0, 0x1f, 0x80, 0x3, 0xf0, 0x0, 0x7e,
    0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0, 0x3f, 0x0,
    0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f, 0x80, 0x3,
    0xff, 0xff, 0xbd, 0xff, 0xf9, 0xff, 0xff, 0xc0,

    /* U+0031 "1" */
    0x2d, 0xff, 0xff, 0xff, 0xfe, 0xd7, 0xff, 0xff,
    0xff, 0xff, 0xb2,

    /* U+0032 "2" */
    0xff, 0xff, 0xa7, 0xff, 0xf4, 0x7f, 0xfd, 0x80,
    0x0, 0x70, 0x0, 0xe, 0x0, 0x1, 0xc0, 0x0,
    0x38, 0x0, 0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c,
    0x0, 0x3, 0x80, 0x0, 0x70, 0x0, 0xe, 0x3f,
    0xff, 0x47, 0xff, 0xc5, 0xff, 0xf8, 0xe0, 0x0,
    0x1c, 0x0, 0x3, 0x80, 0x0, 0x70, 0x0, 0xe,
    0x0, 0x1, 0xc0, 0x0, 0x38, 0x0, 0x7, 0x0,
    0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0,
    0x7f, 0xff, 0x8d, 0xff, 0xf9, 0xff, 0xff, 0xc0,

    /* U+0033 "3" */
    0x7f, 0xff, 0xa7, 0xff, 0xf4, 0x7f, 0xfd, 0x80,
    0x0, 0x70, 0x0, 0xe, 0x0, 0x1, 0xc0, 0x0,
    0x38, 0x0, 0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c,
    0x0, 0x3, 0x80, 0x0, 0x70, 0x0, 0xe, 0x3f,
    0xff, 0x47, 0xff, 0xd9, 0xff, 0xff, 0x0, 0x0,
    0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x8f, 0xff, 0xb1, 0xff, 0xf8, 0x7f, 0xff, 0xc0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0x0, 0x7, 0x0, 0x1, 0xf0,
    0x0, 0x3e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xc0,
    0x1, 0xff, 0xff, 0xee, 0xff, 0xfb, 0x3f, 0xff,
    0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x80, 0x0, 0x70, 0x0, 0x6, 0x0, 0x0, 0x0,

    /* U+0035 "5" */
    0xff, 0xff, 0x87, 0xff, 0xf3, 0x7f, 0xfc, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x80, 0x0, 0x70, 0x0, 0xe, 0x0, 0x1, 0xff,
    0xff, 0x37, 0xff, 0xd9, 0xff, 0xff, 0x0, 0x0,
    0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x8f, 0xff, 0xb1, 0xff, 0xf8, 0x7f, 0xff, 0xc0,

    /* U+0036 "6" */
    0xff, 0xff, 0x87, 0xff, 0xf3, 0x7f, 0xfc, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x80, 0x0, 0x70, 0x0, 0xe, 0x0, 0x1, 0xff,
    0xff, 0x37, 0xff, 0xdd, 0xff, 0xff, 0xe0, 0x0,
    0xfc, 0x0, 0x1f, 0x80, 0x3, 0xf0, 0x0, 0x7e,
    0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0, 0x3f, 0x0,
    0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f, 0x80, 0x3,
    0xff, 0xff, 0xbd, 0xff, 0xf9, 0xff, 0xff, 0xc0,

    /* U+0037 "7" */
    0xff, 0xff, 0xa7, 0xff, 0xf7, 0x7f, 0xfd, 0xf0,
    0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xc0,
    0x0, 0xf8, 0x0, 0xa, 0x0, 0x3, 0x0, 0x0,
    0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x80, 0x0, 0x70, 0x0, 0x2,

    /* U+0038 "8" */
    0xff, 0xff, 0xa7, 0xff, 0xf7, 0x7f, 0xfd, 0xf0,
    0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xff,
    0xff, 0x77, 0xff, 0xdd, 0xff, 0xff, 0xe0, 0x0,
    0xfc, 0x0, 0x1f, 0x80, 0x3, 0xf0, 0x0, 0x7e,
    0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0, 0x3f, 0x0,
    0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f, 0x80, 0x3,
    0xff, 0xff, 0xbd, 0xff, 0xf9, 0xff, 0xff, 0xc0,

    /* U+0039 "9" */
    0xff, 0xff, 0xa7, 0xff, 0xf7, 0x7f, 0xfd, 0xf0,
    0x0, 0x7e, 0x0, 0xf, 0xc0, 0x1, 0xf8, 0x0,
    0x3f, 0x0, 0x7, 0xe0, 0x0, 0xfc, 0x0, 0x1f,
    0x80, 0x3, 0xf0, 0x0, 0x7e, 0x0, 0xf, 0xff,
    0xff, 0x77, 0xff, 0xd9, 0xff, 0xff, 0x0, 0x0,
    0xe0, 0x0, 0x1c, 0x0, 0x3, 0x80, 0x0, 0x70,
    0x0, 0xe, 0x0, 0x1, 0xc0, 0x0, 0x38, 0x0,
    0x7, 0x0, 0x0, 0xe0, 0x0, 0x1c, 0x0, 0x3,
    0x8f, 0xff, 0xb1, 0xff, 0xf8, 0x7f, 0xff, 0xc0,

    /* U+003A ":" */
    0xff, 0x80, 0x0, 0x0, 0x1, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 392, .box_w = 14, .box_h = 3, .ofs_x = 5, .ofs_y = 14},
    {.bitmap_index = 7, .adv_w = 0, .box_w = 3, .box_h = 4, .ofs_x = -2, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 392, .box_w = 3, .box_h = 29, .ofs_x = 19, .ofs_y = 1},
    {.bitmap_index = 92, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 1},
    {.bitmap_index = 308, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 392, .box_w = 19, .box_h = 29, .ofs_x = 3, .ofs_y = 1},
    {.bitmap_index = 521, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 392, .box_w = 19, .box_h = 30, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 96, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xd, 0xe
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 15, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 48, .range_length = 11, .glyph_id_start = 4,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t dseg30 = {
#else
lv_font_t dseg30 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 31,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if DSEG30*/

