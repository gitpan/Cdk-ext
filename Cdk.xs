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

MODULE	= Cdk	PACKAGE	= Cdk

double
constant(name,arg)
	char *		name
	int		arg

void
Beep()
	CODE:
	{
	   Beep();
	}

CDKSCREEN *
init()
	CODE:
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
	OUTPUT:
	   RETVAL

chtype
mixChtype(character,attribute)
	char	character
	chtype 	attribute
	CODE:
	{
	   RETVAL = character | attribute;
	}

long
getColor(pair)
	int	pair
	CODE:
	{
	   RETVAL = COLOR_PAIR(pair);
	}

chtype
makeChtype (attr1,attr2)
	chtype	attr1
	chtype	attr2
	CODE:
	{
	   RETVAL = attr1 | attr2;
	}

chtype
makeColorChtype(attribute,pair)
	chtype 	attribute = sv2chtype ($arg);
	int	pair
	CODE:
	{
	   RETVAL = attribute | COLOR_PAIR(pair);
	}

void
end()
	CODE:
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

CDKSCREEN *
getCdkScreen()
	CODE:
	{
	   RETVAL = GCDKSCREEN;
	}
	OUTPUT:
	   RETVAL

void
getCdkScreenDim()
	PPCODE:
	{
	   XPUSHs (sv_2mortal(newSViv(GCDKSCREEN->window->_maxy)));
	   XPUSHs (sv_2mortal(newSViv(GCDKSCREEN->window->_maxx)));
	}

WINDOW *
getCdkWindow()
	CODE:
	{
	   RETVAL = GCDKSCREEN->window;
	}


void
refreshCdkScreen()
	CODE:
	{
	   refreshCDKScreen (GCDKSCREEN);
	}

void
eraseCdkScreen()
	CODE:
	{
	   eraseCDKScreen (GCDKSCREEN);
	}

void
destroyCdkScreen()
	CODE:
	{
	   destroyCDKScreen(GCDKSCREEN);
	}

void
DrawMesg(window,mesg,attrib=A_NORMAL,xpos=CENTER,ypos=CENTER,align=HORIZONTAL)
	WINDOW *	window
	char *		mesg
	chtype		attrib = sv2chtype ($arg);
	int		xpos = sv2int ($arg);
	int		ypos = sv2int ($arg);
	int		align = sv2int ($arg);
	CODE:
	{
	   printattr (window, xpos, ypos, align, attrib, mesg);
	}

chtype
getch()

void
raw()

void
noraw()

MODULE	= Cdk	PACKAGE	= Cdk::Label

CDKLABEL *
New(mesg,xPos=CENTER,yPos=CENTER,Box=TRUE,shadow=FALSE)
	SV *	mesg
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Draw(object,Box=TRUE)
	CDKLABEL *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKLabel (object, Box);
	}

void
Erase(object)
	CDKLABEL *	object
	CODE:
	{
	   eraseCDKLabel(object);
	}

char
Wait(object, key=(chtype)NULL)
	CDKLABEL *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = waitCDKLabel (object, key);
	}

void
Register(object)
	CDKLABEL *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vLABEL, object);
	}

void
Unregister(object)
	CDKLABEL *	object
	CODE:
	{
	   unregisterCDKObject (vLABEL, object);
	}

void
Raise(object)
	CDKLABEL *	object
	CODE:
	{
	   raiseCDKObject (vLABEL, object);
	}

void
Lower(object)
	CDKLABEL *	object
	CODE:
	{
	   lowerCDKObject (vLABEL, object);
	}

WINDOW *
GetWindow(object)
	CDKLABEL *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Dialog

CDKDIALOG *
New(message,buttons,xPos=CENTER,yPos=CENTER,highlight=A_REVERSE,seperator=TRUE,Box=TRUE,shadow=FALSE)
	SV *	message
	SV *	buttons
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	chtype	highlight = sv2chtype ($arg);
	int	seperator = sv2int ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKDIALOG *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKDIALOG *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKDialog (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKDIALOG *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vDIALOG, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=TRUE)
        CDKDIALOG *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKDialog (object,Box);
        }

void
Erase(object)
	CDKDIALOG *	object
	CODE:
	{
	   eraseCDKDialog (object);
	}

void
Set(object,highlight=A_REVERSE,seperator=TRUE,Box=TRUE)
	CDKDIALOG *	object
	chtype		highlight = sv2chtype ($arg);
	int		seperator = sv2int ($arg);
	int		Box = sv2int ($arg);
	CODE:
	{
	   setCDKDialog (object,highlight,seperator,Box);
	}

void
Register(object)
	CDKDIALOG *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vDIALOG, object);
	}

void
Unregister(object)
	CDKDIALOG *	object
	CODE:
	{
	   unregisterCDKObject (vDIALOG, object);
	}

void
Raise(object)
	CDKDIALOG *	object
	CODE:
	{
	   raiseCDKObject (vDIALOG, object);
	}

