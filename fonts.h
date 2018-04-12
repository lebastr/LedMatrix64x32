struct Bitmap {
   int width;
   int height;
   int byte_width;
   unsigned char *data;
};


unsigned char font1_0_data[] = { 0x0, 0x0, 0x1, 0x0, 0x3, 0x1, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x3, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 };
Bitmap font1_0_bitmap = { .width = 10, .height = 14, .byte_width = 2, .data = font1_0_data };


unsigned char font1_1_data[] = { 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x3f, 0x3f, 0x1f, 0x7 };
Bitmap font1_1_bitmap = { .width = 6, .height = 14, .byte_width = 1, .data = font1_1_data };


unsigned char font1_2_data[] = { 0xff, 0xff, 0xff, 0x78, 0x3c, 0x1c, 0xe, 0x7, 0x7, 0x7, 0xc7, 0xff, 0x7e, 0x3c };
Bitmap font1_2_bitmap = { .width = 8, .height = 14, .byte_width = 1, .data = font1_2_data };


unsigned char font1_3_data[] = { 0x1, 0x0, 0x3, 0x1, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 };
Bitmap font1_3_bitmap = { .width = 9, .height = 14, .byte_width = 2, .data = font1_3_data };


unsigned char font1_4_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font1_4_bitmap = { .width = 9, .height = 14, .byte_width = 2, .data = font1_4_data };


unsigned char font1_5_data[] = { 0xfc, 0xfe, 0xcf, 0x7, 0x7, 0x7, 0xf, 0xfe, 0xfc, 0xe0, 0x60, 0x7f, 0x7f, 0x7f };
Bitmap font1_5_bitmap = { .width = 8, .height = 14, .byte_width = 1, .data = font1_5_data };


