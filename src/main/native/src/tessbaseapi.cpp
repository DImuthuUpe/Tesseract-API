#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "android/bitmap.h"
//#include "common.h"
#include "baseapi.h"
#include "allheaders.h"
#include <iostream>
#include <fstream> 
#include "jni.h"
#include "com_apache_pdfbox_ocr_tesseract_TessBaseAPI.h"

static jfieldID field_mNativeData;

struct native_data_t {
	tesseract::TessBaseAPI *api;
	tesseract::ResultIterator* ri;
	native_data_t() {
		api = new tesseract::TessBaseAPI();
	}
};

static inline native_data_t * get_native_data(JNIEnv *env, jobject object) {
	return (native_data_t *) (env->GetLongField(object, field_mNativeData)); //converted for 64 bit architecture
}

#ifdef __cplusplus
extern "C" {
#endif

void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeClassInit
(JNIEnv *env, jclass clazz) {

	//printf("------------Native Class Init----------------\n");
	field_mNativeData = env->GetFieldID(clazz, "mNativeData", "J");
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeConstruct
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeConstruct
(JNIEnv * env, jobject object) {
	//printf("------------Construct----------------\n");
	native_data_t *nat = new native_data_t;

	if (nat == NULL) {
		//LOGE("%s: out of memory!", __FUNCTION__);
		//printf("-----------Out of memory--------%s",__FUNCTION__);
		return;
	}

	//printf("pointer %d",nat);
	jlong pt = (jlong)(unsigned long long)nat;
	env->SetLongField(object, field_mNativeData, pt); // converted to 64 bit architecture
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeFinalize
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeFinalize
(JNIEnv *env, jobject thiz) {
	native_data_t *nat = get_native_data(env, thiz);
	if(nat->api!=NULL){
		delete nat->api;
	}
	if (nat != NULL)
	    delete nat;
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeInit
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeInit(
		JNIEnv *env, jobject thiz, jstring dir, jstring lang) {

	//printf("------------Init----------------\n");
	native_data_t *nat = get_native_data(env, thiz);

	const char *c_dir = env->GetStringUTFChars(dir, NULL);
	const char *c_lang = env->GetStringUTFChars(lang, NULL);
	jboolean res = JNI_TRUE;

	if (nat->api->Init(c_dir, c_lang)) {
		res = JNI_FALSE;
	} else {
	}

	env->ReleaseStringUTFChars(dir, c_dir);
	env->ReleaseStringUTFChars(lang, c_lang);

	return res;
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeClear
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeClear
(JNIEnv *, jobject) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeEnd
 * Signature: ()V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeEnd
(JNIEnv *env, jobject thiz) {
	native_data_t *nat = get_native_data(env, thiz);
	nat->api->End();
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetImageBytes
 * Signature: ([BIIII)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetImageBytes
(JNIEnv *env, jobject thiz, jbyteArray data, jint width, jint height, jint bpp, jint bpl) {
	jbyte *data_array = env->GetByteArrayElements(data, NULL);
	int count = env->GetArrayLength(data);
	unsigned char* imagedata = (unsigned char *) malloc(count * sizeof(unsigned char));

	// This is painfully slow, but necessary because we don't know
	// how many bits the JVM might be using to represent a byte
	for (int i = 0; i < count; i++) {
		imagedata[i] = (unsigned char) data_array[i];
	}

	env->ReleaseByteArrayElements(data, data_array, JNI_ABORT);

	native_data_t *nat = get_native_data(env, thiz);
	nat->api->SetImage(imagedata, (int) width, (int) height, (int) bpp, (int) bpl);
}

void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetImagePath
(JNIEnv *env, jobject thiz, jstring path) {
	native_data_t *nat = get_native_data(env, thiz);
	const char *c_path = env->GetStringUTFChars(path, NULL);
	Pix *image =pixRead(c_path);
	nat->api->SetImage(image);
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetImagePix
 * Signature: (I)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetImagePix
(JNIEnv *, jobject, jint) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetRectangle
 * Signature: (IIII)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetRectangle
(JNIEnv *, jobject, jint, jint, jint, jint) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetUTF8Text
 * Signature: ()Ljava/lang/String;
 */
jstring JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetUTF8Text(
		JNIEnv *env, jobject thiz) {
	native_data_t *nat = get_native_data(env, thiz);
	char *text = nat->api->GetUTF8Text();
	jstring result = env->NewStringUTF(text);

	free(text);
	//printf("OCR output:\n%s", text);

	return result;
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetRegions
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetRegions(
		JNIEnv *, jobject) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetWords
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetWords(
		JNIEnv *, jobject) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeMeanConfidence
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeMeanConfidence(
		JNIEnv *, jobject) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeWordConfidences
 * Signature: ()[I
 */
jintArray JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeWordConfidences(
		JNIEnv *, jobject) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetVariable
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Z
 */
jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetVariable(
		JNIEnv *, jobject, jstring, jstring) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetDebug
 * Signature: (Z)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetDebug
(JNIEnv *, jobject, jboolean) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeSetPageSegMode
 * Signature: (I)V
 */
void JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeSetPageSegMode
(JNIEnv *, jobject, jint) {
}

/*
 * Class:     com_apache_pdfbox_ocr_tesseract_TessBaseAPI
 * Method:    nativeGetResultIterator
 * Signature: ()I
 */
jint JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetResultIterator(
		JNIEnv *env, jobject thiz) {
	native_data_t *nat = get_native_data(env, thiz);
	nat->api->Recognize(0);
	nat->ri = nat->api->GetIterator();

}

jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeResultIteratorNext(
		JNIEnv *env, jobject thiz, jint mode) {
	native_data_t *nat = get_native_data(env, thiz);
	tesseract::PageIteratorLevel level;
	if(mode==0){
	   level = tesseract::RIL_SYMBOL;//RIL_WORD,RIL_TEXTLINE,RIL_PARA,RIL_BLOCK
	}else if(mode ==1){
	    level = tesseract::RIL_WORD;
	}
	if (nat->ri->Next(level)) {
		return true;
	} else {
		return false;
	}
}

jboolean JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeIsResultIteratorAvailable(
		JNIEnv *env, jobject thiz, jint mode) {
	native_data_t *nat = get_native_data(env, thiz);
	tesseract::PageIteratorLevel level;
    if(mode==0){
        level = tesseract::RIL_SYMBOL;
    }else if(mode ==1){
        level = tesseract::RIL_WORD;
    }
	if (nat->ri != 0) {
		return true;
	} else {
		return false;
	}
}

jstring JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetWord(
		JNIEnv *env, jobject thiz, jint mode) {
	native_data_t *nat = get_native_data(env, thiz);
	tesseract::PageIteratorLevel level;
    if(mode==0){
        level = tesseract::RIL_SYMBOL;
    }else if(mode ==1){
        level = tesseract::RIL_WORD;
    }
	if (nat->ri != 0) {
		const char* word = nat->ri->GetUTF8Text(level);
		jstring result = env->NewStringUTF(word);
		//free(word);
		return result;
	}
}

jstring JNICALL Java_com_apache_pdfbox_ocr_tesseract_TessBaseAPI_nativeGetBoundingBox(
		JNIEnv *env, jobject thiz, jint mode) {
	native_data_t *nat = get_native_data(env, thiz);
	tesseract::PageIteratorLevel level;
    if(mode==0){
        level = tesseract::RIL_SYMBOL;
    }else if(mode ==1){
        level = tesseract::RIL_WORD;
    }
	if (nat->ri != 0) {
		int x1, y1, x2, y2;
		nat->ri->BoundingBox(level, &x1, &y1, &x2, &y2);

		char stringBuffer[20];
		char* cx1;
		char* cy1;
		char* cx2;
		char* cy2;
		char* seperator = ",";

		snprintf(stringBuffer, 20, "%d", x1);
		cx1 = strdup(stringBuffer);

		snprintf(stringBuffer, 20, "%d", y1);
		cy1 = strdup(stringBuffer);

		snprintf(stringBuffer, 20, "%d", x2);
		cx2 = strdup(stringBuffer);

		snprintf(stringBuffer, 20, "%d", y2);
		cy2 = strdup(stringBuffer);

		char str[40];
		strcpy(str, cx1);
		strcat(str, seperator);
		strcat(str, cy1);
		strcat(str, seperator);
		strcat(str, cx2);
		strcat(str, seperator);
		strcat(str, cy2);

		char* str2;
		str2 = strdup(str);
		jstring result = env->NewStringUTF(str2);
		return result;
	}
}

#ifdef __cplusplus
}
#endif
