#include <stdio.h>
#include <stdlib.h>
//#include "android/bitmap.h"
//#include "common.h"
#include "baseapi.h"
#include "allheaders.h"
#include <iostream>
#include <fstream> 
#include "jni.h"


#ifdef __cplusplus
extern "C" {
#endif

void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeClassInit
  (JNIEnv *, jclass){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeConstruct
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeConstruct
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeFinalize
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeFinalize
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeInit
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeInit
  (JNIEnv *, jobject, jstring, jstring){
  return true;
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeClear
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeClear
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeEnd
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeEnd
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetImageBytes
 * Signature: ([BIIII)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetImageBytes
  (JNIEnv *, jobject, jbyteArray, jint, jint, jint, jint){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetImagePix
 * Signature: (I)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetImagePix
  (JNIEnv *, jobject, jint){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetRectangle
 * Signature: (IIII)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetRectangle
  (JNIEnv *, jobject, jint, jint, jint, jint){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetUTF8Text
 * Signature: ()Ljava/lang/String;
 */
jstring JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetUTF8Text
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetRegions
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetRegions
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetWords
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetWords
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeMeanConfidence
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeMeanConfidence
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeWordConfidences
 * Signature: ()[I
 */
jintArray JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeWordConfidences
  (JNIEnv *, jobject){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetVariable
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetVariable
  (JNIEnv *, jobject, jstring, jstring){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetDebug
 * Signature: (Z)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetDebug
  (JNIEnv *, jobject, jboolean){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetPageSegMode
 * Signature: (I)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetPageSegMode
  (JNIEnv *, jobject, jint){
  }

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetResultIterator
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetResultIterator
  (JNIEnv *, jobject){
  }

#ifdef __cplusplus
}
#endif
