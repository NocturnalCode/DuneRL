/*
 *  Ascii.h
 *  Roguelike
 *
 *  Created by Daniel Brooker on 6/04/08.
 *  Copyright 2008 quantoaduro.com. All rights reserved.
 *
 */

#ifndef ASCII_H_INC
#define ASCII_H_INC 
#include <cstdlib>
#include <vector>

#include "Sprite.h"
#include "Colour.h"

// First Row
#define BLANK		0
#define SMILIE		1
#define SMILIE_1	2
#define HEART		3
#define DIAMOND		4
#define CLUB		5
#define SPADE		6
#define BLANK_1		7
#define BLANK_2		8
#define BLANK_3		9  
#define BLANK_4		10
#define MALE		11
#define FEMALE		12
#define BLANK_5		13
#define NOTE		14
#define COG			15
// Second Row
#define ARROW_RIGHT_FAT		16
#define ARROW_LEFT_FAT		17
#define	ARROW_UP_DOWN		18
#define EXCLAMATION_DOUBLE	19
#define RETURN				20
#define SIMOLEAN			21
#define	BAR_FAT				22
#define ARROW_UP_DOWN_BAR	23
#define ARROW_UP_THIN		24
#define ARROW_DOWN_THIN		25
#define	ARROW_LEFT_THIN		26
#define ARROW_RIGHT_THIN	27
#define ELBOW_LEFT			28
#define ARROW_LEFT_RIGHT	29
#define	ARROW_UP_FAT		30
#define ARROW_DOWN_FAT		31
// Third Row
#define BLANK_6					32
#define EXCLAMATION				33
#define QUOTE_DOUBLE			34
#define HASH					35
#define DOLLAR					36
#define PERCENT					37
#define AMPERSAND				38
#define QUOTE_SINGLE			39
#define BRACKET_LEFT_CURVED		40
#define BRACKET_RIGHT_CURVED	41 
#define ASTERIX					42
#define PLUS					43
#define COMMA					44
#define MINUS					45
#define FULL_STOP				46
#define SLASH_FORWARD			47
// Fourth Row
#define NUMBER_0				48
#define NUMBER_1				49
#define NUMBER_2				50
#define NUMBER_3				51
#define NUMBER_4				52
#define NUMBER_5				53
#define NUMBER_6				54
#define NUMBER_7				55
#define NUMBER_8				56
#define NUMBER_9				57
#define COLON					58
#define SEMI_COLON				59
#define BRACKET_LEFT_POINTY		60
#define EQUALS					61
#define BRACKET_RIGHT_POINTY	62
#define QUESTION				63
// Fifth Row
#define PLAYER		48
#define LETTER_A	49
#define LETTER_B	50
#define LETTER_C	51
#define LETTER_D	52
#define LETTER_E	53
#define LETTER_F	54
#define LETTER_G	55
#define LETTER_H	56
#define LETTER_I	57
#define LETTER_J	58
#define LETTER_K	59
#define LETTER_L	60
#define LETTER_M	61
#define LETTER_N	62
#define LETTER_O	63
// Sixth Row
#define LETTER_P				64
#define LETTER_Q				65
#define LETTER_R				66
#define LETTER_S				67
#define LETTER_T				68
#define LETTER_U				69
#define LETTER_V				70
#define LETTER_W				71
#define LETTER_X				72
#define LETTER_Y				73
#define LETTER_Z				74
#define BRACKET_LEFT_SQUARE		75
#define SLASH_BACKWARD			76
#define BRACKET_RIGHT_SQUARE	77
#define HAT						78
#define UNDERSCORE				79
// Seventh Row
#define CHAR_TO_ASCII(x) (/*x < 97 ? x-80+32+32 :*/ x-80+64 )