void
Lower(object)
	CDKDIALOG *	object
	CODE:
	{
	   lowerCDKObject (vDIALOG, object);
	}

WINDOW *
GetWindow(object)
	CDKDIALOG *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Scroll

CDKSCROLL *
New (title,mesg,height,width,xPos=CENTER,yPos=CENTER,numbers=TRUE,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)
	char * 	title
	SV *	mesg
	int	height
	int	width
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	numbers	 = sv2int ($arg);
	chtype	highlight = sv2chtype ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKSCROLL *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKSCROLL *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKScroll (object,key);
	}
	OUTPUT:
	   RETVAL

void
Add(object,line)
	CDKSCROLL *	object
	char *		line
	CODE:
	{
	   addCDKScrollItem (object,line);
	}

void
Delete(object,position)
	CDKSCROLL *	object
	int		position = sv2int ($arg);
	CODE:
	{
	   deleteCDKScrollItem (object,position);
	}

void
Bind(object,key,functionRef)
	CDKSCROLL *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSCROLL, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKSCROLL *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKScroll (object,Box);
        }

void
Erase(object)
	CDKSCROLL *	object
	CODE:
	{
	   eraseCDKScroll(object);
	}

void
Info(object)
	CDKSCROLL *	object
	PPCODE:
	{
	   int currentItem = object->currentItem;
	   int size = object->listSize;

	   XPUSHs (sv_2mortal (newSViv(size)));
	   XPUSHs (sv_2mortal (newSViv(currentItem)));
	}

void
Set(object,mesg,numbers=FALSE,highlight=A_REVERSE,Box=TRUE)
	CDKSCROLL *	object
	SV *		mesg
	int		numbers = sv2int ($arg);
	chtype		highlight = sv2chtype ($arg);
	int		Box = sv2int ($arg);
	CODE:
	{
	   char *Message[MAXITEMS];
	   int mesglen;
 
	   MAKE_CHAR_ARRAY(0,mesg,Message,mesglen);
	   Message[mesglen] = "";

	   setCDKScroll (object,Message,mesglen,numbers,highlight,Box);
	}

void
Register(object)
	CDKSCROLL *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vSCROLL, object);
	}

void
Unregister(object)
	CDKSCROLL *	object
	CODE:
	{
	   unregisterCDKObject (vSCROLL, object);
	}

void
Raise(object)
	CDKSCROLL *	object
	CODE:
	{
	   raiseCDKObject (vSCROLL, object);
	}

void
Lower(object)
	CDKSCROLL *	object
	CODE:
	{
	   lowerCDKObject (vSCROLL, object);
	}

WINDOW *
GetWindow(object)
	CDKSCROLL *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Scale

CDKSCALE *
New(label,start,low,high,inc,fastinc,fieldwidth,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)
	char *	label
	int	start
	int	low
	int	high
	int	inc
	int	fastinc
	int	fieldwidth
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	lPos = sv2int ($arg);
	chtype	fieldattr = sv2chtype ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKSCALE *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKSCALE *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKScale (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKSCALE *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSCALE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKSCALE *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKScale (object,Box);
        }

void
Erase(object)
	CDKSCALE *	object
	CODE:
	{
	   eraseCDKScale(object);
	}

void
Set(object,low,high,value,Box=TRUE)
	CDKSCALE *	object
	int		low
	int		high
	int		value
	int		Box = sv2int ($arg);
	CODE:
	{
	   setCDKScale (object,low,high,value,Box);
	}

void
Register(object)
	CDKSCALE *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vSCALE, object);
	}

void
Unregister(object)
	CDKSCALE *	object
	CODE:
	{
	   unregisterCDKObject (vSCALE, object);
	}

void
Raise(object)
	CDKSCALE *	object
	CODE:
	{
	   raiseCDKObject (vSCALE, object);
	}

void
Lower(object)
	CDKSCALE *	object
	CODE:
	{
	   lowerCDKObject (vSCALE, object);
	}

WINDOW *
GetWindow(object)
	CDKSCALE *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Histogram

CDKHISTOGRAM *
New(label,height,width,orient=HORIZONTAL,xPos=CENTER,yPos=CENTER,lPos=LEFT,Box=TRUE,shadow=FALSE)
	char *	label
	int	height
	int	width
	int	orient = sv2int ($arg);
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	lPos = sv2int ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Set(object,low,high,value,filler='.',fillattr=A_NORMAL,sType="vPERCENT",statsPos=TOP,statsAttr=A_REVERSE,Box=BOX)
	CDKHISTOGRAM *		object
	int			low
	int			high
	int			value
	char			filler
	chtype			fillattr = sv2chtype ($arg);
	char *			sType
	int			statsPos = sv2int ($arg);
	chtype			statsAttr = sv2chtype ($arg);
	int			Box = sv2int ($arg);
	CODE:
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

void
Draw(object,Box=BOX)
	CDKHISTOGRAM *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKHistogram (object,Box);
	}

