/*
 * This file was generated automatically by xsubpp version 1.933 from the 
 * contents of Cdk.xs. Don't edit this file, edit Cdk.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "cdk.h"

CDKSCREEN * 	GCDKSCREEN	= (CDKSCREEN *)NULL;
WINDOW *	GCWINDOW	= (WINDOW *)NULL;
int GCBCount			= 0;
SV *GCBList[MAXBINDINGS];

#define MAKE_CHAR_MATRIX(START,INPUT,NEWARRAY,ARRAYSIZE,ARRAYLEN)	\
	do {								\
      	   AV *array	= (AV *)SvRV((INPUT));				\
	   int x, y;							\
									\
	   (ARRAYLEN)	= av_len (array);				\
									\
	   for (x = 0; x <= (ARRAYLEN); x++)				\
	   {								\
	      SV *name			= *av_fetch(array,x,FALSE);	\
	      AV *subArray		= (AV *)SvRV(name);		\
	      int subLen		= av_len (subArray);		\
	      (ARRAYSIZE)[x+(START)]	= subLen + 1;			\
									\
	      for (y=0; y <= subLen; y++)				\
	      {								\
	         SV *sv	= *av_fetch(subArray,y,FALSE);			\
	         (NEWARRAY)[x+(START)][y+(START)]	= copyChar((char *)SvPV(sv,na));	\
	      }								\
	   }								\
	   (ARRAYLEN)++;						\
	} while (0)
	
#define	MAKE_INT_ARRAY(START,INPUT,DEST,LEN)				\
	do {								\
	   AV *src	= (AV *)SvRV((INPUT));				\
	   int x;							\
									\
	   (LEN)	= av_len(src);					\
									\
	   for (x=0; x <= (LEN); x++)					\
	   {								\
	      SV *foo		= *av_fetch(src, x, FALSE);		\
	      (DEST)[x+(START)]	= sv2int (foo);				\
	   }								\
	   (LEN)++;							\
	} while (0)

#define	MAKE_DTYPE_ARRAY(START,INPUT,DEST,LEN)				\
	do {								\
	   AV *src	= (AV *)SvRV((INPUT));				\
	   int x;							\
									\
	   (LEN)	= av_len(src);					\
									\
	   for (x=0; x <= (LEN); x++)					\
	   {								\
	      SV *foo		= *av_fetch(src, x, FALSE);		\
	      (DEST)[x+(START)]	= sv2dtype (foo);			\
	   }								\
	   (LEN)++;							\
	} while (0)

#define	MAKE_CHTYPE_ARRAY(START,INPUT,DEST,LEN)				\
	do {								\
   	   AV *src	= (AV *)SvRV((INPUT));				\
	   int x;							\
									\
	   (LEN)	= av_len(src);					\
									\
	   for (x=0; x <= (LEN); x++)					\
	   {								\
	      SV *foo		= *av_fetch(src, x, FALSE);		\
	      (DEST)[x+(START)]	= (chtype)sv2chtype (foo);		\
	   }								\
	   (LEN)++;							\
	} while (0)

#define	MAKE_CHAR_ARRAY(START,INPUT,DEST,LEN)				\
	do {								\
	   AV *src	= (AV *)SvRV((INPUT));				\
	   int x;							\
									\
	   (LEN)	= av_len(src);					\
									\
	   for (x=0; x <= (LEN); x++)					\
	   {								\
	      SV *foo		= *av_fetch(src, x, FALSE);		\
	      (DEST)[x+(START)]	= copyChar((char *)SvPV(foo,na));	\
	   }								\
	   (LEN)++;							\
	} while (0)

/*
 * The callback callback to run Perl callback routines. Are you confused???
 */
void PerlBindCB (EObjectType cdktype, void *object, void *data)
{
/*
   dSP ;

   PUSHMARK(sp) ;
*/
   SV *foo = (SV*)data;
   perl_call_sv (foo, G_DISCARD|G_NOARGS);
}

/*
 * This callback is for the pre and post process function callbacks.
 */
int PerlProcessCB (EObjectType cdktype, void *object, void *data, chtype input)
{
   dSP;

   SV *foo = (SV*)data;
   int returnValueCount, returnValue;

   ENTER;
   SAVETMPS;

   PUSHMARK (sp);
   XPUSHs (sv_2mortal(newSViv(input)));
   PUTBACK;

   /* Call the perl subroutine.					*/
   returnValueCount = perl_call_sv (foo, G_SCALAR);

   SPAGAIN;

   /* Check the number of values returned from this function.	*/
   if (returnValueCount == 0)
   {
      /* They didn't return anything, let them continue.	*/
      PUTBACK;
      FREETMPS;
      LEAVE;
      return 1;
   }

   /* They returned something, lets find out what it is.	*/
   returnValue = POPi;

   PUTBACK;
   FREETMPS;
   LEAVE;

   return returnValue;
}

void
checkCdkInit()
{
   if (GCDKSCREEN == (CDKSCREEN *)NULL)
   {
      croak ("Cdk has not been initialized.\n");
   }
}

chtype
sv2chtype(sv)
SV *sv;
{
   if (SvPOK(sv))
   {
      char *name = SvPV(sv,na);
      if (strEQ(name, "ACS_BTEE"))
          return ACS_BTEE;
      if (strEQ(name, "ACS_HLINE"))
          return ACS_HLINE;
      if (strEQ(name, "ACS_LLCORNER"))
          return ACS_LLCORNER;
      if (strEQ(name, "ACS_LRCORNER"))
          return ACS_LRCORNER;
      if (strEQ(name, "ACS_LTEE"))
          return ACS_LTEE;
      if (strEQ(name, "ACS_PLUS"))
          return ACS_PLUS;
      if (strEQ(name, "ACS_RTEE"))
          return ACS_RTEE;
      if (strEQ(name, "ACS_TTEE"))
          return ACS_TTEE;
      if (strEQ(name, "ACS_ULCORNER"))
          return ACS_ULCORNER;
      if (strEQ(name, "ACS_URCORNER"))
          return ACS_URCORNER;
      if (strEQ(name, "ACS_VLINE"))
          return ACS_VLINE;
      if (strEQ(name, "A_ALTCHARSET"))
          return A_ALTCHARSET;
      if (strEQ(name, "A_ATTRIBUTES"))
          return A_ATTRIBUTES;
      if (strEQ(name, "A_BLINK"))
          return A_BLINK;
      if (strEQ(name, "A_BOLD"))
          return A_BOLD;
      if (strEQ(name, "A_CHARTEXT"))
          return A_CHARTEXT;
      if (strEQ(name, "A_COLOR"))
          return A_COLOR;
      if (strEQ(name, "A_DIM"))
          return A_DIM;
      if (strEQ(name, "A_INVIS"))
          return A_INVIS;
      if (strEQ(name, "A_NOATTRIB"))
          return A_NOATTRIB;
      if (strEQ(name, "A_NORMAL"))
          return A_NORMAL;
      if (strEQ(name, "A_PROTECT"))
          return A_PROTECT;
      if (strEQ(name, "A_REVERSE"))
          return A_REVERSE;
      if (strEQ(name, "A_STANDOUT"))
          return A_STANDOUT;
      if (strEQ(name, "A_UNDERLINE"))
          return A_UNDERLINE;
      if (strEQ(name, "CDK_COPY"))
          return CDK_COPY;
      if (strEQ(name, "CDK_CUT"))
          return CDK_CUT;
      if (strEQ(name, "CDK_ERASE"))
          return CDK_ERASE;
      if (strEQ(name, "CDK_NEXT"))
          return CDK_NEXT;
      if (strEQ(name, "CDK_PASTE"))
          return CDK_PASTE;
      if (strEQ(name, "CDK_REFRESH"))
          return CDK_REFRESH;
#ifdef COLOR
      if (strEQ(name, "COLOR_BLACK"))
         return COLOR_BLACK;
      if (strEQ(name, "COLOR_BLUE"))
         return COLOR_BLUE;
      if (strEQ(name, "COLOR_CYAN"))
         return COLOR_CYAN;
      if (strEQ(name, "COLOR_GREEN"))
         return COLOR_GREEN;
      if (strEQ(name, "COLOR_MAGENTA"))
         return COLOR_MAGENTA;
      if (strEQ(name, "COLOR_RED"))
         return COLOR_RED;
      if (strEQ(name, "COLOR_WHITE"))
         return COLOR_WHITE;
      if (strEQ(name, "COLOR_YELLOW"))
         return COLOR_YELLOW;
#endif
      if (strEQ(name, "DELETE"))
          return DELETE;
      if (strEQ(name, "KEY_A1"))
          return KEY_A1;
      if (strEQ(name, "KEY_A3"))
          return KEY_A3;
      if (strEQ(name, "KEY_B2"))
          return KEY_B2;
      if (strEQ(name, "KEY_BACKSPACE"))
          return KEY_BACKSPACE;
      if (strEQ(name, "KEY_BEG"))
          return KEY_BEG;
      if (strEQ(name, "KEY_BREAK"))
          return KEY_BREAK;
      if (strEQ(name, "KEY_BTAB"))
          return KEY_BTAB;
      if (strEQ(name, "KEY_C1"))
          return KEY_C1;
      if (strEQ(name, "KEY_C3"))
          return KEY_C3;
      if (strEQ(name, "KEY_CANCEL"))
          return KEY_CANCEL;
      if (strEQ(name, "KEY_CATAB"))
          return KEY_CATAB;
      if (strEQ(name, "KEY_CLEAR"))
          return KEY_CLEAR;
      if (strEQ(name, "KEY_CLOSE"))
          return KEY_CLOSE;
      if (strEQ(name, "KEY_COMMAND"))
          return KEY_COMMAND;
      if (strEQ(name, "KEY_COPY"))
          return KEY_COPY;
      if (strEQ(name, "KEY_CREATE"))
          return KEY_CREATE;
      if (strEQ(name, "KEY_CTAB"))
          return KEY_CTAB;
      if (strEQ(name, "KEY_DC"))
          return KEY_DC;
      if (strEQ(name, "KEY_DL"))
          return KEY_DL;
      if (strEQ(name, "KEY_DOWN"))
          return KEY_DOWN;
      if (strEQ(name, "KEY_EIC"))
          return KEY_EIC;
      if (strEQ(name, "KEY_END"))
          return KEY_END;
      if (strEQ(name, "KEY_ENTER"))
          return KEY_ENTER;
      if (strEQ(name, "KEY_EOL"))
          return KEY_EOL;
      if (strEQ(name, "KEY_EOS"))
          return KEY_EOS;
      if (strEQ(name, "KEY_ESC"))
          return KEY_ESC;
      if (strEQ(name, "KEY_EXIT"))
          return KEY_EXIT;
      if (strEQ(name, "KEY_F0"))
          return KEY_F0;
      if (strEQ(name, "KEY_F1"))
          return KEY_F1;
      if (strEQ(name, "KEY_F10"))
          return KEY_F10;
      if (strEQ(name, "KEY_F11"))
          return KEY_F11;
      if (strEQ(name, "KEY_F12"))
          return KEY_F12;
      if (strEQ(name, "KEY_F2"))
          return KEY_F2;
      if (strEQ(name, "KEY_F3"))
          return KEY_F3;
      if (strEQ(name, "KEY_F4"))
          return KEY_F4;
      if (strEQ(name, "KEY_F5"))
          return KEY_F5;
      if (strEQ(name, "KEY_F6"))
          return KEY_F6;
      if (strEQ(name, "KEY_F7"))
          return KEY_F7;
      if (strEQ(name, "KEY_FIND"))
          return KEY_FIND;
      if (strEQ(name, "KEY_HELP"))
          return KEY_HELP;
      if (strEQ(name, "KEY_HOME"))
          return KEY_HOME;
      if (strEQ(name, "KEY_IC"))
          return KEY_IC;
      if (strEQ(name, "KEY_IL"))
          return KEY_IL;
      if (strEQ(name, "KEY_LEFT"))
          return (chtype)KEY_LEFT;
      if (strEQ(name, "KEY_LL"))
          return KEY_LL;
      if (strEQ(name, "KEY_MARK"))
          return KEY_MARK;
      if (strEQ(name, "KEY_MAX"))
          return KEY_MAX;
      if (strEQ(name, "KEY_MESSAGE"))
          return KEY_MESSAGE;
      if (strEQ(name, "KEY_MIN"))
          return KEY_MIN;
      if (strEQ(name, "KEY_MOVE"))
          return KEY_MOVE;
      if (strEQ(name, "KEY_NEXT"))
          return KEY_NEXT;
      if (strEQ(name, "KEY_NPAGE"))
          return KEY_NPAGE;
      if (strEQ(name, "KEY_OPEN"))
          return KEY_OPEN;
      if (strEQ(name, "KEY_OPTIONS"))
          return KEY_OPTIONS;
      if (strEQ(name, "KEY_PPAGE"))
          return KEY_PPAGE;
      if (strEQ(name, "KEY_PREVIOUS"))
          return KEY_PREVIOUS;
      if (strEQ(name, "KEY_PRINT"))
          return KEY_PRINT;
      if (strEQ(name, "KEY_REDO"))
          return KEY_REDO;
      if (strEQ(name, "KEY_REFERENCE"))
          return KEY_REFERENCE;
      if (strEQ(name, "KEY_REFRESH"))
          return KEY_REFRESH;
      if (strEQ(name, "KEY_REPLACE"))
          return KEY_REPLACE;
      if (strEQ(name, "KEY_RESET"))
          return KEY_RESET;
      if (strEQ(name, "KEY_RESTART"))
          return KEY_RESTART;
      if (strEQ(name, "KEY_RESUME"))
          return KEY_RESUME;
      if (strEQ(name, "KEY_RETURN"))
          return KEY_RETURN;
      if (strEQ(name, "KEY_RIGHT"))
          return KEY_RIGHT;
      if (strEQ(name, "KEY_SAVE"))
          return KEY_SAVE;
      if (strEQ(name, "KEY_SBEG"))
          return KEY_SBEG;
      if (strEQ(name, "KEY_SCANCEL"))
          return KEY_SCANCEL;
      if (strEQ(name, "KEY_SCOMMAND"))
          return KEY_SCOMMAND;
      if (strEQ(name, "KEY_SCOPY"))
          return KEY_SCOPY;
      if (strEQ(name, "KEY_SCREATE"))
          return KEY_SCREATE;
      if (strEQ(name, "KEY_SDC"))
          return KEY_SDC;
      if (strEQ(name, "KEY_SDL"))
          return KEY_SDL;
      if (strEQ(name, "KEY_SELECT"))
          return KEY_SELECT;
      if (strEQ(name, "KEY_SEND"))
          return KEY_SEND;
      if (strEQ(name, "KEY_SEOL"))
          return KEY_SEOL;
      if (strEQ(name, "KEY_SEXIT"))
          return KEY_SEXIT;
      if (strEQ(name, "KEY_SF"))
          return KEY_SF;
      if (strEQ(name, "KEY_SFIND"))
          return KEY_SFIND;
      if (strEQ(name, "KEY_SHELP"))
          return KEY_SHELP;
      if (strEQ(name, "KEY_SHOME"))
          return KEY_SHOME;
      if (strEQ(name, "KEY_SIC"))
          return KEY_SIC;
      if (strEQ(name, "KEY_SLEFT"))
          return KEY_SLEFT;
      if (strEQ(name, "KEY_SMESSAGE"))
          return KEY_SMESSAGE;
      if (strEQ(name, "KEY_SMOVE"))
          return KEY_SMOVE;
      if (strEQ(name, "KEY_SNEXT"))
          return KEY_SNEXT;
      if (strEQ(name, "KEY_SOPTIONS"))
          return KEY_SOPTIONS;
      if (strEQ(name, "KEY_SPREVIOUS"))
          return KEY_SPREVIOUS;
      if (strEQ(name, "KEY_SPRINT"))
          return KEY_SPRINT;
      if (strEQ(name, "KEY_SR"))
          return KEY_SR;
      if (strEQ(name, "KEY_SREDO"))
          return KEY_SREDO;
      if (strEQ(name, "KEY_SREPLACE"))
          return KEY_SREPLACE;
      if (strEQ(name, "KEY_SRESET"))
          return KEY_SRESET;
      if (strEQ(name, "KEY_SRIGHT"))
          return KEY_SRIGHT;
      if (strEQ(name, "KEY_SRSUME"))
          return KEY_SRSUME;
      if (strEQ(name, "KEY_SSAVE"))
          return KEY_SSAVE;
      if (strEQ(name, "KEY_SSUSPEND"))
          return KEY_SSUSPEND;
      if (strEQ(name, "KEY_STAB"))
          return KEY_STAB;
      if (strEQ(name, "KEY_SUNDO"))
          return KEY_SUNDO;
      if (strEQ(name, "KEY_SUSPEND"))
          return KEY_SUSPEND;
      if (strEQ(name, "KEY_TAB"))
          return KEY_TAB;
      if (strEQ(name, "KEY_UNDO"))
          return KEY_UNDO;
      if (strEQ(name, "KEY_UP"))
          return KEY_UP;
      if (strEQ(name, "SPACE"))
         return SPACE;
      if (strEQ(name, "TAB"))
         return TAB;
      return (chtype)name[0];
   }
   return (chtype)SvIV(sv);
}

