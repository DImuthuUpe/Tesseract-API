package com.apache.pdfbox.ocr.tesseract;

import java.io.File;
import com.wapmx.nativeutils.jniloader.NativeLoader;

public class TessBaseAPI {
	private int mNativeData;
	private static TessBaseAPI api = null;
	static {
		try {
			NativeLoader.loadLibrary("tessbaseapi");
			nativeClassInit();
		} catch (Throwable e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	
	//Singleton design pattern applied
	//Creating several instances of TessBaseAPI leads to memory crash.
	//Class can get access to NativeLoader.loadLibrary("tessbaseapi"); if there is another instance of TessBaseAPI
	public static TessBaseAPI getInstance() {
		if (api == null) {
			api = new TessBaseAPI();
		}
		return api;
	}

	private TessBaseAPI() {
		nativeConstruct();
	}

	public boolean init(String dataPath, String lang) {
		boolean init = nativeInit(dataPath, lang);
		return init;
	}

	public void setImagePath(String path) {
		nativeSetImagePath(path);
	}

	public String getUTF8Text() {
		return nativeGetUTF8Text();
	}

	public void getResultIterator() {
		nativeGetResultIterator();
	}

	public void end() {
		nativeEnd();
	}

	public boolean resultIteratorNext() {
		return nativeResultIteratorNext();
	}

	public boolean isResultIteratorAvailable() {
		return nativeIsResultIteratorAvailable();
	}

	public String getWord() {
		return nativeGetWord();
	}

	public String getBoundingBox() {
		return nativeGetBoundingBox();
	}

	// ******************
	// * Native methods *
	// ******************

	/**
	 * Initializes static native data. Must be called on object load.
	 */
	private static native void nativeClassInit();

	/**
	 * Initializes native data. Must be called on object construction.
	 */
	private native void nativeConstruct();

	/**
	 * Finalizes native data. Must be called on object destruction.
	 */
	private native void nativeFinalize();

	private native boolean nativeInit(String datapath, String language);

	private native void nativeClear();

	private native void nativeEnd();

	private native void nativeSetImageBytes(byte[] imagedata, int width,
			int height, int bpp, int bpl);

	private native void nativeSetImagePath(String path);

	private native void nativeSetImagePix(int nativePix);

	private native void nativeSetRectangle(int left, int top, int width,
			int height);

	private native String nativeGetUTF8Text();

	private native int nativeGetRegions();

	private native int nativeGetWords();

	private native int nativeMeanConfidence();

	private native int[] nativeWordConfidences();

	private native boolean nativeSetVariable(String var, String value);

	private native void nativeSetDebug(boolean debug);

	private native void nativeSetPageSegMode(int mode);

	private native int nativeGetResultIterator();

	private native boolean nativeResultIteratorNext();

	private native boolean nativeIsResultIteratorAvailable();

	private native String nativeGetWord();

	private native String nativeGetBoundingBox();

}