void
Erase(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   eraseCDKHistogram (object);
	}

void
Register(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vHISTOGRAM, object);
	}

void
Unregister(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   unregisterCDKObject (vHISTOGRAM, object);
	}

void
Raise(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   raiseCDKObject (vHISTOGRAM, object);
	}

void
Lower(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   lowerCDKObject (vHISTOGRAM, object);
	}

WINDOW *
GetWindow(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Menu

CDKMENU *
New(menulist,menuloc,titleattr=A_REVERSE,subtitleattr=A_REVERSE,menuPos=TOP)
	SV *	menulist
	SV *	menuloc
	chtype	titleattr = sv2chtype ($arg);
	chtype	subtitleattr = sv2chtype ($arg);
	int	menuPos = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKMENU *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKMENU *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKMenu (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKMENU *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMENU, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object)
        CDKMENU *	object
        CODE:
        {
           drawCDKMenu (object);
        }

void
Erase(object)
	CDKMENU *	object
	CODE:
	{
	   eraseCDKMenu (object);
	}

void
Set(object,menuitem,submenuitem,titleattr,subtitleattr)
	CDKMENU *	object
	int		menuitem
	int		submenuitem
	chtype		titleattr = sv2chtype ($arg);
	chtype		subtitleattr = sv2chtype ($arg);
	CODE:
	{
	   setCDKMenu(object,menuitem,submenuitem,titleattr,subtitleattr);
	}

void
Register(object)
	CDKMENU *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vMENU, object);
	}

void
Unregister(object)
	CDKMENU *	object
	CODE:
	{
	   unregisterCDKObject (vMENU, object);
	}

void
Raise(object)
	CDKMENU *	object
	CODE:
	{
	   raiseCDKObject (vMENU, object);
	}

void
Lower(object)
	CDKMENU *	object
	CODE:
	{
	   lowerCDKObject (vMENU, object);
	}

MODULE	= Cdk	PACKAGE	= Cdk::Entry

CDKENTRY *
New(label,min,max,fieldWidth,filler='.',fillattr=A_NORMAL,disptype=vMIXED,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)
	char *		label
	int		min
	int		max
	int		fieldWidth
	char		filler
	chtype		fillattr = sv2chtype ($arg);
	EDisplayType	disptype = sv2dtype ($arg);
	int		xPos = sv2int ($arg);
	int		yPos = sv2int ($arg);
	int		lPos = sv2int ($arg);
	chtype		fieldattr = sv2chtype ($arg);
	int		Box = sv2int ($arg);
	int		shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Activate(object,...)
	CDKENTRY *	object
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Inject(object,key)
	CDKENTRY *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKEntry (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKENTRY *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   SV *function = newSVsv(functionRef);
	   bindCDKObject (vENTRY, object, key, &PerlBindCB, function);
	}

void
Draw(object,Box=BOX)
	CDKENTRY *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKEntry (object, Box);
	}

void
Erase(object)
	CDKENTRY *	object
	CODE:
	{
	   eraseCDKEntry (object);
	}

void
Set(object,value,min,max,Box)
	CDKENTRY *	object
	char *		value
	int		min
	int		max
	int		Box = sv2int ($arg);
	CODE:
	{
	   setCDKEntry (object,value,min,max,Box);
	}

char *
Get(object)
	CDKENTRY *	object
	CODE:
	{
	   RETVAL = object->info;
	}

void
Clean(object)
	CDKENTRY *	object
	CODE:
	{
	   cleanCDKEntry (object);
	}

void
Register(object)
	CDKENTRY *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vENTRY, object);
	}

void
Unregister(object)
	CDKENTRY *	object
	CODE:
	{
	   unregisterCDKObject (vENTRY, object);
	}

void
Raise(object)
	CDKENTRY *	object
	CODE:
	{
	   raiseCDKObject (vENTRY, object);
	}

void
Lower(object)
	CDKENTRY *	object
	CODE:
	{
	   lowerCDKObject (vENTRY, object);
	}

WINDOW *
GetWindow(object)
	CDKENTRY *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Mentry

CDKMENTRY *
New(label,min,physical,logical,fieldWidth,disptype=vMIXED,filler='.',fillattr=A_NORMAL,xPos=CENTER,yPos=CENTER,lPos=LEFT,fieldattr=A_NORMAL,Box=TRUE,shadow=FALSE)
	char *		label
	int		min
	int		physical
	int		logical
	int		fieldWidth
	EDisplayType	disptype = sv2dtype ($arg);
	char		filler
	chtype		fillattr = sv2chtype ($arg);
	int		xPos = sv2int ($arg);
	int		yPos = sv2int ($arg);
	int		lPos = sv2int ($arg);
	chtype		fieldattr = sv2chtype ($arg);
	int		Box = sv2int ($arg);
	int		shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Activate(object,...)
	CDKMENTRY *	object
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Inject(object,key)
	CDKMENTRY *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKMentry (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKMENTRY *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMENTRY, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKMENTRY *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKMentry (object,Box);
        }