unsigned char font1_6_data[] = { 0x0, 0x0, 0x1, 0x0, 0x1, 0x0, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font1_6_bitmap = { .width = 9, .height = 14, .byte_width = 2, .data = font1_6_data };


unsigned char font1_7_data[] = { 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1 };
Bitmap font1_7_bitmap = { .width = 9, .height = 14, .byte_width = 2, .data = font1_7_data };


unsigned char font1_8_data[] = { 0x1, 0x0, 0x3, 0x1, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0 };
Bitmap font1_8_bitmap = { .width = 10, .height = 14, .byte_width = 2, .data = font1_8_data };


unsigned char font1_9_data[] = { 0x1, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0 };
Bitmap font1_9_bitmap = { .width = 9, .height = 14, .byte_width = 2, .data = font1_9_data };


unsigned char font1_percent_data[] = { 0x18, 0xc, 0x1c, 0xe, 0xc, 0x6, 0x6, 0x3, 0x6, 0x3, 0x3b, 0x1d, 0x7f, 0x3f, 0x6f, 0x37, 0xc7, 0x63, 0xc6, 0x63, 0xc6, 0x63, 0x6e, 0x37, 0x7c, 0x3e, 0x38, 0x1c };
Bitmap font1_percent_bitmap = { .width = 15, .height = 14, .byte_width = 2, .data = font1_percent_data };



Bitmap font1[] = { font1_0_bitmap, font1_1_bitmap, font1_2_bitmap, font1_3_bitmap, font1_4_bitmap, font1_5_bitmap, font1_6_bitmap, font1_7_bitmap, font1_8_bitmap, font1_9_bitmap, font1_percent_bitmap };


unsigned char font2_0_data[] = { 0x3, 0x1, 0x7, 0x3, 0xf, 0x7, 0xe, 0x7, 0x1e, 0xf, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1e, 0xf, 0xe, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1 };
Bitmap font2_0_bitmap = { .width = 12, .height = 17, .byte_width = 2, .data = font2_0_data };


unsigned char font2_1_data[] = { 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x3f, 0x3f, 0x1f, 0x7 };
Bitmap font2_1_bitmap = { .width = 6, .height = 17, .byte_width = 1, .data = font2_1_data };


unsigned char font2_2_data[] = { 0xf, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1 };
Bitmap font2_2_bitmap = { .width = 11, .height = 17, .byte_width = 2, .data = font2_2_data };


unsigned char font2_3_data[] = { 0xf, 0x7, 0xf, 0x7, 0xe, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x6, 0xf, 0x7, 0xf, 0x7, 0x7, 0x3 };
Bitmap font2_3_bitmap = { .width = 11, .height = 17, .byte_width = 2, .data = font2_3_data };


unsigned char font2_4_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf, 0x1f, 0xf, 0x1f, 0xf, 0x1e, 0xf, 0xe, 0x7, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font2_4_bitmap = { .width = 12, .height = 17, .byte_width = 2, .data = font2_4_data };


unsigned char font2_5_data[] = { 0x7, 0x3, 0xf, 0x7, 0xe, 0x7, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1, 0x3, 0x1 };
Bitmap font2_5_bitmap = { .width = 11, .height = 17, .byte_width = 2, .data = font2_5_data };


unsigned char font2_6_data[] = { 0x3, 0x1, 0xf, 0x7, 0xf, 0x7, 0x1e, 0xf, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1c, 0xe, 0x1e, 0xf, 0x1f, 0xf, 0x1f, 0xf, 0x1e, 0xf, 0xe, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1, 0x0, 0x0 };
Bitmap font2_6_bitmap = { .width = 12, .height = 17, .byte_width = 2, .data = font2_6_data };


unsigned char font2_7_data[] = { 0x7, 0x3, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xf, 0x7, 0xf, 0x7, 0xf, 0x7 };
Bitmap font2_7_bitmap = { .width = 11, .height = 17, .byte_width = 2, .data = font2_7_data };


unsigned char font2_8_data[] = { 0x7, 0x3, 0xf, 0x7, 0x1f, 0xf, 0x1e, 0xf, 0x1c, 0xe, 0x1c, 0xe, 0x1e, 0xf, 0xf, 0x7, 0x7, 0x3, 0x7, 0x3, 0xf, 0x7, 0xe, 0x7, 0xe, 0x7, 0xe, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1 };
Bitmap font2_8_bitmap = { .width = 12, .height = 17, .byte_width = 2, .data = font2_8_data };


unsigned char font2_9_data[] = { 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x1, 0x7, 0x3, 0xf, 0x7, 0xe, 0x7, 0x1e, 0xf, 0x1e, 0xf, 0x1e, 0xf, 0xe, 0x7, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1 };
Bitmap font2_9_bitmap = { .width = 12, .height = 17, .byte_width = 2, .data = font2_9_data };


unsigned char font2_min_data[] = { 0x99, 0xcc, 0xe6, 0x99, 0xcc, 0xe6, 0x99, 0xcc, 0xe6, 0x99, 0xcc, 0xe6, 0x99, 0xcc, 0xe6, 0x99, 0xcc, 0xe6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x66, 0x33, 0x19, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font2_min_bitmap = { .width = 24, .height = 11, .byte_width = 3, .data = font2_min_data };



Bitmap font2[] = { font2_0_bitmap, font2_1_bitmap, font2_2_bitmap, font2_3_bitmap, font2_4_bitmap, font2_5_bitmap, font2_6_bitmap, font2_7_bitmap, font2_8_bitmap, font2_9_bitmap, font2_min_bitmap };


unsigned char font3_0_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font3_0_bitmap = { .width = 17, .height = 25, .byte_width = 3, .data = font3_0_data };


unsigned char font3_1_data[] = { 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xf, 0xcf, 0xff, 0xff, 0xff, 0x3f, 0xf };
Bitmap font3_1_bitmap = { .width = 8, .height = 25, .byte_width = 1, .data = font3_1_data };


unsigned char font3_2_data[] = { 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x7f, 0x3f, 0x3f, 0x1f, 0xf, 0x7, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0x70, 0xf8, 0x7c, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0x3f, 0x1f };
Bitmap font3_2_bitmap = { .width = 15, .height = 25, .byte_width = 2, .data = font3_2_data };


unsigned char font3_3_data[] = { 0x1f, 0xf, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xc0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf, 0x1f, 0xf, 0x1f, 0xf, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x38, 0x7f, 0x3f, 0x7f, 0x3f, 0x3f, 0x1f };
Bitmap font3_3_bitmap = { .width = 15, .height = 25, .byte_width = 2, .data = font3_3_data };


unsigned char font3_4_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0xf, 0x7, 0x1f, 0xf, 0x7, 0x1f, 0xf, 0x7, 0xf, 0x7, 0x3, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font3_4_bitmap = { .width = 19, .height = 25, .byte_width = 3, .data = font3_4_data };


unsigned char font3_5_data[] = { 0x1f, 0xf, 0xff, 0x7f, 0xff, 0x7f, 0xff, 0x7f, 0xc0, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f, 0x3f, 0x7f, 0x3f, 0x7f, 0x3f, 0x7f, 0x3f, 0x78, 0x3c, 0x78, 0x3c, 0x3c, 0x1e, 0x3c, 0x1e, 0x3c, 0x1e, 0x3f, 0x1f, 0x3f, 0x1f, 0x1f, 0xf };
Bitmap font3_5_bitmap = { .width = 15, .height = 25, .byte_width = 2, .data = font3_5_data };


unsigned char font3_6_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font3_6_bitmap = { .width = 17, .height = 25, .byte_width = 3, .data = font3_6_data };


unsigned char font3_7_data[] = { 0xf0, 0x78, 0xf8, 0x7c, 0x78, 0x3c, 0x7c, 0x3e, 0x3c, 0x1e, 0x3e, 0x1f, 0x1e, 0xf, 0x1f, 0xf, 0xf, 0x7, 0xf, 0x7, 0x7, 0x3, 0x7, 0x3, 0x3, 0x1, 0x3, 0x1, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
Bitmap font3_7_bitmap = { .width = 16, .height = 25, .byte_width = 2, .data = font3_7_data };


unsigned char font3_8_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3, 0x1, 0x0, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font3_8_bitmap = { .width = 17, .height = 25, .byte_width = 3, .data = font3_8_data };


unsigned char font3_9_data[] = { 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x7, 0x3, 0x1, 0x3, 0x1, 0x0, 0x3, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
Bitmap font3_9_bitmap = { .width = 17, .height = 25, .byte_width = 3, .data = font3_9_data };


unsigned char font3_kmh_data[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7b, 0x3d, 0x1e, 0x8f, 0xc7, 0xe3, 0xf3, 0x79, 0x3c, 0x9e, 0xcf, 0xe7, 0xe3, 0x71, 0x38, 0x9c, 0xce, 0xe7, 0xe3, 0xf1, 0x78, 0xbc, 0xde, 0xef, 0xc3, 0xe1, 0xf0, 0xf8, 0xfc, 0xfe, 0x83, 0xc1, 0xe0, 0xf0, 0xf8, 0xfc, 0x3, 0x81, 0xc0, 0xe0, 0xf0, 0xf8, 0x83, 0xc1, 0xe0, 0xf0, 0xf8, 0xfc, 0xc3, 0xe1, 0xf0, 0xf8, 0xfc, 0xfe, 0xe3, 0xf1, 0x78, 0xbc, 0xde, 0xef, 0xf3, 0x79, 0x3c, 0x9e, 0xcf, 0xe7, 0x73, 0x39, 0x1c, 0x8e, 0xc7, 0xe3, 0x0, 0x0, 0x0, 0x80, 0xc0, 0xe0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0xe0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0xe0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0xe0, 0x0, 0x0, 0x0, 0x80, 0xc0, 0xe0 };
Bitmap font3_kmh_bitmap = { .width = 48, .height = 18, .byte_width = 6, .data = font3_kmh_data };



Bitmap font3[] = { font3_0_bitmap, font3_1_bitmap, font3_2_bitmap, font3_3_bitmap, font3_4_bitmap, font3_5_bitmap, font3_6_bitmap, font3_7_bitmap, font3_8_bitmap, font3_9_bitmap, font3_kmh_bitmap };