
#define DEFINE_DATA(name) extern char name##; extern char name##_end; 
#define SIZE(name) (&name##_end - &name##)

DEFINE_DATA(d_pal)
DEFINE_DATA(d_obj_tiles)
DEFINE_DATA(d_bg_tiles)
DEFINE_DATA(d_map_bg1)
