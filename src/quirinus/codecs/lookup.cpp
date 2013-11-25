/**
 * @author    Dmitry Selyutin
 * @copyright GNU General Public License v3.0+
 */

#include <quirinus/core.hpp>
#include <quirinus/codecs.hpp>
#include "tables.cpp"
namespace quirinus {
namespace codecs {


Codec*
lookup(const Bytes& encoding)
{
  // ASCII
  if ((encoding == "ASCII")
  ||  (encoding == "iso-ir-6")
  ||  (encoding == "ANSI_X3.4-1968")
  ||  (encoding == "ANSI_X3.4-1986")
  ||  (encoding == "ISO_646.irv:1991")
  ||  (encoding == "ISO646-US")
  ||  (encoding == "US-ASCII")
  ||  (encoding == "csASCII")
  ||  (encoding == "IBM367")
  ||  (encoding == "CP367"))
    return new Codec_ASCII;


  // UTF-8
  else if ((encoding == "UTF-8")
  ||       (encoding == "UTF8")
  ||       (encoding == "CP65001"))
    return new Codec_UTF8;


  // UTF-16
  else if ((encoding == "UTF-16")
  ||       (encoding == "UTF-16BE")
  ||       (encoding == "UTF-16LE")
  ||       (encoding == "UTF16")
  ||       (encoding == "UTF16BE")
  ||       (encoding == "UTF16LE")
  ||       (encoding == "CP1200")
  ||       (encoding == "CP1201"))
    return new Codec_UTF16;


  // UTF-32
  else if ((encoding == "UTF-32")
  ||       (encoding == "UTF-32BE")
  ||       (encoding == "UTF-32LE")
  ||       (encoding == "UTF32BE")
  ||       (encoding == "UTF32LE")
  ||       (encoding == "CP12000")
  ||       (encoding == "CP12001"))
    return new Codec_UTF32;


  // ISO 8859-1
  else if ((encoding == "iso-ir-100")
  ||       (encoding == "ISO_8859-1")
  ||       (encoding == "ISO-8859-1")
  ||       (encoding == "CP28591")
  ||       (encoding == "csISOLatin1")
  ||       (encoding == "IBM819")
  ||       (encoding == "CP819")
  ||       (encoding == "latin1")
  ||       (encoding == "l1"))
    return new Codec("ISO-8859-1", 28591, codecs::TABLE_ISO_8859_1);


  // ISO 8859-2
  else if ((encoding == "iso-ir-101")
  ||       (encoding == "ISO_8859-2")
  ||       (encoding == "ISO-8859-2")
  ||       (encoding == "CP28592")
  ||       (encoding == "csISOLatin2")
  ||       (encoding == "latin2")
  ||       (encoding == "l2"))
    return new Codec("ISO-8859-2", 28592, codecs::TABLE_ISO_8859_2);


  // ISO 8859-3
  else if ((encoding == "iso-ir-109")
  ||       (encoding == "ISO_8859-3")
  ||       (encoding == "ISO-8859-3")
  ||       (encoding == "CP28593")
  ||       (encoding == "csISOLatin3")
  ||       (encoding == "latin3")
  ||       (encoding == "l3"))
    return new Codec("ISO-8859-3", 28593, codecs::TABLE_ISO_8859_3);


  // ISO 8859-4
  else if ((encoding == "iso-ir-110")
  ||       (encoding == "ISO_8859-4")
  ||       (encoding == "ISO-8859-4")
  ||       (encoding == "CP28594")
  ||       (encoding == "csISOLatin4")
  ||       (encoding == "latin4")
  ||       (encoding == "l4"))
    return new Codec("ISO-8859-4", 28594, codecs::TABLE_ISO_8859_4);


  // ISO 8859-5
  else if ((encoding == "iso-ir-144")
  ||       (encoding == "ISO_8859-5")
  ||       (encoding == "ISO-8859-5")
  ||       (encoding == "CP28595")
  ||       (encoding == "csISOLatinCyrillic")
  ||       (encoding == "cyrillic"))
    return new Codec("ISO-8859-5", 28595, codecs::TABLE_ISO_8859_5);


  // ISO 8859-6
  else if ((encoding == "iso-ir-127")
  ||       (encoding == "ISO_8859-6")
  ||       (encoding == "ISO-8859-6")
  ||       (encoding == "CP28596")
  ||       (encoding == "csISOLatinArabic")
  ||       (encoding == "arabic")
  ||       (encoding == "ECMA-114")
  ||       (encoding == "ASMO-708"))
    return new Codec("ISO-8859-6", 28596, codecs::TABLE_ISO_8859_6);


  // ISO 8859-7
  else if ((encoding == "iso-ir-126")
  ||       (encoding == "ISO_8859-7")
  ||       (encoding == "ISO-8859-7")
  ||       (encoding == "CP28597")
  ||       (encoding == "csISOLatinGreek")
  ||       (encoding == "greek")
  ||       (encoding == "greek8")
  ||       (encoding == "ECMA-118")
  ||       (encoding == "ELOT_928"))
    return new Codec("ISO-8859-7", 28597, codecs::TABLE_ISO_8859_7);


  // ISO 8859-8
  else if ((encoding == "iso-ir-138")
  ||       (encoding == "ISO_8859-8")
  ||       (encoding == "ISO-8859-8")
  ||       (encoding == "CP28598")
  ||       (encoding == "csISOLatinHebrew")
  ||       (encoding == "hebrew"))
    return new Codec("ISO-8859-8", 28598, codecs::TABLE_ISO_8859_8);


  // ISO 8859-9
  else if ((encoding == "iso-ir-148")
  ||       (encoding == "ISO_8859-9")
  ||       (encoding == "ISO-8859-9")
  ||       (encoding == "CP28599")
  ||       (encoding == "csISOLatinLatin5")
  ||       (encoding == "latin5")
  ||       (encoding == "l5"))
    return new Codec("ISO-8859-9", 28599, codecs::TABLE_ISO_8859_9);


  // ISO 8859-10
  else if ((encoding == "iso-ir-157")
  ||       (encoding == "ISO_8859-10")
  ||       (encoding == "ISO-8859-10")
  ||       (encoding == "csISOLatinLatin6")
  ||       (encoding == "latin6")
  ||       (encoding == "l6"))
    return new Codec("ISO-8859-10", 28600, codecs::TABLE_ISO_8859_10);


  // ISO 8859-11
  else if ((encoding == "csTIS620")
  ||       (encoding == "ISO_8859-11")
  ||       (encoding == "ISO-8859-11"))
    return new Codec("ISO-8859-11", 28601, codecs::TABLE_ISO_8859_11);


  // ISO 8859-13
  else if ((encoding == "csISO885913")
  ||       (encoding == "ISO_8859-13")
  ||       (encoding == "ISO-8859-13")
  ||       (encoding == "CP28603"))
    return new Codec("ISO-8859-13", 28603, codecs::TABLE_ISO_8859_13);


  // ISO 8859-14
  else if ((encoding == "iso-ir-199")
  ||       (encoding == "ISO_8859-14")
  ||       (encoding == "ISO-8859-14")
  ||       (encoding == "csISO885914")
  ||       (encoding == "iso-celtic")
  ||       (encoding == "latin8")
  ||       (encoding == "l8"))
    return new Codec("ISO-8859-14", 28604, codecs::TABLE_ISO_8859_14);


  // ISO 8859-15
  else if ((encoding == "csISO885915")
  ||       (encoding == "ISO_8859-15")
  ||       (encoding == "ISO-8859-15")
  ||       (encoding == "CP28605")
  ||       (encoding == "latin9")
  ||       (encoding == "l9"))
    return new Codec("ISO-8859-15", 28605, codecs::TABLE_ISO_8859_15);


  // ISO 8859-16
  else if ((encoding == "iso-ir-226")
  ||       (encoding == "ISO_8859-16")
  ||       (encoding == "ISO-8859-16")
  ||       (encoding == "csISO885916")
  ||       (encoding == "latin10")
  ||       (encoding == "l10"))
    return new Codec("ISO-8859-16", 28606, codecs::TABLE_ISO_8859_16);


  // CP037
  else if ((encoding == "CP037")
  ||       (encoding == "IBM037")
  ||       (encoding == "ebcdic-cp-us")
  ||       (encoding == "ebcdic-cp-ca")
  ||       (encoding == "ebcdic-cp-wt")
  ||       (encoding == "ebcdic-cp-nl")
  ||       (encoding == "csIBM037"))
    return new Codec("CP037", 37, codecs::TABLE_CP037);


  // CP437
  else if ((encoding == "CP437")
  ||       (encoding == "IBM437")
  ||       (encoding == "csPC8CodePage437"))
    return new Codec("CP437", 437, codecs::TABLE_CP437);


  // CP500
  else if ((encoding == "CP500")
  ||       (encoding == "IBM500")
  ||       (encoding == "ebcdic-500")
  ||       (encoding == "ebcdic-cp-be")
  ||       (encoding == "ebcdic-cp-ch")
  ||       (encoding == "csIBM500"))
    return new Codec("CP500", 500, codecs::TABLE_CP500);


  // CP737
  else if (encoding == "CP737")
    return new Codec("CP737", 737, codecs::TABLE_CP737);


  // CP775
  else if ((encoding == "CP775")
  ||       (encoding == "IBM775")
  ||       (encoding == "csPC775Baltic"))
    return new Codec("CP775", 775, codecs::TABLE_CP775);


  // CP775
  else if ((encoding == "CP775")
  ||       (encoding == "IBM775")
  ||       (encoding == "csPC775Baltic"))
    return new Codec("CP775", 775, codecs::TABLE_CP775);


  // CP850
  else if ((encoding == "CP850")
  ||       (encoding == "IBM850")
  ||       (encoding == "csPC850Multilingual"))
    return new Codec("CP850", 850, codecs::TABLE_CP850);


  // CP852
  else if ((encoding == "CP852")
  ||       (encoding == "IBM852")
  ||       (encoding == "csPCp852"))
    return new Codec("CP852", 852, codecs::TABLE_CP852);


  // CP855
  else if ((encoding == "CP855")
  ||       (encoding == "IBM855")
  ||       (encoding == "csIBM855"))
    return new Codec("CP855", 855, codecs::TABLE_CP855);


  // CP857
  else if ((encoding == "CP857")
  ||       (encoding == "IBM857")
  ||       (encoding == "csIBM857"))
    return new Codec("CP857", 857, codecs::TABLE_CP857);


  // CP860
  else if ((encoding == "CP860")
  ||       (encoding == "IBM860")
  ||       (encoding == "csIBM860"))
    return new Codec("CP860", 860, codecs::TABLE_CP860);


  // CP861
  else if ((encoding == "CP860")
  ||       (encoding == "IBM860")
  ||       (encoding == "cp-is")
  ||       (encoding == "csIBM860"))
    return new Codec("CP861", 861, codecs::TABLE_CP861);


  // CP862
  else if ((encoding == "CP862")
  ||       (encoding == "IBM862")
  ||       (encoding == "csPC862LatinHebrew"))
    return new Codec("CP862", 862, codecs::TABLE_CP862);


  // CP863
  else if ((encoding == "CP863")
  ||       (encoding == "IBM863")
  ||       (encoding == "csIBM863"))
    return new Codec("CP863", 863, codecs::TABLE_CP863);


  // CP864
  else if ((encoding == "CP864")
  ||       (encoding == "IBM864")
  ||       (encoding == "csIBM864"))
    return new Codec("CP864", 864, codecs::TABLE_CP864);


  // CP866
  else if ((encoding == "CP866")
  ||       (encoding == "IBM866")
  ||       (encoding == "csIBM866"))
    return new Codec("CP866", 866, codecs::TABLE_CP866);


  // CP869
  else if ((encoding == "CP869")
  ||       (encoding == "IBM869")
  ||       (encoding == "cp-gr")
  ||       (encoding == "csIBM869"))
    return new Codec("CP869", 869, codecs::TABLE_CP869);


  // CP874
  else if ((encoding == "CP874")
  ||       (encoding == "windows-874")
  ||       (encoding == "cswindows874"))
    return new Codec("CP874", 874, codecs::TABLE_CP874);


  // CP875
  else if ((encoding == "CP875")
  ||       (encoding == "IBM875")
  ||       (encoding == "ebcdic-875")
  ||       (encoding == "csIBM875"))
    return new Codec("CP875", 875, codecs::TABLE_CP875);


  // CP1026
  else if ((encoding == "CP1026")
  ||       (encoding == "IBM1026")
  ||       (encoding == "csIBM1026"))
    return new Codec("CP1026", 1026, codecs::TABLE_CP1026);


  // CP1250
  else if ((encoding == "CP1250")
  ||       (encoding == "windows-1250")
  ||       (encoding == "cswindows1250"))
    return new Codec("CP1250", 1250, codecs::TABLE_CP1250);


  // CP1251
  else if ((encoding == "CP1251")
  ||       (encoding == "windows-1251")
  ||       (encoding == "cswindows1251"))
    return new Codec("CP1251", 1251, codecs::TABLE_CP1251);


  // CP1252
  else if ((encoding == "CP1252")
  ||       (encoding == "windows-1252")
  ||       (encoding == "cswindows1252"))
    return new Codec("CP1252", 1252, codecs::TABLE_CP1252);


  // CP1253
  else if ((encoding == "CP1253")
  ||       (encoding == "windows-1253")
  ||       (encoding == "cswindows1253"))
    return new Codec("CP1253", 1253, codecs::TABLE_CP1253);


  // CP1254
  else if ((encoding == "CP1254")
  ||       (encoding == "windows-1254")
  ||       (encoding == "cswindows1254"))
    return new Codec("CP1254", 1254, codecs::TABLE_CP1254);


  // CP1255
  else if ((encoding == "CP1255")
  ||       (encoding == "windows-1255")
  ||       (encoding == "cswindows1255"))
    return new Codec("CP1255", 1255, codecs::TABLE_CP1255);


  // CP1256
  else if ((encoding == "CP1256")
  ||       (encoding == "windows-1256")
  ||       (encoding == "cswindows1256"))
    return new Codec("CP1256", 1256, codecs::TABLE_CP1256);


  // CP1257
  else if ((encoding == "CP1257")
  ||       (encoding == "windows-1257")
  ||       (encoding == "cswindows1257"))
    return new Codec("CP1257", 1257, codecs::TABLE_CP1257);


  // CP1258
  else if ((encoding == "CP1258")
  ||       (encoding == "windows-1258")
  ||       (encoding == "cswindows1258"))
    return new Codec("CP1258", 1258, codecs::TABLE_CP1258);


  // Other
  std::ostringstream sstream;
  sstream << "cannot find encoding: " << '"' << encoding << '"';
  throw LookupError(sstream.str().c_str());
}


} // namespace codecs
} // namespace quirinus