void
Erase(object)
	CDKMENTRY *	object
	CODE:
	{
	   eraseCDKMentry (object);
	}

void
Set(object,value,min,box)
	CDKMENTRY *	object
	char *		value
	int		min
	int		box = sv2int ($arg);
	CODE:
	{
	   setCDKMentry (object,value,min,box);
	}

char *
Get(object)
	CDKMENTRY *	object
	CODE:
	{
	   RETVAL = object->info;
	}

void
Clean(object)
	CDKMENTRY *	object
	CODE:
	{
	   cleanCDKMentry (object);
	}

void
Register(object)
	CDKMENTRY *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vMENTRY, object);
	}

void
Unregister(object)
	CDKMENTRY *	object
	CODE:
	{
	   unregisterCDKObject (vMENTRY, object);
	}

void
Raise(object)
	CDKMENTRY *	object
	CODE:
	{
	   raiseCDKObject (vMENTRY, object);
	}

void
Lower(object)
	CDKMENTRY *	object
	CODE:
	{
	   lowerCDKObject (vMENTRY, object);
	}

WINDOW *
GetWindow(object)
	CDKMENTRY *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Matrix

CDKMATRIX *
New(rowtitles,coltitles,colwidths,colvalues,vrows,vcols,xPos=CENTER,yPos=CENTER,rowspace=1,colspace=1,filler='.',fillattr=A_NORMAL,dominant=NONE,boxMatrix=FALSE,boxCell=TRUE,shadow=FALSE)
	SV *	rowtitles
	SV *	coltitles
	SV *	colwidths
	SV *	colvalues
	int	vrows
	int	vcols
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	rowspace
	int	colspace
	char	filler
	chtype	fillattr = sv2chtype ($arg);
	int	dominant = sv2int ($arg);
	int	boxMatrix = sv2int ($arg);
	int	boxCell = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Activate(object)
	CDKMATRIX *	object
	PPCODE:
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

int
Inject(object,key)
	CDKMATRIX *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKMatrix (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKMATRIX *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMATRIX, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
GetDim(object)
	CDKMATRIX *	object
	PPCODE:
	{
	   XPUSHs (sv_2mortal(newSViv(object->rows)));
	   XPUSHs (sv_2mortal(newSViv(object->cols)));
	}

void
Draw(object,Box=BOX)
        CDKMATRIX *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKMatrix (object,Box);
        }

void
Erase(object)
	CDKMATRIX *	object
	CODE:
	{
	   eraseCDKMatrix (object);
	}

void
Set(object,info)
	CDKMATRIX *	object
	SV *		info
	CODE:
	{
	   char *	Info[MAXMATRIXROWS][MAXMATRIXCOLS];
	   int		subSize[MAXMATRIXROWS];
	   int		matrixlen;

	   MAKE_CHAR_MATRIX (1,info,Info,subSize,matrixlen);

	   setCDKMatrix (object,Info,matrixlen,subSize);
	}

void
Clean(object)
	CDKMATRIX *	object
	CODE:
	{
	   cleanCDKMatrix (object);
	}

void
Raise(object)
	CDKMATRIX *	object
	CODE:
	{
	   raiseCDKObject (vMATRIX, object);
	}

void
Lower(object)
	CDKMATRIX *	object
	CODE:
	{
	   lowerCDKObject (vMATRIX, object);
	}

WINDOW *
GetWindow(object)
	CDKMATRIX *	object
	CODE:
	{
	   RETVAL = object->win;
	}

void
Register(object)
	CDKMATRIX *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vMATRIX, object);
	}

void
Unregister(object)
	CDKMATRIX *	object
	CODE:
	{
	   unregisterCDKObject (vMATRIX, object);
	}

MODULE	= Cdk	PACKAGE	= Cdk::Marquee

CDKMARQUEE *
New(width,xPos=CENTER,yPos=CENTER,shadow=FALSE)
	int	width
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(marquee,message,delay,repeat,Box=TRUE)
	CDKMARQUEE *	marquee
	char *		message
	int		delay
	int		repeat
	int		Box = sv2int ($arg);
	CODE:
	{
	   RETVAL = activateCDKMarquee (marquee,message,delay,repeat,Box);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKMARQUEE *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vMARQUEE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKMARQUEE *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKMarquee (object,Box);
        }

void
Erase(object)
	CDKMARQUEE *	object
	CODE:
	{
	   eraseCDKMarquee (object);
	}

void
Register(object)
	CDKMARQUEE *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vMARQUEE, object);
	}

void
Unregister(object)
	CDKMARQUEE *	object
	CODE:
	{
	   unregisterCDKObject (vMARQUEE, object);
	}

void
Raise(object)
	CDKMARQUEE *	object
	CODE:
	{
	   raiseCDKObject (vMARQUEE, object);
	}

