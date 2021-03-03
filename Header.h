#pragma once

#define MYICON  100
#define DULHANCHALI 101
#define MY_WOOD 102
#define MY_BRICK 103
#define MY_DOOR 104
#define GRASS 105
#define SKY 106
#define SIDETEXT 107
#define STEM 108
#define LIGHTNING 109
#define FEATHER 110
#define MAHADEV 111
#define TRISHUL 190
#define CEILING 191

//for scene2****************************8
#define NATURE 112
#define NATURE1 113

//for sound effect*******************
#define POEM 114
#define KARPURG 115
#define AIR_SOUND 116
#define INTERRUPT_SOUND 117
#define INTERRUPT2_SOUND 118
#define TANDAV 119
#define LIGHTNING_SOUND 120
#define FALLING_SOUND 121
#define SUNSET 122
#define TITLE_TRACK 128

//for end credit and title***************
#define TITLE1 123
#define TITLE2 124
#define ENDCREDIT1 125
#define ENDCREDIT2 126
#define ENDCREDIT3 127


typedef struct _CYLINDER_EX_CODS {

	GLfloat x1;
	GLfloat y1;
	GLfloat z1;
	GLfloat depping_angle;
}CYLINDER_CODS;

typedef struct Tree_node {

	GLfloat small_radius;
	GLfloat large_radius;
	GLfloat length;
	struct Tree_node *left;
	struct Tree_node *right;

} node;










 