int
sv2cdktype(sv)
SV * sv;
{
   if (SvPOK(sv))
   {
      char *name = SvPV(sv,na);
      if (strEQ (name, "vENTRY"))
         return vENTRY;
      if (strEQ (name, "vMENTRY"))
         return vMENTRY;
      if (strEQ (name, "vLABEL"))
         return vLABEL;
      if (strEQ (name, "vSCROLL"))
         return vSCROLL;
      if (strEQ (name, "vDIALOG"))
         return vDIALOG;
      if (strEQ (name, "vSCALE"))
         return vSCALE;
      if (strEQ (name, "vMARQUEE"))
         return vMARQUEE;
      if (strEQ (name, "vMENU"))
         return vMENU;
      if (strEQ (name, "vMATRIX"))
         return vMATRIX;
      if (strEQ (name, "vHISTOGRAM"))
         return vHISTOGRAM;
      if (strEQ (name, "vSELECTION"))
         return vSELECTION;
      if (strEQ (name, "vVIEWER"))
         return vVIEWER;
      if (strEQ (name, "vGRAPH"))
         return vGRAPH;
      if (strEQ (name, "vRADIO"))
         return vRADIO;
   }
}

int
sv2dtype(sv)
SV * sv;
{
   if (SvPOK(sv))
   {
      char *name = SvPV(sv,na);
      if (strEQ (name, "CHAR"))
         return vCHAR;
      if (strEQ (name, "HCHAR"))
         return vHCHAR;
      if (strEQ (name, "INT"))
         return vINT;
      if (strEQ (name, "HINT"))
         return vHINT;
      if (strEQ (name, "MIXED"))
         return vMIXED;
      if (strEQ (name, "HMIXED"))
         return vHMIXED;
      if (strEQ (name, "UCHAR"))
         return vUCHAR;
      if (strEQ (name, "LCHAR"))
         return vLCHAR;
      if (strEQ (name, "UHCHAR"))
         return vUHCHAR;
      if (strEQ (name, "LHCHAR"))
         return vLHCHAR;
      if (strEQ (name, "UMIXED"))
         return vUMIXED;
      if (strEQ (name, "LMIXED"))
         return vLMIXED;
      if (strEQ (name, "UHMIXED"))
         return vUHMIXED;
      if (strEQ (name, "LHMIXED"))
         return vLHMIXED;
      if (strEQ (name, "VIEWONLY"))
         return vVIEWONLY;
      if (strEQ (name, "NONE"))
         return vNONE;
      if (strEQ (name, "PERCENT"))
         return vPERCENT;
      if (strEQ (name, "REAL"))
         return vREAL;
      if (strEQ (name, "PLOT"))
         return vPLOT;
      if (strEQ (name, "LINE"))
         return vLINE;
   }
   return (int)SvIV(sv);
}

static int
sv2int(sv)
SV *sv;
{
   if (SvPOK(sv))
   {
      char *name = SvPV(sv,na);
      if (strEQ(name, "BOTTOM"))
         return BOTTOM;
      if (strEQ(name, "BOX"))
         return BOX;
      if (strEQ(name, "CENTER"))
         return CENTER;
      if (strEQ(name, "COL"))
         return COL;
      if (strEQ(name, "FALSE"))
         return FALSE;
      if (strEQ(name, "FULL"))
         return FULL;
      if (strEQ(name, "HORIZONTAL"))
         return HORIZONTAL;
      if (strEQ(name, "LEFT"))
         return LEFT;
      if (strEQ(name, "NOBOX"))
         return NOBOX;
      if (strEQ(name, "NONE"))
         return NONE;
      if (strEQ(name, "NONUMBERS"))
         return NONUMBERS;
      if (strEQ(name, "NUMBERS"))
         return NUMBERS;
      if (strEQ(name, "RIGHT"))
         return RIGHT;
      if (strEQ(name, "ROW"))
         return ROW;
      if (strEQ(name, "TRUE"))
         return TRUE;
      if (strEQ(name, "TOP"))
         return TOP;
      if (strEQ(name, "VERTICAL"))
         return VERTICAL;
   }
   return (int)SvIV(sv);
}

static char *
sv2CharPtr(inp)
SV *inp;
{
   char *name = (char *)SvPV(inp,na);
   return (name);
}

static int
not_here(s)
char *s;
{
    croak("%s not implemented on this architecture", s);
    return -1;
}

static double
constant(name, arg)
char *name;
int arg;
{
    errno = 0;
    switch (*name) {
    case 'A':
	break;
    case 'B':
	break;
    case 'C':
	break;
    case 'D':
	break;
    case 'E':
	break;
    case 'F':
	break;
    case 'G':
	break;
    case 'H':
	break;
    case 'I':
	break;
    case 'J':
	break;
    case 'K':
	break;
    case 'L':
	break;
    case 'M':
	break;
    case 'N':
	break;
    case 'O':
	break;
    case 'P':
	break;
    case 'Q':
	break;
    case 'R':
	break;
    case 'S':
	break;
    case 'T':
	break;
    case 'U':
	break;
    case 'V':
	break;
    case 'W':
	break;
    case 'X':
	break;
    case 'Y':
	break;
    case 'Z':
	break;
    }
    errno = EINVAL;
    return 0;

not_there:
    errno = ENOENT;
    return 0;
}