void
Lower(object)
	CDKMARQUEE *	object
	CODE:
	{
	   lowerCDKObject (vMARQUEE, object);
	}

WINDOW *
GetWindow(object)
	CDKMARQUEE *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Selection

CDKSELECTION *
New(title,list,choices,height,width,xPos=CENTER,yPos=CENTER,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)
	char *	title
	SV *	list
	SV *	choices
	int	height
	int	width
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	chtype	highlight = sv2chtype ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Activate(object,...)
	CDKSELECTION *	object
	PPCODE:
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

int
Inject(object,key)
	CDKSELECTION *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKSelection (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKSELECTION *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSELECTION, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKSELECTION *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKSelection (object,Box);
        }

void
Erase(object)
	CDKSELECTION *	object
	CODE:
	{
	   eraseCDKSelection (object);
	}

void
Set(object,defaultList,highlight,Box)
	CDKSELECTION *	object
	SV *		defaultList
	chtype		highlight = sv2chtype ($arg);
	int		Box = sv2int ($arg);
	CODE:
	{
	   int defaultChoices[MAXCHOICES];
	   int choicelen;

	   MAKE_INT_ARRAY (0,defaultList,defaultChoices,choicelen);

	   setCDKSelection (object,highlight,defaultChoices,Box);
	}

void
Register(object)
	CDKSELECTION *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vSELECTION, object);
	}

void
Unregister(object)
	CDKSELECTION *	object
	CODE:
	{
	   unregisterCDKObject (vSELECTION, object);
	}

void
Raise(object)
	CDKSELECTION *	object
	CODE:
	{
	   raiseCDKObject (vSELECTION, object);
	}

void
Lower(object)
	CDKSELECTION *	object
	CODE:
	{
	   lowerCDKObject (vSELECTION, object);
	}

WINDOW *
GetWindow(object)
	CDKSELECTION *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Viewer

CDKVIEWER *
New(buttons,height,width,buttonHighlight=A_REVERSE,xpos=CENTER,ypos=CENTER,Box=TRUE,shadow=FALSE)
	SV *	buttons
	int	height
	int	width
	chtype	buttonHighlight = sv2chtype ($arg);
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object)
	CDKVIEWER *	object
	CODE:
	{
	   RETVAL = activateCDKViewer (object);
	}
	OUTPUT:
	   RETVAL
	
void
Set(object,title,info,buttonHighlight=A_REVERSE,attrInterp=TRUE,Box=BOX)
	CDKVIEWER *	object
	char *		title
	SV *		info
	chtype		buttonHighlight = sv2chtype ($arg);
	int		attrInterp = sv2int ($arg);
	int		Box = sv2int ($arg);
	CODE:
	{
	   char *Info[MAXLINES];
	   int infolen;

	   MAKE_CHAR_ARRAY(0,info, Info, infolen);
           Info[infolen] = "";

	   setCDKViewer (object,title,Info,infolen,buttonHighlight,attrInterp,Box);
	}

void
Bind(object,key,functionRef)
	CDKVIEWER *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vVIEWER, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKVIEWER *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKViewer (object,Box);
        }

void
Erase(object)
	CDKVIEWER *	object
	CODE:
	{
	   eraseCDKViewer (object);
	}

void
Register(object)
	CDKVIEWER *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vVIEWER, object);
	}

void
Unregister(object)
	CDKVIEWER *	object
	CODE:
	{
	   unregisterCDKObject (vVIEWER, object);
	}

void
Raise(object)
	CDKVIEWER *	object
	CODE:
	{
	   raiseCDKObject (vVIEWER, object);
	}

void
Lower(object)
	CDKVIEWER *	object
	CODE:
	{
	   lowerCDKObject (vVIEWER, object);
	}

WINDOW *
GetWindow(object)
	CDKVIEWER *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Graph

CDKGRAPH *
New(title,xtitle,ytitle,height,width,xpos=CENTER,ypos=CENTER)
	char *	title
	char *	xtitle
	char *	ytitle
	int	height
	int	width
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Set(object,values,graphchar,startAtZero=TRUE,pType="LINE")
	CDKGRAPH *		object
	SV *			values
	char *			graphchar
	int			startAtZero = sv2int ($arg);
	char *			pType
	CODE:
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
	OUTPUT:
	   RETVAL

void
Draw(object,Box=BOX)
        CDKGRAPH *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKGraph (object,Box);
        }

void
Erase(object)
	CDKGRAPH *	object
	CODE:
	{
	   eraseCDKGraph (object);
	}

void
Register(object)
	CDKGRAPH *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vGRAPH, object);
	}

void
Unregister(object)
	CDKGRAPH *	object
	CODE:
	{
	   unregisterCDKObject (vGRAPH, object);
	}

void
Raise(object)
	CDKGRAPH *	object
	CODE:
	{
	   raiseCDKObject (vGRAPH, object);
	}

void
Lower(object)
	CDKGRAPH *	object
	CODE:
	{
	   lowerCDKObject (vGRAPH, object);
	}