#define BACKTICK		80
#define LETTER_a		81
#define LETTER_b		82
#define LETTER_c		83
#define LETTER_d		84
#define LETTER_e		85
#define LETTER_f		86
#define LETTER_g		87
#define LETTER_h		88
#define LETTER_i		89
#define LETTER_j		90
#define LETTER_k		91
#define LETTER_l		92
#define LETTER_m		93
#define LETTER_n		94
#define LETTER_o		95
// Eighth Row
#define LETTER_p			96
#define LETTER_q			97
#define LETTER_r			98
#define LETTER_s			99
#define LETTER_t			100
#define LETTER_u			101
#define LETTER_v			102
#define LETTER_w			103
#define LETTER_x			104
#define LETTER_y			105
#define LETTER_z			106
#define BRACKET_LEFT_CURLY	107
#define PIPE				108
#define BRACKET_RIGHT_CURLY	109
#define TILDE				110
#define TRIANGLE			111
// Nineth Row
#define LETTER_C_AIGU		112
#define LETTER_u_dotdot		113
#define LETTER_e_acute		114
#define LETTER_a_hat		115
#define LETTER_a_dotdot		116
#define LETTER_a_grav		117
#define LETTER_a_circle		118
#define LETTER_c_aigu		119
#define LETTER_e_hat		120
#define LETTER_e_dotdot		121
#define LETTER_e_grav		122
#define LETTER_i_dotdot		123
#define LETTER_i_hat		124
#define LETTER_i_grav		125
#define LETTER_A_DOTODOT	126
#define LETTER_A_CIRCLE		127
// Tenth Row
#define LETTER_E_ACUTE	128
#define LETTER_ae		129
#define LETTER_AE		130
#define LETTER_o_hat	131
#define LETTER_o_dotdot	132
#define LETTER_o_grav	133
#define LETTER_u_hat	134
#define LETTER_u_grav	135
#define LETTER_y_dotdot	136
#define LETTER_O_dotdot	137
#define LETTER_U_dotdot	138
#define CURRENCY_C		139
#define CURRENCY_POUND	140
#define CURRENCY_YEN	141
#define LETTER_pt		142
#define LETTER_f_fancy	143
// Eleventh Row
#define LETTER_a_acute	144
#define LETTER_i_acute	145
#define LETTER_o_acute	146
#define LETTER_u_acute	147
#define LETTER_n_tilde	148
#define LETTER_N_TILDE	149
#define SYMBOL_Q_UNDERLINE		150
#define SYMBOL_O_UNDERLINE		151
#define SYMBOL_QUESTION_UPSIDEDOWN	152
//#define CORNER_TOP_LEFT_SINGLE		153
//#define CORNER_TOP_RIGHT_SINGLE		154
#define SYMBOL_HALF					155
#define SYMBOL_QUARTER				156
#define SYMBOL_EXCLAMATION_UPSIDEDOWN	157
#define BRACKET_LEFT_DOUBLE				158
#define BRACKET_RIGHT_DOUBLE			159
// Twelve Row
#define BLOCK_DIAGONAL				160
#define BLOCK_STRAIGHT				161
#define BLOCK_DIAGONAL_OPPOSITE		162
#define LINE_VERTICAL_SINGLE		163
#define JOINT_SINGLE_RIGHT_SINGLE	164
#define JOINT_DOUBLE_RIGHT_SINGLE	165
#define JOINT_DOUBLE_RIGHT_DOUBLE	166
//#define CORNER_TOP_RIGHT_DOUBLE		167
#define CORNER_TOP_RIGHT_SINGLE_DOUBLE	168
//#define JOINT_SINGLE_RIGHT_DOUBLE		169
#define LINE_VERTICAL_DOUBLE			170
#define CORNER_TOP_RIGHT_DOUBLE			171
#define CORNER_BOTTOM_RIGHT_DOUBLE		172
#define CORNER_BOTTOM_RIGHT_SINGLE_DOUBLE	173
#define CORNER_BOTTOM_RIGHT_DOUBLE_SINGLE	174
#define CORNER_TOP_RIGHT_SINGLE				175
// Thirteenth Row
#define CORNER_BOTTOM_LEFT_SINGLE	176
#define JOINT_SINGLE_BOTTOM_SINGLE	177
#define JOINT_SINGLE_TOP_SINGLE		178
#define JOINT_SINGLE_LEFT_SINGLE	179
#define LINE_HORIZONTAL_SINGLE		180
#define JOINT_SINGLE_CENTER_SINGLE	181
#define JOINT_DOUBLE_LEFT_SINGLE	182 
#define JOINT_SINGLE_RIGHT_DOUBLE	183
#define CORNER_BOTTOM_LEFT_DOUBLE	184
#define CORNER_TOP_LEFT_DOUBLE		185
#define JOINT_DOUBLE_BOTTOM_DOUBLE	186
#define JOINT_DOUBLE_TOP_DOUBLE		187
#define JOINT_DOUBLE_LEFT_DOUBLE	188
#define LINE_HORIZONTAL_DOUBLE		189
#define JOINT_DOUBLE_CENTER_DOUBLE	190
#define JOINT_DOUBLE_BOTTOM_SINGLE	191
// Fourthenth Row
//#define QUOTE_BACKWARD	192
//#define LETTER_a		193
//#define LETTER_b		194
//#define LETTER_c		195
//#define LETTER_d		196
//#define LETTER_e		197
//#define LETTER_f		198
//#define LETTER_g		199
//#define LETTER_h		200
#define CORNER_BOTTOM_RIGHT_SINGLE	201
#define CORNER_TOP_LEFT_SINGLE		202
#define BLOCK			203
//#define LETTER_l		204
//#define LETTER_m		205
//#define LETTER_n		206
//#define LETTER_o		207
// Fifteenth Row
//#define QUOTE_BACKWARD	208
//#define LETTER_a		209
//#define LETTER_b		210
//#define LETTER_c		211
//#define LETTER_d		212
//#define LETTER_e		213
//#define LETTER_f		214
//#define LETTER_g		215
//#define LETTER_h		216
//#define LETTER_i		217
//#define LETTER_j		218
//#define LETTER_k		219
//#define LETTER_l		220
//#define LETTER_m		221
//#define LETTER_n		222
//#define LETTER_o		223
// Sixteenth Row
//#define QUOTE_BACKWARD	224
//#define LETTER_a		225
//#define LETTER_b		226
//#define LETTER_c		227
//#define LETTER_d		228
//#define LETTER_e		229
//#define LETTER_f		230
//#define LETTER_g		231
//#define LETTER_h		232
//#define LETTER_i		233
//#define LETTER_j		234
//#define LETTER_k		235
//#define LETTER_l		236
//#define LETTER_m		237
//#define LETTER_n		238
//#define LETTER_o		239
// Seventeenth Row ???
//#define QUOTE_BACKWARD	240
//#define LETTER_a		241
//#define LETTER_b		242
//#define LETTER_c		243
//#define LETTER_d		244
//#define LETTER_e		245
//#define TILDE_DOUBLE	246
#define TILDE_DOUBLE	247
//#define LETTER_h		248
//#define LETTER_i		249
//#define LETTER_j		250
//#define LETTER_k		251
//#define LETTER_l		252
//#define LETTER_m		253
//#define LETTER_n		254
//#define LETTER_o		255

class Ascii
{
public:
    SpriteIndex Index;
    Colour Foreground;
    Colour Background;
    bool backgroundInherits;
    Ascii();
    Ascii(SpriteIndex index, float red,float green, float blue);
    Ascii(SpriteIndex index, Colour fg = Colour::white(),Colour bg = Colour::black());
    
    // copy operator
    Ascii& operator=(const Ascii& a);
};

typedef std::vector<Ascii*> Asciis;

class AsciiGroup {
protected:
    int index;
    Asciis asciis;
public:
    AsciiGroup();
    AsciiGroup(Ascii *ascii);
    AsciiGroup(Asciis asciis);
    virtual Ascii* currentAscii();
    virtual void update();
};

class RandomAscii: public AsciiGroup {
public:
    RandomAscii(Asciis asciis);
    virtual void update();
};

#endif /*ASCII_H_INC */