XS(XS_Cdk_constant)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::constant(name,arg)");
    {
	char *	name = (char *)SvPV(ST(0),na);
	int	arg = (int)SvIV(ST(1));
	double	RETVAL;

	RETVAL = constant(name, arg);
	ST(0) = sv_newmortal();
	sv_setnv(ST(0), (double)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk_Beep)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::Beep()");
    {
	{
	   Beep();
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_init)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::init()");
    {
	CDKSCREEN *	RETVAL;
	{
	   int x	= 0;
	   GCWINDOW	= initscr();
	   GCDKSCREEN 	= initCDKScreen (GCWINDOW);

	   /* Start the colors.				*/
	   initCDKColor();

	   /* Empty out the callback binding list.	*/
	   for (x=0; x < MAXBINDINGS; x++)
	   {
	      GCBList[x] = (SV *)NULL;
	   }

	   RETVAL = GCDKSCREEN;
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSCREENPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk_mixChtype)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::mixChtype(character,attribute)");
    {
	char	character = (char)*SvPV(ST(0),na);
	chtype	attribute = (chtype)SvIV(ST(1));
	chtype	RETVAL;
	{
	   RETVAL = character | attribute;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_getColor)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::getColor(pair)");
    {
	int	pair = (int)SvIV(ST(0));
	long	RETVAL;
	{
	   RETVAL = COLOR_PAIR(pair);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_makeChtype)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::makeChtype(attr1,attr2)");
    {
	chtype	attr1 = (chtype)SvIV(ST(0));
	chtype	attr2 = (chtype)SvIV(ST(1));
	chtype	RETVAL;
	{
	   RETVAL = attr1 | attr2;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_makeColorChtype)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::makeColorChtype(attribute,pair)");
    {
	chtype attribute = sv2chtype (ST(0));
	int	pair = (int)SvIV(ST(1));
	chtype	RETVAL;
	{
	   RETVAL = attribute | COLOR_PAIR(pair);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_end)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::end()");
    {
	{
	   int x	= 0;

	   /* Kill the main screen.			*/
	   destroyCDKScreen (GCDKSCREEN);

	   /* Remove the curses window.			*/
	   delwin (GCWINDOW);

	   /* Free up any memory used.			*/
	   for (x=0; x < GCBCount; x++)
	   {
	      SvREFCNT_dec (GCBList[x]);
	   }

	   /* Shut down curses.				*/
	   endCDK();
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_getCdkScreen)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::getCdkScreen()");
    {
	CDKSCREEN *	RETVAL;
	{
	   RETVAL = GCDKSCREEN;
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSCREENPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk_getCdkScreenDim)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::getCdkScreenDim()");
    SP -= items;
    {
	{
	   XPUSHs (sv_2mortal(newSViv(GCDKSCREEN->window->_maxy)));
	   XPUSHs (sv_2mortal(newSViv(GCDKSCREEN->window->_maxx)));
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk_getCdkWindow)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::getCdkWindow()");
    {
	WINDOW *	RETVAL;
	{
	   RETVAL = GCDKSCREEN->window;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_refreshCdkScreen)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::refreshCdkScreen()");
    {
	{
	   refreshCDKScreen (GCDKSCREEN);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_eraseCdkScreen)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::eraseCdkScreen()");
    {
	{
	   eraseCDKScreen (GCDKSCREEN);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_destroyCdkScreen)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::destroyCdkScreen()");
    {
	{
	   destroyCDKScreen(GCDKSCREEN);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_DrawMesg)
{
    dXSARGS;
    if (items < 2 || items > 6)
	croak("Usage: Cdk::DrawMesg(window,mesg,attrib=A_NORMAL,xpos=CENTER,ypos=CENTER,align=HORIZONTAL)");
    {
	WINDOW *	window;
	char *	mesg = (char *)SvPV(ST(1),na);
	chtype attrib = sv2chtype (ST(2));
	int xpos = sv2int (ST(3));
	int ypos = sv2int (ST(4));
	int align = sv2int (ST(5));

	if (sv_isa(ST(0), "WINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    window = (WINDOW *) tmp;
	}
	else
	    croak("window is not of type WINDOWPtr");
	{
	   printattr (window, xpos, ypos, align, attrib, mesg);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk_getch)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::getch()");
    {
	chtype	RETVAL;

	RETVAL = getch();
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk_raw)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::raw()");
    {

	raw();
    }
    XSRETURN(1);
}

XS(XS_Cdk_noraw)
{
    dXSARGS;
    if (items != 0)
	croak("Usage: Cdk::noraw()");
    {

	noraw();
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_New)
{
    dXSARGS;
    if (items < 1 || items > 5)
	croak("Usage: Cdk::Label::New(mesg,xPos=CENTER,yPos=CENTER,Box=TRUE,shadow=FALSE)");
    {
	SV *	mesg = ST(0);
	int xPos = sv2int (ST(1));
	int yPos = sv2int (ST(2));
	int Box = sv2int (ST(3));
	int shadow = sv2int (ST(4));
	CDKLABEL *	RETVAL;
	{
	   CDKLABEL *	labelWidget = (CDKLABEL *)NULL;
	   char *	Message[MAXLABELROWS];
	   int	 	mesgLines;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY (0,mesg,Message,mesgLines);

	   labelWidget = newCDKLabel (GCDKSCREEN,xPos,yPos,
					Message,mesgLines,
					Box,shadow);

	   /* Check the return value. */
	   if (labelWidget == (CDKLABEL *)NULL)
	   {
  	      croak ("Cdk::Label Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = labelWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKLABELPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Label::Draw(object,Box=TRUE)");
    {
	CDKLABEL *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   drawCDKLabel (object, Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::Erase(object)");
    {
	CDKLABEL *	object;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   eraseCDKLabel(object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Wait)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Label::Wait(object, key=(chtype)NULL)");
    {
	CDKLABEL *	object;
	chtype key = sv2chtype (ST(1));
	char	RETVAL;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   RETVAL = waitCDKLabel (object, key);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::Register(object)");
    {
	CDKLABEL *	object;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   registerCDKObject (GCDKSCREEN, vLABEL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::Unregister(object)");
    {
	CDKLABEL *	object;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   unregisterCDKObject (vLABEL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::Raise(object)");
    {
	CDKLABEL *	object;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   raiseCDKObject (vLABEL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::Lower(object)");
    {
	CDKLABEL *	object;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   lowerCDKObject (vLABEL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Label_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Label::GetWindow(object)");
    {
	CDKLABEL *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKLABELPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not of type CDKLABELPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_New)
{
    dXSARGS;
    if (items < 2 || items > 8)
	croak("Usage: Cdk::Dialog::New(message,buttons,xPos=CENTER,yPos=CENTER,highlight=A_REVERSE,seperator=TRUE,Box=TRUE,shadow=FALSE)");
    {
	SV *	message = ST(0);
	SV *	buttons = ST(1);
	int xPos = sv2int (ST(2));
	int yPos = sv2int (ST(3));
	chtype highlight = sv2chtype (ST(4));
	int seperator = sv2int (ST(5));
	int Box = sv2int (ST(6));
	int shadow = sv2int (ST(7));
	CDKDIALOG *	RETVAL;
	{
	   CDKDIALOG *	dialogWidget = (CDKDIALOG *)NULL;
	   char *	Message[MAXDIALOGROWS];
	   char *	Buttons[MAXDIALOGBUTTONS];
	   int 		buttonCount;
	   int		rowCount;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY (0,message,Message,rowCount);
	   MAKE_CHAR_ARRAY (0,buttons,Buttons,buttonCount);

	   dialogWidget = newCDKDialog (GCDKSCREEN,xPos,yPos,Message,rowCount,Buttons,buttonCount,highlight,seperator,Box,shadow);

	   /* Check the return type. */
	   if (dialogWidget == (CDKDIALOG *)NULL)
	   {
	      croak ("Cdk::Dialog Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = dialogWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKDIALOGPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Dialog::Activate(object,...)");
    {
	CDKDIALOG *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKDialog (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKDialog (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Dialog::Inject(object,key)");
    {
	CDKDIALOG *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   RETVAL = injectCDKDialog (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Dialog::Bind(object,key,functionRef)");
    {
	CDKDIALOG *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vDIALOG, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Dialog::Draw(object,Box=TRUE)");
    {
	CDKDIALOG *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
        {
           drawCDKDialog (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::Erase(object)");
    {
	CDKDIALOG *	object;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   eraseCDKDialog (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Set)
{
    dXSARGS;
    if (items < 1 || items > 4)
	croak("Usage: Cdk::Dialog::Set(object,highlight=A_REVERSE,seperator=TRUE,Box=TRUE)");
    {
	CDKDIALOG *	object;
	chtype highlight = sv2chtype (ST(1));
	int seperator = sv2int (ST(2));
	int Box = sv2int (ST(3));

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   setCDKDialog (object,highlight,seperator,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::Register(object)");
    {
	CDKDIALOG *	object;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   registerCDKObject (GCDKSCREEN, vDIALOG, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::Unregister(object)");
    {
	CDKDIALOG *	object;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   unregisterCDKObject (vDIALOG, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::Raise(object)");
    {
	CDKDIALOG *	object;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   raiseCDKObject (vDIALOG, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::Lower(object)");
    {
	CDKDIALOG *	object;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   lowerCDKObject (vDIALOG, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Dialog_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Dialog::GetWindow(object)");
    {
	CDKDIALOG *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKDIALOGPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not of type CDKDIALOGPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_New)
{
    dXSARGS;
    if (items < 4 || items > 10)
	croak("Usage: Cdk::Scroll::New(title,mesg,height,width,xPos=CENTER,yPos=CENTER,numbers=TRUE,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)");
    {
	char *	title = (char *)SvPV(ST(0),na);
	SV *	mesg = ST(1);
	int	height = (int)SvIV(ST(2));
	int	width = (int)SvIV(ST(3));
	int xPos = sv2int (ST(4));
	int yPos = sv2int (ST(5));
	int numbers = sv2int (ST(6));
	chtype highlight = sv2chtype (ST(7));
	int Box = sv2int (ST(8));
	int shadow = sv2int (ST(9));
	CDKSCROLL *	RETVAL;
	{
	   CDKSCROLL * scrollWidget = (CDKSCROLL *)NULL;
	   char *Message[MAXITEMS];
	   int mesglen;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY(0,mesg,Message,mesglen);
           Message[mesglen] = "";

	   scrollWidget = newCDKScroll (GCDKSCREEN,xPos,yPos,height,width,title,Message,mesglen,numbers,highlight,Box,shadow);

	   /* Check the return type. */
	   if (scrollWidget == (CDKSCROLL *)NULL)
	   {
	      croak ("Cdk::Scroll Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = scrollWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSCROLLPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Scroll::Activate(object,...)");
    {
	CDKSCROLL *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKScroll (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKScroll (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Scroll::Inject(object,key)");
    {
	CDKSCROLL *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   RETVAL = injectCDKScroll (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Add)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Scroll::Add(object,line)");
    {
	CDKSCROLL *	object;
	char *	line = (char *)SvPV(ST(1),na);

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   addCDKScrollItem (object,line);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Delete)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Scroll::Delete(object,position)");
    {
	CDKSCROLL *	object;
	int position = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   deleteCDKScrollItem (object,position);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Scroll::Bind(object,key,functionRef)");
    {
	CDKSCROLL *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSCROLL, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Scroll::Draw(object,Box=BOX)");
    {
	CDKSCROLL *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
        {
           drawCDKScroll (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Erase(object)");
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   eraseCDKScroll(object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Info)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Info(object)");
    SP -= items;
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   int currentItem = object->currentItem;
	   int size = object->listSize;

	   XPUSHs (sv_2mortal (newSViv(size)));
	   XPUSHs (sv_2mortal (newSViv(currentItem)));
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Scroll_Set)
{
    dXSARGS;
    if (items < 2 || items > 5)
	croak("Usage: Cdk::Scroll::Set(object,mesg,numbers=FALSE,highlight=A_REVERSE,Box=TRUE)");
    {
	CDKSCROLL *	object;
	SV *	mesg = ST(1);
	int numbers = sv2int (ST(2));
	chtype highlight = sv2chtype (ST(3));
	int Box = sv2int (ST(4));

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   char *Message[MAXITEMS];
	   int mesglen;

	   MAKE_CHAR_ARRAY(0,mesg,Message,mesglen);
	   Message[mesglen] = "";

	   setCDKScroll (object,Message,mesglen,numbers,highlight,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Register(object)");
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   registerCDKObject (GCDKSCREEN, vSCROLL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Unregister(object)");
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   unregisterCDKObject (vSCROLL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Raise(object)");
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   raiseCDKObject (vSCROLL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::Lower(object)");
    {
	CDKSCROLL *	object;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   lowerCDKObject (vSCROLL, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scroll_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scroll::GetWindow(object)");
    {
	CDKSCROLL *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKSCROLLPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not of type CDKSCROLLPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_New)
{
    dXSARGS;
    if (items < 7 || items > 13)
	croak("Usage: Cdk::Scale::New(label,start,low,high,inc,fastinc,fieldwidth,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	int	start = (int)SvIV(ST(1));
	int	low = (int)SvIV(ST(2));
	int	high = (int)SvIV(ST(3));
	int	inc = (int)SvIV(ST(4));
	int	fastinc = (int)SvIV(ST(5));
	int	fieldwidth = (int)SvIV(ST(6));
	int xPos = sv2int (ST(7));
	int yPos = sv2int (ST(8));
	int lPos = sv2int (ST(9));
	chtype fieldattr = sv2chtype (ST(10));
	int Box = sv2int (ST(11));
	int shadow = sv2int (ST(12));
	CDKSCALE *	RETVAL;
	{
	   CDKSCALE * scaleWidget = (CDKSCALE *)NULL;

	   checkCdkInit();

	   scaleWidget = newCDKScale (GCDKSCREEN,xPos,yPos,lPos,label,fieldattr,fieldwidth,start,low,high,inc,fastinc,Box,shadow);

	   /* Check the return type. */
	   if (scaleWidget == (CDKSCALE *)NULL)
	   {
	      croak ("Cdk::Scale Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = scaleWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSCALEPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Scale::Activate(object,...)");
    {
	CDKSCALE *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKScale (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKScale (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Scale::Inject(object,key)");
    {
	CDKSCALE *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   RETVAL = injectCDKScale (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Scale::Bind(object,key,functionRef)");
    {
	CDKSCALE *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSCALE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Scale::Draw(object,Box=BOX)");
    {
	CDKSCALE *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
        {
           drawCDKScale (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::Erase(object)");
    {
	CDKSCALE *	object;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   eraseCDKScale(object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Set)
{
    dXSARGS;
    if (items < 4 || items > 5)
	croak("Usage: Cdk::Scale::Set(object,low,high,value,Box=TRUE)");
    {
	CDKSCALE *	object;
	int	low = (int)SvIV(ST(1));
	int	high = (int)SvIV(ST(2));
	int	value = (int)SvIV(ST(3));
	int Box = sv2int (ST(4));

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   setCDKScale (object,low,high,value,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::Register(object)");
    {
	CDKSCALE *	object;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   registerCDKObject (GCDKSCREEN, vSCALE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::Unregister(object)");
    {
	CDKSCALE *	object;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   unregisterCDKObject (vSCALE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::Raise(object)");
    {
	CDKSCALE *	object;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   raiseCDKObject (vSCALE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::Lower(object)");
    {
	CDKSCALE *	object;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   lowerCDKObject (vSCALE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Scale_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Scale::GetWindow(object)");
    {
	CDKSCALE *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKSCALEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not of type CDKSCALEPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_New)
{
    dXSARGS;
    if (items < 3 || items > 9)
	croak("Usage: Cdk::Histogram::New(label,height,width,orient=HORIZONTAL,xPos=CENTER,yPos=CENTER,lPos=LEFT,Box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	int	height = (int)SvIV(ST(1));
	int	width = (int)SvIV(ST(2));
	int orient = sv2int (ST(3));
	int xPos = sv2int (ST(4));
	int yPos = sv2int (ST(5));
	int lPos = sv2int (ST(6));
	int Box = sv2int (ST(7));
	int shadow = sv2int (ST(8));
	CDKHISTOGRAM *	RETVAL;
	{
	   CDKHISTOGRAM * histWidget = (CDKHISTOGRAM *)NULL;

	   checkCdkInit();

	   histWidget = newCDKHistogram (GCDKSCREEN,xPos,yPos,lPos,height,width,orient,label,Box,shadow);

	   /* Check the return type. */
	   if (histWidget == (CDKHISTOGRAM *)NULL)
	   {
	      croak ("Cdk::Histogram Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = histWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKHISTOGRAMPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Set)
{
    dXSARGS;
    if (items < 4 || items > 10)
	croak("Usage: Cdk::Histogram::Set(object,low,high,value,filler='.',fillattr=A_NORMAL,sType=\"vPERCENT\",statsPos=TOP,statsAttr=A_REVERSE,Box=BOX)");
    {
	CDKHISTOGRAM *	object;
	int	low = (int)SvIV(ST(1));
	int	high = (int)SvIV(ST(2));
	int	value = (int)SvIV(ST(3));
	char	filler;
	chtype fillattr = sv2chtype (ST(5));
	char *	sType;
	int statsPos = sv2int (ST(7));
	chtype statsAttr = sv2chtype (ST(8));
	int Box = sv2int (ST(9));

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");

	if (items < 5)
	    filler = '.';
	else {
	    filler = (char)*SvPV(ST(4),na);
	}

	if (items < 7)
	    sType = "vPERCENT";
	else {
	    sType = (char *)SvPV(ST(6),na);
	}
	{
	   EHistogramDisplayType statsType = vPERCENT;
	   chtype tempchtype = filler|fillattr;

	   /* Set the stats type.		*/
	   if (strEQ (sType, "PERCENT"))
	      statsType = vPERCENT;
	   if (strEQ (sType, "FRACTION"))
	      statsType = vFRACTION;
	   if (strEQ (sType, "REAL"))
	      statsType = vREAL;
	   if (strEQ (sType, "NONE"))
	      statsType = vNONE;

	   setCDKHistogram (object,statsType,statsPos,statsAttr,low,high,value,tempchtype,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Histogram::Draw(object,Box=BOX)");
    {
	CDKHISTOGRAM *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   drawCDKHistogram (object,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::Erase(object)");
    {
	CDKHISTOGRAM *	object;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   eraseCDKHistogram (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::Register(object)");
    {
	CDKHISTOGRAM *	object;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   registerCDKObject (GCDKSCREEN, vHISTOGRAM, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::Unregister(object)");
    {
	CDKHISTOGRAM *	object;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   unregisterCDKObject (vHISTOGRAM, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::Raise(object)");
    {
	CDKHISTOGRAM *	object;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   raiseCDKObject (vHISTOGRAM, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::Lower(object)");
    {
	CDKHISTOGRAM *	object;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   lowerCDKObject (vHISTOGRAM, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Histogram_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Histogram::GetWindow(object)");
    {
	CDKHISTOGRAM *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKHISTOGRAMPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not of type CDKHISTOGRAMPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_New)
{
    dXSARGS;
    if (items < 2 || items > 5)
	croak("Usage: Cdk::Menu::New(menulist,menuloc,titleattr=A_REVERSE,subtitleattr=A_REVERSE,menuPos=TOP)");
    {
	SV *	menulist = ST(0);
	SV *	menuloc = ST(1);
	chtype titleattr = sv2chtype (ST(2));
	chtype subtitleattr = sv2chtype (ST(3));
	int menuPos = sv2int (ST(4));
	CDKMENU *	RETVAL;
	{
	   CDKMENU * menuWidget = (CDKMENU *)NULL;
	   char *menuList[MAXMENUITEMS][MAXSUBITEMS];
	   int	subSize[MAXSUBITEMS];
	   int	menuLoc[MAXMENUITEMS];
	   int	menuItems;
	   int 	menulen, loclen;
	   int	x;

	   checkCdkInit();

	   MAKE_CHAR_MATRIX(0,menulist,menuList,subSize,menulen);

	   MAKE_INT_ARRAY (0,menuloc,menuLoc,loclen);

	   if (menulen != loclen)
	   {
	      croak ("Cdk::Menu The menu list and menu location arrays are not the same size.");
	   }

	   RETVAL = newCDKMenu (GCDKSCREEN,menuList,menulen,subSize,menuLoc,menuPos,titleattr,subtitleattr);
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKMENUPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Menu::Activate(object,...)");
    {
	CDKMENU *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKMenu (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKMenu (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Menu::Inject(object,key)");
    {
	CDKMENU *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   RETVAL = injectCDKMenu (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Menu::Bind(object,key,functionRef)");
    {
	CDKMENU *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMENU, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Draw)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Draw(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
        {
           drawCDKMenu (object);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Erase(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   eraseCDKMenu (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Set)
{
    dXSARGS;
    if (items != 5)
	croak("Usage: Cdk::Menu::Set(object,menuitem,submenuitem,titleattr,subtitleattr)");
    {
	CDKMENU *	object;
	int	menuitem = (int)SvIV(ST(1));
	int	submenuitem = (int)SvIV(ST(2));
	chtype titleattr = sv2chtype (ST(3));
	chtype subtitleattr = sv2chtype (ST(4));

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   setCDKMenu(object,menuitem,submenuitem,titleattr,subtitleattr);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Register(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   registerCDKObject (GCDKSCREEN, vMENU, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Unregister(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   unregisterCDKObject (vMENU, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Raise(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   raiseCDKObject (vMENU, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Menu_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Menu::Lower(object)");
    {
	CDKMENU *	object;

	if (sv_isa(ST(0), "CDKMENUPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not of type CDKMENUPtr");
	{
	   lowerCDKObject (vMENU, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_New)
{
    dXSARGS;
    if (items < 4 || items > 13)
	croak("Usage: Cdk::Entry::New(label,min,max,fieldWidth,filler='.',fillattr=A_NORMAL,disptype=vMIXED,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	int	min = (int)SvIV(ST(1));
	int	max = (int)SvIV(ST(2));
	int	fieldWidth = (int)SvIV(ST(3));
	char	filler;
	chtype fillattr = sv2chtype (ST(5));
	EDisplayType disptype = sv2dtype (ST(6));
	int xPos = sv2int (ST(7));
	int yPos = sv2int (ST(8));
	int lPos = sv2int (ST(9));
	chtype fieldattr = sv2chtype (ST(10));
	int Box = sv2int (ST(11));
	int shadow = sv2int (ST(12));
	CDKENTRY *	RETVAL;

	if (items < 5)
	    filler = '.';
	else {
	    filler = (char)*SvPV(ST(4),na);
	}
	{
	   CDKENTRY * entryWidget = (CDKENTRY *)NULL;
	   chtype tempchtype	= filler | fillattr;

	   checkCdkInit();

	   entryWidget = newCDKEntry (GCDKSCREEN,xPos,yPos,lPos,label,fieldattr,tempchtype,disptype,fieldWidth,min,max,Box,shadow);

	   /* Check the return type. */
	   if (entryWidget == (CDKENTRY *)NULL)
	   {
	      croak ("Cdk::Entry Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = entryWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKENTRYPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Entry::Activate(object,...)");
    {
	CDKENTRY *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKEntry (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKEntry (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Entry::Inject(object,key)");
    {
	CDKENTRY *	object;
	chtype key = sv2chtype (ST(1));
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   RETVAL = injectCDKEntry (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Entry::Bind(object,key,functionRef)");
    {
	CDKENTRY *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   SV *function = newSVsv(functionRef);
	   bindCDKObject (vENTRY, object, key, &PerlBindCB, function);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Entry::Draw(object,Box=BOX)");
    {
	CDKENTRY *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   drawCDKEntry (object, Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Erase(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   eraseCDKEntry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Set)
{
    dXSARGS;
    if (items != 5)
	croak("Usage: Cdk::Entry::Set(object,value,min,max,Box)");
    {
	CDKENTRY *	object;
	char *	value = (char *)SvPV(ST(1),na);
	int	min = (int)SvIV(ST(2));
	int	max = (int)SvIV(ST(3));
	int Box = sv2int (ST(4));

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   setCDKEntry (object,value,min,max,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Get)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Get(object)");
    {
	CDKENTRY *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   RETVAL = object->info;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Clean)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Clean(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   cleanCDKEntry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Register(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   registerCDKObject (GCDKSCREEN, vENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Unregister(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   unregisterCDKObject (vENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Raise(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   raiseCDKObject (vENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::Lower(object)");
    {
	CDKENTRY *	object;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   lowerCDKObject (vENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Entry_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Entry::GetWindow(object)");
    {
	CDKENTRY *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKENTRYPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_New)
{
    dXSARGS;
    if (items < 5 || items > 14)
	croak("Usage: Cdk::Mentry::New(label,min,physical,logical,fieldWidth,disptype=vMIXED,filler='.',fillattr=A_NORMAL,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	int	min = (int)SvIV(ST(1));
	int	physical = (int)SvIV(ST(2));
	int	logical = (int)SvIV(ST(3));
	int	fieldWidth = (int)SvIV(ST(4));
	EDisplayType disptype = sv2dtype (ST(5));
	char	filler;
	chtype fillattr = sv2chtype (ST(7));
	int xPos = sv2int (ST(8));
	int yPos = sv2int (ST(9));
	int lPos = sv2int (ST(10));
	chtype fieldattr = sv2chtype (ST(11));
	int Box = sv2int (ST(12));
	int shadow = sv2int (ST(13));
	CDKMENTRY *	RETVAL;

	if (items < 7)
	    filler = '.';
	else {
	    filler = (char)*SvPV(ST(6),na);
	}
	{
	   CDKMENTRY * mentryWidget = (CDKMENTRY *)NULL;
	   chtype tempchtype	= filler | fillattr;

	   checkCdkInit();

	   mentryWidget = newCDKMentry (GCDKSCREEN,xPos,yPos,lPos,label,fieldattr,tempchtype,disptype,fieldWidth,physical,logical,min,Box,shadow);

	   /* Check the return type. */
	   if (mentryWidget == (CDKMENTRY *)NULL)
	   {
	      croak ("Cdk::Mentry Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = mentryWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKMENTRYPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Mentry::Activate(object,...)");
    {
	CDKMENTRY *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKMentry (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKMentry (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Mentry::Inject(object,key)");
    {
	CDKMENTRY *	object;
	chtype key = sv2chtype (ST(1));
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   RETVAL = injectCDKMentry (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Mentry::Bind(object,key,functionRef)");
    {
	CDKMENTRY *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMENTRY, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Mentry::Draw(object,Box=BOX)");
    {
	CDKMENTRY *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
        {
           drawCDKMentry (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Erase(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   eraseCDKMentry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Set)
{
    dXSARGS;
    if (items != 4)
	croak("Usage: Cdk::Mentry::Set(object,value,min,box)");
    {
	CDKMENTRY *	object;
	char *	value = (char *)SvPV(ST(1),na);
	int	min = (int)SvIV(ST(2));
	int box = sv2int (ST(3));

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   setCDKMentry (object,value,min,box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Get)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Get(object)");
    {
	CDKMENTRY *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   RETVAL = object->info;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Clean)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Clean(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   cleanCDKMentry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Register(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   registerCDKObject (GCDKSCREEN, vMENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Unregister(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   unregisterCDKObject (vMENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Raise(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   raiseCDKObject (vMENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::Lower(object)");
    {
	CDKMENTRY *	object;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   lowerCDKObject (vMENTRY, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Mentry_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Mentry::GetWindow(object)");
    {
	CDKMENTRY *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKMENTRYPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not of type CDKMENTRYPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_New)
{
    dXSARGS;
    if (items < 6 || items > 16)
	croak("Usage: Cdk::Matrix::New(rowtitles,coltitles,colwidths,colvalues,vrows,vcols,xPos=CENTER,yPos=CENTER,rowspace=1,colspace=1,filler='.',fillattr=A_NORMAL,dominant=NONE,boxMatrix=FALSE,boxCell=TRUE,shadow=FALSE)");
    {
	SV *	rowtitles = ST(0);
	SV *	coltitles = ST(1);
	SV *	colwidths = ST(2);
	SV *	colvalues = ST(3);
	int	vrows = (int)SvIV(ST(4));
	int	vcols = (int)SvIV(ST(5));
	int xPos = sv2int (ST(6));
	int yPos = sv2int (ST(7));
	int	rowspace;
	int	colspace;
	char	filler;
	chtype fillattr = sv2chtype (ST(11));
	int dominant = sv2int (ST(12));
	int boxMatrix = sv2int (ST(13));
	int boxCell = sv2int (ST(14));
	int shadow = sv2int (ST(15));
	CDKMATRIX *	RETVAL;

	if (items < 9)
	    rowspace = 1;
	else {
	    rowspace = (int)SvIV(ST(8));
	}

	if (items < 10)
	    colspace = 1;
	else {
	    colspace = (int)SvIV(ST(9));
	}

	if (items < 11)
	    filler = '.';
	else {
	    filler = (char)*SvPV(ST(10),na);
	}
	{
	   CDKMATRIX * matrixWidget = (CDKMATRIX *)NULL;
	   char	*colTitles[MAXMATRIXCOLS+1];
	   char *rowTitles[MAXMATRIXROWS+1];
	   int	colWidths[MAXMATRIXCOLS+1];
	   int	colValues[MAXMATRIXCOLS+1];
	   int	rows, cols, widths, dtype, x;
	   chtype tempchtype	= filler | fillattr;

	   checkCdkInit();

	   /* Make the arrays.					*/
	   MAKE_CHAR_ARRAY (1,rowtitles,rowTitles,rows);
	   MAKE_CHAR_ARRAY (1,coltitles,colTitles,cols);
	   MAKE_INT_ARRAY (1,colwidths,colWidths,widths);
	   MAKE_DTYPE_ARRAY (1,colvalues,colValues,dtype);


	   /* Now check them...					*/
	   if (cols != widths)
	   {
	      croak ("Cdk::Matrix The col title array size is not the same as the widths array size.");
	   }
	   if (cols != dtype)
	   {
	      croak ("Cdk::Matrix The col title array size is not the same as the column value array size.");
	   }
	   if (vrows > rows || vcols > cols)
	   {
	      croak ("Cdk::Matrix The virtual matrix size is larger then the physical size.");
	   }

	   /* OK, everything is ok. Lets make the matrix.	*/
	   matrixWidget = newCDKMatrix (GCDKSCREEN,
						xPos, yPos,
						rows, cols, vrows, vcols,
						rowTitles, 
						colTitles,
						colWidths, colValues,
						rowspace, colspace, tempchtype,
						dominant,
						boxMatrix, boxCell, shadow);

	   /* Check the return type. */
	   if (matrixWidget == (CDKMATRIX *)NULL)
	   {
	      croak ("Cdk::Matrix Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = matrixWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKMATRIXPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Activate)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Activate(object)");
    SP -= items;
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   AV *cellInfo	= newAV();
	   char *	info[MAXMATRIXROWS][MAXMATRIXCOLS];
	   int		subSize[MAXMATRIXROWS];
	   int x, y, matrixlen;

	   /* Call the Cdk function.	*/
	   activateCDKMatrix(object, NULL);

	   /* Take the info from the matrix and make an array out of it. */
	   for (x=1; x <= object->rows; x++)
	   {
	      AV * av	= newAV();

	      for (y=1; y <= object->cols; y++)
	      {
	         av_push (av, newSVpv (object->info[x][y], strlen (object->info[x][y])));
	      }

	      av_push (cellInfo, newRV((SV *)av));
	   }

	   /* Push the values on the return stack.	*/
	   XPUSHs (sv_2mortal(newSViv(object->rows)));
	   XPUSHs (sv_2mortal(newSViv(object->cols)));
	   XPUSHs (sv_2mortal(newRV((SV*)cellInfo)));
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Matrix_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Matrix::Inject(object,key)");
    {
	CDKMATRIX *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   RETVAL = injectCDKMatrix (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Matrix::Bind(object,key,functionRef)");
    {
	CDKMATRIX *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMATRIX, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_GetDim)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::GetDim(object)");
    SP -= items;
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   XPUSHs (sv_2mortal(newSViv(object->rows)));
	   XPUSHs (sv_2mortal(newSViv(object->cols)));
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Matrix_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Matrix::Draw(object,Box=BOX)");
    {
	CDKMATRIX *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
        {
           drawCDKMatrix (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Erase(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   eraseCDKMatrix (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Set)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Matrix::Set(object,info)");
    {
	CDKMATRIX *	object;
	SV *	info = ST(1);

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   char *	Info[MAXMATRIXROWS][MAXMATRIXCOLS];
	   int		subSize[MAXMATRIXROWS];
	   int		matrixlen;

	   MAKE_CHAR_MATRIX (1,info,Info,subSize,matrixlen);

	   setCDKMatrix (object,Info,matrixlen,subSize);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Clean)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Clean(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   cleanCDKMatrix (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Raise(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   raiseCDKObject (vMATRIX, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Lower(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   lowerCDKObject (vMATRIX, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::GetWindow(object)");
    {
	CDKMATRIX *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Register(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   registerCDKObject (GCDKSCREEN, vMATRIX, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Matrix_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Matrix::Unregister(object)");
    {
	CDKMATRIX *	object;

	if (sv_isa(ST(0), "CDKMATRIXPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not of type CDKMATRIXPtr");
	{
	   unregisterCDKObject (vMATRIX, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_New)
{
    dXSARGS;
    if (items < 1 || items > 4)
	croak("Usage: Cdk::Marquee::New(width,xPos=CENTER,yPos=CENTER,shadow=FALSE)");
    {
	int	width = (int)SvIV(ST(0));
	int xPos = sv2int (ST(1));
	int yPos = sv2int (ST(2));
	int shadow = sv2int (ST(3));
	CDKMARQUEE *	RETVAL;
	{
	   CDKMARQUEE * marqueeWidget = (CDKMARQUEE *)NULL;

	   checkCdkInit();

	   marqueeWidget = newCDKMarquee (GCDKSCREEN,xPos,yPos,width,shadow);

	   /* Check the return type. */
	   if (marqueeWidget == (CDKMARQUEE *)NULL)
	   {
	      croak ("Cdk::Marquee Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = marqueeWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKMARQUEEPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Activate)
{
    dXSARGS;
    if (items < 4 || items > 5)
	croak("Usage: Cdk::Marquee::Activate(marquee,message,delay,repeat,Box=TRUE)");
    {
	CDKMARQUEE *	marquee;
	char *	message = (char *)SvPV(ST(1),na);
	int	delay = (int)SvIV(ST(2));
	int	repeat = (int)SvIV(ST(3));
	int Box = sv2int (ST(4));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    marquee = (CDKMARQUEE *) tmp;
	}
	else
	    croak("marquee is not of type CDKMARQUEEPtr");
	{
	   RETVAL = activateCDKMarquee (marquee,message,delay,repeat,Box);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Marquee::Bind(object,key,functionRef)");
    {
	CDKMARQUEE *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMARQUEE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Marquee::Draw(object,Box=BOX)");
    {
	CDKMARQUEE *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
        {
           drawCDKMarquee (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::Erase(object)");
    {
	CDKMARQUEE *	object;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   eraseCDKMarquee (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::Register(object)");
    {
	CDKMARQUEE *	object;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   registerCDKObject (GCDKSCREEN, vMARQUEE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::Unregister(object)");
    {
	CDKMARQUEE *	object;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   unregisterCDKObject (vMARQUEE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::Raise(object)");
    {
	CDKMARQUEE *	object;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   raiseCDKObject (vMARQUEE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::Lower(object)");
    {
	CDKMARQUEE *	object;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   lowerCDKObject (vMARQUEE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Marquee_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Marquee::GetWindow(object)");
    {
	CDKMARQUEE *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKMARQUEEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not of type CDKMARQUEEPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_New)
{
    dXSARGS;
    if (items < 5 || items > 10)
	croak("Usage: Cdk::Selection::New(title,list,choices,height,width,xPos=CENTER,yPos=CENTER,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)");
    {
	char *	title = (char *)SvPV(ST(0),na);
	SV *	list = ST(1);
	SV *	choices = ST(2);
	int	height = (int)SvIV(ST(3));
	int	width = (int)SvIV(ST(4));
	int xPos = sv2int (ST(5));
	int yPos = sv2int (ST(6));
	chtype highlight = sv2chtype (ST(7));
	int Box = sv2int (ST(8));
	int shadow = sv2int (ST(9));
	CDKSELECTION *	RETVAL;
	{
	   CDKSELECTION * selectionWidget = (CDKSELECTION *)NULL;
	   char *List[MAXITEMS], *Choices[MAXITEMS];
	   int listSize, choiceSize;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY(0,list,List,listSize);
	   MAKE_CHAR_ARRAY(0,choices,Choices,choiceSize);

	   selectionWidget = newCDKSelection (GCDKSCREEN,xPos,yPos,height,width,title,List,listSize,Choices,choiceSize,highlight,Box,shadow);

	   /* Check the return type. */
	   if (selectionWidget == (CDKSELECTION *)NULL)
	   {
	      croak ("Cdk::Selection Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = selectionWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSELECTIONPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Selection::Activate(object,...)");
    SP -= items;
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   chtype Keys[300];
	   int arrayLen, exitValue;
	   int x	= 0;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      exitValue = activateCDKSelection (object, Keys);
	   }
	   else
	   {
	      exitValue = activateCDKSelection (object, NULL);
	   }

	   /* If the exit vaLue is < 0 then return.	*/
	   if (exitValue == -1)
  	   {
	      return;
	   }

	   /* Push the values on the return stack.	*/
	   for (x=0; x < object->listSize ; x++)
	   {
	      XPUSHs (sv_2mortal(newSViv(object->selections[x])));
	   }
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Selection_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Selection::Inject(object,key)");
    {
	CDKSELECTION *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   RETVAL = injectCDKSelection (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Selection::Bind(object,key,functionRef)");
    {
	CDKSELECTION *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSELECTION, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Selection::Draw(object,Box=BOX)");
    {
	CDKSELECTION *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
        {
           drawCDKSelection (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::Erase(object)");
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   eraseCDKSelection (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Set)
{
    dXSARGS;
    if (items != 4)
	croak("Usage: Cdk::Selection::Set(object,defaultList,highlight,Box)");
    {
	CDKSELECTION *	object;
	SV *	defaultList = ST(1);
	chtype highlight = sv2chtype (ST(2));
	int Box = sv2int (ST(3));

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   int defaultChoices[MAXCHOICES];
	   int choicelen;

	   MAKE_INT_ARRAY (0,defaultList,defaultChoices,choicelen);

	   setCDKSelection (object,highlight,defaultChoices,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::Register(object)");
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   registerCDKObject (GCDKSCREEN, vSELECTION, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::Unregister(object)");
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   unregisterCDKObject (vSELECTION, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::Raise(object)");
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   raiseCDKObject (vSELECTION, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::Lower(object)");
    {
	CDKSELECTION *	object;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   lowerCDKObject (vSELECTION, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Selection_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Selection::GetWindow(object)");
    {
	CDKSELECTION *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKSELECTIONPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not of type CDKSELECTIONPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_New)
{
    dXSARGS;
    if (items < 3 || items > 8)
	croak("Usage: Cdk::Viewer::New(buttons,height,width,buttonHighlight=A_REVERSE,xpos=CENTER,ypos=CENTER,Box=TRUE,shadow=FALSE)");
    {
	SV *	buttons = ST(0);
	int	height = (int)SvIV(ST(1));
	int	width = (int)SvIV(ST(2));
	chtype buttonHighlight = sv2chtype (ST(3));
	int xpos = sv2int (ST(4));
	int ypos = sv2int (ST(5));
	int Box = sv2int (ST(6));
	int shadow = sv2int (ST(7));
	CDKVIEWER *	RETVAL;
	{
	   CDKVIEWER * viewerWidget = (CDKVIEWER *)NULL;
	   char *Buttons[MAXBUTTONS];
	   int buttonCount;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY (0,buttons,Buttons,buttonCount);

	   viewerWidget = newCDKViewer (GCDKSCREEN,xpos,ypos,height,width,Buttons,buttonCount,buttonHighlight,Box,shadow);

	   /* Check the return type. */
	   if (viewerWidget == (CDKVIEWER *)NULL)
	   {
	      croak ("Cdk::Viewer Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = viewerWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKVIEWERPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Activate)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Activate(object)");
    {
	CDKVIEWER *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   RETVAL = activateCDKViewer (object);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Set)
{
    dXSARGS;
    if (items < 3 || items > 6)
	croak("Usage: Cdk::Viewer::Set(object,title,info,buttonHighlight=A_REVERSE,attrInterp=TRUE,Box=BOX)");
    {
	CDKVIEWER *	object;
	char *	title = (char *)SvPV(ST(1),na);
	SV *	info = ST(2);
	chtype buttonHighlight = sv2chtype (ST(3));
	int attrInterp = sv2int (ST(4));
	int Box = sv2int (ST(5));

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   char *Info[MAXLINES];
	   int infolen;

	   MAKE_CHAR_ARRAY(0,info, Info, infolen);
           Info[infolen] = "";

	   setCDKViewer (object,title,Info,infolen,buttonHighlight,attrInterp,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Viewer::Bind(object,key,functionRef)");
    {
	CDKVIEWER *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vVIEWER, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Viewer::Draw(object,Box=BOX)");
    {
	CDKVIEWER *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
        {
           drawCDKViewer (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Erase(object)");
    {
	CDKVIEWER *	object;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   eraseCDKViewer (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Register(object)");
    {
	CDKVIEWER *	object;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   registerCDKObject (GCDKSCREEN, vVIEWER, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Unregister(object)");
    {
	CDKVIEWER *	object;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   unregisterCDKObject (vVIEWER, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Raise(object)");
    {
	CDKVIEWER *	object;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   raiseCDKObject (vVIEWER, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::Lower(object)");
    {
	CDKVIEWER *	object;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   lowerCDKObject (vVIEWER, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Viewer_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Viewer::GetWindow(object)");
    {
	CDKVIEWER *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKVIEWERPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not of type CDKVIEWERPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_New)
{
    dXSARGS;
    if (items < 5 || items > 7)
	croak("Usage: Cdk::Graph::New(title,xtitle,ytitle,height,width,xpos=CENTER,ypos=CENTER)");
    {
	char *	title = (char *)SvPV(ST(0),na);
	char *	xtitle = (char *)SvPV(ST(1),na);
	char *	ytitle = (char *)SvPV(ST(2),na);
	int	height = (int)SvIV(ST(3));
	int	width = (int)SvIV(ST(4));
	int xpos = sv2int (ST(5));
	int ypos = sv2int (ST(6));
	CDKGRAPH *	RETVAL;
	{
	   CDKGRAPH * graphWidget = (CDKGRAPH *)NULL;

	   graphWidget = newCDKGraph (GCDKSCREEN,xpos,ypos,height,width,title,xtitle,ytitle);

	   /* Check the return type. */
	   if (graphWidget == (CDKGRAPH *)NULL)
	   {
	      croak ("Cdk::Graph Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = graphWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKGRAPHPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Set)
{
    dXSARGS;
    if (items < 3 || items > 5)
	croak("Usage: Cdk::Graph::Set(object,values,graphchar,startAtZero=TRUE,pType=\"LINE\")");
    {
	CDKGRAPH *	object;
	SV *	values = ST(1);
	char *	graphchar = (char *)SvPV(ST(2),na);
	int startAtZero = sv2int (ST(3));
	char *	pType;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");

	if (items < 5)
	    pType = "LINE";
	else {
	    pType = (char *)SvPV(ST(4),na);
	}
	{
	   EGraphDisplayType plotType = vLINE;
           int 	Values[MAXLINES];
           int 	valueCount;

	   MAKE_INT_ARRAY (0,values,Values,valueCount);
           valueCount--;

	   /* Check the plot type.		*/
	   if (strEQ (pType, "PLOT"))
	      plotType = vPLOT;

           RETVAL = setCDKGraph (object,Values,valueCount,graphchar,startAtZero,plotType);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Graph::Draw(object,Box=BOX)");
    {
	CDKGRAPH *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
        {
           drawCDKGraph (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::Erase(object)");
    {
	CDKGRAPH *	object;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   eraseCDKGraph (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::Register(object)");
    {
	CDKGRAPH *	object;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   registerCDKObject (GCDKSCREEN, vGRAPH, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::Unregister(object)");
    {
	CDKGRAPH *	object;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   unregisterCDKObject (vGRAPH, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::Raise(object)");
    {
	CDKGRAPH *	object;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   raiseCDKObject (vGRAPH, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::Lower(object)");
    {
	CDKGRAPH *	object;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   lowerCDKObject (vGRAPH, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Graph_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Graph::GetWindow(object)");
    {
	CDKGRAPH *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKGRAPHPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not of type CDKGRAPHPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_New)
{
    dXSARGS;
    if (items < 4 || items > 12)
	croak("Usage: Cdk::Radio::New(title,list,height,width,xpos=CENTER,ypos=CENTER,choiceChar='X',choiceattr=A_NORMAL,defaultItem=0,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)");
    {
	char *	title = (char *)SvPV(ST(0),na);
	SV *	list = ST(1);
	int	height = (int)SvIV(ST(2));
	int	width = (int)SvIV(ST(3));
	int xpos = sv2int (ST(4));
	int ypos = sv2int (ST(5));
	char	choiceChar;
	chtype choiceattr = sv2chtype (ST(7));
	int	defaultItem;
	chtype highlight = sv2chtype (ST(9));
	int Box = sv2int (ST(10));
	int shadow = sv2int (ST(11));
	CDKRADIO *	RETVAL;

	if (items < 7)
	    choiceChar = 'X';
	else {
	    choiceChar = (char)*SvPV(ST(6),na);
	}

	if (items < 9)
	    defaultItem = 0;
	else {
	    defaultItem = (int)SvIV(ST(8));
	}
	{
	   CDKRADIO * radioWidget = (CDKRADIO *)NULL;
	   chtype tempchtype = choiceChar | choiceattr;
	   char *List[MAXITEMS];
	   int listlen;

	   MAKE_CHAR_ARRAY(0,list,List,listlen);
           List[listlen] = "";

	   radioWidget = newCDKRadio (GCDKSCREEN,xpos,ypos,height,width,title,List,listlen,tempchtype,defaultItem,highlight,Box,shadow);

	   /* Check the return type. */
	   if (radioWidget == (CDKRADIO *)NULL)
	   {
	      croak ("Cdk::Radio Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = radioWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKRADIOPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Radio::Activate(object,...)");
    {
	CDKRADIO *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKRadio (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKRadio (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Radio::Inject(object,key)");
    {
	CDKRADIO *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   RETVAL = injectCDKRadio (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Radio::Bind(object,key,functionRef)");
    {
	CDKRADIO *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vRADIO, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Radio::Draw(object,Box=BOX)");
    {
	CDKRADIO *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
        {
           drawCDKRadio (object,Box);
        }
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::Erase(object)");
    {
	CDKRADIO *	object;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   eraseCDKRadio (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Set)
{
    dXSARGS;
    if (items < 4 || items > 5)
	croak("Usage: Cdk::Radio::Set(object,highlight,choicechar,choiceattr,Box=TRUE)");
    {
	CDKRADIO *	object;
	chtype highlight = sv2chtype (ST(1));
	char	choicechar = (char)*SvPV(ST(2),na);
	chtype choiceattr = sv2chtype (ST(3));
	int Box = sv2int (ST(4));

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   chtype tempchtype	= choicechar | choiceattr;

	   setCDKRadio (object,highlight,tempchtype,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::Register(object)");
    {
	CDKRADIO *	object;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   registerCDKObject (GCDKSCREEN, vRADIO, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::Unregister(object)");
    {
	CDKRADIO *	object;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   unregisterCDKObject (vRADIO, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::Raise(object)");
    {
	CDKRADIO *	object;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   raiseCDKObject (vRADIO, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::Lower(object)");
    {
	CDKRADIO *	object;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   lowerCDKObject (vRADIO, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Radio_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Radio::GetWindow(object)");
    {
	CDKRADIO *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKRADIOPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not of type CDKRADIOPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_New)
{
    dXSARGS;
    if (items < 3 || items > 8)
	croak("Usage: Cdk::Template::New(label,plate,overlay,xpos=CENTER,ypos=CENTER,lpos=LEFT,Box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	char *	plate = (char *)SvPV(ST(1),na);
	char *	overlay = (char *)SvPV(ST(2),na);
	int xpos = sv2int (ST(3));
	int ypos = sv2int (ST(4));
	int lpos = sv2int (ST(5));
	int Box = sv2int (ST(6));
	int shadow = sv2int (ST(7));
	CDKTEMPLATE *	RETVAL;
	{
	   CDKTEMPLATE * templateWidget = (CDKTEMPLATE *)NULL;

	   checkCdkInit();

	   templateWidget = newCDKTemplate (GCDKSCREEN,xpos,ypos,lpos,label,plate,overlay,Box,shadow);

	   /* Check the return type. */
	   if (templateWidget == (CDKTEMPLATE *)NULL)
	   {
	      croak ("Cdk::Template Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = templateWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKTEMPLATEPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Template::Activate(object,...)");
    {
	CDKTEMPLATE *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKTemplate (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKTemplate (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Template::Inject(object,key)");
    {
	CDKTEMPLATE *	object;
	chtype key = sv2chtype (ST(1));
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   RETVAL = injectCDKTemplate (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Template::Bind(object,key,functionRef)");
    {
	CDKTEMPLATE *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vTEMPLATE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Mix)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Mix(object)");
    {
	CDKTEMPLATE *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   RETVAL = mixCDKTemplate (object);
	}
	ST(0) = sv_newmortal();
	sv_setpv((SV*)ST(0), RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Template::Draw(object,Box=BOX)");
    {
	CDKTEMPLATE *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   drawCDKTemplate (object, Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Erase(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   eraseCDKTemplate (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Set)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Template::Set(object,value,box)");
    {
	CDKTEMPLATE *	object;
	char *	value = (char *)SvPV(ST(1),na);
	int box = sv2int (ST(2));

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   setCDKTemplate (object,value,box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Get)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Get(object)");
    {
	CDKTEMPLATE *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   RETVAL = object->info;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Clean)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Clean(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   cleanCDKTemplate (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Register(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   registerCDKObject (GCDKSCREEN, vTEMPLATE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Unregister(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   unregisterCDKObject (vTEMPLATE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Raise(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   raiseCDKObject (vTEMPLATE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::Lower(object)");
    {
	CDKTEMPLATE *	object;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   lowerCDKObject (vTEMPLATE, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Template_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Template::GetWindow(object)");
    {
	CDKTEMPLATE *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKTEMPLATEPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not of type CDKTEMPLATEPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_New)
{
    dXSARGS;
    if (items < 4 || items > 8)
	croak("Usage: Cdk::Swindow::New(title,savelines,height,width,xpos=CENTER,ypos=CENTER,box=TRUE,shadow=FALSE)");
    {
	char *	title = (char *)SvPV(ST(0),na);
	int	savelines = (int)SvIV(ST(1));
	int	height = (int)SvIV(ST(2));
	int	width = (int)SvIV(ST(3));
	int xpos = sv2int (ST(4));
	int ypos = sv2int (ST(5));
	int box = sv2int (ST(6));
	int shadow = sv2int (ST(7));
	CDKSWINDOW *	RETVAL;
	{
	   CDKSWINDOW * swindowWidget = (CDKSWINDOW *)NULL;

	   swindowWidget = newCDKSwindow (GCDKSCREEN,xpos,ypos,height,width,title,savelines,box,shadow);

	   /* Check the return type. */
	   if (swindowWidget == (CDKSWINDOW *)NULL)
	   {
	      croak ("Cdk::Swindow Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = swindowWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKSWINDOWPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Swindow::Activate(object,...)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      activateCDKSwindow (object, Keys);
	   }
	   else
	   {
	      activateCDKSwindow (object, NULL);
	   }
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Swindow::Inject(object,key)");
    {
	CDKSWINDOW *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   RETVAL = injectCDKSwindow (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Swindow::Bind(object,key,functionRef)");
    {
	CDKSWINDOW *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSWINDOW, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Set)
{
    dXSARGS;
    if (items != 4)
	croak("Usage: Cdk::Swindow::Set(object,info,lines,box)");
    {
	CDKSWINDOW *	object;
	SV *	info = ST(1);
	int	lines = (int)SvIV(ST(2));
	int box = sv2int (ST(3));

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   char *Loginfo[MAXITEMS];
	   int infolen;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY(0,info,Loginfo,infolen);
	   Loginfo[infolen] = "";

	   setCDKSwindow (object, Loginfo, infolen, box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Addline)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Swindow::Addline(object,info,insertpos)");
    {
	CDKSWINDOW *	object;
	char *	info = (char *)SvPV(ST(1),na);
	int insertpos = sv2int (ST(2));

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   addCDKSwindow (object, info, insertpos);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Trim)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Swindow::Trim(object,start,finish)");
    {
	CDKSWINDOW *	object;
	int start = sv2int (ST(1));
	int finish = sv2int (ST(2));

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   trimCDKSwindow (object, start, finish);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Exec)
{
    dXSARGS;
    if (items < 2 || items > 3)
	croak("Usage: Cdk::Swindow::Exec(object,command,insertPos=BOTTOM)");
    {
	CDKSWINDOW *	object;
	char *	command = (char *)SvPV(ST(1),na);
	int insertPos = sv2int (ST(2));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   RETVAL = execCDKSwindow (object, command, insertPos);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Get)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Get(object)");
    SP -= items;
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   int x;
	   char *temp;

           /* Push each item onto the stack.		*/
	   for (x=0; x < object->itemCount ; x++)
	   {
	      /* We need to convert from chtype to char	*/
	      temp = chtype2Char (object->info[x]);

              /* Push it on the stack.			*/
	      XPUSHs (sv_2mortal(newSVpv(temp, strlen(temp))));
	      freeChar (temp);
	   }
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Swindow_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Swindow::Draw(object,Box=BOX)");
    {
	CDKSWINDOW *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   drawCDKSwindow (object, Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Erase(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   eraseCDKSwindow (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Clean)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Clean(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   cleanCDKSwindow (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Register(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   registerCDKObject (GCDKSCREEN, vSWINDOW, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Unregister(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   unregisterCDKObject (vSWINDOW, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Raise(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   raiseCDKObject (vSWINDOW, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::Lower(object)");
    {
	CDKSWINDOW *	object;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   lowerCDKObject (vSWINDOW, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Swindow_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Swindow::GetWindow(object)");
    {
	CDKSWINDOW *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKSWINDOWPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not of type CDKSWINDOWPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_New)
{
    dXSARGS;
    if (items < 2 || items > 8)
	croak("Usage: Cdk::Itemlist::New(label,itemlist,defaultItem=0,xpos=CENTER,ypos=CENTER,lpos=LEFT,box=TRUE,shadow=FALSE)");
    {
	char *	label = (char *)SvPV(ST(0),na);
	SV *	itemlist = ST(1);
	int	defaultItem;
	int xpos = sv2int (ST(3));
	int ypos = sv2int (ST(4));
	int lpos = sv2int (ST(5));
	int box = sv2int (ST(6));
	int shadow = sv2int (ST(7));
	CDKITEMLIST *	RETVAL;

	if (items < 3)
	    defaultItem = 0;
	else {
	    defaultItem = (int)SvIV(ST(2));
	}
	{
	   CDKITEMLIST * itemlistWidget = (CDKITEMLIST *)NULL;
	   char *       Itemlist[MAXLABELROWS];
	   int          itemLength;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY (0,itemlist,Itemlist,itemLength);

	   itemlistWidget = newCDKItemlist (GCDKSCREEN,xpos,ypos,lpos,label,Itemlist,itemLength,defaultItem,box,shadow);

	   /* Check the return type. */
	   if (itemlistWidget == (CDKITEMLIST *)NULL)
	   {
	      croak ("Cdk::Itemlist Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = itemlistWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKITEMLISTPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Activate)
{
    dXSARGS;
    if (items < 1)
	croak("Usage: Cdk::Itemlist::Activate(object,...)");
    {
	CDKITEMLIST *	object;
	int	RETVAL;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   chtype Keys[300];
	   int arrayLen;

	   if (items > 1)
	   {
	      MAKE_CHTYPE_ARRAY(0,ST(1),Keys,arrayLen);
	      RETVAL = activateCDKItemlist (object, Keys);
	   }
	   else
	   {
	      RETVAL = activateCDKItemlist (object, NULL);
	   }
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Inject)
{
    dXSARGS;
    if (items != 2)
	croak("Usage: Cdk::Itemlist::Inject(object,key)");
    {
	CDKITEMLIST *	object;
	chtype key = sv2chtype (ST(1));
	int	RETVAL;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   RETVAL = injectCDKItemlist (object,key);
	}
	ST(0) = sv_newmortal();
	sv_setiv(ST(0), (IV)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Itemlist::Bind(object,key,functionRef)");
    {
	CDKITEMLIST *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vITEMLIST, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Set)
{
    dXSARGS;
    if (items != 4)
	croak("Usage: Cdk::Itemlist::Set(object,info,defaultItem,box)");
    {
	CDKITEMLIST *	object;
	SV *	info = ST(1);
	int	defaultItem = (int)SvIV(ST(2));
	int box = sv2int (ST(3));

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   char *infoList[MAXITEMS];
	   int infolen;

	   checkCdkInit();

	   MAKE_CHAR_ARRAY(0,info,infoList,infolen);

	   setCDKItemlist (object,infoList,infolen,defaultItem,box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Get)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Get(object)");
    {
	CDKITEMLIST *	object;
	char *	RETVAL;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   RETVAL = chtype2Char (object->item[object->currentItem]);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Itemlist::Draw(object,Box=BOX)");
    {
	CDKITEMLIST *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   drawCDKItemlist (object,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Erase(object)");
    {
	CDKITEMLIST *	object;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   eraseCDKItemlist (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Register(object)");
    {
	CDKITEMLIST *	object;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   registerCDKObject (GCDKSCREEN,vITEMLIST,object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Unregister(object)");
    {
	CDKITEMLIST *	object;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   unregisterCDKObject (vITEMLIST, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Raise(object)");
    {
	CDKITEMLIST *	object;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   raiseCDKObject (vITEMLIST, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::Lower(object)");
    {
	CDKITEMLIST *	object;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   lowerCDKObject (vITEMLIST, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Itemlist_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Itemlist::GetWindow(object)");
    {
	CDKITEMLIST *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKITEMLISTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not of type CDKITEMLISTPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_New)
{
    dXSARGS;
    if (items < 2 || items > 14)
	croak("Usage: Cdk::Fselect::New(height,width,dAttrib=\"</N>\",fAttrib=\"</N>\",lAttrib=\"</N>\",sAttrib=\"</N>\",highlight=A_REVERSE,fieldAttribute=A_NORMAL,fillerChar='.',fillerAttr=A_NORMAL,xPos=CENTER,yPos=CENTER,box=TRUE,shadow=FALSE)");
    {
	int	height = (int)SvIV(ST(0));
	int	width = (int)SvIV(ST(1));
	char *	dAttrib;
	char *	fAttrib;
	char *	lAttrib;
	char *	sAttrib;
	chtype highlight = sv2chtype (ST(6));
	chtype fieldAttribute = sv2chtype (ST(7));
	char	fillerChar;
	chtype fillerAttr = sv2chtype (ST(9));
	int xPos = sv2int (ST(10));
	int yPos = sv2int (ST(11));
	int box = sv2int (ST(12));
	int shadow = sv2int (ST(13));
	CDKFSELECT *	RETVAL;

	if (items < 3)
	    dAttrib = "</N>";
	else {
	    dAttrib = (char *)SvPV(ST(2),na);
	}

	if (items < 4)
	    fAttrib = "</N>";
	else {
	    fAttrib = (char *)SvPV(ST(3),na);
	}

	if (items < 5)
	    lAttrib = "</N>";
	else {
	    lAttrib = (char *)SvPV(ST(4),na);
	}

	if (items < 6)
	    sAttrib = "</N>";
	else {
	    sAttrib = (char *)SvPV(ST(5),na);
	}

	if (items < 9)
	    fillerChar = '.';
	else {
	    fillerChar = (char)*SvPV(ST(8),na);
	}
	{
	   CDKFSELECT * fselectWidget = (CDKFSELECT *)NULL;
	   chtype tempChtype = fillerChar | fillerAttr;

	   checkCdkInit();

	   fselectWidget = newCDKFselect (GCDKSCREEN,xPos,yPos,
						height,width,
						fieldAttribute,tempChtype,highlight,
						dAttrib,fAttrib,lAttrib,sAttrib,
						box,shadow);

	   /* Check the return type. */
	   if (fselectWidget == (CDKFSELECT *)NULL)
	   {
	      croak ("Cdk::Fselect Could not create widget. Is the window too small?\n");
	   }
	   else
	   {
	      RETVAL = fselectWidget;
	   }
	}
	ST(0) = sv_newmortal();
	sv_setref_pv(ST(0), "CDKFSELECTPtr", (void*)RETVAL);
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Activate)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Activate(object)");
    SP -= items;
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   SV *sv = (SV *)&sv_undef;
	   char *filename;

	   drawCDKFselect (object, object->box);

	   filename = activateCDKFselect (object);
	   if (filename != (char *)NULL)
	   {
	      sv = newSVpv (filename, strlen (filename));
 	   }
	   XPUSHs (sv);
	}
	PUTBACK;
	return;
    }
}

XS(XS_Cdk__Fselect_Set)
{
    dXSARGS;
    if (items < 2 || items > 10)
	croak("Usage: Cdk::Fselect::Set(object,directory,dAttrib=\"</N>\",fAttrib=\"</N>\",lAttrib=\"</N>\",sAttrib=\"</N>\",highlight=A_REVERSE,fieldAttribute=A_NORMAL,fillerChar='.',box=TRUE)");
    {
	CDKFSELECT*	object;
	char *	directory = (char *)SvPV(ST(1),na);
	char *	dAttrib;
	char *	fAttrib;
	char *	lAttrib;
	char *	sAttrib;
	chtype highlight = sv2chtype (ST(6));
	chtype fieldAttribute = sv2chtype (ST(7));
	chtype fillerChar = sv2chtype (ST(8));
	int box = sv2int (ST(9));

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");

	if (items < 3)
	    dAttrib = "</N>";
	else {
	    dAttrib = (char *)SvPV(ST(2),na);
	}

	if (items < 4)
	    fAttrib = "</N>";
	else {
	    fAttrib = (char *)SvPV(ST(3),na);
	}

	if (items < 5)
	    lAttrib = "</N>";
	else {
	    lAttrib = (char *)SvPV(ST(4),na);
	}

	if (items < 6)
	    sAttrib = "</N>";
	else {
	    sAttrib = (char *)SvPV(ST(5),na);
	}
	{
	   setCDKFselect (object,directory,
				fieldAttribute,fillerChar,highlight,
				dAttrib,fAttrib,lAttrib,sAttrib,
				box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Bind)
{
    dXSARGS;
    if (items != 3)
	croak("Usage: Cdk::Fselect::Bind(object,key,functionRef)");
    {
	CDKFSELECT *	object;
	chtype key = sv2chtype (ST(1));
	SV *	functionRef = ST(2);

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vFSELECT, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Draw)
{
    dXSARGS;
    if (items < 1 || items > 2)
	croak("Usage: Cdk::Fselect::Draw(object,Box=BOX)");
    {
	CDKFSELECT *	object;
	int Box = sv2int (ST(1));

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   drawCDKFselect (object,Box);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Erase)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Erase(object)");
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   eraseCDKFselect (object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Register)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Register(object)");
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   registerCDKObject (GCDKSCREEN,vFSELECT,object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Unregister)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Unregister(object)");
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   unregisterCDKObject (vFSELECT, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Raise)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Raise(object)");
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   raiseCDKObject (vFSELECT, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_Lower)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::Lower(object)");
    {
	CDKFSELECT *	object;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   lowerCDKObject (vFSELECT, object);
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Fselect_GetWindow)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Fselect::GetWindow(object)");
    {
	CDKFSELECT *	object;
	WINDOW *	RETVAL;

	if (sv_isa(ST(0), "CDKFSELECTPtr")) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not of type CDKFSELECTPtr");
	{
	   RETVAL = object->win;
	}
    }
    XSRETURN(1);
}

XS(XS_Cdk__Diag_DumpScreenRegList)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: Cdk::Diag::DumpScreenRegList(mesg)");
    {
	char *	mesg = (char *)SvPV(ST(0),na);
	{
	   debugCDKScreen (GCDKSCREEN, mesg);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKLABELPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKLABELPtr::DESTROY(object)");
    {
	CDKLABEL *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKLABEL *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKLabel (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKDIALOGPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKDIALOGPtr::DESTROY(object)");
    {
	CDKDIALOG *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKDIALOG *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKDialog (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKENTRYPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKENTRYPtr::DESTROY(object)");
    {
	CDKENTRY *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKENTRY *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   int x=0;

	   /* Clear out the bindings.					*/
	   for (x=0; x < MAXBINDINGS; x++)
	   {
	      if (object->bindFunction[x] != (void *)NULL)
	      {
	         SvREFCNT_dec ((SV *)object->bindData);
	      }
	   }

	   /* Now we can destroy the object.				*/
	   destroyCDKEntry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKSCROLLPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKSCROLLPtr::DESTROY(object)");
    {
	CDKSCROLL *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCROLL *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKScroll (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKSCALEPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKSCALEPtr::DESTROY(object)");
    {
	CDKSCALE *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSCALE *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKScale (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKHISTOGRAMPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKHISTOGRAMPtr::DESTROY(object)");
    {
	CDKHISTOGRAM *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKHISTOGRAM *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKHistogram (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKMENUPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKMENUPtr::DESTROY(object)");
    {
	CDKMENU *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENU *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKMenu (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKMENTRYPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKMENTRYPtr::DESTROY(object)");
    {
	CDKMENTRY *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMENTRY *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKMentry (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKMATRIXPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKMATRIXPtr::DESTROY(object)");
    {
	CDKMATRIX *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMATRIX *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKMatrix (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKMARQUEEPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKMARQUEEPtr::DESTROY(object)");
    {
	CDKMARQUEE *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKMARQUEE *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKMarquee (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKSELECTIONPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKSELECTIONPtr::DESTROY(object)");
    {
	CDKSELECTION *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSELECTION *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKSelection (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKVIEWERPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKVIEWERPtr::DESTROY(object)");
    {
	CDKVIEWER *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKVIEWER *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKViewer (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKGRAPHPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKGRAPHPtr::DESTROY(object)");
    {
	CDKGRAPH *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKGRAPH *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKGraph (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKRADIOPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKRADIOPtr::DESTROY(object)");
    {
	CDKRADIO *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKRADIO *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKRadio (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKTEMPLATEPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKTEMPLATEPtr::DESTROY(object)");
    {
	CDKTEMPLATE *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKTEMPLATE *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKTemplate (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKSWINDOWPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKSWINDOWPtr::DESTROY(object)");
    {
	CDKSWINDOW *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKSWINDOW *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKSwindow (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKITEMLISTPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKITEMLISTPtr::DESTROY(object)");
    {
	CDKITEMLIST *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKITEMLIST *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKItemlist (object);
	}
    }
    XSRETURN(1);
}

XS(XS_CDKFSELECTPtr_cdk_DESTROY)
{
    dXSARGS;
    if (items != 1)
	croak("Usage: CDKFSELECTPtr::DESTROY(object)");
    {
	CDKFSELECT *	object;

	if (SvROK(ST(0))) {
	    IV tmp = SvIV((SV*)SvRV(ST(0)));
	    object = (CDKFSELECT *) tmp;
	}
	else
	    croak("object is not a reference");
	{
	   destroyCDKFselect (object);
	}
    }
    XSRETURN(1);
}

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Cdk)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("Cdk::constant", XS_Cdk_constant, file);
        newXS("Cdk::Beep", XS_Cdk_Beep, file);
        newXS("Cdk::init", XS_Cdk_init, file);
        newXS("Cdk::mixChtype", XS_Cdk_mixChtype, file);
        newXS("Cdk::getColor", XS_Cdk_getColor, file);
        newXS("Cdk::makeChtype", XS_Cdk_makeChtype, file);
        newXS("Cdk::makeColorChtype", XS_Cdk_makeColorChtype, file);
        newXS("Cdk::end", XS_Cdk_end, file);
        newXS("Cdk::getCdkScreen", XS_Cdk_getCdkScreen, file);
        newXS("Cdk::getCdkScreenDim", XS_Cdk_getCdkScreenDim, file);
        newXS("Cdk::getCdkWindow", XS_Cdk_getCdkWindow, file);
        newXS("Cdk::refreshCdkScreen", XS_Cdk_refreshCdkScreen, file);
        newXS("Cdk::eraseCdkScreen", XS_Cdk_eraseCdkScreen, file);
        newXS("Cdk::destroyCdkScreen", XS_Cdk_destroyCdkScreen, file);
        newXS("Cdk::DrawMesg", XS_Cdk_DrawMesg, file);
        newXS("Cdk::getch", XS_Cdk_getch, file);
        newXS("Cdk::raw", XS_Cdk_raw, file);
        newXS("Cdk::noraw", XS_Cdk_noraw, file);
        newXS("Cdk::Label::New", XS_Cdk__Label_New, file);
        newXS("Cdk::Label::Draw", XS_Cdk__Label_Draw, file);
        newXS("Cdk::Label::Erase", XS_Cdk__Label_Erase, file);
        newXS("Cdk::Label::Wait", XS_Cdk__Label_Wait, file);
        newXS("Cdk::Label::Register", XS_Cdk__Label_Register, file);
        newXS("Cdk::Label::Unregister", XS_Cdk__Label_Unregister, file);
        newXS("Cdk::Label::Raise", XS_Cdk__Label_Raise, file);
        newXS("Cdk::Label::Lower", XS_Cdk__Label_Lower, file);
        newXS("Cdk::Label::GetWindow", XS_Cdk__Label_GetWindow, file);
        newXS("Cdk::Dialog::New", XS_Cdk__Dialog_New, file);
        newXS("Cdk::Dialog::Activate", XS_Cdk__Dialog_Activate, file);
        newXS("Cdk::Dialog::Inject", XS_Cdk__Dialog_Inject, file);
        newXS("Cdk::Dialog::Bind", XS_Cdk__Dialog_Bind, file);
        newXS("Cdk::Dialog::Draw", XS_Cdk__Dialog_Draw, file);
        newXS("Cdk::Dialog::Erase", XS_Cdk__Dialog_Erase, file);
        newXS("Cdk::Dialog::Set", XS_Cdk__Dialog_Set, file);
        newXS("Cdk::Dialog::Register", XS_Cdk__Dialog_Register, file);
        newXS("Cdk::Dialog::Unregister", XS_Cdk__Dialog_Unregister, file);
        newXS("Cdk::Dialog::Raise", XS_Cdk__Dialog_Raise, file);
        newXS("Cdk::Dialog::Lower", XS_Cdk__Dialog_Lower, file);
        newXS("Cdk::Dialog::GetWindow", XS_Cdk__Dialog_GetWindow, file);
        newXS("Cdk::Scroll::New", XS_Cdk__Scroll_New, file);
        newXS("Cdk::Scroll::Activate", XS_Cdk__Scroll_Activate, file);
        newXS("Cdk::Scroll::Inject", XS_Cdk__Scroll_Inject, file);
        newXS("Cdk::Scroll::Add", XS_Cdk__Scroll_Add, file);
        newXS("Cdk::Scroll::Delete", XS_Cdk__Scroll_Delete, file);
        newXS("Cdk::Scroll::Bind", XS_Cdk__Scroll_Bind, file);
        newXS("Cdk::Scroll::Draw", XS_Cdk__Scroll_Draw, file);
        newXS("Cdk::Scroll::Erase", XS_Cdk__Scroll_Erase, file);
        newXS("Cdk::Scroll::Info", XS_Cdk__Scroll_Info, file);
        newXS("Cdk::Scroll::Set", XS_Cdk__Scroll_Set, file);
        newXS("Cdk::Scroll::Register", XS_Cdk__Scroll_Register, file);
        newXS("Cdk::Scroll::Unregister", XS_Cdk__Scroll_Unregister, file);
        newXS("Cdk::Scroll::Raise", XS_Cdk__Scroll_Raise, file);
        newXS("Cdk::Scroll::Lower", XS_Cdk__Scroll_Lower, file);
        newXS("Cdk::Scroll::GetWindow", XS_Cdk__Scroll_GetWindow, file);
        newXS("Cdk::Scale::New", XS_Cdk__Scale_New, file);
        newXS("Cdk::Scale::Activate", XS_Cdk__Scale_Activate, file);
        newXS("Cdk::Scale::Inject", XS_Cdk__Scale_Inject, file);
        newXS("Cdk::Scale::Bind", XS_Cdk__Scale_Bind, file);
        newXS("Cdk::Scale::Draw", XS_Cdk__Scale_Draw, file);
        newXS("Cdk::Scale::Erase", XS_Cdk__Scale_Erase, file);
        newXS("Cdk::Scale::Set", XS_Cdk__Scale_Set, file);
        newXS("Cdk::Scale::Register", XS_Cdk__Scale_Register, file);
        newXS("Cdk::Scale::Unregister", XS_Cdk__Scale_Unregister, file);
        newXS("Cdk::Scale::Raise", XS_Cdk__Scale_Raise, file);
        newXS("Cdk::Scale::Lower", XS_Cdk__Scale_Lower, file);
        newXS("Cdk::Scale::GetWindow", XS_Cdk__Scale_GetWindow, file);
        newXS("Cdk::Histogram::New", XS_Cdk__Histogram_New, file);
        newXS("Cdk::Histogram::Set", XS_Cdk__Histogram_Set, file);
        newXS("Cdk::Histogram::Draw", XS_Cdk__Histogram_Draw, file);
        newXS("Cdk::Histogram::Erase", XS_Cdk__Histogram_Erase, file);
        newXS("Cdk::Histogram::Register", XS_Cdk__Histogram_Register, file);
        newXS("Cdk::Histogram::Unregister", XS_Cdk__Histogram_Unregister, file);
        newXS("Cdk::Histogram::Raise", XS_Cdk__Histogram_Raise, file);
        newXS("Cdk::Histogram::Lower", XS_Cdk__Histogram_Lower, file);
        newXS("Cdk::Histogram::GetWindow", XS_Cdk__Histogram_GetWindow, file);
        newXS("Cdk::Menu::New", XS_Cdk__Menu_New, file);
        newXS("Cdk::Menu::Activate", XS_Cdk__Menu_Activate, file);
        newXS("Cdk::Menu::Inject", XS_Cdk__Menu_Inject, file);
        newXS("Cdk::Menu::Bind", XS_Cdk__Menu_Bind, file);
        newXS("Cdk::Menu::Draw", XS_Cdk__Menu_Draw, file);
        newXS("Cdk::Menu::Erase", XS_Cdk__Menu_Erase, file);
        newXS("Cdk::Menu::Set", XS_Cdk__Menu_Set, file);
        newXS("Cdk::Menu::Register", XS_Cdk__Menu_Register, file);
        newXS("Cdk::Menu::Unregister", XS_Cdk__Menu_Unregister, file);
        newXS("Cdk::Menu::Raise", XS_Cdk__Menu_Raise, file);
        newXS("Cdk::Menu::Lower", XS_Cdk__Menu_Lower, file);
        newXS("Cdk::Entry::New", XS_Cdk__Entry_New, file);
        newXS("Cdk::Entry::Activate", XS_Cdk__Entry_Activate, file);
        newXS("Cdk::Entry::Inject", XS_Cdk__Entry_Inject, file);
        newXS("Cdk::Entry::Bind", XS_Cdk__Entry_Bind, file);
        newXS("Cdk::Entry::Draw", XS_Cdk__Entry_Draw, file);
        newXS("Cdk::Entry::Erase", XS_Cdk__Entry_Erase, file);
        newXS("Cdk::Entry::Set", XS_Cdk__Entry_Set, file);
        newXS("Cdk::Entry::Get", XS_Cdk__Entry_Get, file);
        newXS("Cdk::Entry::Clean", XS_Cdk__Entry_Clean, file);
        newXS("Cdk::Entry::Register", XS_Cdk__Entry_Register, file);
        newXS("Cdk::Entry::Unregister", XS_Cdk__Entry_Unregister, file);
        newXS("Cdk::Entry::Raise", XS_Cdk__Entry_Raise, file);
        newXS("Cdk::Entry::Lower", XS_Cdk__Entry_Lower, file);
        newXS("Cdk::Entry::GetWindow", XS_Cdk__Entry_GetWindow, file);
        newXS("Cdk::Mentry::New", XS_Cdk__Mentry_New, file);
        newXS("Cdk::Mentry::Activate", XS_Cdk__Mentry_Activate, file);
        newXS("Cdk::Mentry::Inject", XS_Cdk__Mentry_Inject, file);
        newXS("Cdk::Mentry::Bind", XS_Cdk__Mentry_Bind, file);
        newXS("Cdk::Mentry::Draw", XS_Cdk__Mentry_Draw, file);
        newXS("Cdk::Mentry::Erase", XS_Cdk__Mentry_Erase, file);
        newXS("Cdk::Mentry::Set", XS_Cdk__Mentry_Set, file);
        newXS("Cdk::Mentry::Get", XS_Cdk__Mentry_Get, file);
        newXS("Cdk::Mentry::Clean", XS_Cdk__Mentry_Clean, file);
        newXS("Cdk::Mentry::Register", XS_Cdk__Mentry_Register, file);
        newXS("Cdk::Mentry::Unregister", XS_Cdk__Mentry_Unregister, file);
        newXS("Cdk::Mentry::Raise", XS_Cdk__Mentry_Raise, file);
        newXS("Cdk::Mentry::Lower", XS_Cdk__Mentry_Lower, file);
        newXS("Cdk::Mentry::GetWindow", XS_Cdk__Mentry_GetWindow, file);
        newXS("Cdk::Matrix::New", XS_Cdk__Matrix_New, file);
        newXS("Cdk::Matrix::Activate", XS_Cdk__Matrix_Activate, file);
        newXS("Cdk::Matrix::Inject", XS_Cdk__Matrix_Inject, file);
        newXS("Cdk::Matrix::Bind", XS_Cdk__Matrix_Bind, file);
        newXS("Cdk::Matrix::GetDim", XS_Cdk__Matrix_GetDim, file);
        newXS("Cdk::Matrix::Draw", XS_Cdk__Matrix_Draw, file);
        newXS("Cdk::Matrix::Erase", XS_Cdk__Matrix_Erase, file);
        newXS("Cdk::Matrix::Set", XS_Cdk__Matrix_Set, file);
        newXS("Cdk::Matrix::Clean", XS_Cdk__Matrix_Clean, file);
        newXS("Cdk::Matrix::Raise", XS_Cdk__Matrix_Raise, file);
        newXS("Cdk::Matrix::Lower", XS_Cdk__Matrix_Lower, file);
        newXS("Cdk::Matrix::GetWindow", XS_Cdk__Matrix_GetWindow, file);
        newXS("Cdk::Matrix::Register", XS_Cdk__Matrix_Register, file);
        newXS("Cdk::Matrix::Unregister", XS_Cdk__Matrix_Unregister, file);
        newXS("Cdk::Marquee::New", XS_Cdk__Marquee_New, file);
        newXS("Cdk::Marquee::Activate", XS_Cdk__Marquee_Activate, file);
        newXS("Cdk::Marquee::Bind", XS_Cdk__Marquee_Bind, file);
        newXS("Cdk::Marquee::Draw", XS_Cdk__Marquee_Draw, file);
        newXS("Cdk::Marquee::Erase", XS_Cdk__Marquee_Erase, file);
        newXS("Cdk::Marquee::Register", XS_Cdk__Marquee_Register, file);
        newXS("Cdk::Marquee::Unregister", XS_Cdk__Marquee_Unregister, file);
        newXS("Cdk::Marquee::Raise", XS_Cdk__Marquee_Raise, file);
        newXS("Cdk::Marquee::Lower", XS_Cdk__Marquee_Lower, file);
        newXS("Cdk::Marquee::GetWindow", XS_Cdk__Marquee_GetWindow, file);
        newXS("Cdk::Selection::New", XS_Cdk__Selection_New, file);
        newXS("Cdk::Selection::Activate", XS_Cdk__Selection_Activate, file);
        newXS("Cdk::Selection::Inject", XS_Cdk__Selection_Inject, file);
        newXS("Cdk::Selection::Bind", XS_Cdk__Selection_Bind, file);
        newXS("Cdk::Selection::Draw", XS_Cdk__Selection_Draw, file);
        newXS("Cdk::Selection::Erase", XS_Cdk__Selection_Erase, file);
        newXS("Cdk::Selection::Set", XS_Cdk__Selection_Set, file);
        newXS("Cdk::Selection::Register", XS_Cdk__Selection_Register, file);
        newXS("Cdk::Selection::Unregister", XS_Cdk__Selection_Unregister, file);
        newXS("Cdk::Selection::Raise", XS_Cdk__Selection_Raise, file);
        newXS("Cdk::Selection::Lower", XS_Cdk__Selection_Lower, file);
        newXS("Cdk::Selection::GetWindow", XS_Cdk__Selection_GetWindow, file);
        newXS("Cdk::Viewer::New", XS_Cdk__Viewer_New, file);
        newXS("Cdk::Viewer::Activate", XS_Cdk__Viewer_Activate, file);
        newXS("Cdk::Viewer::Set", XS_Cdk__Viewer_Set, file);
        newXS("Cdk::Viewer::Bind", XS_Cdk__Viewer_Bind, file);
        newXS("Cdk::Viewer::Draw", XS_Cdk__Viewer_Draw, file);
        newXS("Cdk::Viewer::Erase", XS_Cdk__Viewer_Erase, file);
        newXS("Cdk::Viewer::Register", XS_Cdk__Viewer_Register, file);
        newXS("Cdk::Viewer::Unregister", XS_Cdk__Viewer_Unregister, file);
        newXS("Cdk::Viewer::Raise", XS_Cdk__Viewer_Raise, file);
        newXS("Cdk::Viewer::Lower", XS_Cdk__Viewer_Lower, file);
        newXS("Cdk::Viewer::GetWindow", XS_Cdk__Viewer_GetWindow, file);
        newXS("Cdk::Graph::New", XS_Cdk__Graph_New, file);
        newXS("Cdk::Graph::Set", XS_Cdk__Graph_Set, file);
        newXS("Cdk::Graph::Draw", XS_Cdk__Graph_Draw, file);
        newXS("Cdk::Graph::Erase", XS_Cdk__Graph_Erase, file);
        newXS("Cdk::Graph::Register", XS_Cdk__Graph_Register, file);
        newXS("Cdk::Graph::Unregister", XS_Cdk__Graph_Unregister, file);
        newXS("Cdk::Graph::Raise", XS_Cdk__Graph_Raise, file);
        newXS("Cdk::Graph::Lower", XS_Cdk__Graph_Lower, file);
        newXS("Cdk::Graph::GetWindow", XS_Cdk__Graph_GetWindow, file);
        newXS("Cdk::Radio::New", XS_Cdk__Radio_New, file);
        newXS("Cdk::Radio::Activate", XS_Cdk__Radio_Activate, file);
        newXS("Cdk::Radio::Inject", XS_Cdk__Radio_Inject, file);
        newXS("Cdk::Radio::Bind", XS_Cdk__Radio_Bind, file);
        newXS("Cdk::Radio::Draw", XS_Cdk__Radio_Draw, file);
        newXS("Cdk::Radio::Erase", XS_Cdk__Radio_Erase, file);
        newXS("Cdk::Radio::Set", XS_Cdk__Radio_Set, file);
        newXS("Cdk::Radio::Register", XS_Cdk__Radio_Register, file);
        newXS("Cdk::Radio::Unregister", XS_Cdk__Radio_Unregister, file);
        newXS("Cdk::Radio::Raise", XS_Cdk__Radio_Raise, file);
        newXS("Cdk::Radio::Lower", XS_Cdk__Radio_Lower, file);
        newXS("Cdk::Radio::GetWindow", XS_Cdk__Radio_GetWindow, file);
        newXS("Cdk::Template::New", XS_Cdk__Template_New, file);
        newXS("Cdk::Template::Activate", XS_Cdk__Template_Activate, file);
        newXS("Cdk::Template::Inject", XS_Cdk__Template_Inject, file);
        newXS("Cdk::Template::Bind", XS_Cdk__Template_Bind, file);
        newXS("Cdk::Template::Mix", XS_Cdk__Template_Mix, file);
        newXS("Cdk::Template::Draw", XS_Cdk__Template_Draw, file);
        newXS("Cdk::Template::Erase", XS_Cdk__Template_Erase, file);
        newXS("Cdk::Template::Set", XS_Cdk__Template_Set, file);
        newXS("Cdk::Template::Get", XS_Cdk__Template_Get, file);
        newXS("Cdk::Template::Clean", XS_Cdk__Template_Clean, file);
        newXS("Cdk::Template::Register", XS_Cdk__Template_Register, file);
        newXS("Cdk::Template::Unregister", XS_Cdk__Template_Unregister, file);
        newXS("Cdk::Template::Raise", XS_Cdk__Template_Raise, file);
        newXS("Cdk::Template::Lower", XS_Cdk__Template_Lower, file);
        newXS("Cdk::Template::GetWindow", XS_Cdk__Template_GetWindow, file);
        newXS("Cdk::Swindow::New", XS_Cdk__Swindow_New, file);
        newXS("Cdk::Swindow::Activate", XS_Cdk__Swindow_Activate, file);
        newXS("Cdk::Swindow::Inject", XS_Cdk__Swindow_Inject, file);
        newXS("Cdk::Swindow::Bind", XS_Cdk__Swindow_Bind, file);
        newXS("Cdk::Swindow::Set", XS_Cdk__Swindow_Set, file);
        newXS("Cdk::Swindow::Addline", XS_Cdk__Swindow_Addline, file);
        newXS("Cdk::Swindow::Trim", XS_Cdk__Swindow_Trim, file);
        newXS("Cdk::Swindow::Exec", XS_Cdk__Swindow_Exec, file);
        newXS("Cdk::Swindow::Get", XS_Cdk__Swindow_Get, file);
        newXS("Cdk::Swindow::Draw", XS_Cdk__Swindow_Draw, file);
        newXS("Cdk::Swindow::Erase", XS_Cdk__Swindow_Erase, file);
        newXS("Cdk::Swindow::Clean", XS_Cdk__Swindow_Clean, file);
        newXS("Cdk::Swindow::Register", XS_Cdk__Swindow_Register, file);
        newXS("Cdk::Swindow::Unregister", XS_Cdk__Swindow_Unregister, file);
        newXS("Cdk::Swindow::Raise", XS_Cdk__Swindow_Raise, file);
        newXS("Cdk::Swindow::Lower", XS_Cdk__Swindow_Lower, file);
        newXS("Cdk::Swindow::GetWindow", XS_Cdk__Swindow_GetWindow, file);
        newXS("Cdk::Itemlist::New", XS_Cdk__Itemlist_New, file);
        newXS("Cdk::Itemlist::Activate", XS_Cdk__Itemlist_Activate, file);
        newXS("Cdk::Itemlist::Inject", XS_Cdk__Itemlist_Inject, file);
        newXS("Cdk::Itemlist::Bind", XS_Cdk__Itemlist_Bind, file);
        newXS("Cdk::Itemlist::Set", XS_Cdk__Itemlist_Set, file);
        newXS("Cdk::Itemlist::Get", XS_Cdk__Itemlist_Get, file);
        newXS("Cdk::Itemlist::Draw", XS_Cdk__Itemlist_Draw, file);
        newXS("Cdk::Itemlist::Erase", XS_Cdk__Itemlist_Erase, file);
        newXS("Cdk::Itemlist::Register", XS_Cdk__Itemlist_Register, file);
        newXS("Cdk::Itemlist::Unregister", XS_Cdk__Itemlist_Unregister, file);
        newXS("Cdk::Itemlist::Raise", XS_Cdk__Itemlist_Raise, file);
        newXS("Cdk::Itemlist::Lower", XS_Cdk__Itemlist_Lower, file);
        newXS("Cdk::Itemlist::GetWindow", XS_Cdk__Itemlist_GetWindow, file);
        newXS("Cdk::Fselect::New", XS_Cdk__Fselect_New, file);
        newXS("Cdk::Fselect::Activate", XS_Cdk__Fselect_Activate, file);
        newXS("Cdk::Fselect::Set", XS_Cdk__Fselect_Set, file);
        newXS("Cdk::Fselect::Bind", XS_Cdk__Fselect_Bind, file);
        newXS("Cdk::Fselect::Draw", XS_Cdk__Fselect_Draw, file);
        newXS("Cdk::Fselect::Erase", XS_Cdk__Fselect_Erase, file);
        newXS("Cdk::Fselect::Register", XS_Cdk__Fselect_Register, file);
        newXS("Cdk::Fselect::Unregister", XS_Cdk__Fselect_Unregister, file);
        newXS("Cdk::Fselect::Raise", XS_Cdk__Fselect_Raise, file);
        newXS("Cdk::Fselect::Lower", XS_Cdk__Fselect_Lower, file);
        newXS("Cdk::Fselect::GetWindow", XS_Cdk__Fselect_GetWindow, file);
        newXS("Cdk::Diag::DumpScreenRegList", XS_Cdk__Diag_DumpScreenRegList, file);
        newXS("CDKLABELPtr::DESTROY", XS_CDKLABELPtr_cdk_DESTROY, file);
        newXS("CDKDIALOGPtr::DESTROY", XS_CDKDIALOGPtr_cdk_DESTROY, file);
        newXS("CDKENTRYPtr::DESTROY", XS_CDKENTRYPtr_cdk_DESTROY, file);
        newXS("CDKSCROLLPtr::DESTROY", XS_CDKSCROLLPtr_cdk_DESTROY, file);
        newXS("CDKSCALEPtr::DESTROY", XS_CDKSCALEPtr_cdk_DESTROY, file);
        newXS("CDKHISTOGRAMPtr::DESTROY", XS_CDKHISTOGRAMPtr_cdk_DESTROY, file);
        newXS("CDKMENUPtr::DESTROY", XS_CDKMENUPtr_cdk_DESTROY, file);
        newXS("CDKMENTRYPtr::DESTROY", XS_CDKMENTRYPtr_cdk_DESTROY, file);
        newXS("CDKMATRIXPtr::DESTROY", XS_CDKMATRIXPtr_cdk_DESTROY, file);
        newXS("CDKMARQUEEPtr::DESTROY", XS_CDKMARQUEEPtr_cdk_DESTROY, file);
        newXS("CDKSELECTIONPtr::DESTROY", XS_CDKSELECTIONPtr_cdk_DESTROY, file);
        newXS("CDKVIEWERPtr::DESTROY", XS_CDKVIEWERPtr_cdk_DESTROY, file);
        newXS("CDKGRAPHPtr::DESTROY", XS_CDKGRAPHPtr_cdk_DESTROY, file);
        newXS("CDKRADIOPtr::DESTROY", XS_CDKRADIOPtr_cdk_DESTROY, file);
        newXS("CDKTEMPLATEPtr::DESTROY", XS_CDKTEMPLATEPtr_cdk_DESTROY, file);
        newXS("CDKSWINDOWPtr::DESTROY", XS_CDKSWINDOWPtr_cdk_DESTROY, file);
        newXS("CDKITEMLISTPtr::DESTROY", XS_CDKITEMLISTPtr_cdk_DESTROY, file);
        newXS("CDKFSELECTPtr::DESTROY", XS_CDKFSELECTPtr_cdk_DESTROY, file);
    ST(0) = &sv_yes;
    XSRETURN(1);
}
