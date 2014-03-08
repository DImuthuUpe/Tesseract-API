package com.apache.pdfbox.ocr.tesseract;


import com.apache.pdfbox.ocr.tesseract.TessBaseAPI;
import junit.framework.TestCase;


public class TessBaseAPITest extends TestCase {
	public void testInit(){
		TessBaseAPI api =new TessBaseAPI();
		boolean init =api.init("","");
		assertEquals(false, init);
	}

}