WINDOW *
GetWindow(object)
	CDKGRAPH *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Radio

CDKRADIO *
New(title,list,height,width,xpos=CENTER,ypos=CENTER,choiceChar='X',choiceattr=A_NORMAL,defaultItem=0,highlight=A_REVERSE,Box=TRUE,shadow=FALSE)
	char *	title
	SV *	list
	int	height
	int	width
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	char	choiceChar
	chtype	choiceattr = sv2chtype ($arg);
	int	defaultItem
	chtype	highlight = sv2chtype ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKRADIO *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKRADIO *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKRadio (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKRADIO *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vRADIO, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
        CDKRADIO *	object
        int		Box = sv2int ($arg);
        CODE:
        {
           drawCDKRadio (object,Box);
        }

void
Erase(object)
	CDKRADIO *	object
	CODE:
	{
	   eraseCDKRadio (object);
	}

void
Set(object,highlight,choicechar,choiceattr,Box=TRUE)
	CDKRADIO *	object
	chtype		highlight = sv2chtype ($arg);
	char		choicechar
	chtype		choiceattr = sv2chtype ($arg);
	int		Box = sv2int ($arg);
	CODE:
	{
	   chtype tempchtype	= choicechar | choiceattr;

	   setCDKRadio (object,highlight,tempchtype,Box);
	}

void
Register(object)
	CDKRADIO *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vRADIO, object);
	}

void
Unregister(object)
	CDKRADIO *	object
	CODE:
	{
	   unregisterCDKObject (vRADIO, object);
	}

void
Raise(object)
	CDKRADIO *	object
	CODE:
	{
	   raiseCDKObject (vRADIO, object);
	}

void
Lower(object)
	CDKRADIO *	object
	CODE:
	{
	   lowerCDKObject (vRADIO, object);
	}

WINDOW *
GetWindow(object)
	CDKRADIO *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Template

CDKTEMPLATE *
New(label,plate,overlay,xpos=CENTER,ypos=CENTER,lpos=LEFT,Box=TRUE,shadow=FALSE)
	char *	label
	char *	plate
	char *	overlay
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	int	lpos = sv2int ($arg);
	int	Box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Activate(object,...)
	CDKTEMPLATE *	object
	CODE:
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
	OUTPUT:
	   RETVAL

char *
Inject(object,key)
	CDKTEMPLATE *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKTemplate (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKTEMPLATE *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vTEMPLATE, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

char *
Mix(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   RETVAL = mixCDKTemplate (object);
	}
	OUTPUT:
	   RETVAL

void
Draw(object,Box=BOX)
	CDKTEMPLATE *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKTemplate (object, Box);
	}

void
Erase(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   eraseCDKTemplate (object);
	}

void
Set(object,value,box)
	CDKTEMPLATE *	object
	char *		value
	int		box = sv2int ($arg);
	CODE:
	{
	   setCDKTemplate (object,value,box);
	}

char *
Get(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   RETVAL = object->info;
	}

void
Clean(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   cleanCDKTemplate (object);
	}

void
Register(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vTEMPLATE, object);
	}

void
Unregister(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   unregisterCDKObject (vTEMPLATE, object);
	}

void
Raise(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   raiseCDKObject (vTEMPLATE, object);
	}

void
Lower(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   lowerCDKObject (vTEMPLATE, object);
	}

WINDOW *
GetWindow(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Swindow
CDKSWINDOW *
New(title,savelines,height,width,xpos=CENTER,ypos=CENTER,box=TRUE,shadow=FALSE)
	char *	title
	int	savelines
	int	height
	int	width
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	int	box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Activate(object,...)
	CDKSWINDOW *	object
	CODE:
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

int
Inject(object,key)
	CDKSWINDOW *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKSwindow (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKSWINDOW *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vSWINDOW, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Set(object,info,lines,box)
	CDKSWINDOW *	object
	SV *		info
	int		lines
	int		box = sv2int ($arg);
	CODE:
	{
	   char *Loginfo[MAXITEMS];
	   int infolen;
 
	   checkCdkInit();
 
	   MAKE_CHAR_ARRAY(0,info,Loginfo,infolen);
	   Loginfo[infolen] = "";

	   setCDKSwindow (object, Loginfo, infolen, box);
	}

void
Addline(object,info,insertpos)
	CDKSWINDOW *	object
	char *		info
	int		insertpos = sv2int ($arg);
	CODE:
	{
	   addCDKSwindow (object, info, insertpos);
	}

void
Trim(object,start,finish)
	CDKSWINDOW *	object
	int		start = sv2int ($arg);
	int		finish = sv2int ($arg);
	CODE:
	{
	   trimCDKSwindow (object, start, finish);
	}

int
Exec(object,command,insertPos=BOTTOM)
	CDKSWINDOW *	object
	char *		command
	int		insertPos = sv2int ($arg);
	CODE:
	{
	   RETVAL = execCDKSwindow (object, command, insertPos);
	}
	
void
Get(object)
	CDKSWINDOW *	object
	PPCODE:
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

void
Draw(object,Box=BOX)
	CDKSWINDOW *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKSwindow (object, Box);
	}

void
Erase(object)
	CDKSWINDOW *	object
	CODE:
	{
	   eraseCDKSwindow (object);
	}

void
Clean(object)
	CDKSWINDOW *	object
	CODE:
	{
	   cleanCDKSwindow (object);
	}

void
Register(object)
	CDKSWINDOW *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN, vSWINDOW, object);
	}

