package com.apache.pdfbox.ocr.tesseract;

import java.io.File;
import com.wapmx.nativeutils.jniloader.NativeLoader;

public class TessBaseAPI {
    

    static {
        //System.loadLibrary("tessbaseapi");
        //System.loadLibrary("tesseract");
		//nativeClassInit();
		try {
            NativeLoader.loadLibrary("tessbaseapi");
        } catch (Throwable e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
    
    //public static void main(String a[]){
    	//TessBaseAPI api = new TessBaseAPI();
    //	System.out.println("jbkb");
    //}

	public boolean init(String dataPath,String lang){
		boolean init =nativeInit("","");	
		return init;
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

    private native void nativeSetImageBytes(
            byte[] imagedata, int width, int height, int bpp, int bpl);

    private native void nativeSetImagePix(int nativePix);

    private native void nativeSetRectangle(int left, int top, int width, int height);

    private native String nativeGetUTF8Text();

    private native int nativeGetRegions();

    private native int nativeGetWords();

    private native int nativeMeanConfidence();

    private native int[] nativeWordConfidences();

    private native boolean nativeSetVariable(String var, String value);

    private native void nativeSetDebug(boolean debug);

    private native void nativeSetPageSegMode(int mode);

    private native int nativeGetResultIterator();

}