void
Unregister(object)
	CDKSWINDOW *	object
	CODE:
	{
	   unregisterCDKObject (vSWINDOW, object);
	}

void
Raise(object)
	CDKSWINDOW *	object
	CODE:
	{
	   raiseCDKObject (vSWINDOW, object);
	}

void
Lower(object)
	CDKSWINDOW *	object
	CODE:
	{
	   lowerCDKObject (vSWINDOW, object);
	}

WINDOW *
GetWindow(object)
	CDKSWINDOW *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Itemlist
CDKITEMLIST *
New(label,itemlist,defaultItem=0,xpos=CENTER,ypos=CENTER,lpos=LEFT,box=TRUE,shadow=FALSE)
	char *	label
	SV *	itemlist
	int	defaultItem
	int	xpos = sv2int ($arg);
	int	ypos = sv2int ($arg);
	int	lpos = sv2int ($arg);
	int	box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

int
Activate(object,...)
	CDKITEMLIST *	object
	CODE:
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
	OUTPUT:
	   RETVAL

int
Inject(object,key)
	CDKITEMLIST *	object
	chtype		key = sv2chtype ($arg);
	CODE:
	{
	   RETVAL = injectCDKItemlist (object,key);
	}
	OUTPUT:
	   RETVAL

void
Bind(object,key,functionRef)
	CDKITEMLIST *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vITEMLIST, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Set(object,info,defaultItem,box)
	CDKITEMLIST *	object
	SV *		info
	int		defaultItem
	int		box = sv2int ($arg);
	CODE:
	{
	   char *infoList[MAXITEMS];
	   int infolen;
 
	   checkCdkInit();
 
	   MAKE_CHAR_ARRAY(0,info,infoList,infolen);

	   setCDKItemlist (object,infoList,infolen,defaultItem,box);
	}

char *
Get(object)
	CDKITEMLIST *	object
	CODE:
	{
	   RETVAL = chtype2Char (object->item[object->currentItem]);
	}

void
Draw(object,Box=BOX)
	CDKITEMLIST *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKItemlist (object,Box);
	}

void
Erase(object)
	CDKITEMLIST *	object
	CODE:
	{
	   eraseCDKItemlist (object);
	}

void
Register(object)
	CDKITEMLIST *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN,vITEMLIST,object);
	}

void
Unregister(object)
	CDKITEMLIST *	object
	CODE:
	{
	   unregisterCDKObject (vITEMLIST, object);
	}

void
Raise(object)
	CDKITEMLIST *	object
	CODE:
	{
	   raiseCDKObject (vITEMLIST, object);
	}

void
Lower(object)
	CDKITEMLIST *	object
	CODE:
	{
	   lowerCDKObject (vITEMLIST, object);
	}

WINDOW *
GetWindow(object)
	CDKITEMLIST *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Fselect
CDKFSELECT *
New(height,width,dAttrib="</N>",fAttrib="</N>",lAttrib="</N>",sAttrib="</N>",highlight=A_REVERSE,fieldAttribute=A_NORMAL,fillerChar='.',fillerAttr=A_NORMAL,xPos=CENTER,yPos=CENTER,box=TRUE,shadow=FALSE)
	int	height
	int	width
	char *	dAttrib
	char *	fAttrib
	char *	lAttrib
	char *	sAttrib
	chtype	highlight = sv2chtype ($arg);
	chtype	fieldAttribute = sv2chtype ($arg);
	char	fillerChar
	chtype	fillerAttr = sv2chtype ($arg);
	int	xPos = sv2int ($arg);
	int	yPos = sv2int ($arg);
	int	box = sv2int ($arg);
	int	shadow = sv2int ($arg);
	CODE:
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
	OUTPUT:
	   RETVAL

void
Activate(object)
	CDKFSELECT *	object
	PPCODE:
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

void
Set(object,directory,dAttrib="</N>",fAttrib="</N>",lAttrib="</N>",sAttrib="</N>",highlight=A_REVERSE,fieldAttribute=A_NORMAL,fillerChar='.',box=TRUE)
	CDKFSELECT*	object
	char *		directory
	char *		dAttrib
	char *		fAttrib
	char *		lAttrib
	char *		sAttrib
	chtype		highlight = sv2chtype ($arg);
	chtype		fieldAttribute = sv2chtype ($arg);
	chtype		fillerChar = sv2chtype ($arg);
	int		box = sv2int ($arg);
	CODE:
	{
	   setCDKFselect (object,directory,
				fieldAttribute,fillerChar,highlight,
				dAttrib,fAttrib,lAttrib,sAttrib,
				box);
	}

void
Bind(object,key,functionRef)
	CDKFSELECT *	object
	chtype		key = sv2chtype ($arg);
	SV *		functionRef
	CODE:
	{
	   GCBList[GCBCount] = newSVsv(functionRef);
	   bindCDKObject (vFSELECT, object, key, &PerlBindCB, GCBList[GCBCount]);
 	   GCBCount++;
	}

void
Draw(object,Box=BOX)
	CDKFSELECT *	object
	int		Box = sv2int ($arg);
	CODE:
	{
	   drawCDKFselect (object,Box);
	}

void
Erase(object)
	CDKFSELECT *	object
	CODE:
	{
	   eraseCDKFselect (object);
	}

void
Register(object)
	CDKFSELECT *	object
	CODE:
	{
	   registerCDKObject (GCDKSCREEN,vFSELECT,object);
	}

void
Unregister(object)
	CDKFSELECT *	object
	CODE:
	{
	   unregisterCDKObject (vFSELECT, object);
	}

void
Raise(object)
	CDKFSELECT *	object
	CODE:
	{
	   raiseCDKObject (vFSELECT, object);
	}

void
Lower(object)
	CDKFSELECT *	object
	CODE:
	{
	   lowerCDKObject (vFSELECT, object);
	}

WINDOW *
GetWindow(object)
	CDKFSELECT *	object
	CODE:
	{
	   RETVAL = object->win;
	}

MODULE	= Cdk	PACKAGE	= Cdk::Diag
void
DumpScreenRegList(mesg)
	char *	mesg
	CODE:
	{
	   debugCDKScreen (GCDKSCREEN, mesg);
	}

MODULE	= Cdk	PACKAGE	= CDKLABELPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKLABEL *	object
	CODE:
	{
	   destroyCDKLabel (object);
	}

MODULE	= Cdk	PACKAGE	= CDKDIALOGPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKDIALOG *	object
	CODE:
	{
	   destroyCDKDialog (object);
	}

MODULE	= Cdk	PACKAGE	= CDKENTRYPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKENTRY *	object
	CODE:
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

MODULE	= Cdk	PACKAGE	= CDKSCROLLPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKSCROLL *	object
	CODE:
	{
	   destroyCDKScroll (object);
	}

MODULE	= Cdk	PACKAGE	= CDKSCALEPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKSCALE *	object
	CODE:
	{
	   destroyCDKScale (object);
	}

MODULE	= Cdk	PACKAGE	= CDKHISTOGRAMPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKHISTOGRAM *	object
	CODE:
	{
	   destroyCDKHistogram (object);
	}

MODULE	= Cdk	PACKAGE	= CDKMENUPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKMENU *	object
	CODE:
	{
	   destroyCDKMenu (object);
	}

MODULE	= Cdk	PACKAGE	= CDKMENTRYPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKMENTRY *	object
	CODE:
	{
	   destroyCDKMentry (object);
	}

MODULE	= Cdk	PACKAGE	= CDKMATRIXPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKMATRIX *	object
	CODE:
	{
	   destroyCDKMatrix (object);
	}

MODULE	= Cdk	PACKAGE	= CDKMARQUEEPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKMARQUEE *	object
	CODE:
	{
	   destroyCDKMarquee (object);
	}

MODULE	= Cdk	PACKAGE	= CDKSELECTIONPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKSELECTION *	object
	CODE:
	{
	   destroyCDKSelection (object);
	}

MODULE	= Cdk	PACKAGE	= CDKVIEWERPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKVIEWER *	object
	CODE:
	{
	   destroyCDKViewer (object);
	}

MODULE	= Cdk	PACKAGE	= CDKGRAPHPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKGRAPH *	object
	CODE:
	{
	   destroyCDKGraph (object);
	}

MODULE	= Cdk	PACKAGE	= CDKRADIOPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKRADIO *	object
	CODE:
	{
	   destroyCDKRadio (object);
	}

MODULE	= Cdk	PACKAGE	= CDKTEMPLATEPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKTEMPLATE *	object
	CODE:
	{
	   destroyCDKTemplate (object);
	}

MODULE	= Cdk	PACKAGE	= CDKSWINDOWPtr		PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKSWINDOW *	object
	CODE:
	{
	   destroyCDKSwindow (object);
	}

MODULE	= Cdk	PACKAGE	= CDKITEMLISTPtr	PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKITEMLIST *	object
	CODE:
	{
	   destroyCDKItemlist (object);
	}

MODULE	= Cdk	PACKAGE	= CDKFSELECTPtr		PREFIX	= cdk_
void
cdk_DESTROY(object)
	CDKFSELECT *	object
	CODE:
	{
	   destroyCDKFselect (object);
	}
